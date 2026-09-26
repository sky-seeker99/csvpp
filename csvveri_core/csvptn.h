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

#ifndef _CSVPTN_H_
#define _CSVPTN_H_

#include "csvmsg.h"

// #var class -----------------
class Var_T{
  public:
  sChar  *name;
  sChar  *size;
  sChar  *clm_msg;
  Var_T(char *p_name,char *p_size);
  ~Var_T();
  };

// #patern class -----------------
class CsvPtn_T{
  public:
  sChar  *name;
  MEM_FP *var_fp;   // Var_T
  sChar  *ary_max;  // ary_max
  sChar  *end_rtn;  // end
  sChar  *clm_msg;  // csv line
  CsvPtn_T(MemHeader_T  *p_it,char *p_name);
  ~CsvPtn_T();
  };

// PaternControlTask Class -----------------
class CsvPtnList_T{
  public:
  MemHeader_T  *it;
  MEM_FP       *vtp_fp;
  Msg_T        *msg;
  CsvPtn_T     *vtp;
  CsvPtnList_T(MemHeader_T  *p_it,Msg_T *p_msg);
  ~CsvPtnList_T();
  bool CsvRead   (CsvAnl_C *csvi);
  bool ExistCheck();

  private:
  void var_rtn   (CsvAnl_C *csvi);
  void arymax_rtn(CsvAnl_C *csvi);
  void endrtn_rtn(CsvAnl_C *csvi);
  void head_rtn  (CsvAnl_C *csvi);
  };

#endif // _CSVPTN_H_
