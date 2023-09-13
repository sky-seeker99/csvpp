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
//  State Machine
//  1.01:#act,#stop ’Ç‰Á
//

#include "csvstate.h"

// change command list cell information (Ver 1.01)------
ChgCmdCell_T::ChgCmdCell_T(char *p_cmd,int p_no){
  cmd = new sChar(p_cmd);
  no  = p_no;
  }
ChgCmdCell_T::~ChgCmdCell_T(){
  delete cmd;
  }

// clock list information (Ver 1.01)------
ChgClkList_T::ChgClkList_T(char *p_clk) {
  clk  = new sChar(p_clk);
  }
ChgClkList_T::~ChgClkList_T(){
  delete clk;
  }

// line change list information (Ver 1.01)------
ChgLineList_T::ChgLineList_T(char *p_clk,char *p_line,int p_line_no) {
  clk        = new sChar(p_clk);
  line       = new sChar(p_line);
  line_no    = p_line_no;
  name       = new sChar(p_clk);
  name->cat("_");
  name->cat(p_line);
  size       = 32;
  }
ChgLineList_T::~ChgLineList_T(){
  delete clk;
  delete line;
  delete name;
  }

// change command list information (Ver 1.01)------
ChgCmdList_T::ChgCmdList_T(MemHeader_T *p_it,char *p_clk){
  cmd_fp = new MEM_FP(p_it);
  clk    = new sChar(p_clk);
  cmd_no = 0;
  }
ChgCmdList_T::~ChgCmdList_T(){
  ChgCmdCell_T *ccc;
  MEM_LOOP(ccc,ChgCmdCell_T,cmd_fp) delete ccc; LOOP_END
  delete clk;
  delete cmd_fp;
  }

// #sparm/#slocal class -----------------
StParm_T::StParm_T(char *p_name,char *p_size,char *p_init){
  name   = new sChar(p_name);
  size   = new sChar(p_size);
  init   = new sChar(p_init);
  clm_msg = new sChar("");
  }
StParm_T::~StParm_T(){
  delete name;
  delete size;
  delete init;
  delete clm_msg;
  }

// value set class ------
ValChg_T::ValChg_T(char *p_name,char *p_val,char *p_cyc){
  name = new sChar(p_name);
  val  = new sChar(p_val);
  cyc  = new sChar(p_cyc);
  }
ValChg_T::~ValChg_T(){
  delete name;
  delete val;
  delete cyc;
  }

// change information------
Chg_T::Chg_T(MemHeader_T  *it,char *p_clk,int p_chg_cnt_no){
  clk        = new sChar(p_clk);
  val_fp     = new MEM_FP(it);
  chg_cnt_no = p_chg_cnt_no;
  clm_msg    = new sChar("");
  }
Chg_T::~Chg_T(){
  ValChg_T *val;
  delete clk;
  MEM_LOOP(val,ValChg_T,val_fp) delete val; LOOP_END
  delete val_fp;
  delete clm_msg;
  }

// linking cell ------------------
LinkCell_T::LinkCell_T(int p_kbn,MM_PTR_T *p_ptr)
  {
  kbn = p_kbn;
  ptr = p_ptr;
  clm_msg = new sChar("");
  }
LinkCell_T::~LinkCell_T(){
  delete clm_msg;
  }

// #if/#st class -----------------
void StIf_T::init(MemHeader_T  *it,char *p_str,char *p_clk,int p_no,MM_PTR_T *p_up_ptr,char *p_status_name,int p_if_kbn){
  str     = new sChar(p_str);
  clk     = new sChar(p_clk);
  status_name = new sChar(p_status_name);  // Ver 1.10
  no      = p_no;
  up_ptr  = p_up_ptr;
  link_fp = new MEM_FP(it);
  next_else = false;
  clm_msg = new sChar("");
  if_kbn  = p_if_kbn;
  }
StIf_T::StIf_T(MemHeader_T  *it,char *p_str,char *p_clk,int p_no,MM_PTR_T *p_up_ptr,int p_if_kbn){
  init(it,p_str,p_clk,p_no,p_up_ptr,p_str,p_if_kbn);  // Ver 1.01
  }
