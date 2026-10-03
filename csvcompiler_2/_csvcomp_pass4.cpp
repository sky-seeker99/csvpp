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
//  CSV COMPILER PASS4(code compile)
//

// ---------------
// Pass 4 Main
// ---------------
bool Inf_T::Pass4(Read64_C *in_fp,char *start_func){
  char *w_str;
  prgC *prg;
  codeC *code;
  jmpC *jmp;

  in_fp->seek((__int64)0);
  printf(" pass4(code compile).\n");

  g_prg = NULL;
  for(line_cnt=0;;++line_cnt){
    unsigned char *buff = in_fp->read();
    if (buff == NULL){break;}
    csvi->Exec(buff);
    src_str = new sChar("");
    char *str=NULL;
    CSV_LOOP(csvi,ustr,SP_PUSH)
      if (str == NULL){str = (char *)ustr;}
      src_str->cat((char *)ustr);
      src_str->cat(",");
    LOOP_END
    it->alloc_ptr = src_str;
    src_fp->mem_alloc();



    //printf("%s\n",src_str->c_str());

    csvi->Exec(buff);
    CSV_LOOP(csvi,ustr,SP_PUSH)
      str = (char *)ustr;
      if (str == NULL){}
      else if (strcmp(str,"#st"      )==0) {func_code    ();}
      else if (strcmp(str,"#irq_st"  )==0) {func_code    ();}   // Ver 1.01
      else if (strcmp(str,"#set"     )==0) {set_code     (false);}
      else if (strcmp(str,"#ptr"     )==0) {set_code     (true);}
      else if (strcmp(str,"#if"      )==0) {if_code      ();}
      else if (strcmp(str,"#else"    )==0) {else_code    ();}
      else if (strcmp(str,"#elseif"  )==0) {elseif_code  ();}
      else if (strcmp(str,"#endif"   )==0) {endif_code   ();}
      else if (strcmp(str,"#for"     )==0) {for_code     ();}
      else if (strcmp(str,"#endfor"  )==0) {endfor_code  ();}
      else if (strcmp(str,"#continue")==0) {continue_code();}
      else if (strcmp(str,"#break"   )==0) {break_code   ();}
      else if (strcmp(str,"#return"  )==0) {return_code  ();}
      else if (strcmp(str,"#do"      )==0) {call_code    ();}
      else if (strcmp(str,"#user"    )==0) {user_code    ();}
      else if (strcmp(str,"#printf"  )==0) {printf_code  ();}
      else if (strcmp(str,"#extend"  )==0) {extend_code  ();}
      break;
    LOOP_END
  }

  // ネストチェック
  if (g_prg != NULL){
    if (if_su  != 0) {Log(false,MSG_201,"#if-#endif"  );}
    if (for_su != 0) {Log(false,MSG_202,"#for-#endfor");}
    if_su = 0;
    for_su = 0;

    if (g_prg->irq_flg){codeAdd("#reg_pop",g_prg->irq_level,irq_number-g_prg->irq_level,0,0,0);}
    else               {return_code();                }
  }

  // プログラムマッピング
  map = 0;
  MEM_LOOP(prg,prgC,prg_fp)
    prg->map = map;
    map     += prg->size;
  LOOP_END

  it->srch_key = start_func;
  if (prg_fp->mem_srch() != 0){Log(false,MSG_209,"#st");}
  else {
    prg = (prgC *)prg_fp->mem_link_ptr_rd();
    start_map = prg->map;
  }

  MEM_LOOP(prg,prgC,prg_fp)
    MEM_LOOP(code,codeC,prg->code_fp)
      if (strcmp(code->code->c_str(),"#jmp") != 0){continue;}
      if (code->call_name != NULL){continue;}
      code->parm[0] += prg->map;
      code->parm[1] += prg->map;
    LOOP_END
  LOOP_END

  MEM_LOOP(code,codeC,link_fp)
    it->srch_key = code->call_name->c_str();
    if (prg_fp->mem_srch() == 0){
      prg = (prgC *)prg_fp->mem_link_ptr_rd();
      code->parm[0] = prg->map;
      code->parm[1] = prg->map;
    }
  LOOP_END

  // 相対ジャンプ未解決マッピング
  MEM_LOOP(jmp,jmpC,jmp_fp)
    jmp->code->parm[2] += jmp->prg->map;
  LOOP_END

  return(true);
}

