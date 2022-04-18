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
//  CLASS BUILD LIBRARY
//

#include <stdio.h>
#include <string.h>
#include "xclass.h"

// # Var_B --------
Var_B::Var_B(char *var,char *init) {
  var_name   = new sChar(var);
  init_value = new sChar(init);
  }
Var_B::~Var_B(){
  delete var_name;
  delete init_value;
  }

// # List_B --------
List_B::List_B(MemHeader_T *p_it,char *list) {
  it        = p_it;
  list_name = new sChar(list);
  idx_fp    = new MEM_FP(it);
  var_fp    = new MEM_FP(it);
  }
List_B::~List_B(){
  Var_B     *var;
  delete list_name;
  MEM_LOOP(var,Var_B,idx_fp) delete var; LOOP_END
  MEM_LOOP(var,Var_B,var_fp) delete var; LOOP_END
  delete idx_fp;
  delete var_fp;
  }
bool List_B::IdxStore(char *var){
  it->srch_key = var;
  if (var_fp->mem_srch() == 0){return(false);}
  it->alloc_ptr = (MM_PTR_T *)new Var_B(var,"NULL");
  idx_fp->mem_alloc();
  return(true);
  }
bool List_B::VarStore(char *var,char *init)
  {
  it->srch_key = var;
  if (var_fp->mem_srch() == 0){return(false);}
  it->alloc_ptr = (MM_PTR_T *)new Var_B(var,init);
  var_fp->mem_srch_alloc();
  return(true);
  }

// # Program_C --------
Program_C::Program_C(int p_sel_su,char **p_sel){
  int i;
  sel_su = 0;
  command = 0;
  for(i=0;i<p_sel_su;i++){
    char *w = *(p_sel+i);
    if (*w != 0x00) {
      sel_su=i+1;
    }
  }

//  sel_su = p_sel_su;
  sel    = new char *[sel_su];
  for(i=0;i<sel_su;++i)
    {
    st_ini(*(sel+i),*(p_sel+i));
    }

  if_jump = NULL;

  alias_num = 0;
  alias_addr = NULL;
  for_jump_addr = NULL;

  }
Program_C::~Program_C(){
  int i;
  for(i=0;i<sel_su;++i){
	if (*(sel+i) != (char *)MM_NULL){delete [] *(sel+i);}
  }
  delete [] sel;

  if (if_jump != NULL){
	JumpCell_C *jc;
	ARY_LOOP(jc,JumpCell_C,if_jump) delete jc; LOOP_END
	delete if_jump;
  }


}

char *Program_C::sel_rd(int idx){
  if (idx > sel_su){return(NULL);}
  return(*(sel+idx));
}


void Program_C::storeJump(int kind,McbArea_C *addr){
  JumpCell_C *jc;
  jc = new JumpCell_C(kind,addr);
  if_jump->mem_alloc((unsigned char *)jc);
}

// # Program_B ----------
Program_B::Program_B(MemHeader_T *p_it,char *prg){
  it        = p_it;
  prg_name  = new sChar(prg);
  prg_fp    = new MEM_FP(it);
  var_fp    = new MEM_FP(it);
  }
Program_B::~Program_B(){
  Program_C *prg_c;
  Var_B *var;
  delete prg_name;
  MEM_LOOP(prg_c,Program_C,prg_fp) delete prg_c; LOOP_END
  MEM_LOOP(var,Var_B,var_fp)       delete var;   LOOP_END
  delete prg_fp;
  delete var_fp;
  }
void Program_B::PrgStore(CsvInf_T *csv_fp){
  it->alloc_ptr  = (MM_PTR_T *)new Program_C(csv_fp->CsvSelSu_Rd(),csv_fp->CsvSel_Rd());
  prg_fp->mem_alloc();
  }
bool Program_B::VarStore(char *var,char *init)
  {
  it->srch_key = var;
  if (var_fp->mem_srch() == 0){return(false);}
  it->alloc_ptr = (MM_PTR_T *)new Var_B(var,init);
  var_fp->mem_srch_alloc();
  return(true);
  }

// # Class_T -------
Class_T::Class_T(MemHeader_T *p_it,char *p_class){
  class_name = new sChar(p_class);
  it         = p_it;
  class_fp   = new MEM_FP(it);
  var_fp     = new MEM_FP(it);
  list_fp    = new MEM_FP(it);
  prg_fp     = new MEM_FP(it);
  version_fp = new MEM_FP(it);
  }
Class_T::~Class_T(){
  sChar     *str;
  Var_B     *var;
  List_B    *list;
  Program_B *prg;
  delete class_name;
  MEM_LOOP(str,sChar,class_fp)   delete str;  LOOP_END
  MEM_LOOP(var,Var_B,var_fp)     delete var;  LOOP_END
  MEM_LOOP(list,List_B,list_fp)  delete list; LOOP_END
  MEM_LOOP(prg,Program_B,prg_fp) delete prg;  LOOP_END
  MEM_LOOP(str,sChar,version_fp) delete str;  LOOP_END
  delete prg_fp;
  delete list_fp;
  delete var_fp;
  delete class_fp;
  delete version_fp;
  }

// Keisyo Class Store
bool Class_T::ClassStore(char *cl){
  sChar *str;

  MEM_LOOP(str,sChar,class_fp)
    if (strcmp(str->c_str(),cl) == 0){return(false);}
  LOOP_END
  it->alloc_ptr = (MM_PTR_T *)new sChar(cl);
  class_fp->mem_alloc();
  return(true);
  }

// Simple Variable Store
bool Class_T::VarStore(char *var,char *init){
  it->srch_key = var;
  if (var_fp->mem_srch() == 0){return(false);}
  it->alloc_ptr = (MM_PTR_T *)new Var_B(var,init);
  var_fp->mem_srch_alloc();
  return(true);
  }

