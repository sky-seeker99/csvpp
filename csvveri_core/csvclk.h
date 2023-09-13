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