// ---------------
// #st / #irq_st
// ---------------
void Inf_T::func_code(){
  int size;
  varC *local;

  // ネストチェック
  if (g_prg != NULL){
    if (if_su  != 0) {Log(false,MSG_201,"#if-#endif"  );}
    if (for_su != 0) {Log(false,MSG_202,"#for-#endfor");}
    if_su = 0;
    for_su = 0;
    if (g_prg->irq_flg){codeAdd("#reg_pop",g_prg->irq_level,irq_number-g_prg->irq_level,0,0,0);}
    else               {return_code();}
  }

  g_prg = NULL;
  CSV_LOOP(csvi,ustr,SP_PUSH)
    it->srch_key = (char *)ustr;
    prg_fp->mem_srch();
    g_prg = (prgC *)prg_fp->mem_link_ptr_rd();
    break;
  LOOP_END

  if (g_prg == NULL){Log(false,MSG_209,"#st"); return;}

  // コード生成
  size = 0;
  MEM_LOOP(local,varC,g_prg->local_fp)
    size += local->size;
  LOOP_END
//  if (g_prg->irq_flg){/* codeAdd("#reg_push",g_prg->irq_level,irq_number-g_prg->irq_level,0,0,0); */}
//  else{
    codeAdd("#set",K_val_reg,V_parm_cnt,V_stk_cnt,0   ,g_prg->parm_su);
    codeAdd("#set",K_val_reg,V_stk_cnt ,V_stk_cnt,size,0);
//  }
}


// ---------------
// #set
// ---------------
void Inf_T::set_code(bool flgPtr){
  sChar *w_str;
  codeC *code;
  char *var;

  if (g_prg == NULL){Log(false,MSG_102,"#set"); return;}
  w_str = new sChar("");
  var = NULL;

  CSV_LOOP(csvi,ustr,SP_PUSH)
    if (var == NULL){var = (char *)ustr; continue;}
    w_str->cat((char *)ustr);
  LOOP_END

  // コード生成
  if (flgPtr){calcApi_PtrSet(var,w_str->c_str(),V_val_assign);}
  else       {calcApi_Set   (var,w_str->c_str(),V_val_assign);}

  delete w_str;
}

// ---------------
// #if
// ---------------
void Inf_T::if_code(){
  sChar *w_str;
  codeC *code;

  if (g_prg == NULL){Log(false,MSG_102,"#if"); return;}
  w_str = new sChar("");

  CSV_LOOP(csvi,ustr,SP_PUSH)
    w_str->cat((char *)ustr);
  LOOP_END
  
  // コード生成
  calcApi_If    (w_str->c_str(),V_val_assign);   
  code = codeAdd("#jmp",g_prg->size+1,-1,0,0,0); 
  if_nest_add(code);                        // ネスト制御

  delete w_str;
}

// ---------------
// #else
// ---------------
void Inf_T::else_code(){
  codeC *code;

  if (g_prg == NULL){Log(false,MSG_102,"#else"); return;}
  if (if_su < 1){Log(false,MSG_203,"#else"); return;}

  ifC *wif = getIfCell();
  if (wif == NULL){Log(false,MSG_203,"#else"); return;}
  if (wif->ifKind == 2){Log(false,MSG_203,"#else"); return;}

  wif->svCode->parm[1] = g_prg->size+1;
  wif->ifKind = 2;

  // ifネスト削除
  code = codeAdd("#jmp",-1,-1,0,0,0); // code gen
  wif->svCode = code;
}

