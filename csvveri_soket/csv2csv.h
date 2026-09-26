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
