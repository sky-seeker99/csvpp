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

void send(HWND hwndTarget,char *str){
  COPYDATASTRUCT data;
  data.dwData = 1;
  data.cbData = strlen(str)+ 1;
  data.lpData = (void*)str;
  SendMessage(hwndTarget,WM_COPYDATA,(WPARAM)Application->Handle,(LPARAM)&data);
}


int main(int argc, char* argv[])
{


  char str[10240];
  HWND hwndTarget = FindWindow(NULL,"ConsoleOutputGet");
  if (hwndTarget != NULL) {
    send(hwndTarget,"-->");

    for(;;){
//	  if (gets(str) == NULL){break;}
	  if (fgets(str, sizeof(str), stdin) == NULL){break;}
	  bool hitFlag = false;
	  for(int i=0;i<=sizeof(str);i++){
		if (*(str+i) == 0x00) {
		  hitFlag = true;
		  break;
		}
	  }
	  if (hitFlag==false) {
		send(hwndTarget,"??\n");
		continue;
	  }
	  send(hwndTarget,str);
	}
//    send(hwndTarget,"Ready OK.");
  }
  else {
	fprintf(stderr,"Window(ConsoleOutputGet) not Found!\n");
	for(;;){
//	  if (gets(str) == NULL){break;}
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
		continue;
	  }
	  printf("%s\n",str);
	}
  }

return 0;
}
//---------------------------------------------------------------------------
