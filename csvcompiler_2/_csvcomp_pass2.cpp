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
//  CSV COMPILER PASS2(#st,#global,#local,#parm)
//  ・関数のトークン解析と関数の登録
//  ・割り込み関数のトークン解析と割り込み関数の登録
//  ・グローバル変数のトークン解析と変数の登録
//  ・パラメータ変数のトークン解析と変数の登録
//  ・ローカル変数のトークン解析と変数の登録
//

// ---------------
// Pass 2 Main
// ---------------
bool Inf_T::Pass2(Read64_C *in_fp){
  in_fp->seek((__int64)0);
  printf(" pass2(#st,#global,#local,#parm check).\n");

  for(line_cnt=0;;++line_cnt){
    unsigned char *buff = in_fp->read();
    if (buff == NULL){break;}
    csvi->Exec(buff);
    CSV_LOOP(csvi,ustr,SP_PUSH)
      char *str = (char*)ustr;
      if      (strcmp(str,"#st"    )==0) {func_rtn(false        );}
      else if (strcmp(str,"#irq_st")==0) {func_rtn(true         );}
      else if (strcmp(str,"#global")==0) {var_rtn (AttrVarGlobal);}
      else if (strcmp(str,"#local" )==0) {var_rtn (AttrVarLocal );}
      else if (strcmp(str,"#parm"  )==0) {var_rtn (AttrVarParm  );}
      break;
    LOOP_END
  }
  return(true);
}


// ---------------
// #st / #irq_st
// ---------------
void Inf_T::func_rtn(bool flg){
  char *func_name = NULL;
  char *line_irq  = NULL;
  CSV_LOOP(csvi,ustr,SP_PUSH)
    if (func_name == NULL) {
      func_name = (char *)ustr;
      it->srch_key = func_name;
      if (prg_fp->mem_srch() == 0){Log(false,MSG_101,"#st/#irq_st"); return;}
      continue;
    }
    line_irq = (char *)ustr;
    break;
  LOOP_END

  if (func_name == NULL) {
    Log(false,MSG_102,"#st/#irq_st"); return;
  }

  if (flg) {
    if (line_irq==NULL) {Log(false,MSG_105,"#irq_st"); return;}
  }
  

  g_prg = new prgC(it,func_name,flg,irq_number,line_irq);
  it->alloc_ptr = (MM_PTR_T *)g_prg;
  prg_fp->mem_srch_alloc();

  if (flg){irq_number++;}
}

// ----------------------
// #global/#local/#parm
// ----------------------
void Inf_T::var_rtn(int kbn){
  char *type_name;
  char *var_name;
  int   ary_su;
  typC *w_typ;
  char *msg;
  MEM_FP *mem_fp;
  bool flgPtr;
  varC *var;

  if (kbn == AttrVarGlobal){msg = "#global";}
  if (kbn == AttrVarLocal ){msg = "#local" ;}
  if (kbn == AttrVarParm  ){msg = "#parm"  ;}

  if ((kbn != AttrVarGlobal) && (g_prg == NULL)){Log(false,MSG_102,msg); return;}

  if (kbn == AttrVarParm)
    {
    if (g_prg->irq_flg){Log(false,MSG_104,"#parm"); return;}
    }

  type_name = NULL;
  var_name  = NULL;
  ary_su    = 1;

  CSV_LOOP(csvi,ustr,SP_PUSH)
    char *str = (char *)ustr;
    if (var_name  == NULL){var_name  = str; continue;}
    if (type_name == NULL){type_name = str; continue;}
    ary_su = SujiConvEx(str);
    break;
  LOOP_END

  if (type_name == NULL){Log(false,MSG_002,msg); return;}
  if (var_name  == NULL){Log(false,MSG_003,msg); return;}
  if (ary_su    <  1   ){Log(false,MSG_004,msg); return;}

  if (kbn == AttrVarGlobal){mem_fp = global_fp;}
  if (kbn == AttrVarLocal ){mem_fp = g_prg->local_fp;}
  if (kbn == AttrVarParm  ){mem_fp = g_prg->parm_fp;}

  if (strcmp(type_name,"int")==0){w_typ = NULL;}
  else{
    it->srch_key = type_name;
    if (typ_fp->mem_srch() != 0){Log(false,MSG_002,msg); return;}
    w_typ = (typC *)typ_fp->mem_link_ptr_rd();
  }

  if (*var_name == '@'){flgPtr = true;  it->srch_key = var_name+1;}
  else                 {flgPtr = false; it->srch_key = var_name;  }

  if (mem_fp->mem_srch() == 0){Log(false,MSG_103,msg); return;}

  var = new varC(it->srch_key,ary_su,w_typ,flgPtr);
  it->alloc_ptr = (MM_PTR_T *)var;
  if (kbn == AttrVarParm  ){var->map = g_prg->parm_su;}
  mem_fp->mem_srch_alloc();

  if (kbn == AttrVarGlobal){++global_su;}
  if (kbn == AttrVarLocal ){++(g_prg->local_su);}
  if (kbn == AttrVarParm  ){++(g_prg->parm_su);}
}