// ---------------
// #elseif
// ---------------
void Inf_T::elseif_code(){
  sChar *w_str;
  codeC *code;

  if (g_prg == NULL){Log(false,MSG_102,"#elseif"); return;}
  if (if_su < 1){Log(false,MSG_210,"#elseif"); return;}

  ifC *wif = getIfCell();
  if (wif == NULL){Log(false,MSG_210,"#elseif"); return;}
  if (wif->ifKind == 2){Log(false,MSG_210,"#elseif"); return;}

  w_str = new sChar("");

  CSV_LOOP(csvi,ustr,SP_PUSH)
	w_str->cat((char *)ustr);
  LOOP_END

  // Ver 0.94
  char *w = w_str->c_str();
  if (*w == 0x00) {
	delete w_str;
    Log(false,MSG_210,"#elseif");
	return;
  }


  // elseif 未解決コード追加
  code = codeAdd("#jmp",-1,-1,0,0,0);
  it->alloc_ptr = code;
  wif->code_fp->mem_alloc();

  // コード生成
  wif->svCode->parm[1] = g_prg->size;
  calcApi_If    (w_str->c_str(),V_val_assign);

  code = codeAdd("#jmp",g_prg->size+1,-1,0,0,0);
  wif->svCode = code;
  wif->ifKind = 1;

  delete w_str;

}

// ---------------
// #endif
// ---------------
void Inf_T::endif_code(){
  if (g_prg == NULL){Log(false,MSG_102,"#endif"); return;}
  if (if_su < 1){Log(false,MSG_203,"#endif"); return;}
  if (if_nest_del(g_prg->size) == false){
    Log(false,MSG_203,"#endif"); 
  }
}


/*

// ---------------
// #if
// ---------------
void Inf_T::if_code(){
  sChar *w_str;
  codeC *code;

  if (g_prg == NULL){Log(false,MSG_102,"#if"); return;}
  w_str = new sChar("");

  CSV_LOOP(csvi,ustr,SP_PUSH)
    w_str->cat((char *)ustr);
  LOOP_END
  
  // コード生成
  calcApi_If    (w_str->c_str(),V_val_assign);   
  code = codeAdd("#jmp",g_prg->size+1,-1,0,0,0); 
  if_nest_add(code,true);                        // ネスト制御

  delete w_str;
}

// ---------------
// #else
// ---------------
void Inf_T::else_code(){
  codeC *code;

  if (g_prg == NULL){Log(false,MSG_102,"#else"); return;}
  if (if_su < 1){Log(false,MSG_203,"#else"); return;}
  // ifネスト削除
  if (if_nest_del(g_prg->size+1)==false){Log(false,MSG_204,"#else");}
  code = codeAdd("#jmp",-1,-1,0,0,0); // code gen
  if_nest_add(code,false);            // if nest control
}

// ---------------
// #endif
// ---------------
void Inf_T::endif_code(){
  if (g_prg == NULL){Log(false,MSG_102,"#endif"); return;}
  if (if_su < 1){Log(false,MSG_203,"#endif"); return;}
  if_nest_del(g_prg->size); // ifネスト削除
}

*/

// ---------------
// #for
// ---------------
void Inf_T::for_code(){
  char  *var;
  char  *cnt;
  codeC *code;
  int    sv_loop_ptr;
  char   siki[50];

  var = NULL;
  cnt = NULL;
  if (g_prg == NULL){Log(false,MSG_102,"#for"); return;}

  CSV_LOOP(csvi,ustr,SP_PUSH)
    if (var == NULL){var = (char *)ustr; continue;}
    cnt = (char *)ustr;
    break;
  LOOP_END

  // code gen
  sv_loop_ptr = g_prg->size;
  if (cnt != NULL){
    calcApi_Set(var,"0",V_val_assign);
    sv_loop_ptr = g_prg->size;
    sprintf(siki,"%s < (%s)",var,cnt);
    calcApi_If(siki,V_val_assign);
    code = codeAdd("#jmp",g_prg->size+1,-1,0,0,0);
  }else{
    code = codeAdd("#nop",g_prg->size+1,-1,0,0,0);
  }

  // forネスト加算
  for_nest_add(code,sv_loop_ptr,var);
}


