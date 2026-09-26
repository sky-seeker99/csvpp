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
  printf("CSV File -> XLS File Adding Program Ver 1.12\n\n");

  char *p_xlsfile  = NULL;
  char *p_filter   = NULL;

  Application->Initialize();
  csvmake_C *csvmake = new csvmake_C;
  int arg_mode = 0;
  for(int i=1;i<argc;i++){
    if (strcmp(argv[i],"-x"    )==0){arg_mode = 1; continue;}
    if (strcmp(argv[i],"-proc" )==0){csvmake->pchkFlag   = true; continue;}
    if (strcmp(argv[i],"-nv"   )==0){csvmake->visual_flg = false; continue;}
    if (strcmp(argv[i],"-new"  )==0){csvmake->delFlg     = true; continue;}
    if (strcmp(argv[i],"-paste")==0){csvmake->pasteFlg   = true; continue;}
    if (strcmp(argv[i],"-xml"  )==0){csvmake->xmlFlg     = true; continue;}
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
    printf("use:csvmake2 xlsfile [-x filter] [-nv] [-new] [-paste] [-proc] csvfile1 csvfile2 ... csvfilex \n");
    printf("ex :csvmake2 aaa.xls -x retconv bbb.csv ccc.csv ddd.csv \n");
    printf("ex :csvmake2 aaa.xls bbb.csv ccc.csv ddd.csv \n");
  }
  else {
    csvmake->csvmake2_begin();
    csvmake->csvmake2(p_xlsfile,p_filter);
    csvmake->csvmake2_end();
  }

  delete csvmake;
  return 0;
}
