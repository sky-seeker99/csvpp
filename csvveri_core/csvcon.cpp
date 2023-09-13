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
// UPDATE:
//   2004.1.1: VtCon_T,VtConList_T
//

#include <string.h>
#include <stdio.h>
#include "csvcon.h"

// # wire define class
ConWire_T::ConWire_T(char *p_wire,int p_size) {
  name = new sChar(p_wire);
  size = p_size;
  defined_flg = false;
  clm_msg = new sChar("");
  }
ConWire_T::~ConWire_T(){
  delete name;
  delete clm_msg;
  }

// # Connection Information
Con_T::Con_T(char *p_port_name,char *p_wire_name,char *p_index,char *p_adding){
  port_name = new sChar(p_port_name);
  wire_name = new sChar(p_wire_name);
  if (p_index == NULL){index     = new sChar("");}
  else                {index     = new sChar(p_index);}
  if (p_adding == NULL){adding    = new sChar("");}
  else                 {adding    = new sChar(p_adding);}
  clm_msg   = new sChar("");
  size      = 0;
  }
Con_T::~Con_T(){
  delete port_name;
  delete wire_name;
  delete index;
  delete adding;
  delete clm_msg;
  }

// # Instance class
Inst_T::Inst_T(MemHeader_T *it,char *p_inst_name){
  inst_name = new sChar(p_inst_name);
  mod_name  = new sChar("?????");
  con_fp    = new MEM_FP(it);
  clm_msg = new sChar("");
  }
Inst_T::~Inst_T(){
  Con_T *con;
  delete inst_name;
  delete mod_name;
  MEM_LOOP(con,Con_T,con_fp)
    delete con;
  LOOP_END
  delete con_fp;
  delete clm_msg;
  }

// # Instance Ptr
InstPtr_T::InstPtr_T(MemHeader_T *it,char *p_inst_name,int p_clm){
  inst = new Inst_T(it,p_inst_name);
  clm  = p_clm;
  clm_msg = new sChar("");
  }
InstPtr_T::~InstPtr_T(){
  delete inst;
  delete clm_msg;
  }

// # ConnectionControl Class -----------------
VtCon_T::VtCon_T(){
  ip             = (InstPtr_T **)MM_NULL;
  ip_max         = 0;
  def_wire_clm   = -1;
  def_line_clm   = -1;
  def_define_clm = -1;    // 2004.1.1
  clm_msg = new sChar("");
  }
VtCon_T::~VtCon_T(){
  int i;
  InstPtr_T  *w_ip;
  if (ip_max > 0)
    {
    for(i=0;i<ip_max;++i){w_ip = *(ip + i); delete w_ip;}
    delete [] ip;
    }
  delete clm_msg;
  }

// # ConnectionControlList Class -----------------
VtConList_T::VtConList_T(MemHeader_T  *p_it,Msg_T *p_msg){
  it          = p_it;
  msg         = p_msg;
  vc_fp       = new MEM_FP(it);
  wire_def_fp = new MEM_FP(it);
  inst_fp     = new MEM_FP(it);
  default_net   = new sChar("hnet");
  default_net_cnt  = 0;
  vc          = NULL;
  ssc         = new StrSrchInf_T();
  ssc->Set('['); ssc->SetFlg();
  ssc->Set(']');
  ssc->Set('('); ssc->SetFlg();
  ssc->Set(')');

  }
VtConList_T::~VtConList_T(){
  ConWire_T *wire;
  MEM_LOOP(wire,ConWire_T,wire_def_fp) delete wire; LOOP_END
  MEM_LOOP(vc,VtCon_T,vc_fp) delete vc; LOOP_END
  delete wire_def_fp;
  delete inst_fp;
  delete vc_fp;
  delete default_net;
  delete ssc;
  }

// Main Loop
bool VtConList_T::CsvRead(CsvAnl_C *csvi) // true:hit false:none hit
  {
  bool flg;
  char *command;

  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  if (strcmp(command,"#con_head") == 0) {flg=true; con_head_rtn(csvi) ;}
  if (strcmp(command,"#con_mod" ) == 0) {flg=true; con_mod_rtn (csvi) ;}
  if (strcmp(command,"#con"     ) == 0) {flg=true; con_rtn     (csvi) ;}
  return(flg);
  }

