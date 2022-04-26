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
