/*

 * Copyright (c) 2013 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
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
#include "..\csvpp_xbase\xcsvmake_oo.h"

//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[]){
  printf("CSV File -> XLS File Adding Program (Libre Office Edition) Ver 1.00\n\n");

  char *p_xlsfile  = NULL;
  char *p_filter   = NULL;

  Application->Initialize();
  csvmake2_oo_C *csvmake = new csvmake2_oo_C;

  int arg_mode = 0;
  for(int i=1;i<argc;i++){
    if (strcmp(argv[i],"-x"    )==0){arg_mode = 1; continue;}
//    if (strcmp(argv[i],"-proc" )==0){csvmake->pchkFlag   = true; continue;}
    if (strcmp(argv[i],"-nv"   )==0){csvmake->visual_flg = false; continue;}
//    if (strcmp(argv[i],"-new"  )==0){csvmake->delFlg     = true; continue;}
//    if (strcmp(argv[i],"-paste")==0){csvmake->pasteFlg   = true; continue;}
//    if (strcmp(argv[i],"-xml"  )==0){csvmake->xmlFlg     = true; continue;}
    if (arg_mode == 0){
      if (p_xlsfile == NULL){p_xlsfile  = argv[i]; continue;}
      sChar *s_str = new sChar(argv[i]);
      csvmake->sheet_fp->mem_alloc ((unsigned char*)s_str);
    }
    else if (arg_mode == 1){
      p_filter = argv[i];
      arg_mode = 0;
      continue;
    }
  }

  if (p_xlsfile == NULL){
    printf("use:csvmake2_ooo xlsfile [-x filter] csvfile1 csvfile2 ... csvfilex \n");
    printf("ex :csvmake2_ooo aaa.xls -x retconv bbb.csv ccc.csv ddd.csv \n");
    printf("ex :csvmake2_ooo aaa.xls bbb.csv ccc.csv ddd.csv \n");
  }
  else {
    csvmake->csvmake_begin();
    csvmake->csvmake(p_xlsfile,p_filter);
    csvmake->csvmake_end();
  }

  delete csvmake;
  return 0;
}
