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
//  Patern
//

#include <string.h>
#include <stdio.h>
#include "csvptn.h"

// #var class -----------------
Var_T::Var_T(char *p_name,char *p_size){
  name   = new sChar(p_name);
  size   = new sChar(p_size);
  clm_msg = new sChar("");
  }
Var_T::~Var_T(){
  delete name;
  delete size;
  delete clm_msg;
  }

// #patern class -----------------
CsvPtn_T::CsvPtn_T(MemHeader_T  *p_it,char *p_name){
  name       = new sChar(p_name);
  var_fp     = new MEM_FP(p_it);
  ary_max    = new sChar("200");
  end_rtn    = new sChar("");
  clm_msg    = new sChar("");
  }
CsvPtn_T::~CsvPtn_T(){
  Var_T *var;
  delete name;
  delete ary_max;
  MEM_LOOP(var,Var_T,var_fp) delete var; LOOP_END
  delete var_fp;
  delete end_rtn;
  delete clm_msg;
  }

// PaternControlTask Class -----------------
CsvPtnList_T::CsvPtnList_T(MemHeader_T  *p_it,Msg_T *p_msg){
  it     = p_it;
  vtp_fp = new MEM_FP(it);
  msg    = p_msg;
  vtp    = NULL;
  }
CsvPtnList_T::~CsvPtnList_T(){
  MEM_LOOP(vtp,CsvPtn_T ,vtp_fp) delete vtp;  LOOP_END
  delete vtp_fp;
  }
bool CsvPtnList_T::ExistCheck(){if (vtp == NULL){return(false);} return(true);}

// Main Loop
bool CsvPtnList_T::CsvRead(CsvAnl_C *csvi) // true:hit false:none hit
  {
  bool flg;
  char *command;

  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  if (strcmp(command,"#patern") == 0){flg=true; head_rtn  (csvi);}
  if (strcmp(command,"#var"   ) == 0){flg=true; var_rtn   (csvi);}
  if (strcmp(command,"#arymax") == 0){flg=true; arymax_rtn(csvi);}
  if (strcmp(command,"#endrtn") == 0){flg=true; endrtn_rtn(csvi);}
  return(flg);
  }

// #patern
void CsvPtnList_T::head_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    it->srch_key = str;
    if (vtp_fp->mem_srch() == 0){vtp = (CsvPtn_T *)vtp_fp->mem_link_ptr_rd(); return;}
    vtp = new CsvPtn_T(it,str);
	vtp->clm_msg->set(csvi->getClmMsg(i));
	it->alloc_ptr = vtp;
    vtp_fp->mem_srch_alloc();
    return;
    }
  msg->ErrMsg(csvi,E000,0);
  }

// #var
void CsvPtnList_T::var_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *name;
  Var_T *var;

  if (vtp == NULL){msg->ErrMsg(csvi,E080,0); return;}
  // main loop
  name = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (name == NULL){name = str; continue;}
    var = new Var_T(name,str);
    var->clm_msg->set(csvi->getClmMsg(i));
    it->alloc_ptr = (MM_PTR_T *)var;
    vtp->var_fp->mem_alloc();
    return;
    }
  msg->ErrMsg(csvi,E000,0);
  }

// #arymax
void CsvPtnList_T::arymax_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  if (vtp == NULL){msg->ErrMsg(csvi,E080,0); return;}
  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    vtp->ary_max->set(str);
    return;
    }
  msg->ErrMsg(csvi,E000,0);
  }

// #endrtn
void CsvPtnList_T::endrtn_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  if (vtp == NULL){msg->ErrMsg(csvi,E080,0); return;}
  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    vtp->end_rtn->set(str);
    return;
    }
  msg->ErrMsg(csvi,E000,0);
  }



