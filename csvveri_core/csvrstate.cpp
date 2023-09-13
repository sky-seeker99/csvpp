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
//  State Machine (For RTL)
//  1.01:#act,#stop 追加
//  1.02:#assign 追加
//  1.03:#wire_reg 追加
//  1.04:ステートマシンがリセット優先になっていない
//  1.05:#andor 追加
//  1.06:#chg のＦＦに対してリセット追加
//  1.07:#chg のＦＦに対してリセット追加  のバグ
//  1.08:#assign バグ '||' -> '|'
//  1.16:#elseif
//

#include <string.h>
#include <stdio.h>
#include "csvrstate.h"

// assign class (Ver 1.02) ------
Assign_T::Assign_T(char *p_var,char *p_siki){
  var  = new sChar(p_var);
  siki = new sChar(p_siki);
  }

Assign_T::~Assign_T(){
  delete siki;
  delete var;
  }

// reg body class ------
Siki_T::Siki_T(MemHeader_T *p_it,char *p_siki,char *p_val){
  if (*p_siki == '@'){sync = false; siki = new sChar(p_siki+1);}
  else               {sync = true;  siki = new sChar(p_siki);  }
  val     = new sChar(p_val);
  idx     = new sChar("");
  s_name  = new sChar("");
  clm_msg = new sChar("");
  reset   = false;     // 1.04
  }
Siki_T::~Siki_T(){
  delete clm_msg;
  delete siki;
  delete val;
  delete idx;
  delete s_name;
  }

// wire class ------
// Ver 1.07 #wire_o
Wire_T::Wire_T(MemHeader_T *p_it,char *p_name,char *p_size,char *p_val,bool p_wire_o_flg){
  name = new sChar(p_name);
  size = new sChar(p_size);
  val  = new sCharGrep(p_val );
  defined_flg = false;
  clm_msg = new sChar("");
  wire_reg = false; // Ver 1.03
  wire_o_flg = p_wire_o_flg;     // Ver 1.07
  body_fp    = new MEM_FP(p_it); // Ver 1.07
  end_cnt    = 0;                // Ver 1.07
  def_val    = new sChar("");    // Ver 1.07
  }
Wire_T::~Wire_T(){
  Siki_T *siki;
  delete name;
  delete size;
  delete val;
  delete clm_msg;
  MEM_LOOP(siki,Siki_T,body_fp) delete siki; LOOP_END
  delete body_fp;
  delete def_val;
  }

// reg class ------
Reg_T::Reg_T(MemHeader_T *p_it,char *p_name,char *p_size,char *p_clk){
  name        = new sChar(p_name);
  size        = new sChar(p_size);
  clk         = new sChar(p_clk);
  body_fp     = new MEM_FP(p_it);
  andor_flg   = false;         // Ver 1.05
  andor_def   = new sChar(""); // Ver 1.05
  use_flg     = false;
  defined_flg = false;
  wire_reg    = false; // Ver 1.03
  idx         = new sChar("");
  clm_msg     = new sChar("");
  }
Reg_T::~Reg_T(){
  Siki_T *siki;
  delete name;
  delete size;
  delete clk;
  MEM_LOOP(siki,Siki_T,body_fp) delete siki; LOOP_END
  delete body_fp;
  delete idx;
  delete andor_def;  // Ver 1.05
  delete clm_msg;
  }

// State Machine body class ------
Body_T::Body_T(Reg_T *p_reg,char *p_val,int p_cyc,char *p_idx){
  reg  = p_reg;
  val  = new sChar(p_val);
  cyc  = p_cyc;
  idx  = new sChar(p_idx);
  clm_msg = new sChar("");
  }
Body_T::~Body_T(){
  delete val;
  delete idx;
  delete clm_msg;
  }

// State Machine if class ------
RStIf_T::RStIf_T(MemHeader_T  *it,char *p_name,MM_PTR_T *p_up_ptr,int p_if_kbn){
  name    = new sChar(p_name);
  if_kbn  = p_if_kbn;         // Ver 1.16
//  move_st = new sChar("");  // Ver 1.01
  act_fp  = new MEM_FP(it);   // Ver 1.01
  stop_fp = new MEM_FP(it);   // Ver 1.01
  up_ptr  = p_up_ptr;
  stif_fp = new MEM_FP(it);
  body_fp = new MEM_FP(it);
  pull_fp = new MEM_FP(it);
  assign_fp = new MEM_FP(it); // Ver 1.02
  max_cyc = 0;
  clm_msg = new sChar("");
  }
RStIf_T::~RStIf_T(){
  RStIf_T *stif;
  Body_T *body;
  sChar  *ss;
  Assign_T *aa;   // Ver 1.02

  delete name;
//  delete move_st;
  MEM_LOOP(stif,RStIf_T,stif_fp) delete stif; LOOP_END
  MEM_LOOP(body,Body_T,body_fp) delete body; LOOP_END
  MEM_LOOP(ss,sChar,pull_fp) delete ss; LOOP_END
  MEM_LOOP(aa,Assign_T,assign_fp) delete aa; LOOP_END   // Ver 1.02
  MEM_LOOP(ss,sChar,act_fp ) delete ss; LOOP_END   // Ver 1.01
  MEM_LOOP(ss,sChar,stop_fp) delete ss; LOOP_END   // Ver 1.01
  delete stif_fp;
  delete body_fp;
  delete pull_fp;
  delete assign_fp; // Ver 1.02
  delete clm_msg;
  delete act_fp;  // Ver 1.01
  delete stop_fp; // Ver 1.01
  }

// State Machine class ------
RState_T::RState_T(MemHeader_T *p_it,char *p_name,char *p_clk){
  name = new sChar(p_name);
  st_name = new sChar("");    // Ver 1.01
  dec_flg = false;
  en_flg  = false;
  enable  = new sChar("");
  clk     = new sChar(p_clk);
  sch_cnt = 0;
  stif_fp = new MEM_FP(p_it);
  rst_fp  = new MEM_FP(p_it);
  chg_fp  = new MEM_FP(p_it);
  init_no = 0;
  first_state = new sChar("");
  clm_msg = new sChar("");
  }
