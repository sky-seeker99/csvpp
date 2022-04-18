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
//  OBJECT BUILD LIBRARY
//

#include <stdio.h>
#include <string.h>
#include "xobject.h"

// # AryCell_T  -----------
AryCell_T::AryCell_T(char *p_name,char * p_atai){
  name = new sChar(p_name);
  atai = new sChar(p_atai);
  }
AryCell_T::~AryCell_T(){
  delete name;
  delete atai;
  }

// # VarCell_T ----------
VarCell_T::VarCell_T (MemHeader_T *p_it,char *p_name,char *p_atai)
  {
  it     = p_it;
  name   = new sChar(p_name);
  if ((p_atai == NULL) || (p_atai == (char *)MM_NULL)){atai = new sChar("");}
  else                                                {atai = new sChar(p_atai);}
  ary_fp = new MEM_FP(p_it);
  }
VarCell_T::~VarCell_T()
  {
  AryCell_T *ac;
   MEM_LOOP(ac,AryCell_T,ary_fp)
    delete ac;
  LOOP_END
  delete ary_fp;
  delete name;
  delete atai;
  }
void VarCell_T::AryStore(char *idx,char *atai){
  AryCell_T *ac;
  it->srch_key = idx;
  if (ary_fp->mem_srch() == 0)
    {
    ac = (AryCell_T *)ary_fp->mem_link_ptr_rd();
    ac->atai->set(atai);
    }
  else
    {
    it->alloc_ptr = (unsigned char *)new AryCell_T(idx,atai);
    ary_fp->mem_srch_alloc();
    }
  }

// # ListCell_T ----------
ListCell_T::ListCell_T (MemHeader_T *p_it,List_B *p_lb){
  it     = p_it;
  lb     = p_lb;
  name   = new sChar(p_lb->list_name->c_str());
  idx_fp = new MEM_FP(p_it);
  var_fp = new MEM_FP(p_it);
  }
ListCell_T::~ListCell_T(){
  delete idx_fp;
  delete var_fp;
  delete name;
  }
void ListCell_T::IdxStore(VarCell_T *var){
  it->srch_key = var->name->c_str();
  if (idx_fp->mem_srch() == 0){return;}
  it->alloc_ptr = (unsigned char *)var;
  idx_fp->mem_srch_alloc();
  }
void ListCell_T::VarStore(VarCell_T *var){
  it->srch_key = var->name->c_str();
  if (var_fp->mem_srch() == 0){return;}
  it->alloc_ptr = (unsigned char *)var;
  var_fp->mem_srch_alloc();
  }

// # ListCallCell_T ----------
ListCallCell_T::ListCallCell_T(int p_clm,VarCell_T *p_vc,char *p_init){
  name  = new sChar(p_vc->name);
  clm   = p_clm;
  vc    = p_vc;
  init  = new sChar(p_init);
  }
ListCallCell_T::ListCallCell_T(int p_clm,VarCell_T *p_vc){
  name  = new sChar(p_vc->name);
  clm   = p_clm;
  vc    = p_vc;
  init  = new sChar("");
  }
ListCallCell_T::~ListCallCell_T(){
  delete name;
  delete init;
  }

// # ListCallIdx_T ----------
ListCallIdx_T::ListCallIdx_T(char *p_idx){
  idx_name = new sChar(p_idx);
  cnt      = 0;
  }
ListCallIdx_T::~ListCallIdx_T(){
  delete idx_name;
  }

// # Object_T ----------
Object_T::Object_T (MemHeader_T *p_it,char *p_name){
  name    = new sChar(p_name);
  it      = p_it;
  var_fp  = new MEM_FP(it);
  list_fp = new MEM_FP(it);
  pg_fp   = new MEM_FP(it);
  ov_mode = false;
  }

