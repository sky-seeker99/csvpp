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

#include "..\csvpp_xbase\xfile_interface64.h"
#include "..\csvpp_xbase\xcsvi_anl.h"

#include "xretchg.cpp"

//---------------------------------------------------------------------------

#pragma argsused

void help(){
  fprintf(stderr,"use:csvcellretchg2 in_file out_file [string] [-buff buffer_size]\n");
  fprintf(stderr,"ex :csvcellretchg2 in.csv out.csv\n");
  fprintf(stderr,"ex :csvcellretchg2 in.csv out.csv [return]\n");
  }

int main(int argc, char* argv[]){
  fprintf(stderr,"csv file return code changer 2 Ver 1.02\n\n");
  char *in_file=NULL;
  char *out_file=NULL;
  char *chg =NULL;
  int buff_size = 10;
  int mode = 0;
  char aa[2];
  aa[0] = 0x0a;
  aa[1] = 0x00;
  char bb[4];
  bb[0] = 0x0d;
  bb[1] = 0x0a;
  bb[2] = 0x00;
  bb[3] = 0x00;

  for(int i=1;i<argc;i++){
  	if (mode == 1) {buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
	if (strcmp(argv[i],"-buff")==0) {mode = 1; continue;}
	if (strcmp(argv[i],"-dbl_no_cut")==0) {g_dbl_no_cut = true; continue;}
    if (in_file  == NULL){in_file  = argv[i]; continue;}
    if (out_file == NULL){out_file = argv[i]; continue;}
    if (chg      == NULL){chg      = argv[i]; continue;}
  }

  if (out_file == NULL){help(); return 1;}
  if (chg      == NULL){chg = "";}

  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  file_inf->file_open(in_file,out_file);
//  printf("%s->%s convert.\n",in_file,out_file);
  file_inf->in_fp->csvModeSet();
  cellStringReplaceDouble(file_inf->in_fp,file_inf->out_fp,bb,aa,chg);
  file_inf->file_close();
  delete file_inf;
  return 0;
}
//---------------------------------------------------------------------------




