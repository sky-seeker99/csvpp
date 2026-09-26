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
  printf("use:csvcellretchg file [string] [-buff buffer_size]\n");
  printf("ex :csvcellretchg c:\csv\*.csv\n");
  printf("ex :csvcellretchg c:\csv\*.csv [return]\n");
  }

int main(int argc, char* argv[]){
  printf("csv file return code changer Ver 1.02\n\n");
  char *path=NULL;
  char *chg =NULL;
  int buff_size = 10;
  int mode = 0;

  for(int i=1;i<argc;i++){
  	if (mode == 1) {buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
	if (strcmp(argv[i],"-buff")==0) {mode = 1; continue;}
	if (strcmp(argv[i],"-dbl_no_cut")==0) {g_dbl_no_cut = true; continue;}
    if (path == NULL){path = argv[i]; continue;}
    if (chg  == NULL){chg  = argv[i]; continue;}
  }

  if (path == NULL){help(); return 1;}
  if (chg  == NULL){chg = "";}

  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  file_inf->file_list_get(path);

  sChar *file;
  char aa[2];
  aa[0] = 0x0a;
  aa[1] = 0x00;
  MEM_LOOP(file,sChar,file_inf->mem_fp)
    printf("%s convert.\n",file->c_str());
    if (file_inf->same_file_open(file->c_str())){
      file_inf->in_fp->csvModeSet();
      cellStringReplace(file_inf->in_fp,file_inf->out_fp,aa,chg);
    }
    file_inf->same_file_close();
  LOOP_END


  delete file_inf;
  return 0;
}
//---------------------------------------------------------------------------




