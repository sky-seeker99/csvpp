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
#include <condefs.h>
#pragma hdrstop

#include "..\csvpp_xbase\xtemp_file64.h"
#include "..\csvpp_xbase\ztool.h"

//---------------------------------------------------------------------------

#pragma argsused

#include "_txt_catcut.h"
#include "_txt_catcut.cpp"


// # main proc #####
int main(int argc, char* argv[]){
  bool newFlg  = false;
  __int64 r_offset = (__int64)0;
  __int64 w_offset = (__int64)-1;
  __int64 r_size   = (__int64)-1;
  char *in_file  = NULL;
  char *out_file = NULL;
  int buff_size = 10;

  fprintf(stderr,"text file cat&cut Ver 1.01\n");

  // argv,argc proc
  int state = 0;
  for(int i=1;i<argc;i++){
	if (state == 1){r_offset  = SujiConvEx64(argv[i]); state = 0; continue;}
	if (state == 2){w_offset  = SujiConvEx64(argv[i]); state = 0; continue;}
	if (state == 3){r_size    = SujiConvEx64(argv[i]); state = 0; continue;}
	if (state == 4){buff_size = SujiConvEx  (argv[i]); state = 0; continue;}
	if (strcmp(argv[i],"-new"     ) == 0   ){newFlg= true;    continue;}
	if (strcmp(argv[i],"-r_offset") == 0   ){state = 1;       continue;}
	if (strcmp(argv[i],"-w_offset") == 0   ){state = 2;       continue;}
	if (strcmp(argv[i],"-size")     == 0   ){state = 3;       continue;}
	if (strcmp(argv[i],"-buff")     == 0   ){state = 4;       continue;}
	if (in_file                     == NULL){in_file  = argv[i]; continue;}
	if (out_file                    == NULL){out_file = argv[i]; continue;}
  }

  if (out_file == NULL){
	fprintf(stderr,"txt_catcut in_file out_file [-new] [-r_offset offset] [-w_offset offset] [-size size] [-buff buffer size]\n");
	fprintf(stderr,"txt_catcut aaa.txt bbb.txt      -- cat");
	fprintf(stderr,"txt_catcut aaa.txt bbb.txt -new -- copy");
	return 1;
  }

  text_ctl_T *inf = new text_ctl_T(in_file,out_file,newFlg,buff_size);
  printf("%s -> %s\n",in_file,out_file);
  inf->Main(r_offset,w_offset,r_size);
  delete inf;

return 0;
}

