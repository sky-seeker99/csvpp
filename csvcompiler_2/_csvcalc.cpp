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
// CSV COMPILER CALC PASS
//

// # 式解析 #######################
// ----------------
// 式解析
// ----------------
calcSikiC *Inf_T::calcPass1_Siki(char *p_str){
  calcSikiC *siki;
  calcVarC  *var;
  char c;
  int len,i,ptr,siki_ptr;;
  int k_lvl0,k_lvl1;
  char *w_str;
  char *w_siki;
  int   w_reg_su;

#ifdef DEBUG_CALC
printf("calc in[%s]\n",p_str);
#endif

  len  = strlen(p_str);
  siki = new calcSikiC(it);

  // # check kakko #####
  k_lvl0 = 0;
  k_lvl1 = 0;
  for(i=0;i<len;++i){
    c = *(p_str+i);
    if (c == '['){++k_lvl0; continue;}
    if (c == ']'){--k_lvl0; continue;}
    if (c == '('){++k_lvl1; continue;}
    if (c == ')'){--k_lvl1; continue;}
  }
  if (k_lvl0 != 0){siki->errFlg = true; Log(false,MSG_301,p_str); return(siki);}
  if (k_lvl1 != 0){siki->errFlg = true; Log(false,MSG_302,p_str); return(siki);}

  // # siki kaiseki #####
  k_lvl0 = 0;
  w_reg_su = 0;
  ptr    = 0;
  siki_ptr = 0;
  w_str = new char[len+1];
  *w_str = 0x00;
  w_siki  = new char[len+1];
  *w_siki = 0x00;
  for(i=0;i<len;++i){
    c = *(p_str+i);
    if (k_lvl0 == 0){
      if (calcPass1_enzanCheck(c)){  // 演算子チェック
        sp_push(w_str); sp_push2(w_str);
        if (*w_str == 0x00){
          *(w_siki+siki_ptr) = c; ++siki_ptr;
          *(w_siki+siki_ptr) = 0x00;

          *w_str = 0x00;   ptr = 0;

          continue;
        }
        var = calcPass1_varCheck(w_str);
        if (var->errFlg == true){siki->errFlg = true;}
        it->alloc_ptr = (MM_PTR_T *)var;
        siki->var_fp->mem_alloc();
        ++w_reg_su; 
        *w_str = 0x00;   ptr = 0;

        *(w_siki+siki_ptr) = '#';   ++siki_ptr;
        *(w_siki+siki_ptr) = c;     ++siki_ptr;
        *(w_siki+siki_ptr) = 0x00;     
        continue;
      }
    }

    if (c == '['){++k_lvl0;}
    if (c == ']'){--k_lvl0;}
    *(w_str + ptr) = c;   ++ptr;
    *(w_str + ptr) = 0x00;
  }

  sp_push(w_str); sp_push2(w_str);
  if (*w_str != 0x00){
    var = calcPass1_varCheck(w_str);
    if (var->errFlg == true){siki->errFlg = true;}
    it->alloc_ptr = (MM_PTR_T *)var;
    siki->var_fp->mem_alloc();
    ++w_reg_su; 

    *(w_siki+siki_ptr) = '#'; ++siki_ptr;
    *(w_siki+siki_ptr) = 0x00; 
  }

  // 式の登録
  it->srch_key = w_siki;
  if (calc_fp->mem_srch() == 0){
    siki->siki = (calcC *)calc_fp->mem_link_ptr_rd();
  }else{
    siki->siki = new calcC(w_siki,w_reg_su,siki_cnt);
    ++siki_cnt;
    it->alloc_ptr = (MM_PTR_T *)siki->siki;
    calc_fp->mem_srch_alloc();
  }

  delete [] w_siki;
  delete [] w_str;

#ifdef DEBUG_CALC
printf("calc out [no:%d][siki:%s][parm:%d]\n",siki->siki->sikiNo,siki->siki->siki->c_str(),siki->siki->reg_su);
#endif

  return(siki);
}


#define K_VarSrch 0
#define K_ArySrch 1

