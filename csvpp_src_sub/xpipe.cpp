/*

 * Copyright (c) 2003 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
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
 
