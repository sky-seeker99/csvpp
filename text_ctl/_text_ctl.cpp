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


#include "xtext_ctl.h"
#include "xtext_ctl.cpp"


//---------------------------------------------------------------------------

#pragma argsused

#define SJIS_EUC 0
#define EUC_SJIS 1 

// # HELP #####
void help()
  {
  printf("use:text_ctl csv_file file [-l log_file] [-r] [-buff buffer_size]\n");
  printf("ex :text_ctl ctrl.csv c:\\*.txt\n");
  printf("ex :text_ctl ctrl.csv c:\\*.txt -r\n");
  }

// # MAIN #####
int main(int argc, char* argv[]){
  printf("text file controler Ver 1.05\n\n");

  char *csv_file_name=NULL;
  char *chg_file_name=NULL;
  char *log_file_name=NULL;
  bool read_only = false;
  int  buff_size = 10;

  int mode = 0;
  for(int i=1;i<argc;i++){
    if (mode == 1) {log_file_name = argv[i];         mode = 0;  continue;}
    if (mode == 2) {buff_size = SujiConvEx(argv[i]); mode = 0;  continue;}
    if (strcmp(argv[i],"-r"   ) == 0){read_only = true; continue;}
    if (strcmp(argv[i],"-l"   ) == 0){mode      = 1;    continue;}
    if (strcmp(argv[i],"-buff") == 0){mode      = 2;    continue;}
    if (csv_file_name == NULL){csv_file_name = argv[i]; continue;}
    if (chg_file_name == NULL){chg_file_name = argv[i]; continue;}
  }

  if (chg_file_name == NULL){help(); return 1;}

  // # CSV File Read #####
  Read64_C *csv_fp = new Read64_C(csv_file_name,"csv",buff_size*1024);
  if (csv_fp->okCheck() == false){
    printf("csv file read error. file=%s\n",csv_file_name);
    delete csv_fp;
    return 1;
  }

  TextCtlInf *inf = new TextCtlInf;
  if (inf->CsvFileRead(csv_fp) == false){
    printf("csv_file read error. (%s)\n",csv_file_name);
    delete csv_fp;
    delete inf;
    return 1;
  }
  delete csv_fp;

  if (log_file_name != NULL) {
    inf->logfile(log_file_name);
  }

  if (read_only){printf("[read only mode]\n");}
  else          {printf("[modify mode]\n");}


  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  file_inf->file_list_get(chg_file_name);

  sChar *file;
  MEM_LOOP(file,sChar,file_inf->mem_fp)
    if (read_only == false){
      printf("%s convert.\n",file->c_str());
      if (file_inf->same_file_open(file->c_str())){
        inf->MainLoop(file_inf->in_fp,file_inf->out_fp,file->c_str());
      }
      file_inf->same_file_close();
    } else {
      printf("%s check.\n",file->c_str());
      Read64_C *in_fp = new Read64_C(file->c_str(),"rt",buff_size*1024);
      if (in_fp->okCheck()){
        inf->MainLoop(in_fp,NULL,file->c_str());
      }
      delete in_fp;
    }  
  LOOP_END

  delete file_inf;

  delete inf;
  return 0;
}
//---------------------------------------------------------------------------
 
