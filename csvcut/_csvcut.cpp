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
#include "..\csvpp_xbase\ztoken.h"


#include "csvcut_core.h"
#include "csvcut_core.cpp"

//---------------------------------------------------------------------------

#pragma argsused

void help(){
  fprintf(stderr,"use:csvcut csv_in_file csv_out_file koumoku,koumoku,koumoku-koumoku,....\n");
  fprintf(stderr,"ex :csvcut aaa.csv aaa_out.csv 1,3-5,7,9\n");
  fprintf(stderr,"ex :type aaa.csv | csvcut - - 1,3-5,7,9 > aaa_out.csv\n");
}


int main(int argc, char* argv[]){
  fprintf(stderr,"csv_file cutter converter Ver 1.05\n\n");

  char *in_file=NULL;
  char *out_file=NULL;
  char *parm=NULL;
  
  for(int i=1;i<argc;i++){
    if (in_file  == NULL){in_file  = argv[i]; continue;}
    if (out_file == NULL){out_file = argv[i]; continue;}
    if (parm     == NULL){parm     = argv[i]; continue;}
  }

  if (parm == NULL){
    help();
    return 1;
  }


  CsvCut_C *csvcut = new CsvCut_C;
  fileInf64_C *file_inf = new fileInf64_C(10240);
  file_inf->file_open(in_file,out_file);
  bool okFlg=true;
  if (file_inf->in_fp->okCheck() == false){printf("input file error. file=%s\n",in_file); okFlg=false;}
  else if (file_inf->out_fp->okCheck() == false){printf("output file error. file=%s\n",out_file); okFlg=false;}
 
  if (okFlg){  
    csvcut->parmGet(parm);
    csvcut->Main(file_inf->in_fp,file_inf->out_fp);
  }

  file_inf->file_close();

  delete csvcut;

  delete file_inf;

  return 0;
}
//---------------------------------------------------------------------------
