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

#ifndef _CSVVINF_H_
#define _CSVVINF_H_

#include "csvmsg.h"

// #inf class -----------------
class CsvInfParm_T{
  public:
  sChar  *name;
  sChar  *size;
  CsvInfParm_T(char *p_name,char *p_size);
  ~CsvInfParm_T();
  };

// #inf_send/#inf_recv class -----------------
class CsvInfSendRecv_T{
  public:
  sChar  *name;
  bool    send;   // true:send  false:recieve
  MEM_FP *mem_fp;    // cell:CsvInfParm_T
  sChar  *ary;    // fifo array
  sChar  *enable;
  CsvInfSendRecv_T(MemHeader_T  *p_it,char *p_name,bool p_send);
  ~CsvInfSendRecv_T();
  };



// Interface Class -----------------
class CsvInterface_T{
  public:
  MemHeader_T  *it;
  MEM_FP       *mem_fp;  // cell:CsvInfSendRecv_T
  Msg_T        *msg;
  CsvInfSendRecv_T *inf;
  CsvInterface_T(MemHeader_T  *p_it,Msg_T *p_msg);
  ~CsvInterface_T();
  bool CsvRead   (CsvAnl_C *csvi,MemHeader_T  *p_it,MEM_FP *in_fp,MEM_FP *out_fp);


  private:
  void inf_enable_rtn(CsvAnl_C *csvi,MemHeader_T  *p_it,MEM_FP *in_fp,MEM_FP *out_fp);
  void inf_rtn       (CsvAnl_C *csvi,MemHeader_T  *p_it,MEM_FP *in_fp,MEM_FP *out_fp);
  void inf_rs_rtn    (CsvAnl_C *csvi,MemHeader_T  *p_it,MEM_FP *inout_fp,bool send);
  };
  
#endif // _CSVVINF_H_