// ----------------
// 変数解析
// ----------------
calcVarC *Inf_T::calcPass1_varCheck(char *p_str){
  calcVarC *var;
  char c;
  int len,i,ptr,siki_ptr;;
  int k_lvl0;
  char *w_str;
  int   mode;
  bool  chkout;
  bool  flgTop;
  calcMemC *mem;
  typC *w_typ;

#ifdef DEBUG_CALC
printf("var in[%s]\n",p_str);
#endif

  if (*p_str == '@'){var = new calcVarC(it,true ); ++p_str;}
  else              {var = new calcVarC(it,false);}

  // 固定値チェック
  if ((i = calcPass1_constCheck(p_str)) != -1){
    it->srch_key = p_str + i;
    var->varKbn = AttrVarConst;
    if (global_fp->mem_srch() == 0){var->var = (varC *)global_fp->mem_link_ptr_rd();}
    else{
      var->var      = new varC(it->srch_key );
      it->alloc_ptr = (MM_PTR_T *)var->var;
      global_fp->mem_srch_alloc();
    }
    return(var);
  }

  w_typ  = NULL;
  len    = strlen(p_str);
  mode   = K_VarSrch;
  k_lvl0 = 0;
  ptr    = 0;
  w_str = new char[len+1];
  *w_str = 0x00;
  flgTop = true;
  mem    = NULL;
  for(i=0;i<len+1;++i){
    c = *(p_str+i);

    if (mode == K_VarSrch){
      chkout = false;
      if (c == '.'){
        if (ptr == 0){continue;}
        chkout = true;
      }
      if (c == '['){
        chkout = true;
        mode = K_ArySrch;
        k_lvl0 = 1;
      }
      if ((c == 0x00) && (ptr > 0)){chkout = true;}
      if (chkout){
        if (flgTop){  // variable instance
          it->srch_key = w_str;
          if      (g_prg->parm_fp->mem_srch()  == 0){var->varKbn = AttrVarParm;   var->var = (varC *)g_prg->parm_fp->mem_link_ptr_rd();}
          else if (g_prg->local_fp->mem_srch() == 0){var->varKbn = AttrVarLocal;  var->var = (varC *)g_prg->local_fp->mem_link_ptr_rd();}
          else if (global_fp->mem_srch()       == 0){var->varKbn = AttrVarGlobal; var->var = (varC *)global_fp->mem_link_ptr_rd();}
          else                                      {Log(false,MSG_303,w_str); var->errFlg = false; return(var);}
          flgTop = false;
        }
        else{
          it->srch_key = w_str;
          if (w_typ == NULL){w_typ = var->var->typ;}
          else              {w_typ = mem->mem->typ;}
          if (w_typ != NULL){
            if (w_typ->member_fp->mem_srch() == 0){
              mem = new calcMemC(w_str,(memberC*)w_typ->member_fp->mem_link_ptr_rd());
            }else{
              Log(false,MSG_303,w_str);
              var->errFlg = false;
              mem = new calcMemC(w_str);
            }
          }else{
            Log(false,MSG_303,w_str);
            var->errFlg = false;
            mem = new calcMemC(w_str);
          }
          it->alloc_ptr = (MM_PTR_T *)mem;
          var->member_fp->mem_alloc();
          var->flgMem = true;
        }
        ptr = 0;
        *w_str = 0x00;
      }else{
        *(w_str + ptr) = c; ++ptr;
        *(w_str + ptr) = 0x00;
      }
      continue;
    }
 
    if (mode == K_ArySrch) { // array index
      if (c == '['){++k_lvl0;}
      if (c == ']'){--k_lvl0;}

      if (k_lvl0 == 0) { // checkout
        //if (var->ary == NULL)
        if (mem == NULL){var->ary = calcPass1_Siki(w_str);}
        else            {mem->ary = calcPass1_Siki(w_str);}
        ptr = 0;
        *w_str = 0x00;
        mode = K_VarSrch;
      }else{
        *(w_str + ptr) = c; ++ptr;
        *(w_str + ptr) = 0x00;
      }
      continue;
    }
  }

#ifdef DEBUG_CALC
if (var->var != NULL)
  {
  printf("var out[name:%s][mem:%d][ptr:%d][kbn:%d]\n",var->var->name->c_str(),var->flgMem,var->flgPtr,var->varKbn);
  }
#endif


  delete [] w_str;
  return(var);
}

// ----------------
// 固定値チェック
// ----------------
int Inf_T::calcPass1_constCheck(char *str){
  int mode;
  int len,i;
  char c;
  int ret;

  ret = 0;
  len = strlen(str);
  for(mode=0,i=0;i<len;++i){
    if ((*(str+i) == '0') && (*(str+i+1) == 'x')){
      *(str+i) = '\'';
      *(str+i+1) = 'h';
    }
    c = *(str+i);
    if (mode == 0){
      if ((c >= '0') && (c <= '9')){continue;}
      if (c == '\''){mode = 1; ret = i; continue;}
      return(-1);
    }
    if (mode == 1){
      if ((c == 'h') || (c == 'b')){return(ret);}
      return(-1);
    }
  }
  return(ret);
}

