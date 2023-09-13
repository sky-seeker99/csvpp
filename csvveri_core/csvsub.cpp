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
//  SubRoutine
//

#include <string.h>
#include <stdio.h>
#include "csvsub.h"

// #if class -----------------
If_T::If_T(MemHeader_T  *it,char *p_str,MM_PTR_T *p_up_ptr){
  str     = new sChar(p_str);
  up_ptr  = p_up_ptr;
  link_fp = new MEM_FP(it);
  next_else = false;
  clm_msg = new sChar("");
  }
If_T::~If_T()
  {
  LinkCell_T *lc;
  MEM_LOOP(lc,LinkCell_T,link_fp) delete lc ; LOOP_END
  delete link_fp;
  delete str;
  delete clm_msg;
  }

// #sub/#event class ---------------------
Sub_T::Sub_T(MemHeader_T  *it,char *p_name,char *p_sub_name){
  name     = new sChar(p_name);
  sub_name = new sChar(p_sub_name);
  parm_fp  = new MEM_FP(it);
  local_fp = new MEM_FP(it);
  dmy_if   = new If_T(it,"",NULL);
  event    = new sChar("");
  opt      = new sChar("");
  clm_msg = new sChar("");
  }
Sub_T::~Sub_T(){
  StParm_T *p;
  MEM_LOOP(p    ,StParm_T  ,parm_fp ) delete p;    LOOP_END
  MEM_LOOP(p    ,StParm_T  ,local_fp) delete p;    LOOP_END
  delete parm_fp;
  delete local_fp;
  delete name;
  delete sub_name;
  delete dmy_if;
  delete event;
  delete opt;
  delete clm_msg;
  }

// Interface -----------------
CsvSub_T::CsvSub_T(MemHeader_T *p_it,Msg_T *p_msg){
  it         = p_it;
  msg        = p_msg;
  sub_fp     = new MEM_FP(it);
  if_fp      = new MEM_FP(it);
  cmd_fp     = new MEM_FP(it);
  g_sub      = NULL;
  g_if       = NULL;
  cur_clm    = 0;
  csvsub_flg = true;
  }
CsvSub_T::~CsvSub_T(){
  Sub_T    *st;
  sChar    *str;
  If_T     *stif;
  MEM_LOOP(st  ,Sub_T,sub_fp  ) delete st;   LOOP_END
  MEM_LOOP(stif,If_T ,if_fp   ) delete stif; LOOP_END
  MEM_LOOP(str ,sChar,cmd_fp  ) delete str;  LOOP_END
  delete sub_fp;
  delete if_fp;
  delete cmd_fp;
  }
bool CsvSub_T::ExistCheck(){if (g_sub == NULL){return(false);}  return(true);}

// Main Loop
bool CsvSub_T::CsvRead(CsvAnl_C *csvi)  // true:hit false:none hit
  {
  bool flg;
  char *command;

  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  cur_clm = 1;

  if (strcmp(command,"#sub"   ) == 0){csvsub_flg = true;}
  if (strcmp(command,"#status") == 0){csvsub_flg = false;}

  if (csvsub_flg == false){return(false);} // csvsub/csvstate select flg
  if (strcmp(command,"#event" ) == 0){flg=true; event_rtn (csvi      );}
  if (strcmp(command,"#option") == 0){flg=true; opt_rtn   (csvi      );}
  if (strcmp(command,"#sub"   ) == 0){flg=true; sub_rtn   (csvi      );}
  if (strcmp(command,"#if"    ) == 0){flg=true; if_rtn    (csvi,true ,false);}
  if (strcmp(command,"#else"  ) == 0){flg=true; if_rtn    (csvi,false,false);}
  if (strcmp(command,"#xelse" ) == 0){flg=true; if_rtn    (csvi,false,true );}
  if (strcmp(command,"#endif" ) == 0){flg=true; endif_rtn (csvi      );}
  if (strcmp(command,"#cmd"   ) == 0){flg=true; cmd_rtn   (csvi      );}
  if (strcmp(command,"#sparm" ) == 0){flg=true; sparm_rtn (csvi      );}
  if (strcmp(command,"#slocal") == 0){flg=true; slocal_rtn(csvi      );}
  return(flg);
  }

// #sub
void CsvSub_T::sub_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *name;
  MEM_FP *mem_fp;

  name = NULL;
  mem_fp = sub_fp;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (name == NULL)
      {
      name = str;
      g_sub = new Sub_T(it,str,"");
      it->alloc_ptr = (MM_PTR_T *)g_sub;
	  g_sub->clm_msg->set(csvi->getClmMsg(i));
      mem_fp->mem_alloc();
      g_if = g_sub->dmy_if;
      continue;
      }
    g_sub->sub_name->set(str);
    return;
    }
  if (name == NULL){msg->ErrMsg(csvi,E000,i);}
  }

// #opt
void CsvSub_T::opt_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  if (g_sub == NULL){msg->ErrMsg(csvi,E020,0); return;}
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	g_sub->opt->set(str);
    return;
    }
  msg->ErrMsg(csvi,E000,i);
  }

