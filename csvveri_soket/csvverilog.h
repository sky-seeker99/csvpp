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
//  CSV -> Verilog-HDL Soket
//
  
#ifndef _CSVVERILOG_H_
#define _CSVVERILOG_H_

#include <stdio.h>
#include <string.h>


#include "../csvveri_core/csvmsg.h"
#include "../csvveri_core/csvvinf.h"
#include "../csvveri_core/csvclk.h"
#include "../csvveri_core/csvcon.h"
#include "../csvveri_core/csvfunc.h"
#include "..\csvveri_core\csvgate.h"
#include "../csvveri_core/csvlang.h"
#include "../csvveri_core/csvparm.h"
#include "../csvveri_core/csvptn.h"
#include "../csvveri_core/csvstate.h"
#include "../csvveri_core/csvsub.h"
#include "../csvveri_core/csvtask.h"
#include "../csvveri_core/csvrstate.h"
#include "../csvveri_core/csvcover.h"
#include "../csvveri_core/csvrmem.h"

// # coverage ##################################
class VOutReadmem_T:public CsvRFileList_T{
  public:
  VOutReadmem_T(Msg_T *p_msg):CsvRFileList_T(p_msg){};
  void PreOutput (FILE *fp);
  void Output    (FILE *fp);
};
 
 

// # coverage ##################################
class VOutCover_T:public CsvCover_T{
  public:
  VOutCover_T(MemHeader_T *p_it,Msg_T *p_msg):CsvCover_T(p_it,p_msg){};
  void PreOutput (FILE *fp);
  void Output    (FILE *fp);
  private:
  void ary_output(FILE *fp,char *str);
  };
 
 

// # Interface ##################################
class VOutVInf_T:public CsvInterface_T{
  public:
  VOutVInf_T(MemHeader_T *p_it,Msg_T *p_msg):CsvInterface_T(p_it,p_msg){};
  bool PortOutput(FILE *fp,int kbn,char *var_name);
  void PreOutput (FILE *fp);
  void Output    (FILE *fp);
  private:
  void ary_output(FILE *fp,char *str);
  };


// # adding string ###################################
class VOutAdding_T{
  public:
  sChar *key;
  sChar *val;
  VOutAdding_T(char *p_key,char *p_val){
    key = new sChar(p_key);
    val = new sChar(p_val);
    }
  ~VOutAdding_T(){
    delete key;
    delete val;
    }

  };


// # Cycle Task ######################################
class VOutTask_T:public CsvCycTaskList_T{
  public:
  sCharGrep *grep;
  VOutTask_T(MemHeader_T *p_it,Msg_T *p_msg):CsvCycTaskList_T(p_it,p_msg){grep = new sCharGrep("");};
  ~VOutTask_T(){delete grep;}
  void PreOutput (FILE *fp);
  void Output    (FILE *fp);
  void rep(sChar *str);
  };

// # Sub/Func ########################################
class VOutSub_T:public CsvSub_T{
  public:
  VOutSub_T(MemHeader_T *p_it,Msg_T *p_msg):CsvSub_T(p_it,p_msg){};
  void Output    (FILE *fp);
  private:
  void StatusWrite    (FILE *fp,If_T *p_stif,int level);
  void ary_output     (FILE *fp,char *str);
  };

// # State Machine ###################################
class VOutState_T:public CsvState_T{
  public:
  VOutState_T(MemHeader_T *p_it,Msg_T *p_msg):CsvState_T(p_it,p_msg){};
  void PreOutput (FILE *fp);
  void Output    (FILE *fp);
  void ChgCheck       (MEM_FP *reg_fp);   // Ver 1.08
  private:
  void StatusWrite    (FILE *fp,StIf_T *p_stif,int level);
  void ParmOutput     (FILE *fp);
  void OutputSub      (FILE *fp,char *clk,char *no,int size,char *line,bool kbn);
  };

// # RTL State Machine ###############################
class VOutRState_T:public CsvRState_T{
  public:
  sChar *rtype_name;  // Ver 1.27
  sChar *wtype_name;  // Ver 1.27
  VOutRState_T(MemHeader_T *p_it,Msg_T *p_msg):CsvRState_T(p_it,p_msg){
    wtype_name = new sChar("wire");
    rtype_name = new sChar("reg");
  };
  ~VOutRState_T(){
    delete wtype_name;
    delete rtype_name;
  }
  void PreOutput (FILE *fp,MEM_FP *add_fp);
  void Output    (FILE *fp,MEM_FP *add_fp);
  bool PortOutput(FILE *fp,int kbn,char *var_name);
  private:
  void reg_output          (FILE *fp,Reg_T *reg);
  void ary_output          (FILE *fp,char *str);
  };

// # RTL Connection ##################################
class VOutCon_T:public VtConList_T{
  public:
  sChar *type_name;  // Ver 1.27

  VOutCon_T(MemHeader_T *p_it,Msg_T *p_msg):VtConList_T(p_it,p_msg){
    type_name = new sChar("wire");
  };
  ~VOutCon_T(){
    delete type_name;
  }
  bool PortOutput(FILE *fp,int kbn,char *name);
  void PreOutput (FILE *fp,MEM_FP *add_fp);
  void Output    (FILE *fp);
  private:
  void AryOutput (FILE *fp,int size);
  };

// # Clock ###########################################
class VOutClk_T:public CsvClk_T{
  public:
  VOutClk_T(MemHeader_T *p_it,Msg_T *p_msg):CsvClk_T(p_it,p_msg){};
  void PreOutput (FILE *fp);
  void Output    (FILE *fp);
  };

// # Function Table ###########################################
class VOutFunc_T:public Function_T{
  public:
  VOutFunc_T(MemHeader_T *p_it,Msg_T *p_msg):Function_T(p_it,p_msg){};
  void Output    (FILE *fp);
  };

// # Gate ###########################################
class VOutGate_T:public VtGate_T{
  public:
  VOutGate_T(MemHeader_T *p_it,Msg_T *p_msg):VtGate_T(p_it,p_msg){};
  void Output    (FILE *fp);
  };

// # Parameter ###########################################
class VOutParm_T:public CsvParmList_T{
  public:
  VOutParm_T(MemHeader_T *p_it,Msg_T *p_msg):CsvParmList_T(p_it,p_msg){};
  void Output    (FILE *fp);
  };

// # Patern ###########################################
class VOutPtn_T:public CsvPtnList_T{
  public:
  VOutPtn_T(MemHeader_T *p_it,Msg_T *p_msg):CsvPtnList_T(p_it,p_msg){};
  void PreOutput (FILE *fp);
  void Output    (FILE *fp);
  };
  
#endif // _CSVVERILOG_H_  