StIf_T::StIf_T(MemHeader_T  *it,char *p_str,MM_PTR_T *p_up_ptr,char *p_status_name,int p_if_kbn){
  init(it,p_str,"",-1,p_up_ptr,p_status_name,p_if_kbn);  // Ver 1.01
  }
StIf_T::~StIf_T()
  {
  LinkCell_T *lc;
  MEM_LOOP(lc,LinkCell_T,link_fp) delete lc ; LOOP_END
  delete status_name; // Ver 1.01
  delete link_fp;
  delete str;
  delete clk;
  delete clm_msg;
  }

// #status class ---------------------
Status_T::Status_T(MemHeader_T  *it,char *p_name){
  name     = new sChar(p_name);
  cur_st_name = new sChar(""); // Ver 1.01
  clk      = new sChar(""); // Ver 1.01
  init_no  = 0;
  st_fp    = new MEM_FP(it);
  st_sub_fp= new MEM_FP(it);
  parm_fp  = new MEM_FP(it);
  local_fp = new MEM_FP(it);
  chg_fp   = new MEM_FP(it);
  clm_msg  = new sChar("");
  }
Status_T::~Status_T(){
  StParm_T *p;
  MEM_LOOP(p    ,StParm_T  ,parm_fp ) delete p;    LOOP_END
  MEM_LOOP(p    ,StParm_T  ,local_fp) delete p;    LOOP_END
  delete st_sub_fp;
  delete st_fp;
  delete chg_fp;
  delete parm_fp;
  delete local_fp;
  delete name;
  delete clm_msg;
  delete cur_st_name; // Ver 1.01
  delete clk; // Ver 1.01
  }

// Interface -----------------
CsvState_T::CsvState_T(MemHeader_T *p_it,Msg_T *p_msg){
  it         = p_it;
  msg        = p_msg;
  status_fp  = new MEM_FP(it);
  chg_fp     = new MEM_FP(it);
  stif_fp    = new MEM_FP(it);
  cmd_fp     = new MEM_FP(it);
  chgline_fp = new MEM_FP(it);
  chgcmd_fp  = new MEM_FP(it);
  chgclk_fp  = new MEM_FP(it);
  g_status   = NULL;
  g_stif     = NULL;
  chgseq_cnt = 0;
  status_no  = 0;
  chgline_cnt = 0;
  ssc        = new StrSrchInf_T();
  ssc->Set(':'); ssc->SetFlg();
  cur_clm    = 0;
  chg_trap   = new sChar("");
  ary_max    = new sChar("50");
  grep       = new sCharGrep("");
  bin_conv   = new binConv_C;
  }
CsvState_T::~CsvState_T(){
  Status_T *st;
  Chg_T    *chg;
  sChar    *str;
  StIf_T   *stif;
  ChgLineList_T *cll;
  ChgCmdList_T  *ccl;
  ChgClkList_T  *clk;
  MEM_LOOP(st  ,Status_T,status_fp) delete st;   LOOP_END
  MEM_LOOP(chg ,Chg_T   ,chg_fp   ) delete chg;  LOOP_END
  MEM_LOOP(str ,sChar   ,cmd_fp   ) delete str;  LOOP_END
  MEM_LOOP(stif,StIf_T  ,stif_fp  ) delete stif; LOOP_END
  MEM_LOOP(ccl ,ChgCmdList_T ,chgcmd_fp  ) delete ccl; LOOP_END
  MEM_LOOP(cll ,ChgLineList_T,chgline_fp ) delete cll; LOOP_END
  MEM_LOOP(clk ,ChgClkList_T ,chgclk_fp )  delete clk; LOOP_END
  delete chgcmd_fp;
  delete chgline_fp;
  delete chgclk_fp;
  delete status_fp;
  delete chg_fp;
  delete stif_fp;
  delete cmd_fp;
  delete ssc;
  delete chg_trap;
  delete ary_max;
  delete grep;
  delete bin_conv;
  }
bool CsvState_T::ExistCheck(){if (g_status == NULL){return(false);}  return(true);}