RState_T::~RState_T(){
  RStIf_T   *stif;
  sChar    *str;
  delete st_name; // Ver 1.01
  delete name;
  delete enable;
  delete clk;
  MEM_LOOP(stif,RStIf_T  ,stif_fp) delete stif; LOOP_END
  MEM_LOOP(str ,sChar   ,rst_fp ) delete str;  LOOP_END
  delete stif_fp;
  delete rst_fp;
  delete chg_fp;
  delete first_state;
  delete clm_msg;
  }

// Interface -----------------
CsvRState_T::CsvRState_T(MemHeader_T *p_it,Msg_T *p_msg){
  it         = p_it;
  msg        = p_msg;
  status_fp  = new MEM_FP(it);
  reg_fp     = new MEM_FP(it);
  wire_fp    = new MEM_FP(it);
  g_status   = NULL;
  g_stif     = NULL;
  status_no  = 0;
  ssc        = new StrSrchInf_T(); ssc->Set(':');  ssc->SetFlg();
  ssc2       = new StrSrchInf_T(); ssc2->Set('='); ssc2->SetFlg(); ssc2->Set(';'); ssc2->SetFlg();
  ssc3       = new StrSrchInf_T(); ssc3->Set('[');
  ssc5       = new StrSrchInf_T(); ssc5->Set('/');
  cur_clm    = 0;
  sv_reg     = NULL;
  own_flg    = false;
  work       = new VariableArea_C(10);
}
CsvRState_T::~CsvRState_T(){
  RState_T  *st;
  Reg_T    *reg;
  Wire_T   *wire;
  MEM_LOOP(st  ,RState_T ,status_fp) delete st;   LOOP_END
  MEM_LOOP(reg ,Reg_T   ,reg_fp   ) delete reg;  LOOP_END
  MEM_LOOP(wire,Wire_T  ,wire_fp  ) delete wire; LOOP_END
  delete status_fp;
  delete reg_fp;
  delete wire_fp;
  delete ssc;
  delete ssc2;
  delete ssc3;
  delete ssc5;
  delete work;
}
bool CsvRState_T::ExistCheck()
  {
  if (g_status != NULL){return(true);}
  reg_fp->mem_mcb_top_set();  if (reg_fp->mem_mcb_ptr_rd() != MM_NULL){return(true);}
  wire_fp->mem_mcb_top_set(); if (wire_fp->mem_mcb_ptr_rd() != MM_NULL){return(true);}
  return(false);
  }

// -----------------
// Main Loop
// -----------------
bool CsvRState_T::CsvRead(CsvAnl_C *csvi)  // true:hit false:none hit
  {
  bool flg;
  char *command;

  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  cur_clm = 1;

  if (strcmp(command,"#reg_andor")== 0){flg=true; reg_andor_rtn(csvi    );}
  if (strcmp(command,"#reg"     ) == 0){flg=true; reg_rtn   (csvi       );}
  if (strcmp(command,"#reg_body") == 0){flg=true; reg_body_rtn(csvi     );}
  if (strcmp(command,"#wire"    ) == 0){flg=true; wire_rtn  (csvi ,false);} // Ver 1.07
  if (strcmp(command,"#wire_o"  ) == 0){flg=true; wire_rtn  (csvi ,true );} // Ver 1.07
  if (strcmp(command,"#wire_reg") == 0){flg=true; wire_reg_rtn  (csvi   );} // Ver 1.03
  if (strcmp(command,"#status"  ) == 0){own_flg = false;}
  if (strcmp(command,"#rstatus" ) == 0){flg=true; status_rtn(csvi       ); own_flg = true;}

  if (own_flg == true)
    {
    for(;;){
      if (strcmp(command,"#st"      ) == 0){flg=true; st_rtn    (csvi        ); break;}
      if (strcmp(command,"#if"      ) == 0){flg=true; if_rtn    (csvi,0,false); break;}  // Ver 1.16
      if (strcmp(command,"#elseif"  ) == 0){flg=true; if_rtn    (csvi,1,false); break;}  // Ver 1.16
      if (strcmp(command,"#xelseif" ) == 0){flg=true; if_rtn    (csvi,1,true ); break;}  // Ver 1.16
      if (strcmp(command,"#else"    ) == 0){flg=true; if_rtn    (csvi,2,false); break;}  // Ver 1.16
      if (strcmp(command,"#xelse"   ) == 0){flg=true; if_rtn    (csvi,2,true ); break;}  // Ver 1.16
      if (strcmp(command,"#endif"   ) == 0){flg=true; endif_rtn (csvi        ); break;}
      if (strcmp(command,"#go"      ) == 0){flg=true; go_rtn    (csvi        ); break;}
      if (strcmp(command,"#act"     ) == 0){flg=true; act_rtn   (csvi        ); break;}
      if (strcmp(command,"#stop"    ) == 0){flg=true; stop_rtn  (csvi        ); break;}
      if (strcmp(command,"#cmd"     ) == 0){flg=true; cmd_rtn   (csvi        ); break;}
      if (strcmp(command,"#pull"    ) == 0){flg=true; pull_rtn  (csvi        ); break;}
      if (strcmp(command,"#assign"  ) == 0){flg=true; assign_rtn(csvi        ); break;}
      if (strcmp(command,"#chg"     ) == 0){flg=true; chg_rtn   (csvi        ); break;}
      break;
      }
    }
  return(flg);
  }

