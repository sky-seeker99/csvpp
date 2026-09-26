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
#include <stdlib.h>
#include <string.h>
#include <condefs.h>
#include <windows.h>
#include <process.h>
#include <tlhelp32.h>
#pragma hdrstop

#include "..\csvpp_xbase\zcsvfile.h"
#include "..\csvpp_xbase\xwildcard.h"
#include "..\csvpp_xbase\xexec.h"
#include "..\csvpp_xbase\xread64.h"
#include "..\csvpp_xbase\xwrite64.h"
#include "..\csvpp_xbase\xtemp_file64.h"
#include "..\csvpp_xbase\xcsvmake_new.h"
#include "..\csvpp_xbase\xcsvmake_oo.h"


#include "_csvretchg.h"
#include "_csvretchg.cpp"
#include "_csvreverse.h"
#include "_csvreverse.cpp"
#include "_csvfront.h"
#include "_csvfront.cpp"

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
Inf_T *inf;

printf("CSV-File preprocessor frontend Program Ver 1.18\n");

if (argc < 2)
  {
  printf("use:csvfront csvfile\n");
  printf("ex :csvfront c:\\csv\\cmd.csv\n");
  return 1;
  }

Application->Initialize();
inf = new Inf_T;

inf->ProgramArgRead(argc,argv);
inf->CsvRead(argv[1],"");
delete inf;

        return 0;
}
//---------------------------------------------------------------------------
 
