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
//  Parameter
//

#ifndef _CSVPARM_H_
#define _CSVPARM_H_

#include "csvmsg.h"

// #phead class -----------------
class CsvParm_T{
  public:
  sChar  *name;
  MEM_FP *mem_fp;
  MEM_FP *clm_fp;
  CsvParm_T(MemHeader_T  *p_it,char *p_name);
  ~CsvParm_T();
  };

// PaternControlTask Class -----------------
class CsvParmList_T{
  public:
  MemHeader_T  *it;
  MEM_FP       *vtp_fp;
  Msg_T        *msg;
  CsvParm_T     *vtp;
  CsvParmList_T(MemHeader_T  *p_it,Msg_T *p_msg);
  ~CsvParmList_T();
  bool CsvRead   (CsvAnl_C *csvi);
  bool ExistCheck();

  private:
  void set_rtn(CsvAnl_C *csvi);
  void head_rtn(CsvAnl_C *csvi);
  };

#endif // _CSVPARM_H_
