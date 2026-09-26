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
#include "..\csvpp_xbase\ztool.h"

//---------------------------------------------------------------------------

#pragma argsused

void exec(Read64_C *in_fp,Write64_C *out_fp,bool spFlg,char *chg_code);

void help(){
  fprintf(stderr,"use:nullchg in_file out_file  [-chg moji] [-chgsp] [-buff buff_size]\n");
  fprintf(stderr,"ex :nullchg aaa.txt bbb.txt\n");
  fprintf(stderr,"ex :nullchg aaa.txt bbb.txt -chg @@@@@@\n");
  fprintf(stderr,"ex :nullchg aaa.txt bbb.txt -chgsp\n");
}

int main(int argc, char* argv[]){
  printf("null change program Ver 1.00\n\n");
  char *in_file=NULL;
  char *out_file=NULL;
  bool spFlg = false;
  char *chg_code = NULL;
  int mode = 0;
  int buff_size = 10;

  for(int i=1;i<argc;++i){
	if (mode==1) {chg_code = argv[i]; mode = 0; continue;}
	if (mode==2) {buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
	if (strcmp(argv[i],"-chgsp") == 0 ){spFlg = true;  continue;}
	if (strcmp(argv[i],"-chg"  ) == 0 ){mode = 1;  continue;}
	if (strcmp(argv[i],"-buff" ) == 0 ){mode = 2;  continue;}
	if (in_file        == NULL){in_file  = argv[i]; continue;}
	if (out_file       == NULL){out_file = argv[i]; continue;}
  }

  if (out_file == NULL){help(); return 1;}

  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  if (file_inf->file_open(in_file,"rb",out_file,"wb")){
	exec(file_inf->in_fp,file_inf->out_fp,spFlg,chg_code);
  }
  file_inf->file_close();
  delete file_inf;
  return 0;
}


//---------------------------------------------------------------------------
void exec(Read64_C *in_fp,Write64_C *out_fp,bool spFlg,char *chg_code){
  unsigned char c;
  int len=0;
  if (chg_code != NULL){
    len = strlen(chg_code);
  }
  for(;;){
	if (in_fp->read(&c,1)==0) {break;}
    if (c == 0x00){
      if (spFlg){
        c = ' ';
        out_fp->write(&c,1);
      }
      else if (chg_code != NULL){
        out_fp->write((unsigned char *)chg_code,len);
      }
    }
    else {
      out_fp->write(&c,1);
    }
  }
}

