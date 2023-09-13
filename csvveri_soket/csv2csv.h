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
//  CSV -> CSV Soket
//
  
#ifndef _CSV2CSV_H_
#define _CSV2CSV_H_

#include <stdio.h>
#include <string.h>

#include "..\csvveri_core\csvcon.h"
#include "..\csvveri_core\csvrstate.h"
#include "wire_anl.h"

// # State Machine ###################################
class csvOutState_T:public CsvState_T{
  public:
  wireAnl_C *wire_anl;
  sCharEX   *ex_str;

  csvOutState_T(MemHeader_T *p_it,Msg_T *p_msg):CsvState_T(p_it,p_msg){
	wire_anl = new wireAnl_C;
	ex_str   = new sCharEX("");
  };
  ~csvOutState_T(){
	delete wire_anl;
	delete ex_str;
  }

  void Output(FILE *fp);
  private:
  void Output_sub(FILE *fp,StIf_T *stif,int nest);
  void Output_link(FILE *fp,StIf_T *stif,int nest);
};


// # RTL State Machine ###############################
class csvOutRState_T:public CsvRState_T{
  public:
  wireAnl_C *wire_anl;

  csvOutRState_T(MemHeader_T *p_it,Msg_T *p_msg):CsvRState_T(p_it,p_msg){
    wire_anl = new wireAnl_C;
  }
  ~csvOutRState_T(){
    delete wire_anl;
  }
  void PreOutput (FILE *fp,MEM_FP *add_fp);
  void Output    (FILE *fp,MEM_FP *add_fp);
  bool PortOutput(FILE *fp,int kbn,char *var_name);
  void reg_output(FILE *fp,Reg_T *reg);
  void hex_change(sChar *str);
  void add_read(sChar *s_str);
  void reg_change(sChar *str);
  void inv_change(sChar *str);


};

// # RTL Connection ##################################
class csvOutCon_T:public VtConList_T{
  public:
  csvOutCon_T(MemHeader_T *p_it,Msg_T *p_msg):VtConList_T(p_it,p_msg){};
  bool PortOutput(FILE *fp,int kbn,char *name);
  void PreOutput (FILE *fp,MEM_FP *add_fp);
  void Output    (FILE *fp);
  };

  
#endif // _CSV2CSV_H_  
