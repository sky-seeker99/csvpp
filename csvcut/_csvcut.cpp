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
#include "..\csvpp_xbase\ztoken.h"


#include "csvcut_core.h"
#include "csvcut_core.cpp"

//---------------------------------------------------------------------------

#pragma argsused

void help(){
  fprintf(stderr,"use:csvcut csv_in_file csv_out_file koumoku,koumoku,koumoku-koumoku,....\n");
  fprintf(stderr,"ex :csvcut aaa.csv aaa_out.csv 1,3-5,7,9\n");
  fprintf(stderr,"ex :type aaa.csv | csvcut - - 1,3-5,7,9 > aaa_out.csv\n");
}


int main(int argc, char* argv[]){
  fprintf(stderr,"csv_file cutter converter Ver 1.05\n\n");

  char *in_file=NULL;
  char *out_file=NULL;
  char *parm=NULL;
  
  for(int i=1;i<argc;i++){
    if (in_file  == NULL){in_file  = argv[i]; continue;}
    if (out_file == NULL){out_file = argv[i]; continue;}
    if (parm     == NULL){parm     = argv[i]; continue;}
  }

  if (parm == NULL){
    help();
    return 1;
  }


  CsvCut_C *csvcut = new CsvCut_C;
  fileInf64_C *file_inf = new fileInf64_C(10240);
  file_inf->file_open(in_file,out_file);
  bool okFlg=true;
  if (file_inf->in_fp->okCheck() == false){printf("input file error. file=%s\n",in_file); okFlg=false;}
  else if (file_inf->out_fp->okCheck() == false){printf("output file error. file=%s\n",out_file); okFlg=false;}
 
  if (okFlg){  
    csvcut->parmGet(parm);
    csvcut->Main(file_inf->in_fp,file_inf->out_fp);
  }

  file_inf->file_close();

  delete csvcut;

  delete file_inf;

  return 0;
}
//---------------------------------------------------------------------------
