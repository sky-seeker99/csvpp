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
//  Cycle Task 
//

#include <string.h>
#include <stdio.h>
#include "csvvinf.h"


// #inf class -----------------
CsvInfParm_T::CsvInfParm_T(char *p_name,char *p_size){
  name   = new sChar(p_name);
  size   = new sChar(p_size);
  }
CsvInfParm_T::~CsvInfParm_T(){
  delete name;
  delete size;
  }

// #inf_send/#inf_recv class -----------------
CsvInfSendRecv_T::CsvInfSendRecv_T(MemHeader_T  *p_it,char *p_name,bool p_send){
  name   = new sChar(p_name);
  mem_fp = new MEM_FP(p_it);
  send   = p_send;
  ary    = NULL;
  enable = NULL;
  }
CsvInfSendRecv_T::~CsvInfSendRecv_T(){
  CsvInfParm_T *cip;
  delete name;
  MEM_LOOP(cip,CsvInfParm_T,mem_fp ) delete cip; LOOP_END
  delete mem_fp;
  if (ary != NULL){delete ary;}
  if (enable != NULL){delete enable;}
  }

// Interface Class -----------------
CsvInterface_T::CsvInterface_T(MemHeader_T  *p_it,Msg_T *p_msg){
  it     = p_it;
  mem_fp = new MEM_FP(it);
  msg    = p_msg; 
  inf    = NULL;
  }
CsvInterface_T::~CsvInterface_T(){  
  MEM_LOOP(inf,CsvInfSendRecv_T ,mem_fp) delete inf;  LOOP_END
  delete mem_fp;
  }

// Main Loop
bool CsvInterface_T::CsvRead(CsvAnl_C *csvi,MemHeader_T  *p_it,MEM_FP *in_fp,MEM_FP *out_fp) // true:hit false:none hit
  {
  bool flg;
  char *command;
  
  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  if (strcmp(command,"#inf"       ) == 0){flg=true; inf_rtn       (csvi,p_it,in_fp,out_fp);}
  if (strcmp(command,"#inf_enable") == 0){flg=true; inf_enable_rtn(csvi,p_it,in_fp,out_fp);}
  if (strcmp(command,"#inf_send"  ) == 0){flg=true; inf_rs_rtn    (csvi,p_it,out_fp,true);}
  if (strcmp(command,"#inf_recv"  ) == 0){flg=true; inf_rs_rtn    (csvi,p_it,in_fp,false);}
  return(flg);
  }


// #inf_enable
void CsvInterface_T::inf_enable_rtn(CsvAnl_C *csvi,MemHeader_T  *p_it,MEM_FP *in_fp,MEM_FP *out_fp)
  {
  int i;
  char *str;
  char *name;

  name = NULL;

  if (inf == NULL){msg->ErrMsg(csvi,E100,0); return;}


  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (name == NULL){name = str; break;}
    }

  if (name == NULL){msg->ErrMsg(csvi,E000,0); return;}
  inf->enable = new sChar(name);

  MEM_FP *m;
  if (inf->send)
    {
    m = in_fp;
    }
  else
    {
    m = out_fp;
    }
  p_it->alloc_ptr = (sChar *)new sChar(name);
  m->mem_alloc();
  }



// #inf
void CsvInterface_T::inf_rtn(CsvAnl_C *csvi,MemHeader_T  *p_it,MEM_FP *in_fp,MEM_FP *out_fp)
  {
  int i;
  char *str;
  char *name;
  char *size;

  name = NULL;
  size = NULL;

  if (inf == NULL){msg->ErrMsg(csvi,E100,0); return;}


  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (name == NULL){name = str; continue;}
    if (size == NULL){size = str; break;}
    }

  if (size == NULL){msg->ErrMsg(csvi,E000,0); return;}
  it->alloc_ptr = (CsvInfParm_T *)new CsvInfParm_T(name,size);
  inf->mem_fp->mem_alloc();

  MEM_FP *m;
  if (inf->send)
    {
    m = out_fp;
    }
  else
    {
    m = in_fp;
    }
  p_it->alloc_ptr = (sChar *)new sChar(name);
  m->mem_alloc();  
  }

// #inf_send/#inf_recv
void CsvInterface_T::inf_rs_rtn(CsvAnl_C *csvi,MemHeader_T  *p_it,MEM_FP *inout_fp,bool send)
  {
  int i;
  char *str;
  char *name;
  char *ary;
  name = NULL;
  ary  = NULL;
  
  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (name == NULL){name = str; continue;}
    if (ary  == NULL){ary  = str; break;}
    }

  if (name == NULL){msg->ErrMsg(csvi,E000,0); return;}

  it->srch_key = name;
  if (mem_fp->mem_srch() == 0)
    {
    msg->ErrMsg(csvi,E101,0);
    return;
    }

  inf = new CsvInfSendRecv_T(it,name,send);
  it->alloc_ptr = inf;
  mem_fp->mem_srch_alloc();

  if ((send == false) && (ary != NULL)){
    inf->ary = new sChar(ary);
  }

  p_it->alloc_ptr = (sChar *)new sChar(name);
  inout_fp->mem_alloc();
  }

