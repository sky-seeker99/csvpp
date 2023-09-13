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
// UPDATE
//   2004.1.1:CsvLangCell_T add,CsvLang_T
//

#ifndef _CSVLANG_H_
#define _CSVLANG_H_

#include "csvmsg.h"

// Language Cell ---------------------
class CsvLangCell_T{
  public:
  sChar *str;
  int section;
  int clm;

  CsvLangCell_T::CsvLangCell_T(char *p_str,int p_section,int p_clm);
  CsvLangCell_T::~CsvLangCell_T();
  };


// Language Class ---------------------
class CsvLang_T{
  private:
  MemHeader_T *it;
  MEM_FP *mem_fp;
  Msg_T  *msg;
  int     clm;
  int     section;

  public:
  CsvLang_T(MemHeader_T  *p_it,Msg_T *p_msg);
  ~CsvLang_T();
  bool CsvRead(CsvAnl_C *csvi);
  void Output(FILE *fp,int section);
  void Output(FILE *fp);

  private:
  void wr_rtn     (CsvAnl_C *csvi);
  void section_rtn(CsvAnl_C *csvi);
  void sp_rtn     (CsvAnl_C *csvi,int clm);
  };

#endif // _CSVLANG_H_
