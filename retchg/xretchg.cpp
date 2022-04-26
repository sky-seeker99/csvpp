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

#define K_MAC 0
#define K_WIN 1
#define K_UNIX 2
void retChg(Read64_C *in_fp,Write64_C *out_fp,int kbn);

void help()
  {
  printf("use:retchg -w|-m|-u file [-buff buffer_size]\n");
  printf("ex :retchg -w c:\\*.txt\n");
  printf("ex :retchg -m c:\\*.txt\n");
  printf("ex :retchg -u c:\\*.txt\n");
  printf("ex :retchg -u c:\\*.txt -buff 100\n");
  }

int main(int argc, char* argv[]){
  printf("return code changer Ver 1.02\n\n");
  int buff_size = 10;
  int kbn = -1;
  char *path = NULL;
  
  int state = 0;
  for(int i=1;i<argc;i++){
	if (state == 1){buff_size  = SujiConvEx(argv[i]); state = 0; continue;}
	if (strcmp(argv[i],"-m"   )  == 0   ){kbn = K_MAC;     continue;}
	if (strcmp(argv[i],"-w"   )  == 0   ){kbn = K_WIN;     continue;}
	if (strcmp(argv[i],"-u"   )  == 0   ){kbn = K_UNIX;    continue;}
	if (strcmp(argv[i],"-buff")  == 0   ){state = 1;       continue;}
	if (path                     == NULL){path  = argv[i]; continue;}
  }

  
  if ((path == NULL) || (kbn == -1)){help(); return 1;}

  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  file_inf->file_list_get(path);

  sChar *file;
  MEM_LOOP(file,sChar,file_inf->mem_fp)
    printf("%s convert.\n",file->c_str());
    if (file_inf->same_file_open(file->c_str())){
      retChg(file_inf->in_fp,file_inf->out_fp,kbn);
    }
    file_inf->same_file_close();
  LOOP_END

  delete file_inf;
  return 0;
}
//---------------------------------------------------------------------------

// # return change #####
void retChg(Read64_C *in_fp,Write64_C *out_fp,int kbn){
  if      (kbn == K_MAC ){out_fp->macRetSet();}
  else if (kbn == K_WIN ){out_fp->winRetSet();}
  else if (kbn == K_UNIX){out_fp->unixRetSet();}
  
  for(;;){
    unsigned char *buff = in_fp->read();
    if (buff == NULL){break;}
	if ((in_fp->return0dGet()) || (in_fp->return0aGet())){out_fp->writeln(buff);}
    else                                                 {out_fp->write  (buff);}
  }

}
 
