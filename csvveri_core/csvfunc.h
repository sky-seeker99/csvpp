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
//  Function Table
//   1.09 : #function_case , #function_direct
//

#ifndef _CSVFUNC_H_
#define _CSVFUNC_H_

#include "csvmsg.h"

// table class -----------------
class Tbl_T{
  public:
  sChar  *val;
  MEM_FP *inptn_fp;
  sChar  *clm_msg;
  Tbl_T(MemHeader_T  *it,char *p_val);
  ~Tbl_T();
  };

// #ftable class -----------------
class Func_T{
  public:
  sChar  *name;
  int     clm;
  MEM_FP *table_fp;
  MEM_FP *in_fp;
  sChar  *clm_msg;
  sChar        *case_str;  // Ver 1.09
  sChar        *direct;    // Ver 1.09
  Func_T(MemHeader_T  *it,char *p_name,int p_clm,char *p_case_str,char *p_direct); // Ver 1.09
  ~Func_T();
  };

// #function class -----------------
class Clm_T{
  public:
  sChar *name;
  int    clm;
  sChar  *clm_msg;
  Clm_T(char *p_name,int p_clm);
  ~Clm_T();
  };

// Function Class -----------------
class Function_T{
  public:
  MemHeader_T  *it;
  MEM_FP       *fdefi_fp;  // function define table (cell:Clm_T)
  MEM_FP       *fdefo_fp;  // function define table (cell:Func_T)
  MEM_FP       *func_fp;   // function table (cell:Func_T)
  sChar        *case_str;  // Ver 1.09
  sChar        *direct;    // Ver 1.09
  Msg_T        *msg;
  Function_T(MemHeader_T  *p_it,Msg_T *p_msg);
  ~Function_T();
  bool CsvRead(CsvAnl_C *csvi);
  void function_rtn(CsvAnl_C *csvi);
  void ftable_rtn  (CsvAnl_C *csvi);
  char *skin(sChar *str){return(str->c_str());}
  void function_str_rtn(CsvAnl_C *csvi,int kbn);
  };

#endif // _CSVFUNC_H_
