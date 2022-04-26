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
#include "..\csvpp_xbase\ztool.h"

//---------------------------------------------------------------------------

#pragma argsused

void exec(Read64_C *in_fp,Write64_C *out_fp,bool spFlg,char *chg_code);

void help(){
  fprintf(stderr,"use:nullchg in_file out_file  [-chg moji] [-chgsp] [-buff buff_size]\n");
  fprintf(stderr,"ex :nullchg aaa.txt bbb.txt\n");
  fprintf(stderr,"ex :nullchg aaa.txt bbb.txt -chg @@@@@@\n");
  fprintf(stderr,"ex :nullchg aaa.txt bbb.txt -chgsp\n");
}

int main(int argc, char* argv[]){
  printf("null change program Ver 1.00\n\n");
  char *in_file=NULL;
  char *out_file=NULL;
  bool spFlg = false;
  char *chg_code = NULL;
  int mode = 0;
  int buff_size = 10;

  for(int i=1;i<argc;++i){
	if (mode==1) {chg_code = argv[i]; mode = 0; continue;}
	if (mode==2) {buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
	if (strcmp(argv[i],"-chgsp") == 0 ){spFlg = true;  continue;}
	if (strcmp(argv[i],"-chg"  ) == 0 ){mode = 1;  continue;}
	if (strcmp(argv[i],"-buff" ) == 0 ){mode = 2;  continue;}
	if (in_file        == NULL){in_file  = argv[i]; continue;}
	if (out_file       == NULL){out_file = argv[i]; continue;}
  }

  if (out_file == NULL){help(); return 1;}

  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  if (file_inf->file_open(in_file,"rb",out_file,"wb")){
	exec(file_inf->in_fp,file_inf->out_fp,spFlg,chg_code);
  }
  file_inf->file_close();
  delete file_inf;
  return 0;
}


//---------------------------------------------------------------------------
void exec(Read64_C *in_fp,Write64_C *out_fp,bool spFlg,char *chg_code){
  unsigned char c;
  int len=0;
  if (chg_code != NULL){
    len = strlen(chg_code);
  }
  for(;;){
	if (in_fp->read(&c,1)==0) {break;}
    if (c == 0x00){
      if (spFlg){
        c = ' ';
        out_fp->write(&c,1);
      }
      else if (chg_code != NULL){
        out_fp->write((unsigned char *)chg_code,len);
      }
    }
    else {
      out_fp->write(&c,1);
    }
  }
}