Object_T::~Object_T(){
  VarCell_T  *vc;
  ListCell_T *lc;
  MEM_LOOP(vc,VarCell_T,var_fp)   delete vc; LOOP_END
  MEM_LOOP(lc,ListCell_T,list_fp) delete lc; LOOP_END
  delete var_fp;
  delete list_fp;
  delete pg_fp;
  delete name;
  }

// Variable Store
void Object_T::VarStore(char *name,char *atai)
    {
    VarCell_T  *vc;
    it->srch_key = name;
    if (var_fp->mem_srch() == 0)
      {
      if (ov_mode == false){return;}
      vc = (VarCell_T *)var_fp->mem_link_ptr_rd();
      vc->atai->set(atai);
      }
    else
      {
      it->alloc_ptr = (unsigned char *)new VarCell_T(it,name,atai);
      var_fp->mem_srch_alloc();
      }
    }

// Variable Array Store
void Object_T::VarAryStore(char *name,char *atai){
  VarCell_T *vc;

  vc = (VarCell_T *)var_fp->mem_link_ptr_rd();
  vc->AryStore(name,atai);
  }

// List Store
bool Object_T::ListStore(List_B *lb){
  it->srch_key = lb->list_name->c_str();
  if (list_fp->mem_srch() == 0){return(false);}
  it->alloc_ptr = (unsigned char *)new ListCell_T(it,lb);
  list_fp->mem_srch_alloc();
  return(true);
  }

// List Index Store
void Object_T::ListIdxStore(VarCell_T *var){
  ListCell_T *lc;

  lc = (ListCell_T *)list_fp->mem_link_ptr_rd();
  lc->IdxStore(var);
  }

// List Variable Store
void Object_T::ListVarStore(VarCell_T *var){
  ListCell_T *lc;

  lc = (ListCell_T *)list_fp->mem_link_ptr_rd();
  lc->VarStore(var);
  }

// Program Store
bool Object_T::PrgStore(Program_B *prg){
  it->srch_key = prg->prg_name->c_str();
  if (pg_fp->mem_srch() == 0){return(false);}
  it->alloc_ptr = (unsigned char *) prg;
  pg_fp->mem_srch_alloc();
  return(true);
  }

// Program Store
void Object_T::VarPrintf()
  {
  VarCell_T *vc;
  MEM_LOOP(vc,VarCell_T,var_fp)
    printf("[%s/%s]\n",vc->name->c_str(),vc->atai->c_str());
  LOOP_END
  }

// # ListCall_T ----------
ListCall_T::ListCall_T (MemHeader_T *p_it,ListCell_T *p_lc){
  lc      = p_lc;
  name    = new sChar(p_lc->name->c_str());
  it      = p_it;
  idx_fp  = new MEM_FP(it);
  var_fp  = new MEM_FP(it);
  cnt_fp  = new MEM_FP(it);
  }
ListCall_T::~ListCall_T(){
  ListCallCell_T *lcc;
  ListCallIdx_T  *lci;
  delete name;
  MEM_LOOP(lcc,ListCallCell_T,idx_fp) delete lcc; LOOP_END
  MEM_LOOP(lcc,ListCallCell_T,var_fp) delete lcc; LOOP_END
  MEM_LOOP(lci,ListCallIdx_T,cnt_fp)  delete lci; LOOP_END
  delete idx_fp;
  delete var_fp;
  delete cnt_fp;
  }

// Index Store
void ListCall_T::IdxStore(int clm,VarCell_T *var)
  {
  it->srch_key  = var->name->c_str();
  it->alloc_ptr = (unsigned char *)new ListCallCell_T(clm,var);
  idx_fp->mem_srch_alloc();
  }

// Var Store
void ListCall_T::VarStore(int clm,VarCell_T *var,char *init)
  {
  it->srch_key  = var->name->c_str();
  it->alloc_ptr = (unsigned char *)new ListCallCell_T(clm,var,init);
  var_fp->mem_srch_alloc();
  }


