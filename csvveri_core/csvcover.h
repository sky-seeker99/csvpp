/*

 * Copyright (c) 2009 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
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
