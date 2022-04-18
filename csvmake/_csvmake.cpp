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

#pragma hdrstop

#include "..\csvpp_xbase\zcsvfile.h"
#include "..\csvpp_xbase\zfile.h"
#include "..\csvpp_xbase\xwildcard.h"
#include "..\csvpp_xbase\xexec.h"
#include "..\csvpp_xbase\xread64.h"
#include "..\csvpp_xbase\xwrite64.h"
#include "..\csvpp_xbase\xcsvmake_new.h"

//---------------------------------------------------------------------------
#pragma argsused

int main(int argc, char* argv[]){
  printf("XLS File -> CSV File Program Ver 1.08\n\n");

  char *p_xlsfile =NULL;
  char *p_dir     =NULL;
  char *p_filter  =NULL;
  char *p_ext     =NULL;
  int  arg_mode   = 0;

  Application->Initialize();
  csvmake_C *csvmake = new csvmake_C;

  for(int i=1;i<argc;i++){
    if (strcmp(argv[i],"-s"   )==0){arg_mode = 1; continue;}
    if (strcmp(argv[i],"-S"   )==0){arg_mode = 2; continue;}
    if (strcmp(argv[i],"-tmp" )==0){csvmake->tmpFlag  = true; continue;}
    if (strcmp(argv[i],"-proc")==0){csvmake->pchkFlag = true; continue;}
    if (arg_mode == 0){
      if (p_xlsfile == NULL){p_xlsfile  = argv[i]; continue;}
      if (p_dir     == NULL){p_dir      = argv[i]; continue;}
      if (p_filter  == NULL){p_filter   = argv[i]; continue;}
      if (p_ext     == NULL){p_ext      = argv[i]; continue;}
    }
    else {
      sChar *s_str = new sChar(argv[i]);
      if (arg_mode == 1){csvmake->sel_fp->mem_alloc ((unsigned char*)s_str);}
      if (arg_mode == 2){csvmake->esel_fp->mem_alloc((unsigned char*)s_str);}
    }
  }
  if (p_dir == NULL){
    printf("use:csvmake xlsfile dir [filter] [ext] [-tmp] [-proc]\n");
    printf("ex :csvmake aaa.xls c:\\csv \n");
    printf("ex :csvmake aaa.xls c:\\csv csvtab txt\n");
    printf("ex :csvmake aaa.xls c:\\csv -s a* sheet* -S ae* sheet_a*\n");
    printf("ex :csvmake aaa.xls c:\\csv csvtab txt -s a* sheet* -S ae* sheet_a*\n");
  }
  else {
    csvmake->csvmake_begin();
    csvmake->csvmake(p_xlsfile,p_dir,p_filter,p_ext,NULL);
    csvmake->csvmake_end();
  }

  delete csvmake;

  return 0;
}
