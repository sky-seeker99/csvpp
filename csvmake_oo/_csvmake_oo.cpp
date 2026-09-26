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
  printf("XLS File -> CSV File Program (OpenOffice.org Edition) Ver 1.07\n\n");

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


