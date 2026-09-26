/*
 * Copyright 2026 Shigeru Kasuya
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by me or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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


