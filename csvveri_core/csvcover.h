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
//  Interface
//

#ifndef _CSVCOVER_H_
#define _CSVCOVER_H_

#include "csvmsg.h"

// #coverage cell class -----------------
class CsvCoverCell_T{
  public:
  int no;
  sChar  *clk;
  sChar  *siki;
  CsvCoverCell_T(int p_no,char *p_clk,char *p_siki);
  ~CsvCoverCell_T();
  };


  
// #coverage Class -----------------
class CsvCover_T{
  public:
  MemHeader_T  *it;
  MEM_FP       *mem_fp;  // cell:CsvInfSendRecv_T
  Msg_T        *msg;
  int           no;
     
  CsvCover_T(MemHeader_T  *p_it,Msg_T *p_msg);
  ~CsvCover_T();
  bool CsvRead   (CsvAnl_C *csvi);

  private:
  void cover_rtn   (CsvAnl_C *csvi);
  };
  
#endif // _CSVCOVER_H_
