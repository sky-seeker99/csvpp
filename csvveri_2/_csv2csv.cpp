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
//  CSV -> CSV
//



// TOP Class -----------------
class csvOutTop_T {
  private:
  MemHeader_T  *it;

  Msg_T        *msg;
  CsvAnl_C     *csvi;
  FILE         *fp;
  Read64_C     *file_fp;

  csvOutRState_T *v_rstate; // Adding
  csvOutState_T  *v_state;
  csvOutCon_T    *v_con;
  MEM_FP       *in_fp;
  MEM_FP       *out_fp;
  MEM_FP       *io_fp;

  MEM_FP       *add_wire_fp;
  MEM_FP       *add_delay_fp;

  public:
  void main();
  void output();



  csvOutTop_T(char *csv_file,char *v_file){
    csvi     = new CsvAnl_C();
    it       = new MemHeader_T;
    in_fp    = new MEM_FP(it);
    out_fp   = new MEM_FP(it);
    io_fp    = new MEM_FP(it);

    add_wire_fp  = new MEM_FP(it);
    add_delay_fp = new MEM_FP(it);

    msg     = new Msg_T();
    v_state = new csvOutState_T (it,msg); // Add
    v_rstate= new csvOutRState_T(it,msg); // Add
    v_con   = new csvOutCon_T   (it,msg);

    fp       = fopen(v_file,"wt");
    if (fp == NULL){printf("open error.(file=%s)\n",v_file);}

    file_fp = new Read64_C(csv_file,"rt",10240);
    csvi->setFileName(csv_file);

    if (file_fp->okCheck() == false){
      printf("open error.(file = %s)\n",csv_file);
      return;
    }
    printf("%s->%s convert complete.\n",csv_file,v_file);
  }

  ~csvOutTop_T(){
    sChar *str;
    VOutPara_T *p;
    VOutAdding_T *aaa;

    delete it;
    delete csvi;
    delete file_fp;
    MEM_LOOP(str,sChar,in_fp     ) delete str; LOOP_END
    MEM_LOOP(str,sChar,out_fp    ) delete str; LOOP_END
    MEM_LOOP(str,sChar,io_fp     ) delete str; LOOP_END
    MEM_LOOP(aaa  ,VOutAdding_T,add_delay_fp) delete aaa;   LOOP_END
    MEM_LOOP(aaa  ,VOutAdding_T,add_wire_fp ) delete aaa;   LOOP_END

    delete in_fp;
    delete out_fp;
    delete io_fp;
    delete add_delay_fp;
    delete add_wire_fp;
    if (fp != NULL){fclose(fp);}
  }
  void port_rtn  (CsvAnl_C *csvi,MEM_FP *mem_fp);
  void delay_rtn (CsvAnl_C *csvi,bool flg);

};


