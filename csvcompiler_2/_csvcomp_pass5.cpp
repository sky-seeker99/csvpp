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
//  CSV COMPILER PASS5(file output)
//
//  Ver 1.01 : #irq_st add
//

// ---------------
// Pass 5 Main
// ---------------
bool Inf_T::Pass5(char *file){
  FILE  *fp;
  calcC *siki;
  memberC *mem;
  char  *w_str;
  char  *w;
  int    j,k,i,len;
  printfC *pp;
  extendC *ex;
  typC *typ;
  codeC *code;
  varC *var;

  fp = fopen(file,"wt");
  if (fp == NULL){return(false);}

  line_cnt = 0;
  printf(" pass5(file output).\n");

  fprintf(fp,"#reg_area,32'h%08x\n",reg_max+1);
  fprintf(fp,"#program_area,32'h%08x\n",map+1);
  fprintf(fp,"#start_addr,32'h%08x\n",start_map);
  fprintf(fp,"#global_area,32'h%08x\n",stk_map+1);
  fprintf(fp,"#irq_number,%d\n",irq_number);

  // ƒOƒ[ƒoƒ‹•Ï”
  MEM_LOOP(var,varC,global_fp)
    if (var->flgConst){continue;}
    fprintf(fp,"#global,%s,%d(%x),%d\n",var->name->c_str(),var->map,var->map,var->size);
  LOOP_END

  MEM_LOOP(siki,calcC,calc_fp)
    w = siki->siki->c_str();
    len = strlen(w);
    w_str = new char[len*2+1];
    for(j=0,k=0,i=0;i<len;++i){
      if (*(w+i) == '#'){
		*(w_str+j) = 'p'; ++j;

		char w_int[10];             // Ver 0.93
		sprintf(w_int,"%d",k);      // Ver 0.93
		int w_len = strlen(w_int);  // Ver 0.93
		for(int i=0;i<w_len;i++){   // Ver 0.93
		  *(w_str+j) = w_int[i];    // Ver 0.93
		  ++j;                      // Ver 0.93
		}                           // Ver 0.93

		++k;
        *(w_str+j) = 0x00;
      }
      else{
        *(w_str+j) = *(w+i); ++j;
        *(w_str+j) = 0x00;
      }
    }

    fprintf(fp,"#method,%d,%d,%s\n",siki->sikiNo,siki->reg_su,w_str);
    delete [] w_str;
  LOOP_END


  sCharEX *w_ex = new sCharEX("");     // Ver 0.93
  MEM_LOOP(pp,printfC,printf_fp)
    w_ex->DblIns(pp->format->c_str()); // Ver 0.93
	fprintf(fp,"#method_printf,%d,%d,%s\n",pp->prNo,pp->parmSu,w_ex->c_str());  // Ver 0.93
  LOOP_END
  delete w_ex; // Ver 0.93

  MEM_LOOP(ex,extendC,extend_fp)
    fprintf(fp,"#method_extend,%d,%d,%s\n",ex->exNo,ex->parmSu,ex->format->c_str());
  LOOP_END

  MEM_LOOP(typ,typC,typ_fp)
    fprintf(fp,"#type,%s,%d\n",typ->name->c_str(),typ->size);
    MEM_LOOP(mem,memberC,typ->member_fp)
      fprintf(fp,"#member,%s,%s,%d\n",typ->name->c_str(),mem->name->c_str(),mem->offset);
    LOOP_END
  LOOP_END

  MEM_LOOP(g_prg,prgC,prg_fp)
    if (g_prg->irq_flg == false){continue;}
    fprintf(fp,"#irq_function,%s,32'h%08x,%d,%d,%s\n",g_prg->name->c_str(),g_prg->map,g_prg->irq_level,irq_number-g_prg->irq_level,g_prg->irq_line->c_str());
  LOOP_END


  MEM_LOOP(g_prg,prgC,prg_fp)
//    if (g_prg->irq_flg){fprintf(fp,"#irq_st,%s,32'h%08x,32'h%08x,32'h%08x,32'h%08x\n",g_prg->name->c_str(),g_prg->map,g_prg->size,g_prg->parm_su,g_prg->local_su);}
//    else               {fprintf(fp,"#st,%s,32'h%08x,32'h%08x,32'h%08x,32'h%08x\n"    ,g_prg->name->c_str(),g_prg->map,g_prg->size,g_prg->parm_su,g_prg->local_su);}

    // function
    fprintf(fp,"#st,%s,32'h%08x,32'h%08x,32'h%08x,32'h%08x\n"    ,g_prg->name->c_str(),g_prg->map,g_prg->size,g_prg->parm_su,g_prg->local_su);

    // parameter variable
    MEM_LOOP(var,varC,g_prg->parm_fp)
      fprintf(fp,"#parm,%s,%d(%x),%d\n",var->name->c_str(),var->map,var->map,var->size);
    LOOP_END

    // local variable
    MEM_LOOP(var,varC,g_prg->local_fp)
      fprintf(fp,"#local,%s,%d(%x),%d\n",var->name->c_str(),var->map,var->map,var->size);
    LOOP_END

    MEM_LOOP(code,codeC,g_prg->code_fp)
      fprintf(fp,"%s,%u,%u,%u,%u,%u",code->code->c_str(),code->parm[0],code->parm[1],code->parm[2],code->parm[3],code->parm[4]);
      if (code->call_name != NULL){fprintf(fp,",//,%s",code->call_name->c_str());}
      fprintf(fp,"\n");
    LOOP_END
  LOOP_END

  fclose(fp);
  return(true);
}


