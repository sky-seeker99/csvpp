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
//  Parameter
//

#include <string.h>
#include <stdio.h>
#include "csvparm.h"

// #phead class -----------------
  CsvParm_T::CsvParm_T(MemHeader_T  *p_it,char *p_name){
    name       = new sChar(p_name);
    mem_fp     = new MEM_FP(p_it);
    clm_fp     = new MEM_FP(p_it);
    }

  CsvParm_T::~CsvParm_T(){
    sChar *str;

    delete name;
    MEM_LOOP(str,sChar,mem_fp) delete str; LOOP_END
    delete mem_fp;
    MEM_LOOP(str,sChar,clm_fp) delete str; LOOP_END
    delete clm_fp;
    }

// PaternControlTask Class -----------------
  CsvParmList_T::CsvParmList_T(MemHeader_T  *p_it,Msg_T *p_msg){
    it     = p_it;
    vtp_fp = new MEM_FP(it);
    msg    = p_msg;
    vtp    = NULL;
    }

  CsvParmList_T::~CsvParmList_T(){
    MEM_LOOP(vtp,CsvParm_T ,vtp_fp) delete vtp;  LOOP_END
    delete vtp_fp;
    }

  bool CsvParmList_T::ExistCheck(){if (vtp == NULL){return(false);} return(true);}

// Main Loop
bool CsvParmList_T::CsvRead(CsvAnl_C *csvi) // true:hit false:none hit
  {
  bool flg;
  char *command;

  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  if (strcmp(command,"#p_patern") == 0){flg=true; head_rtn (csvi);}
  if (strcmp(command,"#set"     ) == 0){flg=true; set_rtn  (csvi);}
  return(flg);
  }

// #p_patern
void CsvParmList_T::head_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    it->srch_key = str;
    if (vtp_fp->mem_srch() == 0){vtp = (CsvParm_T *)vtp_fp->mem_link_ptr_rd(); return;}
    vtp = new CsvParm_T(it,str);
    it->alloc_ptr = vtp;
    vtp_fp->mem_srch_alloc();
    return;
    }
  msg->ErrMsg(csvi,E000,0);
  }

// #set
void CsvParmList_T::set_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  sChar *w;
  bool first;
  sChar *clm;

  if (vtp == NULL){msg->ErrMsg(csvi,E081,0); return;}
  w = new sChar(vtp->name->c_str());
  w->cat("_put(");
  first = true;
  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (first == true){first = false;}
    else              {w->cat(",");}
    w->cat(str);
    }
  w->cat(");");
  it->alloc_ptr = (MM_PTR_T *)w;
  vtp->mem_fp->mem_alloc();
  clm = new sChar("");
  clm->set(csvi->getClmMsg(0));
  it->alloc_ptr = (MM_PTR_T *)clm;
  vtp->clm_fp->mem_alloc();
  }


