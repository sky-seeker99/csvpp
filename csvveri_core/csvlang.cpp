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
//  Language Write II
//

#include <string.h>
#include <stdio.h>
#include "csvlang.h"

// # Language Class Cell  2004.1.1
CsvLangCell_T::CsvLangCell_T(char *p_str,int p_section,int p_clm){
  str = new sChar(p_str);
  section = p_section;
  clm     = p_clm;
  }

CsvLangCell_T::~CsvLangCell_T(){
  delete str;
  }

// # Language Class
CsvLang_T::CsvLang_T(MemHeader_T  *p_it,Msg_T *p_msg){
  it      = p_it;
  mem_fp  = new MEM_FP(it);
  msg     = p_msg;
  clm     = 0;
  section = 0;
  }

CsvLang_T::~CsvLang_T(){
  CsvLangCell_T    *str;                                      // 2004.1.1
  MEM_LOOP(str,CsvLangCell_T   ,mem_fp) delete str; LOOP_END  // 2004.1.1
  delete mem_fp;
  }

// Main Loop
bool CsvLang_T::CsvRead(CsvAnl_C *csvi) // true:hit false:none hit
  {
  bool flg;
  char *command;

  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  if (strcmp(command,"#wr"     ) == 0){flg=true; wr_rtn     (csvi   );}
  if (strcmp(command,"#sp-"    ) == 0){flg=true; sp_rtn     (csvi,-1);}
  if (strcmp(command,"#sp+"    ) == 0){flg=true; sp_rtn     (csvi,1 );}
  if (strcmp(command,"#sp0"    ) == 0){flg=true; sp_rtn     (csvi,0 );}
  if (strcmp(command,"#section") == 0){flg=true; section_rtn(csvi   );} // 2004.1.1
  return(flg);
  }

// #wr
void CsvLang_T::wr_rtn(CsvAnl_C *csvi)
  {
  int i;
  sChar *s;
  char *str;

  s = new sChar("");
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    s->cat(str);
    s->cat(" ");
    }
  it->alloc_ptr = new CsvLangCell_T(s->c_str(),section,clm);  // 2004.1.1
  mem_fp->mem_alloc();
  delete s;                                                   // 2004.1.1
  }

// #section 2004.1.1
void CsvLang_T::section_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;

  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)){continue;}
    section = SujiConvEx(str);
    break;
    }
  }


// #sp
void CsvLang_T::sp_rtn(CsvAnl_C *csvi,int kbn)
  {
  if (kbn == 0){clm = 0;}
  else         {clm = clm + kbn;}
  }

// output 2004.1.1
void CsvLang_T::Output(FILE *fp,int sec)
  {
  CsvLangCell_T *str;
  int i;

  MEM_LOOP(str,CsvLangCell_T,mem_fp)
    if (str->section != sec){continue;}
    for(i=0;i<str->clm;++i){fprintf(fp," ");}
    fprintf(fp,"%s\n",str->str->c_str());
  LOOP_END
  }

// output 2004.1.1
void CsvLang_T::Output(FILE *fp)
  {
  CsvLangCell_T *str;
  int i;

  MEM_LOOP(str,CsvLangCell_T,mem_fp)
    for(i=0;i<str->clm;++i){fprintf(fp," ");}
    fprintf(fp,"%s\n",str->str->c_str());
  LOOP_END
  }




