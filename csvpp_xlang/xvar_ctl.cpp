/*

 * Copyright (c) 2011 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
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

#include <stdio.h>
#include <string.h>
#include "xvar_ctl.h"

// - Del -----
void varCtl_C::del(){
  varCrlCell_C *w = stack_fp->pop();
  VarCell_T *vc;
  AryCell_T *ac;
  if (w != NULL) {
    stack_dust_fp->push(w);
    if (w->local) {
      LIST_LOOP(vc,VarCell_T,w->var_fp)
        var_dust_fp->mem_alloc(vc);
        MEM_LOOP(ac,AryCell_T,vc->ary_fp)
          delete ac;
        LOOP_END
        vc->ary_fp->mem_del_all();
      LOOP_END
    }
    w->var_fp->mem_del_all();
  }
}

// - Add -----
void varCtl_C::add(){
  varCrlCell_C *w = stack_dust_fp->pop();
  if (w == NULL) {w = new varCrlCell_C(it);}
  stack_fp->push(w);
}

// - current Get -----
varCrlCell_C *varCtl_C::getCurrent(){
  varCrlCell_C *w = stack_fp->check();
}


// - Variable Search ------
VarCell_T *varCtl_C::srch(char *p_key){
  char *key = p_key;
  int i;
  if (*key == '*'){
    VarCell_T *vc = srch(key+1);
    if (vc == NULL){return(NULL);}
    key = vc->atai->c_str();
  }

  VarCell_T *vc=NULL;
  for(i=stack_fp->getStorePtr()-1-offset;i>=0;i--){
    varCrlCell_C *wc = stack_fp->get(i);
    it->srch_key = key;
    if (wc->var_fp->mem_srch() != 0) {continue;}
    vc = wc->var_fp->mem_link_ptr_rd();
    break;
  }

#ifdef VAR_CTL_DEBUG
  printf("srch vc=%p name=%s str=%d\n",vc,p_key,i);
#endif

  return(vc);
}

// - Variable Search (local)------
VarCell_T *varCtl_C::srchLocal(char *p_key){
  char *key = p_key;
  if (*key == '*'){
    VarCell_T *vc = srch(key+1);
    if (vc == NULL){return(NULL);}
    key = vc->atai->c_str();
  }

  int num = stack_fp->getStorePtr()-1;
  if (num < 0){return(NULL);}
  varCrlCell_C *wc = stack_fp->get(num);
  it->srch_key = key;

  VarCell_T *vc=NULL;
  if (wc->var_fp->mem_srch() == 0) {vc = wc->var_fp->mem_link_ptr_rd();}
  return(vc);
}


// - Variable Search Store (local) ------
VarCell_T *varCtl_C::srchStoreLocal(char *var,char *init){
  VarCell_T *vc = srchLocal(var);
  if (vc == NULL){vc = store(var,init);}
  else {
    vc->atai->set(init);
  }
  return(vc);
}

// - Variable Search Store ------
VarCell_T *varCtl_C::srchStore(char *var,char *init){
  VarCell_T *vc = srch(var);
  if (vc == NULL){vc = store(var,init);}
  else {
    vc->atai->set(init);
  }
#ifdef VAR_CTL_DEBUG
  printf("vc=%p name=%s value=%s\n",vc,var,init);
#endif

  return(vc);
}


// - Variable Store (local) ------
VarCell_T *varCtl_C::store(char *var,char *init){
  varCrlCell_C *w = getCurrent();
  if (w == NULL){return(NULL);}
  w->local = true;
  it->srch_key = var;
  if (w->var_fp->mem_srch() == 0){return(NULL);}

  VarCell_T *v = var_dust_fp->pop();
  if (v == NULL){
    v = new VarCell_T(old_it,var,init);
  }
  else {
    v->name->set(var);
    v->atai->set(init);
  }
  it->alloc_ptr = v;
  w->var_fp->mem_srch_alloc();
  return(v);
}


// - Variable Store (not local) ------
VarCell_T *varCtl_C::store(VarCell_T *vc){
  varCrlCell_C *w = getCurrent();
  if (w == NULL){return(NULL);}
  w->local = false;
  it->srch_key = vc->name->c_str();
  if (w->var_fp->mem_srch() == 0){return(NULL);}
  it->alloc_ptr = vc;
  w->var_fp->mem_srch_alloc();
  return(vc);
}