// --------------
// #rstatus
// --------------
void CsvRState_T::status_rtn(CsvAnl_C *csvi)
  {
  int i;
  char  *str;
  char  *name;
  char  *clk;
  bool   ok_flg;
  int    clm;

  name = NULL;
  clk  = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (name == NULL){name = str; clm = i; continue;}
    if (clk  == NULL)
      {
      it->srch_key = name;
      clk = str;
      if (status_fp->mem_srch() == 0){msg->ErrMsg(csvi,E001,i); return;}
      if (reg_fp->mem_srch() == 0){msg->ErrMsg(csvi,E002,i); return;}
      g_status = new RState_T(it,name,clk);
      it->alloc_ptr = (MM_PTR_T *)g_status;
      status_fp->mem_srch_alloc();
      g_stif = NULL;
	  g_status->clm_msg->set(csvi->getClmMsg(clm)); //
      continue;
      }
    it->alloc_ptr = (MM_PTR_T *)new sChar(str);
    g_status->rst_fp->mem_alloc();
    }
  if (clk == NULL){msg->ErrMsg(csvi,E000,i);}
  }

// --------------
// #st
// --------------
void CsvRState_T::st_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  bool  ok_flg;

  if (g_status == NULL){msg->ErrMsg(csvi,E003,0); return;}
  ok_flg  = false;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    it->srch_key = str;
    if (g_status->stif_fp->mem_srch() == 0){msg->ErrMsg(csvi,E004,i); return;}
	g_stif = new RStIf_T(it,str,NULL,0);  // Ver 1.16
	g_status->st_name->set(str);
	g_stif->clm_msg->set(csvi->getClmMsg(i)); //
    it->alloc_ptr = (MM_PTR_T *)g_stif;
    g_status->stif_fp->mem_srch_alloc();
    ++(g_status->init_no);
    ok_flg = true;
    if (strcmp(g_status->first_state->c_str(),"")==0)
      {
      g_status->first_state->set(str);
      }
    break;
    }
  if (ok_flg == false){msg->ErrMsg(csvi,E000,i);}

  }


// --------------
// #if/#else
// --------------
void CsvRState_T::if_rtn(CsvAnl_C *csvi,int if_kbn,bool line_kbn)  // 0:#if 1:#elseif  2:#else
  {
  int         i;
  char       *str;
  sChar      *ww;
  RStIf_T     *sv_stif;
  bool        ok_flg;

  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  if (if_kbn > 0)  // #else,#elseif   Ver 1.16
    {
    if (line_kbn == false)
      {
      endif_rtn(csvi);
      }
    }
  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  sv_stif = g_stif;

  ok_flg = false;
  ww = new sChar("");
  if (if_kbn < 2)  // #if,#elseif
    {
    for(i=1;i<csvi->CsvSelSu_Rd();++i)
      {
	  str = csvi->CsvSel_Rd(i);
	  if (csvi->blankCheck(str)) {continue;}
	  if ((strcmp(str,"#")==0)
	   || (strcmp(str,"#pull")==0)
	   || (strcmp(str,"#assign")==0)
	   || (strcmp(str,"#cmd")==0)
	   || (strcmp(str,"#chg")==0)
	   || (strcmp(str,"#act")==0)
	   || (strcmp(str,"#stop")==0)
	   || (strcmp(str,"#go" )==0)) {break;}
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
  g_stif = new RStIf_T(it,ww->c_str(),(MM_PTR_T *)sv_stif,if_kbn);
  g_stif->clm_msg->set(csvi->getClmMsg(i-1));  //
  it->alloc_ptr = (MM_PTR_T *)g_stif;
  sv_stif->stif_fp->mem_alloc();
  delete ww;

  if (ok_flg == false){msg->ErrMsg(csvi,E000,i); return;}

  // line if/else/elseif check
  for(;i<csvi->CsvSelSu_Rd();++i)
	{
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	cur_clm = i+1;
	if (strcmp(str,"#"   )==0){cmd_rtn(csvi);}
	if (strcmp(str,"#cmd")==0){cmd_rtn(csvi);}
	if (strcmp(str,"#chg")==0){chg_rtn(csvi);}
	if (strcmp(str,"#go" )==0){go_rtn (csvi);}
	if (strcmp(str,"#pull" )==0){pull_rtn (csvi);}
	if (strcmp(str,"#assign")==0){assign_rtn (csvi);}
	if (strcmp(str,"#act" )==0){act_rtn (csvi);}
	if (strcmp(str,"#stop")==0){stop_rtn (csvi);}
	if ((strcmp(str,"#")==0)
	 || (strcmp(str,"#pull")==0)
	 || (strcmp(str,"#assign")==0)
	 || (strcmp(str,"#cmd")==0)
	 || (strcmp(str,"#chg")==0)
	 || (strcmp(str,"#act")==0)
	 || (strcmp(str,"#stop")==0)
	 || (strcmp(str,"#go" )==0))
	  {
	  endif_rtn(csvi);
	  break;
	  }
	}

  }


// --------------
// #endif
// --------------
void CsvRState_T::endif_rtn(CsvAnl_C *csvi)
  {
  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  g_stif = (RStIf_T *)g_stif->up_ptr;
  }


// --------------
// #go (Ver 1.01)
// --------------
void CsvRState_T::go_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    it->alloc_ptr = new sChar(str);
    g_stif->act_fp->mem_alloc();
    }
  it->alloc_ptr = new sChar(g_status->st_name->c_str());
  g_stif->stop_fp->mem_alloc();
  }

// ----------------
// #act (Ver 1.01)
// ----------------
void CsvRState_T::act_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    it->alloc_ptr = new sChar(str);
    g_stif->act_fp->mem_alloc();
    }
  }

// ----------------
// #stop (Ver 1.01)
// ----------------
void CsvRState_T::stop_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    it->alloc_ptr = new sChar(str);
    g_stif->stop_fp->mem_alloc();
    }
  }