// # MacCallCell_T ----------
MacCallCell_T::MacCallCell_T (MemHeader_T *p_it,Program_B *p_prg){
  it     = p_it;
  name   = new sChar(p_prg->prg_name);
  prg    = p_prg;
  var_fp = new MEM_FP(p_it);
  }

MacCallCell_T::~MacCallCell_T() {
  ListCallCell_T *llc;
  MEM_LOOP(llc,ListCallCell_T,var_fp) delete llc; LOOP_END
  delete var_fp;
  delete name;
  }

void MacCallCell_T::VarStore(int clm,VarCell_T *var)
  {
  it->alloc_ptr = (unsigned char *)new ListCallCell_T(clm,var);
  var_fp->mem_alloc();
  }

// # FromTo_T ----------
FromTo_T::FromTo_T(McbArea_C *p_from,McbArea_C *p_to){
  from = p_from;
  to   = p_to;
  }

// # IfLvlCell_T ----------
IfLvlCell_T::IfLvlCell_T(MemHeader_T *p_it){
  it     = p_it;
  lvl_fp = new MEM_FP(p_it);
  }
IfLvlCell_T::~IfLvlCell_T(){
  FromTo_T *ft;
  MEM_LOOP(ft,FromTo_T,lvl_fp)
    delete ft;
  LOOP_END
  delete lvl_fp; // 2009.3.9
  }
void IfLvlCell_T::FromToStore(McbArea_C *from,McbArea_C *to){
  it->alloc_ptr = (unsigned char *)new FromTo_T(from,to);
  lvl_fp->mem_alloc();
  }
McbArea_C *IfLvlCell_T::FromToSrch(McbArea_C *cur){
  FromTo_T *ft;
  McbArea_C *sv_ptr;
  MEM_LOOP(ft,FromTo_T,lvl_fp)
    if (ft->from == cur)
      {
      sv_ptr = ft->to;
      delete ft;
      lvl_fp->mem_del();
      return(sv_ptr);
      }
  LOOP_END
  return(MM_NULL);
  }

// # ListFor_T ----------
// %textfor
ListFor_T::ListFor_T(McbArea_C *p_from,McbArea_C *p_to,VarCell_T *p_var,Read64_C *p_fp){
  AryCell_T *ac;
  from    = p_from;
  to      = p_to;
  lc      = (ListCell_T *)MM_NULL;
  cnt     = p_var;
  max     = (VarCell_T *)MM_NULL;
  loop_su = -1;
  mode    = 3;
  fp      = p_fp;
  idx     = new sChar("");   // 2009.3.11
  }
// %aryfor
ListFor_T::ListFor_T(McbArea_C *p_from,McbArea_C *p_to,VarCell_T *p_var,VarCell_T *p_max){
  AryCell_T *ac;
  from    = p_from;
  to      = p_to;
  lc      = (ListCell_T *)MM_NULL;
  cnt     = p_var;
  max     = p_max; // Ver 1.23
  loop_su = -1;
  mode    = 2;
  fp      = NULL;
  cnt->ary_fp->mem_mcb_top_set();
  ac  = (AryCell_T *)cnt->ary_fp->mem_link_ptr_rd();
  if (max != (VarCell_T *)MM_NULL)    // Ver 1.23
    {
    max->atai->set(ac->name->c_str());
    }

  cnt->atai->set(ac->atai->c_str());
  cnt->ary_fp->mem_mcb_next_set();
  if (cnt->ary_fp->mem_mcb_ptr_rd() == MM_NULL)
    {
    idx = new sChar("");
    }
  else
    {
    ac  = (AryCell_T *)cnt->ary_fp->mem_link_ptr_rd();
    idx = new sChar(ac->name->c_str());
    }
  }
