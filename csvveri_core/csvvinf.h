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
