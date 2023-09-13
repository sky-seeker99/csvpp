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
#include "csvtask.h"

// #tparm class -----------------
CsvCycParm_T::CsvCycParm_T(char *p_name,char *p_size,char *p_init){
  name   = new sChar(p_name);
  size   = new sChar(p_size);
  init   = new sChar(p_init);
  }
CsvCycParm_T::~CsvCycParm_T(){
  delete name;
  delete size;
  delete init;
  }

// #tchg class -----------------
CsvCycChg_T::CsvCycChg_T(char *p_name,char *p_cyc,char *p_val){
  name   = new sChar(p_name);
  cyc    = new sChar(p_cyc);
  val    = new sChar(p_val);
  }
CsvCycChg_T::~CsvCycChg_T(){
  delete name;
  delete cyc;
  delete val;
  }

// #task class -----------------
CsvCycTask_T::CsvCycTask_T(MemHeader_T  *p_it,int p_kbn,bool p_init,char *p_name,char *p_clk,char *p_tcnt,char *p_wcnt,char *p_ccnt){
  name   = new sChar(p_name);
  clk    = new sChar(p_clk);
  tcnt   = new sChar(p_tcnt);
  wcnt   = new sChar(p_wcnt);
  ccnt   = new sChar(p_ccnt);
  cmd_fp = new MEM_FP(p_it);
  chg_fp = new MEM_FP(p_it);
  parm_fp= new MEM_FP(p_it);
  local_fp= new MEM_FP(p_it);
  kbn    = p_kbn;
  init   = p_init;
  }
CsvCycTask_T::~CsvCycTask_T(){
  sChar *str;
  CsvCycChg_T *vc;
  CsvCycParm_T *p;
  delete name;
  delete clk;
  delete tcnt;
  delete wcnt;
  delete ccnt;
  MEM_LOOP(str,sChar      ,cmd_fp ) delete str; LOOP_END
  MEM_LOOP(vc ,CsvCycChg_T ,chg_fp ) delete vc;  LOOP_END
  MEM_LOOP(p  ,CsvCycParm_T,parm_fp) delete p;   LOOP_END
  MEM_LOOP(p  ,CsvCycParm_T,local_fp) delete p;   LOOP_END
  delete chg_fp;
  delete parm_fp;
  delete cmd_fp;
  delete local_fp;
  }

// CycTaskControlTask Class -----------------
CsvCycTaskList_T::CsvCycTaskList_T(MemHeader_T  *p_it,Msg_T *p_msg){
  it     = p_it;
  vct_fp = new MEM_FP(it);
  msg    = p_msg;
  vct    = NULL;
  ssc        = new StrSrchInf_T();
  ssc->Set(':');
  grep   = new  sCharGrep("");
  }
CsvCycTaskList_T::~CsvCycTaskList_T(){
  MEM_LOOP(vct,CsvCycTask_T ,vct_fp) delete vct;  LOOP_END
  delete vct_fp;
  delete ssc;
  delete grep;
  }
bool CsvCycTaskList_T::ExistCheck(){if (vct == NULL){return(false);} return(true);}

// Main Loop
bool CsvCycTaskList_T::CsvRead(CsvAnl_C *csvi) // true:hit false:none hit
  {
  bool flg;
  char *command;
  
  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  if (strcmp(command,"#task"    ) == 0){flg=true; task_rtn(csvi,0,false);}
  if (strcmp(command,"#taskn"   ) == 0){flg=true; task_rtn(csvi,1,false);}
  if (strcmp(command,"#taskx"   ) == 0){flg=true; task_rtn(csvi,2,false);}
  if (strcmp(command,"#init"    ) == 0){flg=true; task_rtn(csvi,0,true);}
  if (strcmp(command,"#initn"   ) == 0){flg=true; task_rtn(csvi,1,true);}
  if (strcmp(command,"#initx"   ) == 0){flg=true; task_rtn(csvi,2,true);}
  if (strcmp(command,"#tcmd"    ) == 0){flg=true; tcmd_rtn(csvi);}
  if (strcmp(command,"#tchg"    ) == 0){flg=true; tchg_rtn(csvi);}
  if (strcmp(command,"#tparm"   ) == 0){flg=true; tparm_rtn(csvi);}
  if (strcmp(command,"#tlocal"  ) == 0){flg=true; tlocal_rtn(csvi);}
  if (strcmp(command,"#tdiff"   ) == 0){flg=true; tdiff_rtn(csvi,false);}
  if (strcmp(command,"#tdiffplus")== 0){flg=true; tdiff_rtn(csvi,true);}
  return(flg);
  }
    