// -----------------------
// Command -> body Store
// -----------------------
bool CsvRState_T::body_rtn(CsvAnl_C *csvi,int clm,char *str,int cyc){
  int mode;
  int max;
  sChar *ww;
  sChar *ww2;
  char *name;
  char *val;
  Reg_T *reg;
  int i;
  int j;
  sChar *ss;
  Body_T *body;

  ssc2->Main(str);
  max  = ssc2->GetSu();
  mode = 0;
  for(i=0;i<max;++i){
	ww = ssc2->Get(i);
	ww->Push();

	if (mode == 0){
	  if (ww->c_str() != NULL) {
		work->set_string(ww->c_str());
		name = work->cc_str();
		mode = 1;
	  }
	  continue;
	}
	if (mode == 1){
	  if (strcmp(ww->c_str(),"=")!=0){return(false);}
	  mode = 2;
	  continue;
	}
	if (mode == 2){
	  ssc3->Main(name);
	  ww2 = ssc3->Get(0);
	  ww2->Push();
	  it->srch_key = ww2->c_str();
	  if (reg_fp->mem_srch() != 0){return(false);}
	  reg = (Reg_T *)reg_fp->mem_link_ptr_rd();
	  val = ww->c_str();
	  mode = 3;
	  if (ssc3->GetSu() == 1){body = new Body_T(reg,val,cyc,""); it->alloc_ptr = (MM_PTR_T *)body;}
	  else {
		ss = new sChar("[");
		for(j=1;j<ssc3->GetSu();++j){
		  ww2 = ssc3->Get(j);
		  ss->cat(ww2->c_str());
		}
		body = new Body_T(reg,val,cyc,ss->c_str());
		it->alloc_ptr = (MM_PTR_T *)body;
		delete ss;
	  }
	  body->clm_msg->set(csvi->getClmMsg(clm)); //
	  g_stif->body_fp->mem_alloc();
	  continue;
	}
	if (mode == 3){
	  if (strcmp(ww->c_str(),";")!=0){return(false);}
	  mode = 0;
	  continue;
	}
  }
  return(true);
}

// --------------
// #cmd
// --------------
void CsvRState_T::cmd_rtn(CsvAnl_C *csvi){
  int i;
  char *str;
  sChar *ss;

  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  ss = new sChar("");
  int clm=0;
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i){
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)){continue;}
	ss->cat(str);
	if (clm == 0) {clm=	i;}
  }
  if (body_rtn(csvi,i,ss->c_str(),-1) == false){msg->ErrMsg(csvi,E000,clm);}
  delete ss; 
}

// --------------
// #pull
// --------------
void CsvRState_T::pull_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    it->alloc_ptr = (MM_PTR_T *) new sChar(str);
    g_stif->pull_fp->mem_alloc();
    return;
    }
  msg->ErrMsg(csvi,E000,i);
  }

// --------------------
// #assign (Ver 1.02)
// --------------------
void CsvRState_T::assign_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *w_val;
  Assign_T *aa;

  aa = (Assign_T *)NULL;
  w_val = (char)NULL;
  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (w_val == (char)NULL){w_val = str; continue;}
    if (aa == (Assign_T *)NULL)
      {
      aa = new Assign_T(w_val,str);
      it->alloc_ptr = (MM_PTR_T *)aa;
      g_stif->assign_fp->mem_alloc();
      continue;
      }
    aa->siki->cat(str);
    }
  if (aa == (Assign_T *)NULL){msg->ErrMsg(csvi,E000,i);}
  }

// --------------
// #chg
// --------------
void CsvRState_T::chg_rtn(CsvAnl_C *csvi)
  {
  int i,j;
  char *str;
  char *name;
  sChar *ww;
  int    cyc;
  sChar *val;
  Reg_T *reg;
  Body_T *body;

  if (g_stif == NULL){msg->ErrMsg(csvi,E005,0); return;}
  name = NULL;
  for(i=cur_clm;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (name == NULL){name = str; continue;}
    ssc->Main(str);
    if (ssc->GetSu() < 2){continue;}
    ww = ssc->Get(0);
    cyc = SujiConvEx(ww->c_str());
    if (cyc < 0){msg->ErrMsg(csvi,E006,i); continue;}
    val = new sChar("");
    for(j=2;j<ssc->GetSu();++j){val->cat(ssc->Get(j)->c_str());}

    if (cyc > g_stif->max_cyc){g_stif->max_cyc = cyc;}
    if (strcmp(name,"#cmd")==0)
      {
      if (body_rtn(csvi,i,val->c_str(),cyc) == false){msg->ErrMsg(csvi,E000,i);}
      }
    else
      {
      it->srch_key = name;
      if (reg_fp->mem_srch() != 0){msg->ErrMsg(csvi,E007,i);}
      else
        {
        reg = (Reg_T *)reg_fp->mem_link_ptr_rd();
        body = new Body_T(reg,val->c_str(),cyc,"");
        it->alloc_ptr = (MM_PTR_T *)body;
        body->clm_msg->set(csvi->getClmMsg(i));
        g_stif->body_fp->mem_alloc();
        }
      }
    delete val;
    }
  if (name == NULL){msg->ErrMsg(csvi,E000,i);}
  }

// ---------------
// reg body store
// ---------------
bool CsvRState_T::reg_body(Reg_T *reg,char *str)
  {
  int j;

  char *siki;
  sChar *val;
  sChar *cc;
  Siki_T *sss;
  bool first;
  Siki_T *s;

  ssc->Main(str);
  if (ssc->GetSu() < 2){return(false);}
  sChar *w = ssc->Get(0);
  work->set_string(w->c_str());
  siki = work->cc_str();

  val  = new sChar("");
  for(j=2;j<ssc->GetSu();++j){val->cat(ssc->Get(j)->c_str());}
  if (strcmp(siki,"-") == 0){
	s = new Siki_T(it,"",val->c_str());
	it->alloc_ptr = (MM_PTR_T *)s;
  }
  else{
	s = new Siki_T(it,siki,val->c_str());
	it->alloc_ptr = (MM_PTR_T *)s;
  }
  s->clm_msg->set(reg->clm_msg->c_str());

  reg->body_fp->mem_alloc();
  delete val;
  return(true);
  }

