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

#include "csvxml_core.h"
#include "csvxml_core.cpp"



//---------------------------------------------------------------------------
#pragma argsused

void help(){
  fprintf(stderr,"csv_file -> xml_file converter Ver 1.02\n\n");
  fprintf(stderr,"use:csvxml csv_file out_file [-header header_file] [-tag tag_file ] [-buff buffer_size] [-e]\n");
  fprintf(stderr,"ex :csvxml data.csv out.xml\n");
  fprintf(stderr,"ex :csvxml data.csv out.xml -tag tag.csv -header header.txt \n");
}


int main(int argc, char* argv[]){
  char *ctl_file=NULL;
  char *header_file=NULL;
  char *in_file=NULL;
  char *out_file=NULL;
  int   buff_size=10;
  int  mode = 0;
  bool eFlag = true;

  for(int i=1;i<argc;i++){
    if (mode == 1){buff_size   = SujiConvEx(argv[i]); mode = 0; continue;}
    if (mode == 2){header_file = argv[i]; mode = 0; continue;}
    if (mode == 3){ctl_file    = argv[i]; mode = 0; continue;}
    if (strcmp(argv[i],"-buff"  ) == 0){mode = 1; continue;}
    if (strcmp(argv[i],"-header") == 0){mode = 2; continue;}
    if (strcmp(argv[i],"-tag"   ) == 0){mode = 3; continue;}
    if (strcmp(argv[i],"-e"     ) == 0){eFlag = false; continue;}
    if (in_file  == NULL){in_file  = argv[i]; continue;}
    if (out_file == NULL){out_file = argv[i]; continue;}
  }

  if (out_file == NULL){help(); return 1;}

  Read64_C *ctl_fp      = NULL;
  Read64_C *head_fp     = NULL;

  if (ctl_file != NULL) {
    ctl_fp      = new Read64_C(ctl_file,"csv",buff_size*1024);
  }
  if (header_file != NULL) {
    head_fp     = new Read64_C(header_file,"rt",buff_size*1024);
  }
  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  file_inf->file_open(in_file,out_file);
  file_inf->in_fp->csvModeSet();

  csvxml_inf_C *csvxml = new csvxml_inf_C;
  csvxml->CsvRead(ctl_fp);
  csvxml->escapeFlag = eFlag;
  csvxml->Main(head_fp,file_inf->in_fp,file_inf->out_fp);

  file_inf->file_close();

  delete file_inf;
  if (ctl_fp != NULL){delete ctl_fp;}
  if (head_fp != NULL){delete head_fp;}
  
  return 0;
}
//---------------------------------------------------------------------------

