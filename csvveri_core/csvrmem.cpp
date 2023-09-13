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

