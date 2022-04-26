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

//---------------------------------------------------------------------------
#pragma argsused

void help(){
  fprintf(stderr,"csv_file -> tab_file converter Ver 1.06\n\n");
  fprintf(stderr,"use:csvtab csv_file tab_file [-buff buffer_size] [-dbl_no_cut]\n");
  fprintf(stderr,"ex :csvtab aaa.csv bbb.tab\n");
}

void exec(Read64_C *in_fp,Write64_C *out_fp);

bool  dbl_no_cut=false;
int main(int argc, char* argv[]){
  char *in_file=NULL;
  char *out_file=NULL;
  int   buff_size=10;
  int  mode = 0;

  for(int i=1;i<argc;i++){
    if (mode == 1){buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
    if (strcmp(argv[i],"-buff") == 0){mode = 1; continue;}
    if (strcmp(argv[i],"-dbl_no_cut") == 0){dbl_no_cut = true; continue;}
    if (in_file  == NULL){in_file  = argv[i]; continue;}
    if (out_file == NULL){out_file = argv[i]; continue;}
  }

  if (out_file == NULL){help(); return 1;}

  fileInf64_C *file_inf = new fileInf64_C(buff_size);

  file_inf->file_open(in_file,out_file);

  exec(file_inf->in_fp,file_inf->out_fp);
  file_inf->file_close();

  delete file_inf;

  return 0;
}
//---------------------------------------------------------------------------

void exec(Read64_C *in_fp,Write64_C *out_fp){
  CsvAnl_C *csvi = new CsvAnl_C;
  if (dbl_no_cut) {csvi->dbl_nocut_mode();}
  in_fp->csvModeSet();
  for(;;){
	unsigned char *buff = in_fp->read();
	if (buff == NULL) {break;}
	csvi->Exec(buff);
    bool firstFlg=true;
	CSV_LOOP_NOCHK(csvi,ustr,NON_SP_PUSH)
	  if (firstFlg){firstFlg=false;}
	  else         {out_fp->write("\t");}
      out_fp->write(ustr);
    LOOP_END
    if ((in_fp->return0dGet()) || (in_fp->return0aGet())){out_fp->writeln("");}
  }
  delete csvi;
}
//---------------------------------------------------------------------------
