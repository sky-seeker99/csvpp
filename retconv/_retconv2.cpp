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

#include "..\csvpp_xbase\xfile_interface64.h"
#include "..\csvpp_xbase\xcsvi_anl.h"
#include "..\csvcellretchg\xretchg.cpp"

//---------------------------------------------------------------------------

#pragma argsused

void help(){
  printf("use:retconv2 in_file out_file [-buff buffer_size]\n");
  printf("ex :retconv2 aaa.csv bbb.csv\n");
}


int main(int argc, char* argv[]){
  printf("excel return conversion(lf->crlf) Ver 1.05\n\n");

  char *in_file=NULL;
  char *out_file=NULL;
  int buff_size = 10;
  int mode = 0;

  for(int i=1;i<argc;i++){
  	if (mode == 1) {buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
	if (strcmp(argv[i],"-buff")==0) {mode = 1; continue;}
    if (in_file == NULL){in_file = argv[i]; continue;}
    if (out_file== NULL){out_file= argv[i]; continue;}
  }

  if (out_file == NULL){help(); return 1;}

  char lf[2];
  char crlf[3];

  lf[0] = 0x0a;
  lf[1] = 0x00;
  crlf[0] = 0x0d;
  crlf[1] = 0x0a;
  crlf[2] = 0x00;

  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  file_inf->file_open(in_file,out_file);
  file_inf->in_fp->csvModeSet();
  cellStringReplace(file_inf->in_fp,file_inf->out_fp,lf,crlf);
  file_inf->file_close();

  delete file_inf;
  return 0;
}
//---------------------------------------------------------------------------
