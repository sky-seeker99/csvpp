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

//---------------------------------------------------------------------------
#include <stdio.h>
#include <condefs.h>
#pragma hdrstop

#include "..\csvpp_xbase\xtemp_file64.h"
#include "..\csvpp_xbase\ztool.h"

//---------------------------------------------------------------------------

#pragma argsused

#include "_txt_catcut.h"
#include "_txt_catcut.cpp"


// # main proc #####
int main(int argc, char* argv[]){
  bool newFlg  = false;
  __int64 r_offset = (__int64)0;
  __int64 w_offset = (__int64)-1;
  __int64 r_size   = (__int64)-1;
  char *in_file  = NULL;
  char *out_file = NULL;
  int buff_size = 10;

  fprintf(stderr,"text file cat&cut Ver 1.01\n");

  // argv,argc proc
  int state = 0;
  for(int i=1;i<argc;i++){
	if (state == 1){r_offset  = SujiConvEx64(argv[i]); state = 0; continue;}
	if (state == 2){w_offset  = SujiConvEx64(argv[i]); state = 0; continue;}
	if (state == 3){r_size    = SujiConvEx64(argv[i]); state = 0; continue;}
	if (state == 4){buff_size = SujiConvEx  (argv[i]); state = 0; continue;}
	if (strcmp(argv[i],"-new"     ) == 0   ){newFlg= true;    continue;}
	if (strcmp(argv[i],"-r_offset") == 0   ){state = 1;       continue;}
	if (strcmp(argv[i],"-w_offset") == 0   ){state = 2;       continue;}
	if (strcmp(argv[i],"-size")     == 0   ){state = 3;       continue;}
	if (strcmp(argv[i],"-buff")     == 0   ){state = 4;       continue;}
	if (in_file                     == NULL){in_file  = argv[i]; continue;}
	if (out_file                    == NULL){out_file = argv[i]; continue;}
  }

  if (out_file == NULL){
	fprintf(stderr,"txt_catcut in_file out_file [-new] [-r_offset offset] [-w_offset offset] [-size size] [-buff buffer size]\n");
	fprintf(stderr,"txt_catcut aaa.txt bbb.txt      -- cat");
	fprintf(stderr,"txt_catcut aaa.txt bbb.txt -new -- copy");
	return 1;
  }

  text_ctl_T *inf = new text_ctl_T(in_file,out_file,newFlg,buff_size);
  printf("%s -> %s\n",in_file,out_file);
  inf->Main(r_offset,w_offset,r_size);
  delete inf;

return 0;
}

