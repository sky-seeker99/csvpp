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
//  Update
//    2004.1.1:VtGateConCell_T,VtGateCell_T add,VtGate_T update
//

#ifndef _CSVGATE_H_
#define _CSVGATE_H_

#include "csvmsg.h"

//  parts define class
class Parts_T{
  public:
  sChar     *parts_name;    // parts name
  MEM_FP    *port_fp;       // port list
  Parts_T(MemHeader_T *it,char *p_parts);
  ~Parts_T();
  };

//  Connect Class 
class VtGateConCell_T{
  public:
  sChar *port_name;
  sChar *net_name;
  char   io_kbn;   // 'i'/'o'/'c'
  VtGateConCell_T(char *p_port_name,char *p_net_name,char p_io_kbn);
  ~VtGateConCell_T();
  };

//  Instance Define Class
class VtGateCell_T{
  public:
  MemHeader_T  *it;
  sChar *inst_name;
  sChar *mod_name;
  MEM_FP *con_fp;
  VtGateCell_T(MemHeader_T *p_it,char *p_inst_name,char *p_mod_name);
  ~VtGateCell_T();
  };

// GateControl Class 
class VtGate_T{
  public:
    MemHeader_T  *it;
    Msg_T        *msg;
    MEM_FP       *parts_fp;
    MEM_FP       *verilog_fp;
    MEM_FP       *gate_fp;           // 2004.1.1
    sChar        *default_inst;      // default instance name
    int           default_inst_cnt;  // default instance name count
    sChar        *sv_default_inst;      // default instance name
    int           sv_default_inst_cnt;  // default instance name count

  VtGate_T(MemHeader_T  *p_it,Msg_T *p_msg);
  ~VtGate_T();
  bool CsvRead  (CsvAnl_C *csvi);

  private:
  void gate_rtn (CsvAnl_C *csvi);
  void net_rtn  (CsvAnl_C *csvi);
  };

#endif // _CSVGATE_H_
