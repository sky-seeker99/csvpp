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
