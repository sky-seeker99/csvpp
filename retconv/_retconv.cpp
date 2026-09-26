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


#include "..\csvcellretchg\xretchg.cpp"

//---------------------------------------------------------------------------

#pragma argsused


void help(){
  printf("use:retconv in_file out_file [-buff buffer_size]\n");
  printf("ex :retconv aaa.csv bbb.csv\n");
}


int main(int argc, char* argv[]){
  printf("excel return conversion(crlf->lf) Ver 1.05\n\n");

  char *in_file=NULL;
  char *out_file=NULL;
  int buff_size = 10;
  int mode = 0;

  for(int i=1;i<argc;i++){
  	if (mode == 1) {buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
	if (strcmp(argv[i],"-buff")==0) {mode = 1; continue;}
    if (in_file == NULL){in_file = argv[i]; continue;}
    if (out_file== NULL){out_file= argv[i]; continue;}
  }

  if (out_file == NULL){help(); return 1;}

  char lf[2];
  char crlf[3];

  lf[0] = 0x0a;
  lf[1] = 0x00;
  crlf[0] = 0x0d;
  crlf[1] = 0x0a;
  crlf[2] = 0x00;

  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  file_inf->file_open(in_file,out_file);
  file_inf->in_fp->csvModeSet();
  cellStringReplace(file_inf->in_fp,file_inf->out_fp,crlf,lf);
  file_inf->file_close();

  delete file_inf;
  return 0;
}
//---------------------------------------------------------------------------
