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