// #event
void CsvSub_T::event_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  if (g_sub == NULL){msg->ErrMsg(csvi,E020,0); return;}
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	g_sub->event->set(str);
    return;
    }
  msg->ErrMsg(csvi,E000,i);
  }


// #sparm
void CsvSub_T::sparm_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *name;
  StParm_T *sp;

  if (g_sub == NULL){msg->ErrMsg(csvi,E020,0); return;}
  // main loop
  name = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (name == NULL){name = str; continue;}
    sp = new StParm_T(name,str,"");
    it->alloc_ptr = (MM_PTR_T *)sp;
    sp->clm_msg->set(csvi->getClmMsg(i));
    g_sub->parm_fp->mem_alloc();
    return;
    }
  msg->ErrMsg(csvi,E000,0);
  }

// #slocal
void CsvSub_T::slocal_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *name;
  char *size;
  StParm_T *sp;

  if (g_sub == NULL){msg->ErrMsg(csvi,E020,0); return;}
  // main loop
  name = NULL;
  size = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (name == NULL){name = str; continue;}
    if (size == NULL){size = str; continue;}
    sp = new StParm_T(name,size,str);
    it->alloc_ptr = (MM_PTR_T *)sp;
    sp->clm_msg->set(csvi->getClmMsg(i));
    g_sub->local_fp->mem_alloc();
    return;
    }
  msg->ErrMsg(csvi,E000,0);
  }

// #if/#else
void CsvSub_T::if_rtn(CsvAnl_C *csvi,bool if_kbn,bool line_kbn)  // true:#if false:#else
  {
  int         i;
  char       *str;
  sChar      *ww;
  If_T       *sv_if;
  bool        ok_flg;
  LinkCell_T *lc;

  if (g_if == NULL){msg->ErrMsg(csvi,E005,0); return;}
  if (if_kbn == false)  // #else
    {
    if (line_kbn == false)
      {
      g_if->next_else = true;
      endif_rtn(csvi);
      }
    else
      {
      sv_if = (If_T *)if_fp->mem_link_ptr_rd();
      sv_if->next_else = true;
      }
    }
  if (g_if == NULL){msg->ErrMsg(csvi,E005,0); return;}
  sv_if = g_if;

  ok_flg = false;
  ww = new sChar("");
  if (if_kbn == true)
    {
    for(i=1;i<csvi->CsvSelSu_Rd();++i)
      {
	  str = csvi->CsvSel_Rd(i);
	  if (csvi->blankCheck(str)) {continue;}
	  if (strcmp(str,"#")==0) {break;}
      ww->cat(str);
      ok_flg = true;
      }
    }
  else
    {
    ww->set("#else");
    ok_flg = true;
    i = 1;
    }
  g_if = new If_T(it,ww->c_str(),(MM_PTR_T *)sv_if);
  lc   = new LinkCell_T(StIfKbn,(MM_PTR_T *)g_if);
  it->alloc_ptr = (MM_PTR_T *)g_if;  if_fp->mem_alloc();
  it->alloc_ptr = (MM_PTR_T *)lc;    sv_if->link_fp->mem_alloc();
  g_if->clm_msg->set(csvi->getClmMsg(0));
  lc->clm_msg->set(csvi->getClmMsg(0));
  delete ww;
  if (ok_flg == false){msg->ErrMsg(csvi,E000,i); return;}

  // line if/else check
  for(;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	cur_clm = i+1;
	if (strcmp(str,"#"   )==0)
	  {
	  cmd_rtn(csvi);
	  endif_rtn(csvi);
	  break;
	  }
	}
  }

// #endif
void CsvSub_T::endif_rtn(CsvAnl_C *csvi)
  {
  if (g_if == NULL){msg->ErrMsg(csvi,E005,0); return;}
  if (g_if->up_ptr != NULL){g_if = (If_T *)g_if->up_ptr;}
  else                     {g_if = (If_T *)NULL;}
  }

// #cmd
void CsvSub_T::cmd_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  sChar *ww;
  bool ok_flg;
  LinkCell_T *lc;

  if (g_if == NULL){msg->ErrMsg(csvi,E005,0); return;}
  ww = new sChar("");
  ok_flg = false;
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}

	ww->cat(str);
    ww->cat(" ");
    ok_flg = true;
    }
  lc = new LinkCell_T(StCmdKbn,(MM_PTR_T *)ww);
  lc->clm_msg->set(csvi->getClmMsg(0));
  it->alloc_ptr = (MM_PTR_T *)ww; cmd_fp->mem_alloc();
  it->alloc_ptr = (MM_PTR_T *)lc; g_if->link_fp->mem_alloc();
  if (ok_flg == false){msg->ErrMsg(csvi,E000,i);}
  }

// Space
void CsvSub_T::space(FILE *fp,int level)
  {
  int i;
  for(i=0;i<level;++i){fprintf(fp,"  ");}
  }


