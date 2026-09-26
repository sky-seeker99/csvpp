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
//  Clock Class
//

#ifndef _CSVCLK_H_
#define _CSVCLK_H_

#include "csvmsg.h"

// #clk --------------------
class Clk_T{
  public:
  sChar  *name;
  sChar  *cyc;
  sChar  *chg1;
  sChar  *chg2;
  sChar  *init;
  sChar  *line;
  sChar  *clm_msg;
  Clk_T(char *p_name,char *p_cyc,char *p_chg1,char *p_chg2,char *p_init,char *p_line);
  ~Clk_T();
  };

// interface class -----------------
class CsvClk_T{
  public:
  MemHeader_T  *it;
  MEM_FP       *clk_fp;
  Msg_T        *msg;
  Clk_T        *clk;
  CsvClk_T(MemHeader_T *p_it,Msg_T *p_msg);
  ~CsvClk_T();
  bool ExistCheck();
  bool CsvRead     (CsvAnl_C *csvi);
  void patern_write();
  void clk_rtn     (CsvAnl_C *csvi);
  };

#endif // _CSVCLK_H_


