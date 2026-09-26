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
// update :
//   2004.1.1: VtCon_T,VtConList_T
//

#ifndef _CSVCON_H_
#define _CSVCON_H_

#include "../csvpp_xbase/ztoken.h"
#include "csvmsg.h"

// # wire define class
class ConWire_T{
  public:
  sChar    *name;        // net name
  int       size;        // MSB
  bool      defined_flg; // defined flg
  sChar  *clm_msg;       // csv line
  ConWire_T(char *p_wire,int p_size);
  ~ConWire_T();
  };

// # Connection Information
class Con_T{
  public:
  sChar     *port_name;    // Port Name
  sChar     *wire_name;    // Wire Name
  sChar     *index;        // index
  sChar     *adding;       // adding
  sChar     *clm_msg;      // csv line
  int        size;         // MSB
  Con_T(char *p_port_name,char *p_wire_name,char *p_index,char *p_adding);
  ~Con_T();
  };

// # Instance class
class Inst_T{
  public:
  sChar    *inst_name; // Instance Name
  sChar    *mod_name;  // Module Name
  MEM_FP   *con_fp;    // Connection Information(con)
  sChar    *clm_msg;   // csv line
  Inst_T(MemHeader_T *it,char *p_inst_name);
  ~Inst_T();
  };

// # Instance Ptr
class InstPtr_T{
  public:
  int     clm;  // Column Ichi
  Inst_T *inst; // Instance Module
  sChar  *clm_msg; // csv line
  InstPtr_T(MemHeader_T *it,char *p_inst_name,int p_clm);
  ~InstPtr_T();
  };

// # ConnectionControl Class -----------------
class VtCon_T{
  public:
  InstPtr_T **ip;             // Column Module Information
  int      ip_max;            // ip max
  int      def_wire_clm;      // define wire column
  int      def_line_clm;      // define line column
  int      def_define_clm;    // define define column (2004.1.1)
  sChar   *clm_msg;           // csv line
  public:
  VtCon_T();
  ~VtCon_T();
  };

// # ConnectionControlList Class -----------------
class VtConList_T{
  public:
  MemHeader_T  *it;
  Msg_T        *msg;
  MEM_FP       *vc_fp;
  MEM_FP       *inst_fp;  // Ver 1.02
  MEM_FP       *wire_def_fp;
  sChar   *default_net;       // default net name
  int      default_net_cnt;   // default net name count
  StrSrchInf_T *ssc;
  VtCon_T      *vc;
  VtConList_T(MemHeader_T  *p_it,Msg_T *p_msg);
  ~VtConList_T();
  bool CsvRead     (CsvAnl_C *csvi);
  void complete_rtn(              );

  private:
  void con_head_rtn(CsvAnl_C *csvi);
  void con_mod_rtn (CsvAnl_C *csvi);
  void con_rtn     (CsvAnl_C *csvi);

  };

#endif // _CSVCON_H_