// ----------------
// 演算子チェック
// ----------------
bool Inf_T::calcPass1_enzanCheck(char c){
  if (c == '+'){return(true);}
  if (c == '-'){return(true);}
  if (c == '*'){return(true);}
  if (c == '/'){return(true);}
  if (c == '&'){return(true);}
  if (c == '|'){return(true);}
  if (c == '%'){return(true);}
  if (c == '>'){return(true);}
  if (c == '<'){return(true);}
  if (c == '='){return(true);}
  if (c == '!'){return(true);}
  if (c == '|'){return(true);}
  if (c == '('){return(true);}
  if (c == ')'){return(true);}
  if (c == '{'){return(true);}
  if (c == '}'){return(true);}
  if (c == '~'){return(true);}
  if (c == '^'){return(true);}  // Ver 0.92

  return(false);
}



// # 式コード化 ##############################
// ----------------
// 式コード化
// ----------------
void Inf_T::calcPass2_Siki(calcSikiC *siki,int reg_no){
  calcVarC *var;
  int sv_reg_no;

  //printf("siki [%s]\n",siki->siki->siki->c_str());

  sv_reg_no = reg_no;
  MEM_LOOP(var,calcVarC,siki->var_fp)
    if (var->flgPtr){calcPass2_Var(var,reg_no++);}
    else            {calcPass2_Val(var,reg_no++);}
    if (siki->siki->reg_su == 1) {return;}
  LOOP_END
  codeAdd("#calc",siki->siki->sikiNo,sv_reg_no,siki->siki->reg_su,0,0);
}

// -----------------------------------
// ポインタ変数実体があるアドレス算出
// -----------------------------------
bool Inf_T::calcPass2_Ptr(calcVarC *var,int reg_no){
  calcMemC *mem;
  typC *typ;
  bool  flg;
  int arySize;
  calcSikiC *w_calc;
  bool svPtrFlg;
  bool specialFlg;
  bool svFisrtAry;
  bool svSecondAry;
  calcMemC *sv_mem;

  if (var->var == NULL){return(false);}

  //printf("ptr name=%s\n",var->var->name->c_str());

  // base sum
  if (var->varKbn == AttrVarConst  ){codeAdd("#set",K_val_const,reg_no,SujiConvEx(var->var->name->c_str()),0,0); return(false);}
  if (var->varKbn == AttrVarGlobal ){codeAdd("#set",K_val_const,reg_no,var->var->map,0,0);         }
  if (var->varKbn == AttrVarLocal  ){codeAdd("#set",K_val_reg  ,reg_no,V_parm_cnt,var->var->map,0);}
  if (var->varKbn == AttrVarParm   ){codeAdd("#set",K_val_reg  ,reg_no,V_parm_cnt,var->var->map,0);}

  // ポインタ変数 ?
  svPtrFlg    = false;
  specialFlg  = false;
  svFisrtAry  = false;
  svSecondAry = false;

  if  ((var->var->flgPtr)
   || ((var->varKbn == AttrVarParm) && (var->var->typ != NULL))){
    // ポインタ変数が配列 でかつ インデックス指定あり?
    if ((var->var->ary_su > 1) && (var->ary != NULL)){
      calcPass2_Siki(var->ary,reg_no+1);
      codeAdd("#set",K_offset_calc,reg_no,reg_no+1,1,0);
      specialFlg = true;
    }
    svPtrFlg = true;
    //codeAdd("#set",K_val_preg,reg_no,reg_no,0,0);
  }

  // ポインタ変数配列ではなく、インデックス指定あり ?
  if ((var->ary != NULL) && (specialFlg == false)){
    if (svPtrFlg){
      svFisrtAry = true;
    }
    else{
      calcPass2_Siki(var->ary,reg_no+1);
      if (var->var->typ == NULL) {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,1                  ,0);}
      else                       {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,var->var->typ->size,0);}
    }
  }

  MEM_LOOP(mem,calcMemC,var->member_fp)
    if (mem->mem == NULL){continue;}
    if (svPtrFlg){
      codeAdd("#set",K_val_preg,reg_no,reg_no,0,0);
      svPtrFlg = false;
      if (svFisrtAry){
        calcPass2_Siki(var->ary,reg_no+1);
        if (var->var->typ == NULL) {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,1                  ,0);}
        else                       {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,var->var->typ->size,0);}
        svFisrtAry = false;
      }
      if (svSecondAry){
        calcPass2_Siki(sv_mem->ary,reg_no+1);
        if (sv_mem->mem->typ == NULL) {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,1                     ,0);}
        else                          {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,sv_mem->mem->typ->size,0);}
        svSecondAry = false;
      }
    }
    // メンバのオフセット計算
    if (mem->mem->offset > 0){codeAdd("#set",K_val_reg  ,reg_no,reg_no,mem->mem->offset,0);}
    // ポインタ変数 ?
    specialFlg = false;
    svSecondAry = false;
    if (mem->mem->flgPtr){
      // ポインタ変数が配列 でかつ インデックス指定あり?
      if ((mem->mem->ary_su > 1) && (mem->ary != NULL)){
        calcPass2_Siki(mem->ary,reg_no+1);
        codeAdd("#set",K_offset_calc,reg_no,reg_no+1,1,0);
        specialFlg = true;
      }
      svPtrFlg = true;
      //codeAdd("#set",K_val_preg,reg_no,reg_no,0,0);
    }
    // ポインタ変数ではなく、インデックス指定あり ?
    if ((mem->ary != NULL) && (specialFlg == false)){
      if (svPtrFlg){
        svSecondAry = true;
        sv_mem = mem;
      }
      else{
        calcPass2_Siki(mem->ary,reg_no+1);
        if (mem->mem->typ == NULL) {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,1                  ,0);}
        else                       {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,mem->mem->typ->size,0);}
      }
    }
  LOOP_END

  // 値代入用
  if (valueFlg){
    if (svPtrFlg){
      codeAdd("#set",K_val_preg,reg_no,reg_no,0,0);
      svPtrFlg = false;
      if (svFisrtAry){
        calcPass2_Siki(var->ary,reg_no+1);
        if (var->var->typ == NULL) {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,1                  ,0);}
        else                       {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,var->var->typ->size,0);}
        svFisrtAry = false;
      }
      if (svSecondAry){
        calcPass2_Siki(sv_mem->ary,reg_no+1);
        if (sv_mem->mem->typ == NULL) {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,1                     ,0);}
        else                          {codeAdd("#set",K_offset_calc,reg_no,reg_no+1,sv_mem->mem->typ->size,0);}
        svSecondAry = false;
      }
    }
  }

  return(svPtrFlg);
}

