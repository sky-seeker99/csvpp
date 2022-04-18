/*

 * Copyright (c) 2009 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
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