// -----------------
// Main Loop
// -----------------
bool CsvState_T::CsvRead(CsvAnl_C *csvi)  // true:hit false:none hit
  {
  bool flg;
  char *command;

  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  cur_clm = 1;
  if (strcmp(command,"#status") == 0){flg=true; status_rtn(csvi      );}
  if (strcmp(command,"#st"    ) == 0){flg=true; st_rtn    (csvi      );}
  if (strcmp(command,"#if"    ) == 0){flg=true; if_rtn    (csvi,0,false);}
  if (strcmp(command,"#elseif") == 0){flg=true; if_rtn    (csvi,1,false);}
  if (strcmp(command,"#xelseif")== 0){flg=true; if_rtn    (csvi,1,true );}
  if (strcmp(command,"#else"  ) == 0){flg=true; if_rtn    (csvi,2,false);}
  if (strcmp(command,"#xelse" ) == 0){flg=true; if_rtn    (csvi,2,true );}
  if (strcmp(command,"#endif" ) == 0){flg=true; endif_rtn (csvi      );}
  if (strcmp(command,"#go"    ) == 0){flg=true; go_rtn    (csvi      );}
  if (strcmp(command,"#cmd"   ) == 0){flg=true; cmd_rtn   (csvi      );}
  if (strcmp(command,"#chg"   ) == 0){flg=true; chg_rtn   (csvi      );}
  if (strcmp(command,"#sparm" ) == 0){flg=true; sparm_rtn (csvi      );}
  if (strcmp(command,"#slocal") == 0){flg=true; slocal_rtn(csvi      );}
  if (strcmp(command,"#chgtrap") ==0){flg=true; chgtrap_rtn(csvi     );}
  if (strcmp(command,"#chgmax") == 0){flg=true; chgmax_rtn(csvi      );}
  if (strcmp(command,"#act"   ) == 0){flg=true; st_move_rtn(csvi,StActKbn    );} // Ver 1.01
  if (strcmp(command,"#stop"  ) == 0){flg=true; st_move_rtn(csvi,StStopKbn   );} // Ver 1.01
  if (strcmp(command,"#exec"  ) == 0){flg=true; st_move_rtn(csvi,StExecKbn   );} // Ver 1.01
  return(flg);
  }

// --------------
// #chgtrap
// --------------
void CsvState_T::chgtrap_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	chg_trap->set(str);
    return;
    }
  msg->ErrMsg(csvi,E000,i);
  }

// --------------
// #chgmax
// --------------
void CsvState_T::chgmax_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    ary_max->set(str);
    return;
    }
  msg->ErrMsg(csvi,E000,i);
  }


// --------------
// #status
// --------------
void CsvState_T::status_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *st_name;     // Ver 1.01
  bool  ok_flg;

  ok_flg  = false;
  st_name = NULL;    // Ver 1.01
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (st_name == NULL){st_name = str; continue;}

    it->srch_key = st_name;              // Ver 1.01
    if (status_fp->mem_srch() == 0){msg->ErrMsg(csvi,E001,i); return;}
    g_status = new Status_T(it,st_name); // Ver 1.01
    g_status->clk->set(str);             // Ver 1.01
	g_status->clm_msg->set(csvi->getClmMsg(i));
    it->alloc_ptr = (MM_PTR_T *)g_status;
    status_fp->mem_srch_alloc();
    g_stif = NULL;
    ok_flg  = true;
    break;
    }
  if (ok_flg == false){msg->ErrMsg(csvi,E000,i);}
  }

// --------------
// #sparm
// --------------
void CsvState_T::sparm_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *name;
  StParm_T *sp;

  if (g_status == NULL){msg->ErrMsg(csvi,E003,0); return;}
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
	g_status->parm_fp->mem_alloc();
    return;
    }
  msg->ErrMsg(csvi,E000,0);
  }

// --------------
// #slocal
// --------------
void CsvState_T::slocal_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *name;
  char *size;
  StParm_T *sp;

  if (g_status == NULL){msg->ErrMsg(csvi,E003,0); return;}
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
    g_status->local_fp->mem_alloc();
    return;
    }
  msg->ErrMsg(csvi,E000,0);
  }

