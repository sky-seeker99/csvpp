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

#include "xretchg.cpp"

//---------------------------------------------------------------------------

#pragma argsused

void help(){
  printf("use:csvcellretchg file [string] [-buff buffer_size]\n");
  printf("ex :csvcellretchg c:\csv\*.csv\n");
  printf("ex :csvcellretchg c:\csv\*.csv [return]\n");
  }

int main(int argc, char* argv[]){
  printf("csv file return code changer Ver 1.02\n\n");
  char *path=NULL;
  char *chg =NULL;
  int buff_size = 10;
  int mode = 0;

  for(int i=1;i<argc;i++){
  	if (mode == 1) {buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
	if (strcmp(argv[i],"-buff")==0) {mode = 1; continue;}
	if (strcmp(argv[i],"-dbl_no_cut")==0) {g_dbl_no_cut = true; continue;}
    if (path == NULL){path = argv[i]; continue;}
    if (chg  == NULL){chg  = argv[i]; continue;}
  }

  if (path == NULL){help(); return 1;}
  if (chg  == NULL){chg = "";}

  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  file_inf->file_list_get(path);

  sChar *file;
  char aa[2];
  aa[0] = 0x0a;
  aa[1] = 0x00;
  MEM_LOOP(file,sChar,file_inf->mem_fp)
    printf("%s convert.\n",file->c_str());
    if (file_inf->same_file_open(file->c_str())){
      file_inf->in_fp->csvModeSet();
      cellStringReplace(file_inf->in_fp,file_inf->out_fp,aa,chg);
    }
    file_inf->same_file_close();
  LOOP_END


  delete file_inf;
  return 0;
}
//---------------------------------------------------------------------------




