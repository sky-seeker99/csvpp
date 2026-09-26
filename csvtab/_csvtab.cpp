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

//---------------------------------------------------------------------------
#pragma argsused

void help(){
  fprintf(stderr,"csv_file -> tab_file converter Ver 1.06\n\n");
  fprintf(stderr,"use:csvtab csv_file tab_file [-buff buffer_size] [-dbl_no_cut]\n");
  fprintf(stderr,"ex :csvtab aaa.csv bbb.tab\n");
}

void exec(Read64_C *in_fp,Write64_C *out_fp);

bool  dbl_no_cut=false;
int main(int argc, char* argv[]){
  char *in_file=NULL;
  char *out_file=NULL;
  int   buff_size=10;
  int  mode = 0;

  for(int i=1;i<argc;i++){
    if (mode == 1){buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
    if (strcmp(argv[i],"-buff") == 0){mode = 1; continue;}
    if (strcmp(argv[i],"-dbl_no_cut") == 0){dbl_no_cut = true; continue;}
    if (in_file  == NULL){in_file  = argv[i]; continue;}
    if (out_file == NULL){out_file = argv[i]; continue;}
  }

  if (out_file == NULL){help(); return 1;}

  fileInf64_C *file_inf = new fileInf64_C(buff_size);

  file_inf->file_open(in_file,out_file);

  exec(file_inf->in_fp,file_inf->out_fp);
  file_inf->file_close();

  delete file_inf;

  return 0;
}
//---------------------------------------------------------------------------

void exec(Read64_C *in_fp,Write64_C *out_fp){
  CsvAnl_C *csvi = new CsvAnl_C;
  if (dbl_no_cut) {csvi->dbl_nocut_mode();}
  in_fp->csvModeSet();
  for(;;){
	unsigned char *buff = in_fp->read();
	if (buff == NULL) {break;}
	csvi->Exec(buff);
    bool firstFlg=true;
	CSV_LOOP_NOCHK(csvi,ustr,NON_SP_PUSH)
	  if (firstFlg){firstFlg=false;}
	  else         {out_fp->write("\t");}
      out_fp->write(ustr);
    LOOP_END
    if ((in_fp->return0dGet()) || (in_fp->return0aGet())){out_fp->writeln("");}
  }
  delete csvi;
}
//---------------------------------------------------------------------------