// --------------
// #reg
// --------------
void CsvRState_T::reg_rtn(CsvAnl_C *csvi)
  {
  int i;
  char  *str;
  char  *name;
  char  *size;
  char  *clk;
  Reg_T *reg;
  sChar *ss;
  int clm;

  name = NULL;
  clk  = NULL;
  size = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i){
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (name == NULL){clm = i; name = str; continue;}
	if (size == NULL){size = str; continue;}
	if (clk  == NULL){
	  it->srch_key = name;
	  clk = str;
	  if (reg_fp->mem_srch() == 0){msg->ErrMsg(csvi,E002,i); return;}
	  ssc5->Main(size);
	  ss = ssc5->Get(0);
	  reg = new Reg_T(it,name,ss->c_str(),clk);
	  reg->clm_msg->set(csvi->getClmMsg(clm)); //
	  it->alloc_ptr = (MM_PTR_T *)reg;
	  reg_fp->mem_srch_alloc();
	  if (ssc5->GetSu() > 1){
		ss = ssc5->Get(1);
		reg->idx->set(ss->c_str());
	  }
	  continue;
	}
	if (reg_body(reg,str) == false){msg->ErrMsg(csvi,E000,i);}
  }
  if (size == NULL){msg->ErrMsg(csvi,E000,i);}
  if (clk == NULL){
	it->srch_key = name;
	if (reg_fp->mem_srch() == 0){msg->ErrMsg(csvi,E002,i); return;}
	ssc5->Main(size);
	ss = ssc5->Get(0);
	reg = new Reg_T(it,name,ss->c_str(),"");
	reg->clm_msg->set(csvi->getClmMsg(clm));  //
	it->alloc_ptr = (MM_PTR_T *)reg;
	reg_fp->mem_srch_alloc();
	if (ssc5->GetSu() > 1){
	  ss = ssc5->Get(1);
	  reg->idx->set(ss->c_str());
	}
  }
}

// --------------
// #reg_body
// --------------
void CsvRState_T::reg_body_rtn(CsvAnl_C *csvi){
  int i;
  char  *str;
  char  *name;
  Reg_T *reg;

  name = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i){
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (name == NULL){
	  name = str;
	  it->srch_key = name;
	  if (reg_fp->mem_srch() != 0){msg->ErrMsg(csvi,E007,i); return;}
	  reg = (Reg_T *)reg_fp->mem_link_ptr_rd();
	  reg->clm_msg->set(csvi->getClmMsg(i));
	  continue;
	}
	if (reg_body(reg,str) == false){msg->ErrMsg(csvi,E000,i);}
  }
  if (name == NULL){msg->ErrMsg(csvi,E000,i);}
}


// -----------------------
// #reg_andor (Ver 1.05)
// -----------------------
void CsvRState_T::reg_andor_rtn(CsvAnl_C *csvi)
  {
  int i;
  char  *str;
  char  *name;
  char  *def;
  Reg_T *reg;

  name = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)){continue;}
    if (name == NULL)
      {
      name = str;
      it->srch_key = name;
      if (reg_fp->mem_srch() != 0){msg->ErrMsg(csvi,E007,i); return;}
      reg = (Reg_T *)reg_fp->mem_link_ptr_rd();
      reg->clm_msg->set(csvi->getClmMsg(i));
      continue;
      }
    def = str;
    }
  if (def == NULL){msg->ErrMsg(csvi,E000,i);}
  else
    {
    reg->andor_flg = true;
    reg->andor_def->set(def);
    }
  }


// ---------------
// wire body store
// ---------------
bool CsvRState_T::wire_body(Wire_T *wire,char *str)
  {
  int j;
  sChar *siki;
  sChar *val;
  sChar *cc;
  Siki_T *sss;
  bool first;
  Siki_T *s;

  ssc->Main(str);
  if (ssc->GetSu() < 2){return(false);}
  siki = ssc->Get(0);
  val  = new sChar("");
  for(j=2;j<ssc->GetSu();++j){val->cat(ssc->Get(j)->c_str());}
  if (strcmp(siki->c_str(),"-") == 0)
    {
    s = new Siki_T(it,"",val->c_str());
    it->alloc_ptr = (MM_PTR_T *)s;
    }
  else
    {
    s = new Siki_T(it,siki->c_str(),val->c_str());
    it->alloc_ptr = (MM_PTR_T *)s;
    }
  s->clm_msg->set(wire->clm_msg->c_str());

  wire->body_fp->mem_alloc();
  delete val;
  return(true);
  }

// --------------
// #wire / #wire_o
// Ver 1.07
// --------------
void CsvRState_T::wire_rtn(CsvAnl_C *csvi,bool wire_o_flg)
  {
  int i;
  char  *str;
  char  *name;
  char  *size;
  sChar *val;
  int clm;
  Wire_T *wire;

  name = NULL;
  size = NULL;
  val  = new sChar("");
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (name == NULL)
      {
      name = str;
      it->srch_key = name;
      if (wire_fp->mem_srch() == 0){delete val; msg->ErrMsg(csvi,E008,i); return;}
      clm = i;
      continue;
      }
    if (size == NULL)
      {
      size = str;
      wire = new Wire_T(it,name,size,val->c_str(),wire_o_flg);
      continue;
      }

    // Ver 1.07
    if (wire_o_flg)
      {
      if (wire_body(wire,str) == false){msg->ErrMsg(csvi,E000,i);}
      }
    else
      {
      wire->val->cat(str);
      }
    }

  if (size == NULL){msg->ErrMsg(csvi,E000,i);}
  else
    {
    it->alloc_ptr = (MM_PTR_T *)wire;
    wire_fp->mem_srch_alloc();
	wire->clm_msg->set(csvi->getClmMsg(clm));    //
    }
  delete val;
  }