// ---------------
// #break
// ---------------
void Inf_T::break_code(){
  codeC *code;
  if (g_prg == NULL){Log(false,MSG_102,"#break"); return;}
  if (for_su < 1){Log(false,MSG_205,"#break"); return;}
  code = codeAdd("#jmp",-1,-1,0,0,0);   // code add
  break_list_add(code);                 // break list store
}

// ---------------
// #continue
// ---------------
void Inf_T::continue_code(){
  codeC *code;
  forC  *wfor;
  char   siki[50];

  if (g_prg == NULL){Log(false,MSG_102,"#continue"); return;}
  if (for_su < 1){Log(false,MSG_205,"#continue"); return;}

  for_fp->mem_mcb_end_set();
  wfor = (forC *)for_fp->mem_link_ptr_rd();

  // コード生成
  if (wfor->var != NULL){
    sprintf(siki,"%s + 1",wfor->var->c_str());
    calcApi_Set(wfor->var->c_str(),siki,V_val_assign);
  }
  codeAdd("#jmp",wfor->loop_ptr,wfor->loop_ptr,0,0,0);
}

// ---------------
// #endfor
// ---------------
void Inf_T::endfor_code(){
  forC  *wfor;
  char   siki[50];

  if (g_prg == NULL){Log(false,MSG_102,"#endfor"); return;}
  if (for_su < 1){Log(false,MSG_205,"#endfor"); return;}

  for_fp->mem_mcb_end_set();
  wfor = (forC *)for_fp->mem_link_ptr_rd();

  // コード生成
  if (wfor->var != NULL){
    sprintf(siki,"%s + 1",wfor->var->c_str());
    calcApi_Set(wfor->var->c_str(),siki,V_val_assign);
  }
  codeAdd("#jmp",wfor->loop_ptr,wfor->loop_ptr,0,0,0);

  for_nest_del();
}

// ---------------
// #return
// ---------------
void Inf_T::return_code(){
  codeC *code;
  int pop_size;
  varC *local;

  if (g_prg == NULL){Log(false,MSG_102,"#return"); return;}

  pop_size = g_prg->parm_su;
  MEM_LOOP(local,varC,g_prg->local_fp)
    pop_size += local->size;
  LOOP_END

  // コード生成
  codeAdd("#set",K_val_reg ,V_stk_cnt ,V_stk_cnt,0,pop_size+1);
  codeAdd("#set",K_val_preg,V_parm_cnt,V_stk_cnt,0,0);
  codeAdd("#set",K_val_reg ,V_stk_cnt ,V_stk_cnt,0,1);
  codeAdd("#set",K_val_preg,V_prg_cnt ,V_stk_cnt,0,0);
  }


