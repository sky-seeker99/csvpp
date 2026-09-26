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

#include <stdio.h>
#include <string.h>
#pragma hdrstop

#include "..\csvpp_xbase\xfile_interface64.h"
#include "..\csvpp_xbase\xcsvi_anl.h"
#include "..\csvpp_xbase\ztoken.h"

#include "..\csvveri_soket\csvverilog.h"
#include "..\csvveri_soket\wire_anl.h"
#include "..\csvveri_soket\csv2csv.h"

#include "..\csvveri_soket\csvverilog.cpp"
#include "..\csvveri_soket\wire_anl.cpp"
#include "..\csvveri_soket\csv2csv.cpp"

#include "_csvveri.cpp"
#include "_csv2csv.cpp"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[])
{
  char *csv_file=NULL;
  char *out_file=NULL;
  int   mode=0;

  printf("Csv-Verilog Maker II Ver 1.28\n");
  for(int i=1;i<argc;i++){
	if (strcmp(argv[i],"-csvout")==0) {mode = 1; continue;}
	if (csv_file == NULL) {csv_file = argv[i]; continue;}
	if (out_file == NULL) {out_file = argv[i]; continue;}
  }

  if (out_file == NULL){
	printf("use:csvveri csvfile verilog_file\n");
	printf("ex :csvveri aaa.csv aaa.v\n");
	return 1;
  }
  if (mode == 0) {
	VOutTop_T *it = new VOutTop_T(csv_file,out_file);
	delete it;
  }
  else {
	csvOutTop_T *it = new csvOutTop_T(csv_file,out_file);
	it->main();
	it->output();
	delete it;
  }

  return 0;
}


