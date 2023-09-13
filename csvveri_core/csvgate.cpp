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
//  Update
//    2004.1.1:VtGateConCell_T,VtGateCell_T add,VtGate_T update
//

#include <string.h>
#include <stdio.h>
#include "csvgate.h"
                  
//  parts define class
Parts_T::Parts_T(MemHeader_T *it,char *p_parts){
  parts_name = new sChar(p_parts);
  port_fp    = new MEM_FP(it);
  }
Parts_T::~Parts_T(){
  sChar *port;
  delete parts_name;
  MEM_LOOP(port,sChar,port_fp)
    delete port;
  LOOP_END
  delete port_fp;
  }

//  Connect Class 2004.1.1 ---------
VtGateConCell_T::VtGateConCell_T(char *p_port_name,char *p_net_name,char p_io_kbn){
  port_name = new sChar(p_port_name);
  net_name  = new sChar(p_net_name);
  io_kbn    = p_io_kbn;
  if (io_kbn == 'e'){io_kbn = 'i';}
  }

VtGateConCell_T::~VtGateConCell_T(){
  delete port_name;
  delete net_name;
  }

//  Instance Define Class 2004.1.1 --------------
VtGateCell_T::VtGateCell_T(MemHeader_T *p_it,char *p_inst_name,char *p_mod_name){
  it        = p_it;
  inst_name = new sChar(p_inst_name);
  mod_name  = new sChar(p_mod_name);
  con_fp    = new MEM_FP(it);
  }

VtGateCell_T::~VtGateCell_T(){
  VtGateConCell_T *vgcc;

  delete inst_name;
  delete mod_name;
  MEM_LOOP(vgcc,VtGateConCell_T,con_fp) delete vgcc; LOOP_END
  delete con_fp;
  }

// GateControl Class -----------------
VtGate_T::VtGate_T(MemHeader_T  *p_it,Msg_T *p_msg){
  it   = p_it;
  msg  = p_msg;
  parts_fp      = new MEM_FP(it);
  verilog_fp    = new MEM_FP(it);
  gate_fp       = new MEM_FP(it);  // 2004.1.1
  default_inst  = new sChar("hinst");
  default_inst_cnt = 0;
  sv_default_inst  = new sChar("hinst");
  sv_default_inst_cnt = 0;
  }

VtGate_T::~VtGate_T(){
  Parts_T *parts;
  sChar   *str;
  VtGateCell_T *vgc;  // 2004.1.1

  MEM_LOOP(vgc  ,VtGateCell_T,gate_fp   ) delete vgc;   LOOP_END  // 2004.1.1
  MEM_LOOP(parts,Parts_T     ,parts_fp  ) delete parts; LOOP_END
  MEM_LOOP(str  ,sChar       ,verilog_fp) delete str;   LOOP_END
  delete parts_fp;
  delete gate_fp;  // 2004.1.1
  delete verilog_fp;
  delete default_inst;
  delete sv_default_inst;
  }

// Main Loop
bool VtGate_T::CsvRead(CsvAnl_C *csvi) // true:hit false:none hit
  {
  bool flg;
  char *command;

  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  if (strcmp(command,"#gate"      ) == 0) {flg=true; gate_rtn      (csvi) ;}
  if (strcmp(command,"#net"       ) == 0) {flg=true; net_rtn       (csvi) ;}
  return(flg);
  }

// Gate Syori
void VtGate_T::gate_rtn(CsvAnl_C *csvi)
  {
  int i;
  int first;
  char *str;
  Parts_T *parts;

  first = 0;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)){continue;}
    if (first == 0)
      {
      it->srch_key = str;
      if (parts_fp->mem_srch() == 0){msg->ErrMsg(csvi,E040,i); return;}
      parts = new Parts_T(it,str);
      it->alloc_ptr = (MM_PTR_T *)parts;
      parts_fp->mem_srch_alloc();
      first = 1;
      continue;
      }
    it->alloc_ptr = (MM_PTR_T *)new sChar(str);
    parts->port_fp->mem_alloc();
    }
  }

// Net Syori 
void VtGate_T::net_rtn(CsvAnl_C *csvi)
  {
  int i;
  int first;
  char *str;
  Parts_T *parts;
  sChar *cmd;
  sChar *w;
  int first2;
  // 2004.1.1
  sChar *inst_name;
  char  *mod_name;
  VtGateCell_T *vgc;
  VtGateConCell_T *vgcc;
  char io_kbn;

  io_kbn = 'o';
  first = 0;
  first2 = 0;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)){continue;}
    if (first == 0)
      {
      it->srch_key = str;
      if (parts_fp->mem_srch() != 0){msg->ErrMsg(csvi,E040,i);}
      parts = (Parts_T *)parts_fp->mem_link_ptr_rd();
      parts->port_fp->mem_mcb_top_set();
      first = 1;
      cmd = new sChar(str);
      cmd->cat(" ");
      cmd->cat(default_inst->c_str());
      if (default_inst_cnt >= 0){  // Ver 1.28
        cmd->intcat(default_inst_cnt);
        ++default_inst_cnt;
      }
      cmd->cat("(");

      // 2004.1.1
      inst_name = new sChar(default_inst->c_str());
      if (default_inst_cnt >= 0){ // Ver 1.28
        inst_name->intcat(default_inst_cnt-1);
      }
      else {
        default_inst_cnt = sv_default_inst_cnt;
        default_inst->set(sv_default_inst->c_str());
      }
      mod_name = str;
      vgc = new VtGateCell_T(it,inst_name->c_str(),mod_name);
      delete inst_name;
      continue;
      }
    if (parts->port_fp->mem_mcb_ptr_rd() == MM_NULL){msg->ErrMsg(csvi,E041,i); break;}
    w = (sChar *)parts->port_fp->mem_link_ptr_rd();

    if (strcmp(w->c_str(),"#")==0)
      {
      ++first;
      if (strcmp(str,"#")!=0){msg->ErrMsg(csvi,E041,i); break;}
      if (io_kbn == 'e'){io_kbn = 'c';}
      if (io_kbn == 'i'){io_kbn = 'e';}
      if (io_kbn == 'o'){io_kbn = 'i';}
      }
    else
      {
      if (strcmp(str,"#")==0)
        {
        if (first != 1){msg->ErrMsg(csvi,E041,i); break;}
        for(;;)
          {
          if (parts->port_fp->mem_mcb_ptr_rd() == MM_NULL){break;}
          w = (sChar *)parts->port_fp->mem_link_ptr_rd();
          if (strcmp(w->c_str(),"#")==0){++first; break;}
          parts->port_fp->mem_mcb_next_set();
          }
        }
      else
        {
        if (first2 == 1){cmd->cat(",");}
        else            {first2 = 1;}
        cmd->cat(".");
        cmd->cat(w->c_str());
        cmd->cat("(");
        cmd->cat(str);
        cmd->cat(")");

        // 2004.1.1
        vgcc = new VtGateConCell_T(w->c_str(),str,io_kbn);
        it->alloc_ptr = vgcc;
        vgc->con_fp->mem_alloc();
        }
      }
    parts->port_fp->mem_mcb_next_set();
    }

  cmd->cat(");");
  it->alloc_ptr = cmd;
  verilog_fp->mem_alloc();
  }


