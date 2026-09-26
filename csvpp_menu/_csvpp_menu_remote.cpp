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

void msg(){
  printf("csvpp_menu_remote.exe excel_file [open_excel_file]\n");
  printf("ex)\n");
  printf("csvpp_menu_remote.exe aaa.xls\n");
  printf("csvpp_menu_remote.exe aaa.xls aaa.xls\n");
  exit(1);
}

void sendString(char *str){
  HWND hwndTarget = FindWindow(NULL,"csvpp_menu");
  if (hwndTarget != NULL) {
    send(hwndTarget,str);
  }
  else {
    AnsiString Msg = "csvpp_menu not Found!";
    ShowMessage ( Msg);
  }
}


int main(int argc, char* argv[])
{
  char *p0 = NULL;
  char *p1 = NULL;
  char str[10240];

  printf("csvpp_menu remote exec Ver 1.00\n");

  for(int i=1;i<argc;i++){
    if (p0 == NULL) {p0 = argv[i]; continue;}
    if (p1 == NULL) {p1 = argv[i]; continue;}
  }
  if (p0 == NULL) {
    msg();  
  }
  if (p1 == NULL){
    sprintf(str,"#exec,%s",p0);
  }
  else {
    sprintf(str,"#exec,%s,%s",p0,p1);
  }
  sendString(str);

return 0;
}
//---------------------------------------------------------------------------
