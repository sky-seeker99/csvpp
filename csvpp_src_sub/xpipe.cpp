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
#include <vcl.h>

#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
FILE *fp;
char str[4096];

if (argc != 2)
  {
  printf("pipe program ver 1.01\n");
  printf("use:pp log_file\n");
  printf("ex :pp c:\csv\log\n");
  return 1;
  }


fp = fopen(argv[1],"wt");
if (fp == NULL){printf("file open error.(file=%s)\n",argv[1]);}
for(;;){
//  if (gets(str) == NULL){break;}
  if (fgets(str, sizeof(str), stdin) == NULL){break;}

  bool hitFlag = false;
  for(int i=0;i<=sizeof(str);i++){
	if (*(str+i) == 0x00) {
	  hitFlag = true;
	  break;  
	}
  }
  if (hitFlag==false) {
	printf("??\n");
	if (fp != NULL){fprintf(fp,"??\n");}
	continue;
  }

  printf("%s",str);
  if (fp != NULL){fprintf(fp,"%s",str);}
}
if (fp != NULL){fclose(fp);}

        return 0;
}
//---------------------------------------------------------------------------
 