// ---------------------
// #wire_reg (Ver 1.03)
// ---------------------
void CsvRState_T::wire_reg_rtn(CsvAnl_C *csvi)
  {
  int i;
  char  *str;
  char  *name;
  char  *size;
  char  *clk;
  Reg_T *reg;
  sChar *ss;
  int clm;
  Wire_T *wire;
  bool  reg_mode;

  name = NULL;
  clk  = NULL;
  size = NULL;
  reg_mode = true;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (name == NULL){clm = i; name = str; continue;}
    if (size == NULL){size = str; continue;}
    if (clk  == NULL)
      {
      it->srch_key = name;
      clk = str;
      if (reg_fp->mem_srch() == 0){msg->ErrMsg(csvi,E002,i); return;}
      ssc5->Main(size);
      ss = ssc5->Get(0);

      // Register --- 
      reg = new Reg_T(it,name,ss->c_str(),clk);
	  reg->clm_msg->set(csvi->getClmMsg(clm));   //
      it->alloc_ptr = (MM_PTR_T *)reg;
      reg_fp->mem_srch_alloc();
      if (ssc5->GetSu() > 1)
        {
        ss = ssc5->Get(1);
        reg->idx->set(ss->c_str());
        }
      reg->wire_reg = true;

      // Wire ---
      wire = new Wire_T(it,name,size,"",false);
      it->alloc_ptr = (MM_PTR_T *)wire;
      wire_fp->mem_srch_alloc();
      wire->clm_msg->set(csvi->getClmMsg(clm));
      wire->wire_reg = true;

      continue;
      }
    if (*str == '#'){reg_mode = false; continue;}
    if (reg_mode == true)
      {
      if (reg_body(reg,str) == false){msg->ErrMsg(csvi,E000,i);}
      }
    else
      {
      wire->val->cat(str);
      }
    }
  if (clk == NULL){msg->ErrMsg(csvi,E000,i);}
  }