// ---------------
// Pass 5 List
// ---------------
bool Inf_T::Pass5_list(char *file){
  FILE    *fp;
  calcC   *siki;
  memberC *mem;
  char    *w_str;
  char    *w;
  int      j,k,i,len;
  printfC *pp;
  typC    *typ;
  codeC   *code;
  varC    *var;
  extendC *ex;

  fp = fopen(file,"wt");
  if (fp == NULL){return(false);}

  line_cnt = 0;
//  printf(" pass5(file output).\n");

  fprintf(fp,"##### top imformation #####\n"); 
  fprintf(fp,"register area      ,%d(%x)\n",reg_max+1,reg_max+1);
  fprintf(fp,"program area       ,%d(%x)\n",map+1,map+1);
  fprintf(fp,"start address      ,%x\n",start_map);
  fprintf(fp,"global area        ,%d(%x)\n",global_su+1,global_su+1);
  fprintf(fp,"irq function number,%d(%x)\n",irq_number,irq_number);

  // global variable
  fprintf(fp,"\n");
  fprintf(fp,"##### global veriable #####\n");
  MEM_LOOP(var,varC,global_fp)
    if (var->flgConst){continue;}
    fprintf(fp,"global,%s,mapping:%d(%x),size:%d\n",var->name->c_str(),var->map,var->map,var->size);
  LOOP_END

  fprintf(fp,"\n");
  fprintf(fp,"##### calcuration #####\n");
  MEM_LOOP(siki,calcC,calc_fp)
    w = siki->siki->c_str();
    len = strlen(w);
    w_str = new char[len*2+1];
    for(j=0,k=0,i=0;i<len;++i){
      if (*(w+i) == '#'){
        *(w_str+j) = 'p'; ++j;
        *(w_str+j) = '0' + k; ++j; ++k;
        *(w_str+j) = 0x00;
      }
      else{
        *(w_str+j) = *(w+i); ++j;
        *(w_str+j) = 0x00;
      }
    }

    fprintf(fp,"%03d,argCnt:%d,method:%s\n",siki->sikiNo,siki->reg_su,w_str);
    delete [] w_str;
  LOOP_END

  fprintf(fp,"\n");
  fprintf(fp,"##### printf #####\n");

  MEM_LOOP(pp,printfC,printf_fp)
	fprintf(fp,"%03d,argCnt:%d,format:%s\n",pp->prNo,pp->parmSu,pp->format->c_str());
  LOOP_END

  fprintf(fp,"\n");
  fprintf(fp,"##### extend code #####\n");
  MEM_LOOP(ex,extendC,extend_fp)
    fprintf(fp,"%03d,argCnt:%d,string:%s\n",ex->exNo,ex->parmSu,ex->format->c_str());
  LOOP_END

  fprintf(fp,"\n");
  fprintf(fp,"##### type define #####\n");  
  MEM_LOOP(typ,typC,typ_fp)
    fprintf(fp,"class:%s,size:%d\n",typ->name->c_str(),typ->size);
    MEM_LOOP(mem,memberC,typ->member_fp)
      if (mem->typ == NULL){fprintf(fp," member:%s,type:int,offset:%d\n",mem->name->c_str(),mem->offset);}
      else                 {fprintf(fp," member:%s,type:%s,offset:%d\n",mem->name->c_str(),mem->typ->name->c_str(),mem->offset);}
    LOOP_END
  LOOP_END


  fprintf(fp,"##### irq function #####\n");
  MEM_LOOP(g_prg,prgC,prg_fp)
    if (g_prg->irq_flg == false){continue;}
    fprintf(fp,"program:%s,address:%08x,saveAreaNo:%d,IrqLevel:%d,IrqAssignLine:%s\n",g_prg->name->c_str(),g_prg->map,g_prg->irq_level,irq_number-g_prg->irq_level,g_prg->irq_line->c_str());
  LOOP_END


  fprintf(fp,"\n");
  k = 0;
  fprintf(fp,"##### program #####\n");
  MEM_LOOP(g_prg,prgC,prg_fp)
    fprintf(fp,"addr:%08x(%08d),function:%s,programSize:%d,argSize:%d,localSize:%d\n"
      ,k,k,g_prg->name->c_str(),g_prg->size,g_prg->parm_su,g_prg->local_su);

    // parameter variable
    MEM_LOOP(var,varC,g_prg->parm_fp)
      fprintf(fp,"parm,%s,mapping:%d(%x),size:%d\n",var->name->c_str(),var->map,var->map,var->size);
    LOOP_END

    // local variable
    MEM_LOOP(var,varC,g_prg->local_fp)
      fprintf(fp,"local,%s,mapping:%d(%x),size:%d\n",var->name->c_str(),var->map,var->map,var->size);
    LOOP_END

    MEM_LOOP(code,codeC,g_prg->code_fp)
      fprintf(fp,"addr:%08x(%08d),code:%s,",k,k,code->code->c_str());
      if (strcmp(code->code->c_str(),"#nop"  ) == 0){fprintf(fp,",,");}
//      if (strcmp(code->code->c_str(),"#reg_push") == 0){fprintf(fp,"saveAreaNo:%03d,irqLevel:%03d",code->parm[0],code->parm[1]);}
      if (strcmp(code->code->c_str(),"#reg_pop" ) == 0){fprintf(fp,"saveAreaNo:%03d,irqLevel:%03d",code->parm[0],code->parm[1]);}
      if (strcmp(code->code->c_str(),"#user" ) == 0){fprintf(fp,"userCode:%03d,regNo:%03d,argCnt:%03d",code->parm[0],code->parm[1],code->parm[2]);}
      if (strcmp(code->code->c_str(),"#set"  ) == 0){
        if (code->parm[0] == K_val_const  ){reg(fp,code->parm[1],false); fprintf(fp," <- %u + %u - %u,,",code->parm[2],code->parm[3],code->parm[4]);}
        if (code->parm[0] == K_ptr_const  ){reg(fp,code->parm[1],true ); fprintf(fp," <- %u + %u - %u,,",code->parm[2],code->parm[3],code->parm[4]);}
        if (code->parm[0] == K_val_preg   ){reg(fp,code->parm[1],false); fprintf(fp," <- "); reg(fp,code->parm[2],true ); fprintf(fp," + %u - %u,,",code->parm[3],code->parm[4]);}
        if (code->parm[0] == K_val_reg    ){reg(fp,code->parm[1],false); fprintf(fp," <- "); reg(fp,code->parm[2],false); fprintf(fp," + %u - %u,,",code->parm[3],code->parm[4]);}
        if (code->parm[0] == K_ptr_reg    ){reg(fp,code->parm[1],true ); fprintf(fp," <- "); reg(fp,code->parm[2],false); fprintf(fp," + %u - %u,,",code->parm[3],code->parm[4]);}
        if (code->parm[0] == K_offset_calc){reg(fp,code->parm[1],false); fprintf(fp," <- "); reg(fp,code->parm[1],false); fprintf(fp," + "); reg(fp,code->parm[2],false);  fprintf(fp," * %u,,",code->parm[3]);}
      }
      if (strcmp(code->code->c_str(),"#jmp"   ) == 0){
        fprintf(fp,"trueAddr:%08x,falseAddr:%08x,",code->parm[0],code->parm[1]);
      }
      if (strcmp(code->code->c_str(),"#calc"  ) == 0){
        fprintf(fp,"methodNo:%03d,regNo:%03d,argCnt:%03d,",code->parm[0],code->parm[1],code->parm[2]);
      }
      if (strcmp(code->code->c_str(),"#printf") == 0){
        fprintf(fp,"printfNo:%03d,regNo:%d,argCnt:%d",code->parm[0],code->parm[1],code->parm[2]);
      }
      if (strcmp(code->code->c_str(),"#extend") == 0){
        fprintf(fp,"extendNo:%03d,regNo:%d,argCnt:%d,",code->parm[0],code->parm[1],code->parm[2]);
      }
      if (code->src == NULL){fprintf(fp,"\n");}
      else                  {fprintf(fp,",,//,%s\n",code->src->c_str());}
      ++k;
    LOOP_END
  LOOP_END

  fclose(fp);
  return(true);
}

void Inf_T::reg(FILE *fp,int no,bool flgPtr){
  if (flgPtr){fprintf(fp,"*(");}
  if (no == V_prg_cnt ){fprintf(fp,"PrgCnt");}
  if (no == V_stk_cnt ){fprintf(fp,"StkCnt");}
  if (no == V_parm_cnt){fprintf(fp,"ParmCnt");}
  if (no == V_sum     ){fprintf(fp,"SumCnt");}
  if (no >= V_val_assign){fprintf(fp,"r%d",no);}
  if (flgPtr){fprintf(fp,")");}

}
