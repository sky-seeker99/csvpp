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
