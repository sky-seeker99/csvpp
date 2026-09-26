/*
 * Copyright 2026 Shigeru Kasuya
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by me or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