// --------------------------
// State Machine -> Register
// --------------------------
void CsvRState_T::CsvPostSub(RStIf_T *p_stif,char *p_siki)
  {
  RStIf_T *w_stif;
  sChar  *val;
  sChar  *siki;
  sChar  *siki2;
  sChar  *sch;
  sChar  *sch_moto;
  sChar  *size;
  Reg_T  *reg;
  Body_T *body;
  RStIf_T *up_stif;
  MM_PTR_T *sv_ptr;
  Siki_T *s;
  int    k;
  sChar  *pull;
  Wire_T *pull_wire;
  Siki_T *w_siki;
  Wire_T *wire;
  int i;
  bool    wire_use;
  bool    wire_define;
  sChar  *sss;
  Assign_T *aa;

  val      = new sChar("");
  siki     = new sChar("");
  siki2    = new sChar("");
  sch      = new sChar("");
  sch_moto = new sChar("");
  size     = new sChar("");
  wire_use = false;
  wire_define = false;


  if (p_siki == NULL){
	if (g_status->init_no > 1){
	  siki->set("(");
	  siki->cat(g_status->name->c_str());
	  siki->cat("_");
	  siki->cat(g_stif->name->c_str());
	  siki->cat(")");
	}
  }
  else {
	siki->set(p_siki);
	if (strcmp(p_siki,"")!=0){siki->cat(" && ");}

	// Ver 1.16
	up_stif = (RStIf_T *)p_stif->up_ptr;
	sv_ptr =(unsigned char *) up_stif->stif_fp->mem_mcb_ptr_rd();

	// search
	bool hitFlag = false;
	MEM_LOOP(w_stif,RStIf_T,up_stif->stif_fp)
	  if (p_stif == w_stif){hitFlag=true; break;}
	LOOP_END
	if (hitFlag==false){printf("error. #if/#elseif/#else\n");}

	McbArea_C *w_ptr = up_stif->stif_fp->mem_mcb_ptr_rd();
	bool andFlag=false;
	for(int k=0;;k++){
	  up_stif->stif_fp->mem_mcb_ptr_wr(w_ptr);
	  w_stif = (RStIf_T *)up_stif->stif_fp->mem_link_ptr_rd();
	  if (w_stif->if_kbn < 2){
		if (andFlag){siki->cat(" && ");}
		if (k>0){siki->cat("~");}
		siki->cat("(");
		siki->cat(w_stif->name->c_str());
		siki->cat(")");
		andFlag = true;
		if (w_stif->if_kbn == 0){break;}
	  }
	  w_ptr = up_stif->stif_fp->mem_mcb_before_rd();
	  if (w_ptr == MM_NULL){break;}
	}
	up_stif->stif_fp->mem_mcb_ptr_wr((McbArea_C *)sv_ptr);
  }


/*  Ver 1.16
	if (strcmp(p_stif->name->c_str(),"#else")==0)
	  {
	  up_stif = (RStIf_T *)p_stif->up_ptr;
	  sv_ptr =(unsigned char *) up_stif->stif_fp->mem_mcb_ptr_rd();
	  up_stif->stif_fp->mem_mcb_before_set();
	  w_stif = (RStIf_T *)up_stif->stif_fp->mem_link_ptr_rd();
	  siki->cat("~(");
	  siki->cat(w_stif->name->c_str());
	  siki->cat(")");
	  up_stif->stif_fp->mem_mcb_ptr_wr((McbArea_C *)sv_ptr);
	  }
	else
	  {
	  siki->cat("(");
	  siki->cat(p_stif->name->c_str());
	  siki->cat(")");
	  }
	}
*/


  // wire define ---------
  if (strcmp(siki->c_str(),"")!=0)
	{
	wire_define = true;
	for(i=0;;++i)
	  {
      sch_moto->set(g_status->name->c_str());
      sch_moto->intcat(i);
      sch_moto->cat("_p");
      it->srch_key = sch_moto->c_str();
      if (wire_fp->mem_srch() != 0){break;}
      }
    wire = new Wire_T(it,sch_moto->c_str(),"1",siki->c_str(),false);
    wire->clm_msg->set(p_stif->clm_msg->c_str());
    wire->clm_msg->cat("(*3)");
    }

  // #act (Ver 1.01) ---------------
  MEM_LOOP(sss,sChar,p_stif->act_fp)
    wire_use = true;
    val->set("?");
    val->cat(g_status->name->c_str());
    val->cat("_");
    val->cat(sss->c_str());
    it->srch_key = val->c_str();
    if (reg_fp->mem_srch() != 0)
      {
      msg->WarningMsg(p_stif->clm_msg->c_str(),it->srch_key,W000);
      }
    reg = (Reg_T *)reg_fp->mem_link_ptr_rd();
    w_siki = new Siki_T(it,sch_moto->c_str(),"1'b1");
    it->alloc_ptr = (MM_PTR_T *)w_siki;
    reg->body_fp->mem_alloc();
    w_siki->clm_msg->set(p_stif->clm_msg->c_str());
  LOOP_END

  // #stop (Ver 1.01) ---------------
  MEM_LOOP(sss,sChar,p_stif->stop_fp)
    wire_use = true;
    val->set("?");
    val->cat(g_status->name->c_str());
    val->cat("_");
    val->cat(sss->c_str());
    it->srch_key = val->c_str();
    if (reg_fp->mem_srch() != 0)
      {
      msg->WarningMsg(p_stif->clm_msg->c_str(),it->srch_key,W000);
      }
    reg = (Reg_T *)reg_fp->mem_link_ptr_rd();
    w_siki = new Siki_T(it,sch_moto->c_str(),"1'b0");
    it->alloc_ptr = (MM_PTR_T *)w_siki;
    reg->body_fp->mem_alloc();
    w_siki->clm_msg->set(p_stif->clm_msg->c_str());
  LOOP_END

  // schedule F/F ---------------
  if (p_stif->max_cyc > 0)
    {
    wire_use = true;
    // schedule F/F define ---------
    for(;;)
      {
      sch->set(g_status->name->c_str());
      sch->intcat(g_status->sch_cnt);
      ++(g_status->sch_cnt);
      size->intset(p_stif->max_cyc);
      sch->cat("_fp");
      it->srch_key = sch->c_str();
      if (reg_fp->mem_srch() != 0){break;}
      }
    reg = new Reg_T(it,sch->c_str(),size->c_str(),g_status->clk->c_str());
    reg->clm_msg->set(p_stif->clm_msg->c_str());
    reg->clm_msg->cat("(*2)");
    it->alloc_ptr = (MM_PTR_T *)reg;
    reg_fp->mem_srch_alloc();
    g_status->chg_fp->mem_alloc();

    if (strcmp(size->c_str(),"1")==0)
      {
      val->set(sch_moto->c_str());
      }
    else
      {
      val->set("{");
      val->cat(sch->c_str());
      val->cat("[");
      k = SujiConvEx(size->c_str());
      if (k > 0)
        {
        val->intcat(k-2);
        if (k==2){val->cat("],");}
        else     {val->cat(":0],");}
        }
      else      {val->cat(size->c_str()); val->cat("-2:0],");}
      val->cat(sch_moto->c_str());
      val->cat("}");
      }

    // Ver 1.06 add #####
    sChar *str;
    char xxx[6]; sprintf(xxx,"%s'b0",size->c_str()); // Ver 1.07

    MEM_LOOP(str,sChar,g_status->rst_fp)
      // w_siki = new Siki_T(it,str->c_str(),"1'b0"); Ver 1.07
      w_siki = new Siki_T(it,str->c_str(),xxx); // Ver 1.07
      w_siki->reset = true;
      it->alloc_ptr = (MM_PTR_T *)w_siki;
      reg->body_fp->mem_alloc();
    LOOP_END
    // Ver 1.06 add #####

    w_siki = new Siki_T(it,"",val->c_str());
    it->alloc_ptr = (MM_PTR_T *)w_siki;
    w_siki->clm_msg->set(p_stif->clm_msg->c_str());
    reg->body_fp->mem_alloc();
    }

  // Body F/F ---------------
  MEM_LOOP(body,Body_T,p_stif->body_fp)
    if (body->cyc > 0)
      {
      if (p_stif->max_cyc == 1)
        {
        siki2->set(sch->c_str());
        }
      else
        {
        siki2->set(sch->c_str());
        siki2->cat("[");
        siki2->intcat(body->cyc-1);
        siki2->cat("]");
        }
      }
    else
      {
      wire_use = true;
      siki2->set(sch_moto->c_str());
//      if (body->cyc == 0)     // #chg cyc = 0
//      else                    // #cmd
      }
    s = new Siki_T(it,siki2->c_str(),body->val->c_str());
    s->s_name->set(g_status->name->c_str());  // Ver 1.05
    s->clm_msg->set(body->clm_msg->c_str());
    it->alloc_ptr = (MM_PTR_T *)s;
    s->idx->set(body->idx->c_str());
    body->reg->body_fp->mem_alloc();
  LOOP_END


  // Pull Wire ---------------
  MEM_LOOP(pull,sChar,p_stif->pull_fp)
    it->srch_key = pull->c_str();
    if (wire_fp->mem_srch() != 0)
      {
      msg->WarningMsg(p_stif->clm_msg->c_str(),it->srch_key,W001);
      continue;
      }
    pull_wire = (Wire_T *)wire_fp->mem_link_ptr_rd();
    if (pull_wire->wire_o_flg == false) // Ver 1.07
      {
      if (strcmp(pull_wire->val->c_str(),"")!=0){pull_wire->val->cat(" | ");}
      pull_wire->val->cat("(");
      pull_wire->val->cat(siki->c_str());
      pull_wire->val->cat(")");
      pull_wire->clm_msg->cat(p_stif->clm_msg->c_str());
      }
    else
      {
      // Ver 1.07
      pull_wire->val->cat("(( ");
      pull_wire->val->cat(siki->c_str());
      pull_wire->val->cat(" )? 1'b1 :");
      pull_wire->end_cnt++;
      }
  LOOP_END

  // Assign Wire (Ver 1.02) ---------------
  MEM_LOOP(aa,Assign_T,p_stif->assign_fp)
    it->srch_key = aa->var->c_str();
    if (wire_fp->mem_srch() != 0)
      {
      msg->WarningMsg(p_stif->clm_msg->c_str(),it->srch_key,W001);
      continue;
      }
    pull_wire = (Wire_T *)wire_fp->mem_link_ptr_rd();
    if (pull_wire->wire_o_flg == false) // Ver 1.07
      {
      if (strcmp(pull_wire->val->c_str(),"")!=0){pull_wire->val->cat(" | ");}   // Ver 1.08
      if (strcmp(siki->c_str(),"") == 0)
        {
        pull_wire->val->cat("(");
        pull_wire->val->cat(aa->siki->c_str());
        pull_wire->val->cat(")");
        }
      else
        {
        pull_wire->val->cat("((");
        pull_wire->val->cat(siki->c_str());
        pull_wire->val->cat(") ? (");
        pull_wire->val->cat(aa->siki->c_str());
        pull_wire->val->cat(") : ");
        pull_wire->val->cat(pull_wire->size->c_str());
        pull_wire->val->cat("'h0)");
        }
      pull_wire->clm_msg->cat(p_stif->clm_msg->c_str());
      }
    else
      {
      // Ver 1.07
      pull_wire->val->cat("(( ");
      if (strcmp(siki->c_str(),"") == 0)
        {
        pull_wire->val->cat("???");
        }
      else
        {
        pull_wire->val->cat(siki->c_str());
        }

      pull_wire->val->cat(" ) ? ");
      pull_wire->val->cat(aa->siki->c_str());
      pull_wire->val->cat(" : ");
      pull_wire->clm_msg->cat(p_stif->clm_msg->c_str());

      pull_wire->end_cnt++;
      }
  LOOP_END



  if ((wire_use == true) && (wire_define == true))
    {
    it->srch_key = sch_moto->c_str();
    it->alloc_ptr = (MM_PTR_T *)wire;
    wire_fp->mem_srch_alloc();
    }
  else
    {
    if (wire_define == true) {delete wire;}
    }

  // recursive
  MEM_LOOP(w_stif,RStIf_T,p_stif->stif_fp)
    CsvPostSub(w_stif,siki->c_str());
  LOOP_END
  delete val;
  delete siki;
  delete siki2;
  delete sch;
  delete sch_moto;
  delete size;

  }


