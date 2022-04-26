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

#include "_csvstrcnv.h"
#include "_csvstrcnv.cpp"

//---------------------------------------------------------------------------

#pragma argsused


void help(){
  printf("csv string converter for excel Ver 1.03\n\n");
  printf("use:csvstrcnv [+all] [+num] [+numex] [+dbl] [+single] in_file out_file\n");
  printf("ex :csvstrcnv +dbl +single aaa_org.csv aaa.csv\n");
  printf("ex :type aaa_org.csv | csvstrcnv +dbl - - > aaa.csv\n");
}


int main(int argc, char* argv[]){
  char *in_file=NULL;
  char *out_file=NULL;
  csvstrcnv_T c;
  bool def_flg = true;
  int   buff_size=10;
  int  mode = 0;

  for(int i=1;i<argc;++i){
    if (mode == 1){buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
    if (strcmp(argv[i],"-buff") == 0){mode = 1; continue;}
    if (*argv[i] == '+'){
      def_flg = false;
      if (strcmp(argv[i],"+all"   )==0){c.all_flg    = true;}
      if (strcmp(argv[i],"+num"   )==0){c.num_flg    = true;}
      if (strcmp(argv[i],"+numex" )==0){c.numex_flg  = true;}
      if (strcmp(argv[i],"+dbl"   )==0){c.dbl_flg    = true;}
      if (strcmp(argv[i],"+single")==0){c.single_flg = true;}
      continue;
    }
    if (in_file  == NULL){in_file  = argv[i]; continue;}
    if (out_file == NULL){out_file = argv[i]; continue;}
  }

  if (out_file == NULL){help(); return 1;}
  if (def_flg){c.numex_flg = true;}

  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  file_inf->file_open(in_file,out_file);
  c.Conv(file_inf->in_fp,file_inf->out_fp);
  file_inf->file_close();

  delete file_inf;
  return 0;
}
//---------------------------------------------------------------------------
