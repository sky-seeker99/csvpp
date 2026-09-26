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
//  Patern
//

#ifndef _CSVRMEM_H_
#define _CSVRMEM_H_

#include "csvmsg.h"
#include "csvptn.h"

// #readfile class -----------------
class CsvRFile_T{
  public:
  VariableArea_C  *file_name;
  VariableArray_C *var_fp;   // cell:Var_T
  int              ary_max;  // ary_max
  int              wid_bus;  // width
  VariableArea_C  *ptr_name; // ptr name
  VariableArea_C  *clm_msg;  // csv line
  CsvRFile_T(char *p_file_name,char *p_ary_max,char *p_ptr_name){
    file_name = new VariableArea_C(p_file_name);
    ary_max   = SujiConvEx(p_ary_max);
    wid_bus   = 0;
    ptr_name  = new VariableArea_C(p_ptr_name);
    clm_msg   = new VariableArea_C(10);
    var_fp    = new VariableArray_C(10);
  }
  ~CsvRFile_T(){
    Var_T *v;
    delete file_name;
    delete ptr_name;
    delete clm_msg;
    ARY_LOOP(v,Var_T,var_fp) delete v; LOOP_END;
    delete var_fp;
  }
};

// PaternControlTask Class -----------------
class CsvRFileList_T{
  public:
  VariableArray_C *ary_fp; // cell:CsvRFile_T
  Msg_T           *msg;
  CsvRFile_T      *g_rf;
  CsvRFileList_T(Msg_T *p_msg){
    msg    = p_msg;
    ary_fp = new VariableArray_C(10);
    g_rf   = NULL;
  }
    
  ~CsvRFileList_T(){
    ARY_LOOP(rf,CsvRFile_T,ary_fp) delete rf; LOOP_END
    delete ary_fp;
  }
  bool CsvRead(CsvAnl_C *csvi);
  private:
  void var_rtn   (CsvAnl_C *csvi);
  void head_rtn  (CsvAnl_C *csvi);
  };

#endif // _CSVRMEM_H_