// %for
ListFor_T::ListFor_T(McbArea_C *p_from,McbArea_C *p_to,VarCell_T *p_cnt,int p_loop_su){
  from    = p_from;
  to      = p_to;
  lc      = (ListCell_T *)MM_NULL;
  cnt     = p_cnt;
  max     = (VarCell_T *)MM_NULL;
  loop_su = p_loop_su;
  mode    = 1;
  idx     = new sChar("");
  fp      = NULL;
  // Atai Set
  cnt->atai->intset(0);
  }
// %listfor
ListFor_T::ListFor_T(MemHeader_T *it,McbArea_C *p_from,McbArea_C *p_to,ListCell_T *p_lc,VarCell_T *p_cnt,VarCell_T *p_max){
  VarCell_T *vc;
  char w[9];
  sChar *str;
  int  w_int;
  from    = p_from;
  to      = p_to;
  lc      = p_lc;
  cnt     = p_cnt;
  max     = p_max;
  loop_su = 0;
  mode    = 0;
  fp      = NULL;
  // Index Name Make
  idx  = new sChar("");
  MEM_LOOP(vc,VarCell_T,lc->idx_fp)
    idx->cat(vc->atai->c_str());
    idx->cat("_");
  LOOP_END
  // Max Sansyutu
  lc->var_fp->mem_mcb_top_set();
  vc = (VarCell_T *)lc->var_fp->mem_link_ptr_rd();
//  w_int = 0;
  str = new sChar("");
  for(w_int=0;;++w_int)
    {
    str->set(idx->c_str());
    str->intcat(w_int);
    it->srch_key=str->c_str();
    if (vc->ary_fp->mem_srch()!=0){break;}
    }
  delete str;
  // Atai Set
  cnt->atai->intset(0);
  max->atai->intset(w_int);
  }

ListFor_T::~ListFor_T(){
  delete idx;
//  if (fp != NULL){fclose(fp);}
  if (fp != NULL){delete fp;}
  }


// # ForLvlCell_T ----------
ForLvlCell_T::ForLvlCell_T(MemHeader_T *p_it){
  it     = p_it;
  lvl_fp = new MEM_FP(p_it);
  }
ForLvlCell_T::~ForLvlCell_T(){
  ListFor_T *lf;
  MEM_LOOP(lf,ListFor_T,lvl_fp)
    delete lf;
  LOOP_END
  delete lvl_fp;  // 2009.3.9
  }
bool ForLvlCell_T::CntUp(ListFor_T *lf)
  {
  int i;
  AryCell_T *ac;
  char *buff;
  int len;

  if (lf->mode == 3) // %textfor
	{
	if ((buff = lf->fp->read()) == NULL){return(true);}

	len = strlen(buff);
	for(i=len-1;i>=0;--i)
	  {
	  if (*(buff+i) >= ' '){break;}
	  *(buff+i) = 0x00;
	  }
	lf->cnt->atai->set(buff);
	return(false);
	}

  if (lf->mode == 2) // %aryfor
    {
    if (strcmp(lf->idx->c_str(),"")==0){return(true);}
    it->srch_key = lf->idx->c_str();
    if (lf->cnt->ary_fp->mem_srch() != 0){return(true);}
    ac = (AryCell_T *)lf->cnt->ary_fp->mem_link_ptr_rd();
    lf->cnt->atai->set(ac->atai->c_str());

    if (lf->max != (VarCell_T *)MM_NULL)    // Ver 1.23
      {
      lf->max->atai->set(ac->name->c_str());
      }

    lf->cnt->ary_fp->mem_mcb_next_set();
    if (lf->cnt->ary_fp->mem_mcb_ptr_rd() == MM_NULL){lf->idx->set("");}
    else
      {
      ac  = (AryCell_T *)lf->cnt->ary_fp->mem_link_ptr_rd();
      lf->idx->set(ac->name->c_str());
      }
    return(false);
    }
//  i = lf->cnt->atai->c_int();
  i = SujiConvEx(lf->cnt->atai->c_str());
  ++i;
  if (lf->mode == 0) // %listfor
    {
//    if (i >= lf->max->atai->c_int()) {return(true);}
    if (i >= SujiConvEx(lf->max->atai->c_str())) {return(true);}
    }
  else               // %for
    {
    if (i >= lf->loop_su){return(true);}
    }
  lf->cnt->atai->intset(i);
  return(false);
  }
