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

#include "..\csvpp_xbase\xarea.h"
#include "..\csvpp_xbase\xread64.h"
#include "..\csvpp_xbase\xwrite64.h"
#include "..\csvpp_xbase\xcsvi_anl.h"

#include "text_create_core.h"
#include "text_create_core.cpp"

//---------------------------------------------------------------------------

#pragma argsused
//---------------------------------------------------------------------------


 void help()
  {
  printf("use:text_create csv_file [-buff buff_size]\n");
  printf("ex :text_create in.csv \n");
  }


int main(int argc, char* argv[])
{
  printf("text file creater Ver 1.04\n\n");
  int buff_size = 10;
  char *csv_file=NULL;
  int mode = 0;

  for(int i=1;i<argc;i++){
  	if (mode == 1) {buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
	if (strcmp(argv[i],"-buff")==0) {mode = 1; continue;}
    if (csv_file == NULL){csv_file = argv[i]; continue;}
  }

  if (csv_file == NULL){help(); return 1;}
  Read64_C *in_fp = new Read64_C(csv_file,"rt",buff_size);
  if (in_fp->okCheck()){
    text_create_C *text = new text_create_C;
    text->csvRead(in_fp);
    text->output();
    delete text;
  }
  delete in_fp;

  return 0;
}
//---------------------------------------------------------------------------