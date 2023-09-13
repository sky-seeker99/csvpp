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
//  Function Table
//   1.09 : #function_case , #function_direct
//

#ifndef _CSVFUNC_H_
#define _CSVFUNC_H_

#include "csvmsg.h"

// table class -----------------
class Tbl_T{
  public:
  sChar  *val;
  MEM_FP *inptn_fp;
  sChar  *clm_msg;
  Tbl_T(MemHeader_T  *it,char *p_val);
  ~Tbl_T();
  };

// #ftable class -----------------
class Func_T{
  public:
  sChar  *name;
  int     clm;
  MEM_FP *table_fp;
  MEM_FP *in_fp;
  sChar  *clm_msg;
  sChar        *case_str;  // Ver 1.09
  sChar        *direct;    // Ver 1.09
  Func_T(MemHeader_T  *it,char *p_name,int p_clm,char *p_case_str,char *p_direct); // Ver 1.09
  ~Func_T();
  };

// #function class -----------------
class Clm_T{
  public:
  sChar *name;
  int    clm;
  sChar  *clm_msg;
  Clm_T(char *p_name,int p_clm);
  ~Clm_T();
  };

// Function Class -----------------
class Function_T{
  public:
  MemHeader_T  *it;
  MEM_FP       *fdefi_fp;  // function define table (cell:Clm_T)
  MEM_FP       *fdefo_fp;  // function define table (cell:Func_T)
  MEM_FP       *func_fp;   // function table (cell:Func_T)
  sChar        *case_str;  // Ver 1.09
  sChar        *direct;    // Ver 1.09
  Msg_T        *msg;
  Function_T(MemHeader_T  *p_it,Msg_T *p_msg);
  ~Function_T();
  bool CsvRead(CsvAnl_C *csvi);
  void function_rtn(CsvAnl_C *csvi);
  void ftable_rtn  (CsvAnl_C *csvi);
  char *skin(sChar *str){return(str->c_str());}
  void function_str_rtn(CsvAnl_C *csvi,int kbn);
  };

#endif // _CSVFUNC_H_