// Head Read Rtn
void VtConList_T::con_head_rtn(CsvAnl_C *csvi){
  int i,j;
  InstPtr_T *w_ip;
  char *str;
  bool err;

  vc = new VtCon_T();
  it->alloc_ptr = vc;
  vc_fp->mem_alloc();

  for(i=1;i<csvi->CsvSelSu_Rd();++i){
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)){continue;}
	if (strcmp(str,"#define")==0){vc->def_wire_clm = i; continue;}
	if (strcmp(str,"#width" )==0){vc->def_define_clm = i; continue;}
	if (strcmp(str,"#line"  )==0){vc->def_line_clm = i; continue;}
	++(vc->ip_max);
  }

  err = false;
  if (vc->def_wire_clm   == -1){msg->ErrMsg(csvi,E050,0); err = true;}
  if (vc->def_line_clm   == -1){msg->ErrMsg(csvi,E051,0); err = true;}
  if (vc->def_define_clm == -1){vc->def_define_clm = vc->def_wire_clm;}
  else {
	i = vc->def_define_clm;
	vc->def_define_clm = vc->def_wire_clm;
	vc->def_wire_clm   = i;
  }

  if (vc->ip_max       ==  0){msg->ErrMsg(csvi,E052,0); err = true;}
  if (err == true){
	delete vc;
	vc_fp->mem_del();
	vc = NULL;
	return;
  }

  vc->ip = new InstPtr_T*[vc->ip_max];

  j=0;
  for(i=1;i<csvi->CsvSelSu_Rd();++i){
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)){continue;}
	if (i == vc->def_wire_clm){continue;}
	if (i == vc->def_line_clm){continue;}
	w_ip = new InstPtr_T(it,str,i);
	w_ip->clm_msg->set(csvi->getClmMsg(i));
	w_ip->clm = i;
	*(vc->ip + j) = w_ip;
	++j;
  }
}

// Head Sub Rtn
void VtConList_T::con_mod_rtn(CsvAnl_C *csvi)
  {
  int i;
  InstPtr_T *w_ip;

  if (vc == NULL){msg->ErrMsg(csvi,E053,0); return;}
  for(i=0;i<vc->ip_max;++i)
    {
    w_ip = *(vc->ip + i);
	char *ww = csvi->CsvSel_Rd(w_ip->clm);
	if (csvi->blankCheck(ww))
      {
      msg->ErrMsg(csvi,E054,w_ip->clm);
      continue;
      }
    w_ip->inst->mod_name->set(csvi->CsvSel_Rd(w_ip->clm));
    }
  return;
  }

