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

#include "..\csvpp_xbase\zcsvfile.h"

#include "_csvarc.cpp"
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
Inf_T *inf;
printf("command line archiver Ver 1.02\n\n");

if (argc != 3)
  {
  printf("use:csvarc csv log\n");
  printf("ex :csvarc aaa.csv out.log\n");
  return 1;
  }

inf = new Inf_T();
inf->Main(argv[1],argv[2]);

delete inf;
        return 0;
}
//---------------------------------------------------------------------------



