/*

 * Copyright (c) 2003 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
//
//  CSV -> CSV Soket
//


#include "csv2csv.h"

// # State Machine Ver 1.01 ###################################
// -----------------
// moving status
// -----------------
void csvOutState_T::Output_sub(FILE *fp,StIf_T *stif,int nest){
  if (stif->if_kbn == 0){
	fprintf(fp,"#if,%s,%d,%s,%d\n",stif->str->c_str(),stif->next_else,stif->clm_msg->c_str(),nest);
  }
  else if (stif->if_kbn == 1){
	fprintf(fp,"#elseif,%s,%d,%s,%d\n",stif->str->c_str(),stif->next_else,stif->clm_msg->c_str(),nest);
  }
  else if (stif->if_kbn == 2){
	fprintf(fp,"#else,%s,%d\n",stif->clm_msg->c_str(),nest);
  }

  Output_link(fp,stif,nest);

  if (stif->next_else == false){
	fprintf(fp,"#endif,%s,%d\n",stif->clm_msg->c_str(),nest);
  }
}

void csvOutState_T::Output_link(FILE *fp,StIf_T *stif,int nest){
  LinkCell_T *link;
  MEM_LOOP(link,LinkCell_T,stif->link_fp)
	if (link->kbn == StCmdKbn){
	  sChar *w = (sChar *)link->ptr;
	  ex_str->DblIns(w->c_str());
	  fprintf(fp,"#cmd,%s,%s\n",ex_str->c_str(),link->clm_msg->c_str());
	}
	else if (link->kbn == StIfKbn){
	  StIf_T *w = (StIf_T *)link->ptr;
	  Output_sub(fp,w,nest+1);
	}
	else if (link->kbn == StChgKbn){
	  Chg_T *w = (Chg_T *)link->ptr;
	  fprintf(fp,"#chg_clk,%s\n"
	  ,w->clk->c_str());
	  ValChg_T *vc;
	  MEM_LOOP(vc,ValChg_T,w->val_fp)
		ex_str->DblIns(vc->val->c_str());
		fprintf(fp,"#chg,%s,%s,%s\n",vc->name->c_str(),vc->cyc->c_str(),ex_str->c_str());
	  LOOP_END
	}
	else if (link->kbn == StActKbn){
	  sChar *w = (sChar *)link->ptr;
	  fprintf(fp,"#act,%s,%s\n",w->c_str(),link->clm_msg->c_str());
	}
	else if (link->kbn == StStopKbn){
	  sChar *w = (sChar *)link->ptr;
	  fprintf(fp,"#stop,%s,%s\n",w->c_str(),link->clm_msg->c_str());
	}
	else if (link->kbn == StExecKbn){
	  sChar *w = (sChar *)link->ptr;
	  fprintf(fp,"#go,%s,%s\n",w->c_str(),link->clm_msg->c_str());
	}
  LOOP_END
}

void csvOutState_T::Output(FILE *fp){
  Status_T *s;
  StIf_T   *stif;
  StParm_T *p;

  if (strcmp(chg_trap->c_str(),"")!=0) {
	fprintf(fp,"#chgtrap,%s\n", chg_trap->c_str());
  }
  fprintf(fp,"#chgmax,%s\n",ary_max->c_str());

  MEM_LOOP(s,Status_T,status_fp)
    fprintf(fp,"#status,%s,%s,%s\n"
	,s->name->c_str()
	,s->clk->c_str()
	,s->clm_msg->c_str());

    // local variable
    MEM_LOOP(p,StParm_T,s->local_fp)
      fprintf(fp,"#local,%s,%s,%s\n",p->name->c_str(),p->size->c_str(),p->clm_msg->c_str());
    LOOP_END
	// parameter variable
    MEM_LOOP(p,StParm_T,g_status->parm_fp)
      fprintf(fp,"#parm,%s,%s,%s\n",p->name->c_str(),p->size->c_str(),p->clm_msg->c_str());
    LOOP_END

    MEM_LOOP(stif,StIf_T,s->st_sub_fp)
      fprintf(fp,"#st,%s,%d,%s\n"
	  ,stif->str->c_str()
      ,stif->no
      ,stif->clm_msg->c_str());

      Output_link(fp,stif,0);

    LOOP_END
  LOOP_END
}

// # RTL State Machine ###############################
// ----------------------
// Port define Ouput
// ----------------------
bool csvOutRState_T::PortOutput(FILE *fp,int kbn,char *var_name){
  char   *name;
  char   *size;
  Reg_T  *reg;
  Wire_T *wire;
  char   *clm;
  char    kind[5];

  it->srch_key = var_name;
  for(;;){
    if (reg_fp->mem_srch() == 0){
      reg = (Reg_T *)reg_fp->mem_link_ptr_rd();
      name = reg->name->c_str();
      size = reg->size->c_str();
      clm  = reg->clm_msg->c_str();
      strcpy(kind,"reg");
      break;
    }
    if (wire_fp->mem_srch() == 0){
      wire = (Wire_T *)wire_fp->mem_link_ptr_rd();
      name = wire->name->c_str();
      size = wire->size->c_str();
      clm  = wire->clm_msg->c_str();
      wire->defined_flg = true;
      strcpy(kind,"wire");
      break;
    }
    return(false);
  }


  if (kbn == 0){fprintf(fp,"#signal,in,");}
  if (kbn == 1){fprintf(fp,"#signal,out,");}
  if (kbn == 2){fprintf(fp,"#signal,io,");}
  fprintf(fp,"%s,%s,%s,%s\n",kind,name,size,clm);
  return(true);
}


// ----------------------
// Variable define Ouput
// ----------------------
void csvOutRState_T::PreOutput(FILE *fp,MEM_FP *add_fp){
  int i;
  char *ww;
  Reg_T *reg;
  Wire_T *wire;

  // register define
  MEM_LOOP(reg,Reg_T,reg_fp)
    if (reg->defined_flg == true){continue;}
    reg->defined_flg = true;
    fprintf(fp,"#signal,inner,reg,");
    if (*reg->name->c_str() == '?'){fprintf(fp,"%s",reg->name->c_str()+1);}
    else                           {fprintf(fp,"%s",reg->name->c_str()  );}
    fprintf(fp,",%s,%s,%s\n",reg->size->c_str(),reg->clm_msg->c_str(),reg->idx->c_str());
  LOOP_END

  // wire define
  MEM_LOOP(wire,Wire_T,wire_fp)
    if (wire->defined_flg == true){continue;}
    wire->defined_flg = true;
    fprintf(fp,"#signal,inner");
    it->srch_key = wire->name->c_str();
    if (add_fp->mem_srch() == 0){
      VOutAdding_T *aaa = (VOutAdding_T *)add_fp->mem_link_ptr_rd();
      fprintf(fp,",%s",aaa->val->c_str());
    }
    else{
      fprintf(fp,",wire");
    }
    fprintf(fp,",%s,%s,%s\n",wire->name->c_str(),wire->size->c_str(),wire->clm_msg->c_str());
  LOOP_END
  }


// -----------------
// Register Output
// -----------------
void csvOutRState_T::reg_output(FILE *fp,Reg_T *reg){
  Siki_T *siki;
  char *ww;
  bool first;


  // Ver 1.01  ðŒŽ®‚ª‚È‚¢siki‚ÍÅŒã‚É’Ç‰Á‚·‚é
  MEM_LOOP(siki,Siki_T,reg->body_fp)
    if (strcmp(siki->siki->c_str(),"") != 0){continue;}
    reg->body_fp->mem_del();
    it->alloc_ptr = siki;
    reg->body_fp->mem_alloc();
  LOOP_END

  if (reg->use_flg == true){return;}
  if (strcmp(reg->clk->c_str(),"") == 0){return;}
  reg->use_flg = true;

  fprintf(fp,"#always_begin");
  if (*reg->name->c_str() == '?') {fprintf(fp,",%s",reg->name->c_str()+1);}
  else                            {fprintf(fp,",%s",reg->name->c_str());}

  ww = reg->clk->c_str();
  if ((*ww == '~') || (*ww == '!')){fprintf(fp,",neg,%s\n",ww+1);}
  else                             {fprintf(fp,",pos,%s\n",ww);}

  MEM_LOOP(siki,Siki_T,reg->body_fp)
    if (siki->sync == true){continue;}
    ww = siki->siki->c_str();
    if ((*ww == '~') || (*ww == '!')){fprintf(fp,"#async_reset,neg,%s\n",ww+1);}
    else                             {fprintf(fp,"#async_reset,pos,%s\n",ww);}
  LOOP_END

  if (*reg->name->c_str() == '?'){
    for(int mode=0;mode<3;++mode){
      MEM_LOOP(siki,Siki_T,reg->body_fp)
        hex_change(siki->val);
        add_read(siki->siki);

        if (mode == 0){
          if (!siki->reset){continue;}
        }
        if (mode == 1){
          if (siki->reset){continue;}
          if (strcmp(siki->val->c_str(),"1'b0") == 0){continue;}
        }
        if (mode == 2){
          if (siki->reset){continue;}
          if (strcmp(siki->val->c_str(),"1'b1") == 0){continue;}
        }
        fprintf(fp,"#reg_logic,%s,%s,%s,%s\n",siki->siki->c_str(),siki->val->c_str(),siki->clm_msg->c_str(),siki->idx->c_str());
      LOOP_END
      }
    }
  else {
    MEM_LOOP(siki,Siki_T,reg->body_fp)
      hex_change(siki->val);
      add_read(siki->siki);
      fprintf(fp,"#reg_logic,%s,%s,%s,%s\n",siki->siki->c_str(),siki->val->c_str(),siki->clm_msg->c_str(),siki->idx->c_str());
    LOOP_END
  }
  fprintf(fp,"#always_end\n");

}

// -----------------
// .read add
// -----------------
void csvOutRState_T::add_read(sChar *s_str){
  Wire_T *wire;
  MEM_LOOP(wire,Wire_T,wire_fp)
    if (strcmp(wire->name->c_str(),s_str->c_str()) == 0){
      s_str->cat(".read()");
    }
  LOOP_END
}


// -----------------
// reg change
// -----------------
void csvOutRState_T::reg_change(sChar *s_str){
  Reg_T *reg;
  sChar *srch = new sChar("");
  sChar *rep  = new sChar("");

  sCharGrep *grep = new sCharGrep(s_str->c_str());
  MEM_LOOP(reg,Reg_T,reg_fp)
    if (*(reg->name->c_str()) != '?'){continue;}

    srch->set("(");
    srch->cat(reg->name->c_str()+1);
    srch->cat(")");
    rep->set("(");
    rep->cat(reg->name->c_str()+1);
    rep->cat(".read())");

    grep->replace_all(srch->c_str(),rep->c_str());

    
//    printf("reg_change srch:%s rep:%s  %s\n",srch->c_str(),rep->c_str(),grep->c_str());


  LOOP_END
  s_str->set(grep->c_str());

  delete grep;
  delete srch;
  delete rep;
}

// -----------------
// invert change
// -----------------
void csvOutRState_T::inv_change(sChar *s_str){
  sCharGrep *grep = new sCharGrep(s_str->c_str());
  grep->replace_all("~(","!(");
  s_str->set(grep->c_str());
  delete grep;
}


// -----------------
// nnn'haa -> 0xaa
// -----------------
void csvOutRState_T::hex_change(sChar *s_str){
  char  *str    = s_str->c_str();
  int    len    = strlen(str);
  char  *w_buff = new char[len+1];
  int   *w_int  = new int [len+1];
  int    w_int_ptr = 0;

  int start_posi = 0;
  int state = -1;  // 0:space 1:not space -1:first space
  for(int i=0;i<len;i++){
    char w  = *(str+i);
    char w2 = *(str+i+1);
    if (state == -1){
      if (w != 0x20){state=1; start_posi=i;}
    }
    else if (state == 0){
      if (w != 0x20){state=1; start_posi=i;}
    }
    else if (state == 1){
      if (w == 0x20){state=0;}
    }
    if ((w == '\'') && (w2 == 'h')){
      *(str+i) = '@';
      *(str+i+1) = '@';
      int ptr=0;
      for(int k=start_posi;k<i;k++){
        w_buff[ptr++] = *(str+k);
        *(str+k) = ' ';
      }
      w_buff[ptr] = 0x00;
      w_int[w_int_ptr++] = SujiConvEx(w_buff);
    }
  }

  if (w_int_ptr > 0){
    int offset = 0;
    sCharGrep *grep = new sCharGrep(s_str->c_str());
    for(int i=0;i<w_int_ptr;i++){
      if (w_int[i] < 64){
        sprintf(w_buff,"(sc_uint<%d>)0x",w_int[i]);
      }
      else {
        sprintf(w_buff,"(sc_biguint<%d>)0x",w_int[i]);
      }

      offset = grep->replace("@@",w_buff,offset);
    }
    s_str->set(grep->c_str());
    delete grep;
  }


  delete [] w_buff;
  delete [] w_int;
}




// -----------------
// Main Ouput
// -----------------
void csvOutRState_T::Output(FILE *fp,MEM_FP *add_fp){
  Reg_T *reg;
  Wire_T *wire;
  sCharGrep *grep = new sCharGrep("");

  MEM_LOOP(wire,Wire_T,wire_fp)
    if (strcmp(wire->val->c_str(),"")==0){continue;}

    hex_change(wire->val);
    inv_change(wire->val);
    reg_change(wire->val);

    it->srch_key = wire->name->c_str();
    fprintf(fp,"#wire_logic");
    fprintf(fp,",%s,%s,%s",wire->name->c_str(),wire->val->c_str(),wire->clm_msg->c_str());
    if (add_fp->mem_srch() == 0){
      VOutAdding_T *aaa = (VOutAdding_T *)add_fp->mem_link_ptr_rd();
      fprintf(fp,",%s",aaa->val->c_str());
    }
    fprintf(fp,"\n");
    wire_anl->exec(wire->val->c_str());

    fprintf(fp,"#sensibility");
    for(int i=0;;i++){
      char *w = wire_anl->get(i);
      if (w == NULL){break;}
      grep->set(w);
      grep->replace_all(".read","");

      fprintf(fp,",%s",grep->c_str());

    }
    fprintf(fp,"\n");

  LOOP_END
  MEM_LOOP(reg,Reg_T,reg_fp)
    reg_output(fp,reg);
  LOOP_END

  delete grep;
}


// # RTL Connection ##################################
// ------------------
// Port define
// ------------------
bool csvOutCon_T::PortOutput(FILE *fp,int kbn,char *var_name)
  {
  ConWire_T *wire;

  it->srch_key = var_name;
  if (wire_def_fp->mem_srch() != 0){return(false);}
  wire = (ConWire_T *)wire_def_fp->mem_link_ptr_rd();
  wire->defined_flg = true;
  if (kbn == 0){fprintf(fp,"#signal,in,");}
  if (kbn == 1){fprintf(fp,"#signal,out,");}
  if (kbn == 2){fprintf(fp,"#signal,io,");}
  fprintf(fp,"wire,%s,%d,%s\n",wire->name->c_str(),wire->size,wire->clm_msg->c_str());
  return(true);
  }


// ------------------
// Varriable define
// ------------------
void csvOutCon_T::PreOutput(FILE *fp,MEM_FP *add_fp){
  ConWire_T *wire;
  MEM_LOOP(wire,ConWire_T,wire_def_fp)
    if (wire->defined_flg == true){continue;}
    wire->defined_flg = true;
    it->srch_key = wire->name->c_str();
    fprintf(fp,"#signal,inner,wire,%s,%d,%s",wire->name->c_str(),wire->size,wire->clm_msg->c_str());
    if (add_fp->mem_srch() == 0){
      VOutAdding_T *aaa = (VOutAdding_T *)add_fp->mem_link_ptr_rd();
      fprintf(fp,",%s",aaa->val->c_str());
    }
    fprintf(fp,"\n");

  LOOP_END
}


// ------------------
// output 
// ------------------
void csvOutCon_T::Output(FILE *out_fp){
  Inst_T     *inst;
  Con_T      *con;
  int         i;
  int         first;
  sChar      *ww;

  ww = new sChar("");
  MEM_LOOP(inst,Inst_T,inst_fp)
    fprintf(out_fp,"#instance,%s,%s\n",inst->mod_name->c_str(),inst->inst_name->c_str());
    MEM_LOOP(con,Con_T,inst->con_fp)
      fprintf(out_fp,"#connect,%s,%s,%s\n",con->port_name->c_str(),con->wire_name->c_str(),con->clm_msg->c_str());
    LOOP_END
  LOOP_END
  delete ww;

  }