// Connect  Rtn
void VtConList_T::con_rtn(CsvAnl_C *csvi){
  int i;

  char   *w_size;
  char   *w_line;
  char   *w_define;
  sChar  *line_str;
  char   *str;
  InstPtr_T *w_ip;
  Inst_T *inst;
  ConWire_T *cw;
  Con_T *con;
  ConWire_T *w_con;
  char   *portName;
  char   *indexName;
  char   *addName;

  if (vc == NULL){msg->ErrMsg(csvi,E053,0); return;}
  // size,line get
  w_size   = csvi->CsvSel_Rd(vc->def_wire_clm);
  w_line   = csvi->CsvSel_Rd(vc->def_line_clm);
  w_define = csvi->CsvSel_Rd(vc->def_define_clm);


  if (csvi->blankCheck(w_line) == false){line_str = new sChar(w_line);}
  else{
	line_str = new sChar(default_net);
	line_str->intcat(default_net_cnt);
	++(default_net_cnt);
  }

  if (csvi->blankCheck(w_size) == false){
	it->srch_key = line_str->c_str();
	if (wire_def_fp->mem_srch() == 0){
	  w_con = (ConWire_T *) wire_def_fp->mem_link_ptr_rd();
	  if (w_con->size != SujiConvEx(w_size)){
		msg->ErrMsg(csvi,E008,vc->def_wire_clm);
	  }
	  else{
		if (w_con->defined_flg == true){
		  if (csvi->blankCheck(w_define) == false){w_con->defined_flg == false;}
		}
	  }
	}
	else {
	  cw = new ConWire_T(line_str->c_str(),SujiConvEx(w_size));
	  it->alloc_ptr = (MM_PTR_T *)cw;
	  cw->clm_msg->set(csvi->getClmMsg(vc->def_wire_clm));
	  wire_def_fp->mem_srch_alloc();
	  if (csvi->blankCheck(w_define)){w_con->defined_flg == true;} // 2004.1.1
	}
  }

  for(i=0;i<vc->ip_max;++i){
	w_ip = *(vc->ip + i);
	str = csvi->CsvSel_Rd(w_ip->clm);
	if (csvi->blankCheck(str)){continue;}
	inst = w_ip->inst;

	portName  = NULL;
	indexName = NULL;
	addName   = NULL;
	ssc->Main(str);
	int mode_kk;
	mode_kk = 0;
	for(int kk=0;kk<ssc->GetSu();++kk){
	  sChar *ww = ssc->Get(kk);
	  if (portName == NULL){portName = ww->c_str(); continue;}
	  if (strcmp(ww->c_str(),"[") == 0){mode_kk = 1; continue;}
	  if (strcmp(ww->c_str(),"(") == 0){mode_kk = 2; continue;}
	  if (mode_kk == 1){indexName = ww->c_str(); mode_kk = 0; continue;}
	  if (mode_kk == 2){addName   = ww->c_str(); mode_kk = 0; continue;}
	}

	it->srch_key = portName;
	if (inst->con_fp->mem_srch() == 0){msg->ErrMsg(csvi,E055,i);}
	else{
	  con = new Con_T(portName,line_str->c_str(),indexName,addName);
	  it->alloc_ptr = (MM_PTR_T *)con;
	  con->clm_msg->set(csvi->getClmMsg(w_ip->clm));
	  inst->con_fp->mem_srch_alloc();
	}
  }

  delete line_str;
}

// vc_fp -> inst_fp  (Ver 1.02)
void VtConList_T::complete_rtn()
  {
  int i;
  InstPtr_T *w_ip;
  Inst_T *w_it;
  Inst_T *t_it;
  Con_T *w_con;
  Con_T *t_con;
  char buff[255];

  MEM_LOOP(vc,VtCon_T,vc_fp)
    for(i=0;i<vc->ip_max;++i)
      {
      w_ip = *(vc->ip+i);
      w_it = w_ip->inst;
      it->srch_key = w_it->inst_name->c_str();
      if (inst_fp->mem_srch() == 0)
        {
        t_it = (Inst_T *)inst_fp->mem_link_ptr_rd();
        if (strcmp(t_it->mod_name->c_str(),w_it->mod_name->c_str()) != 0)
          {
          msg->ErrMsg(E056,"#con_mod",w_it->clm_msg->c_str());
          }
        MEM_LOOP(w_con,Con_T,w_it->con_fp)
          it->srch_key = w_con->port_name->c_str();
          if (t_it->con_fp->mem_srch() == 0)
            {
            t_con = (Con_T *)t_it->con_fp->mem_link_ptr_rd();
            if (strcmp(t_con->wire_name->c_str(),w_con->wire_name->c_str()) != 0)
              {
              sprintf(buff,"inst=%s port=%s net=%s",w_it->inst_name->c_str(),w_con->port_name->c_str(),w_con->wire_name->c_str());
              msg->ErrMsg(E057,"#con",buff);
              }
            }
          else
            {
            it->alloc_ptr = (MM_PTR_T *)new Con_T(w_con->port_name->c_str(),w_con->wire_name->c_str(),w_con->index->c_str(),w_con->adding->c_str());
            t_it->con_fp->mem_srch_alloc();
            }
        LOOP_END
        }
      else
        {
        it->alloc_ptr = (MM_PTR_T *)w_it;
        inst_fp->mem_srch_alloc();
        }
      }
  LOOP_END

  }