// --------------
// #st
// --------------
void CsvState_T::st_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *st_name;
  bool  ok_flg;

  if (g_status == NULL){msg->ErrMsg(csvi,E003,0); return;}
  ok_flg  = false;
  st_name = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (st_name == NULL){st_name = str;}
	it->srch_key = st_name;
    if (g_status->st_fp->mem_srch() == 0){msg->ErrMsg(csvi,E004,i); return;}
    g_stif = new StIf_T(it,st_name,str,g_status->init_no,(MM_PTR_T *)g_status,0);
    g_status->cur_st_name->set(st_name);   // Ver 1.01
    g_stif->clm_msg->set(csvi->getClmMsg(i));
    it->alloc_ptr = (MM_PTR_T *)g_stif;
    g_status->st_fp->mem_srch_alloc();
    g_status->st_sub_fp->mem_alloc();
    stif_fp->mem_alloc();
    ++(g_status->init_no);
    ok_flg = true;
    break;
  LOOP_END
  if (ok_flg == false){msg->ErrMsg(csvi,E000,i);}
  }

// ------------------
// #if/#else/#elseif
// ------------------
void CsvState_T::if_rtn(CsvAnl_C *csvi,int if_kbn,bool line_kbn)  // 0:#if 1:#elseif 2:#else
  {
  int         i;
  char       *str;
  sChar      *ww;
  StIf_T     *sv_stif;
  bool        ok_flg;
  LinkCell_T *lc;

  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  if (if_kbn > 0) { // #else,#elseif
    if (line_kbn == false){
      g_stif->next_else = true;
      endif_rtn(csvi);
    }
    else {
      sv_stif = (StIf_T *)stif_fp->mem_link_ptr_rd();
      sv_stif->next_else = true;
    }
  }
  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  sv_stif = g_stif;

  ok_flg = false;
  ww = new sChar("");
  if (if_kbn < 2){
    for(i=1;i<csvi->CsvSelSu_Rd();++i){
	  str = csvi->CsvSel_Rd(i);
	  if (csvi->blankCheck(str)) {continue;}
	  if ((strcmp(str,"#")==0)
       || (strcmp(str,"#cmd")==0)
       || (strcmp(str,"#chg")==0)
       || (strcmp(str,"#act")==0)   // Ver 1.01
       || (strcmp(str,"#stop")==0)  // Ver 1.01
       || (strcmp(str,"#exec")==0)  // Ver 1.01
       || (strcmp(str,"#go" )==0)) {break;}
      ww->cat(str);
      ok_flg = true;
    }
  }
  else{
    ww->set("#else");
    ok_flg = true;
    i = 1;
  }
  g_stif = new StIf_T(it,ww->c_str(),(MM_PTR_T *)sv_stif,g_status->cur_st_name->c_str(),if_kbn); // Ver 1.01
  lc     = new LinkCell_T(StIfKbn,(MM_PTR_T *)g_stif);
  g_stif->clm_msg->set(csvi->getClmMsg(0));
  lc->clm_msg->set(csvi->getClmMsg(0));
  it->alloc_ptr = (MM_PTR_T *)g_stif;  stif_fp->mem_alloc();
  it->alloc_ptr = (MM_PTR_T *)lc;      sv_stif->link_fp->mem_alloc();
  delete ww;
  if (ok_flg == false){msg->ErrMsg(csvi,E000,i); return;}

  // line if/else/elseif check
  for(;i<csvi->CsvSelSu_Rd();++i){
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}

	cur_clm = i+1;
    if (strcmp(str,"#"   )==0 ){cmd_rtn(csvi);}
    if (strcmp(str,"#cmd")==0 ){cmd_rtn(csvi);}
    if (strcmp(str,"#chg")==0 ){chg_rtn(csvi);}
    if (strcmp(str,"#act")==0 ){st_move_rtn(csvi,StActKbn);} // Ver 1.01
    if (strcmp(str,"#stop")==0){st_move_rtn(csvi,StStopKbn);} // Ver 1.01
    if (strcmp(str,"#exec")==0){st_move_rtn(csvi,StExecKbn);} // Ver 1.01
    if (strcmp(str,"#go" )==0){go_rtn (csvi);}
    if ((strcmp(str,"#")==0)
     || (strcmp(str,"#cmd")==0)
     || (strcmp(str,"#chg")==0)
     || (strcmp(str,"#act")==0)   // Ver 1.01
     || (strcmp(str,"#stop")==0)  // Ver 1.01
     || (strcmp(str,"#exec")==0)  // Ver 1.01
     || (strcmp(str,"#go" )==0)){
      endif_rtn(csvi);
      break;
    }
  }
}