// ---------------
// #do
// ---------------
void Inf_T::call_code(){
  codeC *code,*svCode;
  int parm_su;
  prgC *prg;

  parm_su = 0;
  if (g_prg == NULL){Log(false,MSG_102,"#do"); return;}
  prg = NULL;

  CSV_LOOP(csvi,ustr,SP_PUSH)
    char *str = (char *)ustr;
    if (prg == NULL){
      it->srch_key = str;
      if (prg_fp->mem_srch() != 0){Log(false,MSG_206,"#do"); return;}
      svCode = codeAdd("#set",K_ptr_const ,V_stk_cnt ,-1,0,0);
               codeAdd("#set",K_val_reg   ,V_stk_cnt ,V_stk_cnt ,1,0);
               codeAdd("#set",K_ptr_reg   ,V_stk_cnt ,V_parm_cnt,0,0);
               codeAdd("#set",K_val_reg   ,V_stk_cnt ,V_stk_cnt ,1,0);
      prg = (prgC *)prg_fp->mem_link_ptr_rd();
      prg->parm_fp->mem_mcb_top_set();
      continue;
    }

    ++parm_su;
    if (parm_su > prg->parm_su){Log(false,MSG_208,"#do"); return;}

    // コード生成
    calcApi_Siki(str,V_val_assign);
    codeAdd("#set",K_ptr_reg ,V_stk_cnt ,V_val_assign,0,0);
    codeAdd("#set",K_val_reg ,V_stk_cnt ,V_stk_cnt   ,1,0);
  LOOP_END

  if (prg == NULL){Log(false,MSG_207,"#do"); return;}
  code = codeAdd("#jmp",prg->name->c_str(),0,0);
  svCode->parm[2] = g_prg->size;
  it->alloc_ptr = (MM_PTR_T *)code;
  link_fp->mem_alloc();

  // 未解決コード
  it->alloc_ptr = (MM_PTR_T *)new jmpC(svCode,g_prg);
  jmp_fp->mem_alloc();

  // パラメータチェック
  if (prg->parm_su != parm_su){Log(false,MSG_208,"#do");}
}

// ---------------
// #user
// ---------------
void Inf_T::user_code(){
  char *user_name;
  int   regNo;

  regNo = V_val_assign;
  user_name = NULL;
  if (g_prg == NULL){Log(false,MSG_102,"#user"); return;}
  CSV_LOOP(csvi,ustr,SP_PUSH)
    if (user_name == NULL){user_name = (char *)ustr; continue;}
    calcApi_Siki((char *)ustr,regNo++);    // code gen
  LOOP_END

  codeAdd("#user",(int)SujiConvEx(user_name),V_val_assign,regNo-V_val_assign,0,0);
}

// ---------------
// #printf
// ---------------
void Inf_T::printf_code(){
  char *user_name;
  int   regNo;
  int   prNo;
  printfC *pr;

  regNo = V_val_assign;
  user_name = NULL;
  if (g_prg == NULL){Log(false,MSG_102,"#printf"); return;}
  CSV_LOOP(csvi,ustr,SP_PUSH)
    if (user_name == NULL){user_name = (char *)ustr; continue;}
    calcApi_Siki((char *)ustr,regNo++);    // code gen
  LOOP_END

  it->srch_key = user_name;
  if (printf_fp->mem_srch() == 0){pr = (printfC *)printf_fp->mem_link_ptr_rd();}
  else{
    pr = new printfC(user_name,printf_cnt++,regNo-V_val_assign,V_val_assign);
    it->alloc_ptr = (MM_PTR_T *)pr;
    printf_fp->mem_srch_alloc();
  }

  codeAdd("#printf",pr->prNo,V_val_assign,regNo-V_val_assign,0,0);
}

// ---------------
// #extend
// ---------------
void Inf_T::extend_code(){
  sChar *user_name;
  bool  mode;
  int   regNo;
  int   exNo;
  extendC *ex;

  regNo = V_val_assign;
  user_name = new sChar("");
  mode = true;
  if (g_prg == NULL){Log(false,MSG_102,"#extend"); return;}
  CSV_LOOP(csvi,ustr,SP_PUSH)
    char *str = (char *)ustr;
    if (mode){
      if (strcmp(str,"#") == 0){mode = false; continue;}
      user_name->cat(str);
      user_name->cat(",");
      continue;
    }
    calcApi_Siki(str,regNo++);    // code gen
  LOOP_END

  it->srch_key = user_name->c_str();
  if (extend_fp->mem_srch() == 0){ex = (extendC *)extend_fp->mem_link_ptr_rd();}
  else{
    ex = new extendC(user_name->c_str(),extend_cnt++,regNo-V_val_assign,V_val_assign);
    it->alloc_ptr = (MM_PTR_T *)ex;
    extend_fp->mem_srch_alloc();
  }
  codeAdd("#extend",ex->exNo,V_val_assign,regNo-V_val_assign,0,0);
  delete user_name;
}

