/*
 
 * Copyright (c) 2003 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
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