// -------------------------------
// 変数のオフセット算出コード生成
// -------------------------------
void Inf_T::calcPass2_Var(calcVarC *var,int reg_no){
  valueFlg = true;
  calcPass2_Ptr(var,reg_no);
  valueFlg = false;
}

// -----------------------------------
// 変数のオフセット算出後の値取り出し
// -----------------------------------
void Inf_T::calcPass2_Val(calcVarC *var,int reg_no) {
  calcPass2_Var(var,reg_no);
  if (var->varKbn == AttrVarConst  ){return;}
  codeAdd("#set",K_val_preg,reg_no,reg_no,0,0);
}

//  # インターフェース ########################
// --------------------------------------
// ポインタ変数のポインタの実体コード化
// --------------------------------------
bool Inf_T::calcApi_Ptr(char *p_var,int p_reg_no){
  bool flg;
  calcVarC *var;
  var = calcPass1_varCheck(p_var);
  if (var->errFlg == true){delete var; return(false);}
  flg = calcPass2_Ptr(var,p_reg_no);
  delete var;
  return(flg);
}

// ----------------
// 変数コード化
// ----------------
bool Inf_T::calcApi_Var(char *p_var,int p_reg_no){
  calcVarC *var;
  var = calcPass1_varCheck(p_var);
  if (var->errFlg == true){delete var; return(false);}
  calcPass2_Var(var,p_reg_no);
  delete var;
  return(true);
}

// ----------------
// 式コード化
// ----------------
bool Inf_T::calcApi_Siki(char *p_siki,int p_reg_no){
  calcSikiC *siki;

  //printf("siki = %s\n",p_siki);

  siki = calcPass1_Siki(p_siki);

  if (siki->errFlg == true){delete siki; return(false);}
  calcPass2_Siki(siki,p_reg_no);
  delete siki;
  return(true);
}

// ----------------
// 変数代入
// ----------------
bool Inf_T::calcApi_Set(char *p_var,char *p_siki,int p_reg_no){
  if (calcApi_Var (p_var ,p_reg_no  ) == false){return(false);}
  if (calcApi_Siki(p_siki,p_reg_no+1) == false){return(false);}
  codeAdd("#set",K_ptr_reg ,p_reg_no,p_reg_no+1,0,0);
  return(true);
}

// ----------------
// ポインタ変更
// ----------------
bool Inf_T::calcApi_PtrSet(char *p_var,char *p_siki,int p_reg_no){
  if (calcApi_Ptr (p_var ,p_reg_no  ) == false){return(false);}
  if (calcApi_Siki(p_siki,p_reg_no+1) == false){return(false);}
  codeAdd("#set",K_ptr_reg ,p_reg_no,p_reg_no+1,0,0);
  return(true);
}

// ----------------
// 条件式算出
// ----------------
bool Inf_T::calcApi_If(char *p_siki,int p_reg_no){
  if (calcApi_Siki(p_siki,p_reg_no) == false){return(false);}
  codeAdd("#set",K_val_reg,V_sum,p_reg_no,0,0);
  return(true);
}


