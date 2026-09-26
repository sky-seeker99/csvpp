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

#pragma hdrstop

#include "..\csvpp_xbase\zcsvfile.h"
#include "..\csvpp_xbase\zfile.h"
#include "..\csvpp_xbase\xwildcard.h"
#include "..\csvpp_xbase\xexec.h"
#include "..\csvpp_xbase\xread64.h"
#include "..\csvpp_xbase\xwrite64.h"
#include "..\csvpp_xbase\xcsvmake_new.h"

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
  Application->Initialize();

  printf("process kill Program Ver 1.00\n\n");

  if (argc == 1){
	printf("use:proc_kill process_name process_name ... process_name\n");
	printf("ex :proc_kill EXCEL.EXE\n");
	return 1;
  }


  Application->Initialize();
  csvmake_C *csvmake = new csvmake_C;
  csvmake->pchkFlag=true;
  //csvmake->excel_kill();

  for(int i=1;i<argc;i++){
	csvmake->process_check(argv[i],false);
  }

  delete csvmake;
  return 0;
}
//---------------------------------------------------------------------------


