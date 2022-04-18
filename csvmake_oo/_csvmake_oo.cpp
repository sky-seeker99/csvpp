/*

 * Copyright (c) 2008 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <condefs.h>
#include <vcl/utilcls.h>
#pragma hdrstop

#include "..\csvpp_xbase\zcsvfile.h"
#include "..\csvpp_xbase\zfile.h"
#include "..\csvpp_xbase\xwildcard.h"

#include "..\csvpp_xbase\xcsvmake_oo.h"
#include "..\csvpp_xbase\xcsvmake_oo.cpp"



//---------------------------------------------------------------------------
#pragma argsused

void help(){
    printf("use:csvmake_oo xlsfile dir [-s mask] [-S mask] [-U] [-E] [filter] [ext]\n");
    printf("ex :csvmake_oo aaa.xls c:\\csv \n");
    printf("ex :csvmake_oo aaa.xls c:\\csv -U\n");
    printf("ex :csvmake_oo aaa.xls c:\\csv -E\n");
    printf("ex :csvmake_oo aaa.xls c:\\csv csvtab txt\n");
    printf("ex :csvmake_oo aaa.xls c:\\csv -s a* sheet* -S ae* sheet_a*\n");
    printf("ex :csvmake_oo aaa.xls c:\\csv csvtab txt -s a* sheet* -S ae* sheet_a*\n");
}


int main(int argc, char* argv[]){
  printf("XLS File -> CSV File Program (OpenOffice.org Edition) Ver 1.06\n\n");

  char *xls_file = NULL;
  char *out_dir  = NULL;
  char *filter   = NULL;
  char *ext      = NULL;

  Application->Initialize();

  csvmake_oo_C *c = new csvmake_oo_C;
  int arg_mode = 0;
  for(int i=1;i<argc;++i){
    if (arg_mode == 0){
      if      (strcmp(argv[i],"-U")==0   ){c->moji_kind = 2; }
      else if (strcmp(argv[i],"-E")==0   ){c->moji_kind = 1; }
      else if (strcmp(argv[i],"-s")==0   ){arg_mode = 1; }
      else if (strcmp(argv[i],"-S")==0   ){arg_mode = 2; }
      else if (xls_file            ==NULL){xls_file = argv[i];}
      else if (out_dir             ==NULL){out_dir  = argv[i];}
      else if (filter              ==NULL){filter   = argv[i];}
      else if (ext                 ==NULL){ext      = argv[i];}
    }
    else if (arg_mode == 1){
      c->it->alloc_ptr = new sChar(argv[i]);
      c->sel_fp->mem_alloc();
      arg_mode = 0;
    }
    else if (arg_mode == 2){
      c->it->alloc_ptr = new sChar(argv[i]);
      c->esel_fp->mem_alloc();
      arg_mode = 0;
    }
  }

  if (out_dir == NULL){
    delete c;
    help();
    return 1;
  }


  c->csvmake_begin();
  c->csvmake(xls_file,out_dir,filter,ext);
  c->csvmake_end();
  delete c;
  return 0;
}


