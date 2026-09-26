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
//  Patern
//

#include <string.h>
#include <stdio.h>
#include "csvrmem.h"


// Main Loop
bool CsvRFileList_T::CsvRead(CsvAnl_C *csvi){
  bool flg;
  char *command;

  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  if (strcmp(command,"#readmemh") == 0){flg=true; head_rtn  (csvi);}
  if (strcmp(command,"#readvar" ) == 0){flg=true; var_rtn   (csvi);}
  return(flg);
}

// #readmemh
void CsvRFileList_T::head_rtn(CsvAnl_C *csvi){
  int i;
  char *str;
  char *ptr=NULL;
  char *ary=NULL;
  char *file=NULL;

  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i){
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (ptr  == NULL){ptr  = str; continue;}
	if (ary  == NULL){ary  = str; continue;}
	if (file == NULL){file = str; continue;}
  }
  if (file == NULL){msg->ErrMsg(csvi,E000,0); return;}



  g_rf = new CsvRFile_T(file,ary,ptr);
  ary_fp->mem_alloc((unsigned char *)g_rf);
}

// #readvar
void CsvRFileList_T::var_rtn(CsvAnl_C *csvi){
  int i;
  char *str;
  char *name=NULL;
  char *size=NULL;
  Var_T *var;

  if (g_rf == NULL){msg->ErrMsg(csvi,E110,0); return;}
  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i){
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (name == NULL){name = str; continue;}
    if (size == NULL){size = str; continue;}
  }
  if (size == NULL){msg->ErrMsg(csvi,E000,0);}
  var = new Var_T(name,size);
  g_rf->var_fp->mem_alloc((unsigned char *)var);
}