// --------------
// #endif
// --------------
void CsvState_T::endif_rtn(CsvAnl_C *csvi)
  {
  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  if (g_stif->no == -1){g_stif = (StIf_T *)g_stif->up_ptr;}
  else                 {g_stif = (StIf_T *)NULL;}
  }

// --------------
// #go Ver 1.01
// --------------
void CsvState_T::go_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  sChar *ww;
  LinkCell_T *lc;
  int sv;

  sv = -1;
  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (sv == -1){sv = i;}
    if (*str == '*')
      {
      ww = new sChar(str+1); it->alloc_ptr = (MM_PTR_T *)ww; cmd_fp->mem_alloc();
      lc = new LinkCell_T(StActKbn ,(MM_PTR_T *)ww); it->alloc_ptr = (MM_PTR_T *)lc; g_stif->link_fp->mem_alloc();
	  lc->clm_msg->set(csvi->getClmMsg(i));
	  lc = new LinkCell_T(StExecKbn,(MM_PTR_T *)ww); it->alloc_ptr = (MM_PTR_T *)lc; g_stif->link_fp->mem_alloc();
      lc->clm_msg->set(csvi->getClmMsg(i));
      }
    else
      {
      ww = new sChar(str);   it->alloc_ptr = (MM_PTR_T *)ww; cmd_fp->mem_alloc();
      lc = new LinkCell_T(StActKbn ,(MM_PTR_T *)ww); it->alloc_ptr = (MM_PTR_T *)lc; g_stif->link_fp->mem_alloc();
      lc->clm_msg->set(csvi->getClmMsg(i));
      }
    }
 lc = new LinkCell_T(StStopKbn ,(MM_PTR_T *)g_stif->status_name);
 it->alloc_ptr = (MM_PTR_T *)lc;
 g_stif->link_fp->mem_alloc();
 lc->clm_msg->set(csvi->getClmMsg(sv));
 }

// --------------------------
// #act/#stop/#exec Ver 1.01
// --------------------------
void CsvState_T::st_move_rtn(CsvAnl_C *csvi,int kbn)
  {
  int i;
  char *str;
  sChar *ww;
  LinkCell_T *lc;

  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}

	ww = new sChar(str);
    it->alloc_ptr = (MM_PTR_T *)ww;
    cmd_fp->mem_alloc();
    lc = new LinkCell_T(kbn ,(MM_PTR_T *)ww);
    it->alloc_ptr = (MM_PTR_T *)lc;
    g_stif->link_fp->mem_alloc();
    lc->clm_msg->set(csvi->getClmMsg(i));
    }
  }

// --------------
// #cmd
// --------------
void CsvState_T::cmd_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  sChar *ww;
  bool ok_flg;
  LinkCell_T *lc;
  int sv;

  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  ww = new sChar("");
  ok_flg = false;
  sv = -1;
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (sv == -1){sv = i;}
    ww->cat(str);
    ww->cat(" ");
    ok_flg = true;
    }
  lc = new LinkCell_T(StCmdKbn,(MM_PTR_T *)ww);
  lc->clm_msg->set(csvi->getClmMsg(sv));
  it->alloc_ptr = (MM_PTR_T *)ww; cmd_fp->mem_alloc();
  it->alloc_ptr = (MM_PTR_T *)lc; g_stif->link_fp->mem_alloc();
  if (ok_flg == false){msg->ErrMsg(csvi,E000,i);}
  }


