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
#include <condefs.h>
#include <stdio.h>
#include <fcntl.h>
#pragma hdrstop

#include "..\csvpp_xbase\zcsvfile.h"
#include "..\csvpp_xlang\xdbctl.h"

#include "_csvlib.cpp"

//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[])
{
  DbApi_T *it;
  char *str;
  MEM_FP *msg_fp;

  printf("CSV-file preprocessor library Ver 1.02\n");

  it = new DbApi_T(argv,argc);

  it->Main();
/*
  msg_fp = it->GetMsg();
  MEM_LOOP(str,char,msg_fp)
    printf("%s\n",str);
  LOOP_END
*/
  if (it->error_flg == true)
    {
    printf("use:csvlib c in_csv out_csv lib1 lib2 - libn\n");
    printf("    csvlib a libfile csvfile1 csvfile2 - csvfilen\n");
    printf("    csvlib d libfile class1 class2 - classn\n");
    printf("    csvlib o libfile csvfile\n");
    printf("    csvlib l libfile logfile\n");
    printf("ex :csvlib c cmd.csv include.csv aaa.db bbb.db\n");
    printf("    csvlib a aaa.db a.csv b.csv c.csv\n");
    printf("    csvlib d aaa.db aaa_class bbb_class\n");
    printf("    csvlib o aaa.db out.csv\n");
    printf("    csvlib l aaa.db out.log\n");
    }

  delete it;

        return 0;
}



