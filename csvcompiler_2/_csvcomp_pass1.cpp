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
//  CSV COMPILER PASS1(#type,#member)
//  ・変数のタイプのトークン解析とタイプの登録
//  ・変数のタイプ内のメンバのトークン解析とタイプ内のメンバの登録
//

// ---------------
// Command Check
// ---------------
bool Inf_T::cmdCheck(char *str)
  {
  if (strcmp(str,"#st"      ) == 0){return(true);}
  if (strcmp(str,"#irq_st"  ) == 0){return(true);}
  if (strcmp(str,"#set"     ) == 0){return(true);}
  if (strcmp(str,"#ptr"     ) == 0){return(true);}
  if (strcmp(str,"#if"      ) == 0){return(true);}
  if (strcmp(str,"#else"    ) == 0){return(true);}
  if (strcmp(str,"#elseif"  ) == 0){return(true);}
  if (strcmp(str,"#endif"   ) == 0){return(true);}
  if (strcmp(str,"#for"     ) == 0){return(true);}
  if (strcmp(str,"#endfor"  ) == 0){return(true);}
  if (strcmp(str,"#continue") == 0){return(true);}
  if (strcmp(str,"#break"   ) == 0){return(true);}
  if (strcmp(str,"#return"  ) == 0){return(true);}
  if (strcmp(str,"#do"      ) == 0){return(true);}
  if (strcmp(str,"#user"    ) == 0){return(true);}
  if (strcmp(str,"#printf"  ) == 0){return(true);}
  if (strcmp(str,"#type"    ) == 0){return(true);}
  if (strcmp(str,"#extend"  ) == 0){return(true);}
  if (strcmp(str,"#member"  ) == 0){return(true);}
  if (strcmp(str,"#global"  ) == 0){return(true);}
  if (strcmp(str,"#local"   ) == 0){return(true);}
  if (strcmp(str,"#parm"    ) == 0){return(true);}
  return(false);
  }


// ---------------
// Pass 1 Main
// ---------------
bool Inf_T::Pass1(Read64_C *in_fp){
  in_fp->seek((__int64)0);
  printf(" pass1(#type,#member check).\n");
  for(line_cnt=0;;++line_cnt){
    unsigned char *buff = in_fp->read();
    if (buff == NULL){break;}
    csvi->Exec(buff);
    CSV_LOOP(csvi,ustr,SP_PUSH)
      char *str = (char*)ustr;
      if (cmdCheck(str) == false){Log(false,MSG_000,str);}
      else if (strcmp(str,"#type"   )==0) {type_rtn   ();}
      else if (strcmp(str,"#member" )==0) {member_rtn ();}
      break;
    LOOP_END
  }
  return(true);
}

// ---------------
// #type
// ---------------
void Inf_T::type_rtn(){
  CSV_LOOP(csvi,ustr,SP_PUSH)
    it->srch_key = (char *)ustr;
    if (typ_fp->mem_srch() == 0){Log(false,MSG_001,"#type"); return;}
    g_typ = new typC(it,(char *)ustr);
    it->alloc_ptr = (MM_PTR_T *)g_typ;
    typ_fp->mem_srch_alloc();
    break;
  LOOP_END
}

// ---------------
// #member
// ---------------
void Inf_T::member_rtn(){
  char *type_name;
  char *var_name;
  int   ary_su;
  typC *w_typ;
  bool  flgPtr;

  if (g_typ == NULL){Log(false,MSG_002,"#member"); return;}
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
  
  if (type_name == NULL){Log(false,MSG_002,"#member"); return;}
  if (var_name  == NULL){Log(false,MSG_003,"#member"); return;}
  if (ary_su    <  1   ){Log(false,MSG_004,"#member"); return;}

  if (strcmp(type_name,"int") == 0){w_typ = NULL;}
  else {
    it->srch_key = type_name;
    if (typ_fp->mem_srch() != 0){Log(false,MSG_001,"#member"); return;}
    w_typ = (typC *)typ_fp->mem_link_ptr_rd();
    if (w_typ == g_typ){Log(false,MSG_006,"#member"); return;}
  }

  if (*var_name == '@'){it->srch_key = var_name+1; flgPtr = true;}
  else                 {it->srch_key = var_name;   flgPtr = false;}
  if (g_typ->member_fp->mem_srch() == 0){Log(false,MSG_005,"#member"); return;}
  it->alloc_ptr = (MM_PTR_T *)new memberC(it->srch_key,ary_su,w_typ,flgPtr);
  g_typ->member_fp->mem_srch_alloc();
}