// List Store
bool Class_T::ListStore(char *list){
  it->srch_key = list;
  if (list_fp->mem_srch() == 0){return(false);}
  it->alloc_ptr = (MM_PTR_T *)new List_B(it,list);
  list_fp->mem_srch_alloc();
  return(true);
  }

// List->Var Store
bool Class_T::ListVarStore(char *var,char *init){
  List_B *list;
  list = (List_B *)list_fp->mem_link_ptr_rd();
  return(list->VarStore(var,init));
  }

// List->Index Store
bool Class_T::ListIdxStore(char *idx){
  List_B *list;
  list = (List_B *)list_fp->mem_link_ptr_rd();
  return(list->IdxStore(idx));
  }

// Program Store
bool Class_T::PrgStore(char *prg){
  it->srch_key = prg;
  if (prg_fp->mem_srch() == 0){return(false);}
  it->alloc_ptr = (MM_PTR_T *)new Program_B(it,prg);
  prg_fp->mem_srch_alloc();
  return(true);
  }

// Program->Line Store
void Class_T::PrgLineStore(CsvInf_T *csv_fp){
  Program_B *prg;
  prg = (Program_B *)prg_fp->mem_link_ptr_rd();
  prg->PrgStore(csv_fp);
  }

// Program->Var Store
bool Class_T::PrgVarStore(char *var,char *init){
  Program_B *prg;
  prg = (Program_B *)prg_fp->mem_link_ptr_rd();
  return(prg->VarStore(var,init));
  }

// Version Store
void Class_T::VersionStore(CsvInf_T *csv_fp,int cur){
  int max;
  int i;
  char *str;
  sChar *s_str;

  max = csv_fp->CsvSelSu_Rd();

  s_str = new sChar("");
  for(i=cur;i<max;++i)
    {
    if ((str = csv_fp->CsvSel_Rd(i)) == MM_NULL) {continue;}
    s_str->cat(str);
    }

  it->alloc_ptr = (MM_PTR_T *)s_str;
  version_fp->mem_alloc();
  }

// # Classcall_T ------
Classcall_T::Classcall_T(MemHeader_T *p_it,char *p_class,char *obj){
  class_name = new sChar(p_class);
  obj_name   = new sChar(obj);
  it         = p_it;
  prg_fp     = new MEM_FP(it);
  var_fp     = new MEM_FP(it);
  }
Classcall_T::~Classcall_T(){
  Program_C *prg;
  Var_B     *var;
  delete class_name;
  delete obj_name;
  MEM_LOOP(var,Var_B,var_fp) delete var; LOOP_END
  MEM_LOOP(prg,Program_C,prg_fp) delete prg; LOOP_END
  delete var_fp;
  delete prg_fp;
  }

// Program->Line Store
void Classcall_T::PrgLineStore(CsvInf_T *csv_fp){
  it->alloc_ptr  = (MM_PTR_T *)new Program_C(csv_fp->CsvSelSu_Rd(),csv_fp->CsvSel_Rd());
  prg_fp->mem_alloc();
  }

// Simple Variable Store
bool Classcall_T::VarStore(char *var,char *init){
  it->srch_key = var;
  if (var_fp->mem_srch() == 0){return(false);}
  it->alloc_ptr = (MM_PTR_T *)new Var_B(var,init);
  var_fp->mem_srch_alloc();
  return(true);
  }

// # Alias_T ------------------
Alias_T::Alias_T(Program_C *pc){
  int   cnt;
  char *str;
  int   i;
  char *www;
  cnt = 0;
  max = 0;
  alias_name = new sChar("");
  for(i=0;i<pc->sel_su;++i)
    {
    if ((str = pc->sel_rd(i)) == MM_NULL) {continue;}
    if (strcmp(str,"//") == 0){break;}
    if (cnt == 0){++cnt; continue;}
    if (cnt == 1){++cnt; alias_name->set(str); continue;}
    ++max;
    }
  if (max == 0){return;}
  sel = new char *[max];
  cnt = 0;
  for(i=0;i<pc->sel_su;++i)
    {
    if ((str = pc->sel_rd(i)) == MM_NULL) {continue;}
    if (strcmp(str,"//") == 0){break;}
    if (cnt < 2){++cnt; continue;}
    st_ini(www,str);
    *(sel+cnt-2) = www;
    ++cnt;
    }
  }

Alias_T::~Alias_T(){
  int i;
  bool first;
  delete alias_name;
  if (max == 0){return;}
  for(i=0;i<max;++i)
    {
    delete [] *(sel+i);
    }
  delete [] sel;
  }

void Alias_T::Replace(Program_C *pc){
  char **ww;
  int cnt;
  int i,j;
  char *str;
  bool first;
  cnt = 0;
  for(i=0;i<pc->sel_su;++i){++cnt;}
  cnt = cnt - 1 + max;
  ww = new char *[cnt];
  cnt = 0;
  first = true;
  for(i=0;i<pc->sel_su;++i)
    {
    str = pc->sel_rd(i);
    if ((first == true) && (str != MM_NULL))
      {
      for(j=0;j<max;++j,++cnt){st_ini(*(ww+cnt),*(sel+j));}
      first = false;
      continue;
      }
    st_ini(*(ww+cnt),str);
    ++cnt;
    }
  for(i=0;i<pc->sel_su;++i)
    {
    if (*(pc->sel+i) != (char *)MM_NULL)
      {
      delete [] *(pc->sel+i);
      }
    }
  delete [] pc->sel;
  pc->sel_su = cnt;
  pc->sel = ww;
  }