void ForLvlCell_T::AryRead(ListFor_T *lf)
  {
  sChar *ww;
  VarCell_T *vc;
  Var_B *vb;
  AryCell_T *ac;
  ww = new sChar(lf->idx);
  ww->cat(lf->cnt->atai->c_str());
  it->srch_key = ww->c_str();
  MEM_LOOP(vc,VarCell_T,lf->lc->var_fp)
    if (vc->ary_fp->mem_srch() != 0)
      {
      vc->atai->set("");
      if (lf->lc->lb->var_fp->mem_srch() == 0)
        {
        vb = (Var_B *)lf->lc->lb->var_fp->mem_link_ptr_rd();
        vc->atai->set(vb->init_value);
        }
      continue;
      }
    ac = (AryCell_T *)vc->ary_fp->mem_link_ptr_rd();
    vc->atai->set(ac->atai->c_str());
  LOOP_END
  delete ww;
  }

McbArea_C *ForLvlCell_T::ListForSrch(McbArea_C *cur){
  ListFor_T *lf;
  sChar     *ww;
  VarCell_T *vc;
  Var_B     *vb;
  AryCell_T *ac;
  MEM_LOOP(lf,ListFor_T,lvl_fp)
    if (lf->from == cur)
      {
      if (CntUp(lf) == false)
        {
        if (lf->mode == 0){AryRead(lf);}
        return(lf->to);
        }
      delete lf;
      lvl_fp->mem_del();
      return(MM_NULL);
      }
  LOOP_END
  return(MM_NULL);
  }

// %listfor
bool ForLvlCell_T::ListForStore(McbArea_C *from,McbArea_C *to,ListCell_T *lc,VarCell_T *cnt,VarCell_T *max){
  ListFor_T *lf;
  lf = new ListFor_T(it,from,to,lc,cnt,max);
  if (SujiConvEx(max->atai->c_str()) == 0){delete lf; return(false);}
  it->alloc_ptr = (unsigned char *)lf;
  lvl_fp->mem_alloc();
  return(true);
  }

// %for
bool ForLvlCell_T::ListForStore(McbArea_C *from,McbArea_C *to,VarCell_T *cnt,int loop_su){
  ListFor_T *lf;
  if (loop_su == 0){return(false);}
  lf = new ListFor_T(from,to,cnt,loop_su);
  it->alloc_ptr = (unsigned char *)lf;
  lvl_fp->mem_alloc();
  return(true);
  }

// %aryfor
bool ForLvlCell_T::ListForStore(McbArea_C *from,McbArea_C *to,VarCell_T *cnt,VarCell_T *max){  // Ver 1.23
  ListFor_T *lf;
  if (cnt->ary_fp->mem_mcb_top_rd() == MM_NULL){return(false);}
  lf = new ListFor_T(from,to,cnt,max); // Ver 1.23
  it->alloc_ptr = (unsigned char *)lf;
  lvl_fp->mem_alloc();
  return(true);
  }

// %textfor
bool ForLvlCell_T::ListForStore(McbArea_C *from,McbArea_C *to,VarCell_T *cnt,char *file_name){
  ListFor_T *lf;
/*
  FILE *fp;
  fp = fopen(file_name,"rt");
  if (fp == NULL){return(false);}
*/
  Read64_C *fp = new Read64_C(file_name,"rt",10240);
  if (fp->okCheck() == false) {
	delete fp;
	return(false);  
  }

  lf = new ListFor_T(from,to,cnt,fp);
  it->alloc_ptr = (unsigned char *)lf;
  lvl_fp->mem_alloc();
  return(true);
  }