// --------------------------
// State Machine -> Register
// --------------------------
void CsvRState_T::CsvPost()
  {
  Reg_T  *reg;
  Wire_T *wire;
  Siki_T *siki;
  Siki_T *w_siki;
  sChar  *str;
  sChar  *name;

  name = new sChar("");


  // #wire_o (Ver 1.07) -------------
  MEM_LOOP(wire,Wire_T,wire_fp)
    if (wire->wire_o_flg == false){continue;}
    MEM_LOOP(w_siki,Siki_T,wire->body_fp)
      if (*(w_siki->siki->c_str()) ==0)
        {
        wire->def_val->set(w_siki->val->c_str());
        }
      else
        {
        wire->val->cat("(( ");
        wire->val->cat(w_siki->siki->c_str());
        wire->val->cat(" ) ? ");
        wire->val->cat(w_siki->val->c_str());
        wire->val->cat(" : ");
        wire->end_cnt++;
        }
    LOOP_END
  LOOP_END


  // wire_reg (Ver 1.03)
  MEM_LOOP(wire,Wire_T,wire_fp)
    if (wire->wire_reg == false){continue;}
    name->set(wire->name->c_str());
    name->cat("_pp");
    wire->val->replace_all("@",name->c_str());
  LOOP_END
  MEM_LOOP(reg,Reg_T,reg_fp)
    if (reg->wire_reg == false){continue;}
    reg->name->cat("_pp");
  LOOP_END

  // State Machine -> Register
  MEM_LOOP(g_status,RState_T,status_fp)
    MEM_LOOP(g_stif,RStIf_T,g_status->stif_fp)
      if (g_status->init_no > 1)
        {
        name->set("?");
        name->cat(g_status->name->c_str());
        name->cat("_");
        name->cat(g_stif->name->c_str());
        it->srch_key = name->c_str();
        if (reg_fp->mem_srch() == 0)
          {
          reg = (Reg_T *)reg_fp->mem_link_ptr_rd();
          }
        else
          {
          reg = new Reg_T(it,name->c_str(),"1",g_status->clk->c_str());
          it->alloc_ptr = (MM_PTR_T *)reg;
          reg_fp->mem_srch_alloc();
          }
        reg->clm_msg->cat(g_stif->clm_msg->c_str());
        reg->clm_msg->cat("(*1)");
        MEM_LOOP(str,sChar,g_status->rst_fp)
          if (strcmp(g_status->first_state->c_str(),g_stif->name->c_str()) == 0)
            {
            siki = new Siki_T(it,str->c_str(),"1'b1");
            siki->reset = true; // 1.04
            }
          else
            {
            siki = new Siki_T(it,str->c_str(),"1'b0");
            siki->reset = true; // 1.04
            }
          it->alloc_ptr = (MM_PTR_T *)siki;
          siki->clm_msg->set(g_status->clm_msg->c_str());
          reg->body_fp->mem_alloc();
        LOOP_END
        }
    LOOP_END
  LOOP_END

  MEM_LOOP(g_status,RState_T,status_fp)
    MEM_LOOP(g_stif,RStIf_T,g_status->stif_fp)
      CsvPostSub(g_stif,NULL); // State Machine Main Loop
    LOOP_END
  LOOP_END


  // #wire_o (Ver 1.07) -----------
  MEM_LOOP(wire,Wire_T,wire_fp)
    if (wire->wire_o_flg == false){continue;}
    if (*(wire->def_val->c_str()) == 0x00)
      {
      wire->val->cat(wire->size->c_str());
      wire->val->cat("'h0");
      }
    else
      {
      wire->val->cat(wire->def_val->c_str());
      }

    for(int i=0;i<wire->end_cnt;i++)
      {
      wire->val->cat(")");
      }
  LOOP_END

  
  delete name;
  }


// -----------------
// Space
// -----------------
void CsvRState_T::space(FILE *fp,int level)
  {
  int i;
  for(i=0;i<level;++i){fprintf(fp,"  ");}
  }