// # output #####
void csvOutTop_T::output(){
  VOutAdding_T *aaa;
  MEM_FP *mem_fp;
  sChar *sstr;
  if (fp == NULL){return;}
  for(int i=0;i<3;++i){
    if (i==0){mem_fp = in_fp; }
    if (i==1){mem_fp = out_fp;}
    if (i==2){mem_fp = io_fp; }
    MEM_LOOP(sstr,sChar,mem_fp)
      if (v_rstate->PortOutput(fp,i,sstr->c_str())){continue;}
      if (v_con->PortOutput   (fp,i,sstr->c_str())){continue;}
      fprintf(fp,"#undefine,%s\n",sstr->c_str());
    LOOP_END
  }


  char buff[255];
  ConWire_T *c_wire;
  Wire_T *wire;
  MEM_LOOP(wire,Wire_T,v_rstate->wire_fp)
    v_con->it->srch_key = wire->name->c_str();
    if (v_con->wire_def_fp->mem_srch() != 0) {continue;}
    c_wire = (ConWire_T *)v_con->wire_def_fp->mem_link_ptr_rd();
    sprintf(buff,"%d",c_wire->size);
    if (strcmp(buff,wire->size->c_str()) == 0){
      c_wire->defined_flg = true;
    }
    else{
      sprintf(buff," net=%s",v_con->it->srch_key);
      msg->ErrMsg(E008,"#con",buff);
    }
  LOOP_END
  v_con->complete_rtn(  );
  v_rstate->CsvPost  (  );
  v_rstate->PreOutput(fp,add_wire_fp);
  v_con->PreOutput   (fp,add_wire_fp);

  v_rstate->Output   (fp,add_delay_fp);
  v_con->Output      (fp);
  v_state->Output    (fp);


  delete v_state; // 2013.8.17
  delete v_rstate;
  delete v_con;
  delete msg;
  MEM_LOOP(sstr,sChar,in_fp ) delete sstr; LOOP_END
  MEM_LOOP(sstr,sChar,out_fp) delete sstr; LOOP_END
  MEM_LOOP(sstr,sChar,io_fp ) delete sstr; LOOP_END
  MEM_LOOP(aaa  ,VOutAdding_T,add_delay_fp) delete aaa;   LOOP_END
  MEM_LOOP(aaa  ,VOutAdding_T,add_wire_fp ) delete aaa;   LOOP_END

  in_fp->mem_del_all();
  out_fp->mem_del_all();
  io_fp->mem_del_all();
  add_wire_fp->mem_del_all();
  add_delay_fp->mem_del_all();
  }

// # Main Loop #####
void csvOutTop_T::main(){
  char *str;
  int   i;
  bool non_flg;

  csvi->initLineNum();
  TEXT_READ_LOOP(file_fp,buff)
    csvi->Exec(buff);
    csvi->plusLineNum();
    if ((str = csvi->CsvSel_Rd(0)) == MM_NULL) {continue;}
    if (strcmp(str,"#input"     ) == 0){port_rtn (csvi,in_fp );  continue;}
    if (strcmp(str,"#output"    ) == 0){port_rtn (csvi,out_fp); continue;}
    if (strcmp(str,"#inout"     ) == 0){port_rtn (csvi,io_fp );  continue;}
    if (strcmp(str,"#delay"     ) == 0){delay_rtn(csvi,true  );  continue;}
    if (strcmp(str,"#wire_attr" ) == 0){delay_rtn(csvi,false );  continue;}
    if (v_rstate->CsvRead(csvi) == true){continue;}
    if (v_state->CsvRead (csvi) == true){continue;}
    if (v_con->CsvRead   (csvi) == true){continue;}
    // msg->ErrMsg(csvi,E000,0);
  }
}

// ----------------------
// #input/#output/#inout
// ----------------------
void csvOutTop_T::port_rtn(CsvAnl_C *csvi,MEM_FP *mem_fp){
  int i;
  char *str;

  for(i=1;i<csvi->CsvSelSu_Rd();++i){
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    it->alloc_ptr = (MM_PTR_T *)new sChar(str);
    mem_fp->mem_alloc();
  }
}


// ----------------------
// #delay / #wire_attr
// ----------------------
void csvOutTop_T::delay_rtn(CsvAnl_C *csvi,bool flg){
  int i;
  char *str;
  char *name;
  sChar *sstr;
  MEM_FP *mem_fp;
  VOutAdding_T *aa;

  sstr = new sChar("");
  name = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    if (name == NULL){name = str; continue;}
    sstr->cat(str);
    }
  if (flg){mem_fp = add_delay_fp;}
  else    {mem_fp = add_wire_fp;}

  it->srch_key = name;
  if (mem_fp->mem_srch() == 0)
    {
    aa = (VOutAdding_T *)mem_fp->mem_link_ptr_rd();
    aa->val->set(sstr->c_str());
    }
  else
    {
    it->alloc_ptr = (MM_PTR_T *)new VOutAdding_T(name,sstr->c_str());
    mem_fp->mem_srch_alloc();
    }
    
  delete sstr;
}