// --------------
// #chg
// --------------
void CsvState_T::chg_rtn(CsvAnl_C *csvi)
  {
  int i,j;
  int cnt;
  char *str;
  char *line;
  char *clk;
  Chg_T *chg;
  sChar *cyc;
  sChar *val;
  ValChg_T *vc;
  LinkCell_T *lc;
  bool hit;
  ChgLineList_T *cll;
  ChgCmdList_T  *ccl;
  sChar *key;
  sChar *sizechk;

  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  cnt = 0;
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i){
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (cnt == 0){line = str; ++cnt; continue;}
	if (cnt == 1){clk = str;  ++cnt; continue;}
	if (cnt == 2){
	  hit = false;
	  MEM_LOOP(lc,LinkCell_T,g_stif->link_fp)
		if (lc->kbn != StChgKbn) {continue;}
		chg = (Chg_T *)lc->ptr;
		if (strcmp(chg->clk->c_str(),clk) == 0){hit = true; break;}
	  LOOP_END
	  if (hit == false){
		chg = new Chg_T(it,clk,chgseq_cnt); ++chgseq_cnt;
		lc = new LinkCell_T(StChgKbn,(MM_PTR_T *)chg);
		lc->clm_msg->set(csvi->getClmMsg(i));
		chg->clm_msg->set(csvi->getClmMsg(i));
		it->alloc_ptr = (MM_PTR_T *)chg; chg_fp->mem_alloc(); g_status->chg_fp->mem_alloc();
		it->alloc_ptr = (MM_PTR_T *)lc; g_stif->link_fp->mem_alloc();
	  }

	  // Ver 1.01
	  it->srch_key = clk;
	  if (chgclk_fp->mem_srch() != 0){
		it->alloc_ptr = (ChgClkList_T *)new ChgClkList_T(clk);
		chgclk_fp->mem_srch_alloc();
	  }
	  if (strcmp(line,"#cmd") != 0){
		key = new sChar(clk);
		key->cat("_");
		key->cat(line);
		it->srch_key = key->c_str();
		if (chgline_fp->mem_srch() != 0){
		  cll = new ChgLineList_T(clk,line,chgline_cnt);
		  ++chgline_cnt;
		  it->alloc_ptr = (MM_PTR_T *)cll;
		  chgline_fp->mem_srch_alloc();
		}
		else {
		  cll = (ChgLineList_T *)chgline_fp->mem_link_ptr_rd();
		}
		delete key;
	  }
	  else{
		it->srch_key = clk;
		if (chgcmd_fp->mem_srch() == 0){
		  ccl = (ChgCmdList_T *)chgcmd_fp->mem_link_ptr_rd();
		}
		else {
		  ccl = new ChgCmdList_T(it,clk);
		  it->alloc_ptr = (MM_PTR_T *)ccl;
		  chgcmd_fp->mem_srch_alloc();
		}
	  }
	}
	ssc->Main(str);
	if (ssc->GetSu() < 2){continue;}
	cyc = ssc->Get(0);
	sChar *w_cyc = new sChar(cyc->c_str());
	val = new sChar("");
	for(j=2;j<ssc->GetSu();++j){val->cat(ssc->Get(j)->c_str());}
	vc = new ValChg_T(line,val->c_str(),w_cyc->c_str());
	it->alloc_ptr = (MM_PTR_T *)vc; chg->val_fp->mem_alloc();
    delete w_cyc;

	// Ver 1.01
	if (strcmp(line,"#cmd") == 0){
	  rep(val);
	  it->srch_key = val->c_str();
	  if (ccl->cmd_fp->mem_srch() != 0){
		it->alloc_ptr = new ChgCmdCell_T(val->c_str(),ccl->cmd_no);
		ccl->cmd_fp->mem_srch_alloc();
		++(ccl->cmd_no);
	  }
	}
	else {
	  char *w = bin_conv->conv(val->c_str());
	  if (w != NULL){
		cll->size = strlen(w);
	  }
	}
	delete val;
  }
}

// -----------------
// Space
// -----------------
void CsvState_T::space(FILE *fp,int level)
  {
  int i;
  for(i=0;i<level;++i){fprintf(fp,"  ");}
  }

// -----------------
// @L,@P Change
// -----------------
void CsvState_T::rep(sChar *str)
  {
  sChar *local;
  sChar *parm;

  local = new sChar("l_"); local->cat(g_status->name->c_str()); local->cat("_");
  parm  = new sChar("p_"); parm->cat(g_status->name->c_str());  parm->cat("_");
  grep->set(str->c_str());
  grep->replace_all("@L",local->c_str());
  grep->replace_all("@P",parm->c_str());
  str->set(grep->c_str());

  delete local; // Ver 1.11
  delete parm;  // Ver 1.11

  }




