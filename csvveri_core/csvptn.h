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