// #task
void CsvCycTaskList_T::task_rtn(CsvAnl_C *csvi,int kbn,bool init)
  {
  int i;
  int cnt;
  char *str;
  char *name;
  char *clk;
  char *tcnt;
  char *wcnt;
  char *ccnt;

  // main loop
  cnt = 0;
  name = NULL;
  clk  = NULL;
  tcnt = NULL;
  wcnt = NULL;
  ccnt = NULL;

  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}

	if (cnt == 0)
      {
      ++cnt;
      name = str;
      it->srch_key = name;
      if (vct_fp->mem_srch() == 0){msg->ErrMsg(csvi,E060,0); return;}
      continue;
      }
    if (cnt == 1){++cnt; clk  = str; continue;}
    if (cnt == 2){++cnt; tcnt = str; continue;}
    if (cnt == 3){++cnt; wcnt = str; continue;}
    if (cnt == 4){       ccnt = str; break;   }
    }

  for(;;)
    {
    if (ccnt != NULL){vct = new CsvCycTask_T(it,kbn,init,name,clk,tcnt,wcnt,ccnt); break;}
    if (wcnt != NULL){vct = new CsvCycTask_T(it,kbn,init,name,clk,tcnt,wcnt,""  ); break;}
    if (tcnt != NULL){vct = new CsvCycTask_T(it,kbn,init,name,clk,tcnt,""  ,""  ); break;}
    if (clk  != NULL){vct = new CsvCycTask_T(it,kbn,init,name,clk,""  ,""  ,""  ); break;}
    msg->ErrMsg(csvi,E000,0);
    return;
    }  
  
  it->alloc_ptr = vct;
  vct_fp->mem_srch_alloc();
  }

// #tcmd
void CsvCycTaskList_T::tcmd_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  sChar *cmd;

  if (vct == NULL){msg->ErrMsg(csvi,E061,0); return;}
  cmd = new sChar("");
  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}

	cmd->cat(str);
    cmd->cat(" ");
    }
  if (strcmp(cmd->c_str(),"")!=0){it->alloc_ptr = cmd; vct->cmd_fp->mem_alloc();}  
  else                           {delete cmd;}
  }

// #tchg
void CsvCycTaskList_T::tchg_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *line;
  CsvCycChg_T *chg;
  sChar *cyc;
  sChar *val;

  if (vct == NULL){msg->ErrMsg(csvi,E061,0); return;}
  line = NULL;
  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}

	if (line == NULL){line = str; continue;}
    ssc->Main(str);
    if (ssc->GetSu() < 2){msg->ErrMsg(csvi,E000,i); return;}
    cyc = ssc->Get(0);
    val = ssc->Get(1);
    it->alloc_ptr = new CsvCycChg_T(line,cyc->c_str(),val->c_str());
    vct->chg_fp->mem_alloc();
    }
  }

// #tdiff
void CsvCycTaskList_T::tdiff_rtn(CsvAnl_C *csvi,bool plus)
  {
  int i;
  char *str;

  if (vct == NULL){msg->ErrMsg(csvi,E061,0); return;}
  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}

	if (plus == true){it->alloc_ptr = new CsvCycChg_T("#diffplus","",str);}
    else             {it->alloc_ptr = new CsvCycChg_T("#diff","",str);}
    vct->chg_fp->mem_alloc();
    }
  }

// #tparm
void CsvCycTaskList_T::tparm_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *name;

  if (vct == NULL){msg->ErrMsg(csvi,E061,0); return;}
  // main loop
  name = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}

	if (name == NULL){name = str; continue;}
    it->alloc_ptr = new CsvCycParm_T(name,str,"");
    vct->parm_fp->mem_alloc();
    return;
    }
  msg->ErrMsg(csvi,E000,0);
  }

// #tlocal
void CsvCycTaskList_T::tlocal_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *name;
  char *size;

  if (vct == NULL){msg->ErrMsg(csvi,E061,0); return;}
  // main loop
  name = NULL;
  size = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}

	if (name == NULL){name = str; continue;}
    if (size == NULL){size = str; continue;}
    it->alloc_ptr = new CsvCycParm_T(name,size,str);
    vct->local_fp->mem_alloc();
    return;
    }
  msg->ErrMsg(csvi,E000,0);
  }

// column
void CsvCycTaskList_T::space(FILE *fp,int max)
  {
  int i;
  for(i=0;i<max;++i){fprintf(fp,"  ");}
  }

// @L,@P Change
void CsvCycTaskList_T::rep(sChar *str)
  {
  sChar *local;
  sChar *parm;
  grep->set(str->c_str());
  grep->replace_all("@L","");
  grep->replace_all("@P","");
  str->set(grep->c_str());
  }



