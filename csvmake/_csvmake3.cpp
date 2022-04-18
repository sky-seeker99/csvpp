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


#pragma hdrstop

#include "..\csvpp_xbase\zcsvfile.h"
#include "..\csvpp_xbase\zfile.h"
#include "..\csvpp_xbase\xwildcard.h"
#include "..\csvpp_xbase\xexec.h"
#include "..\csvpp_xbase\xread64.h"
#include "..\csvpp_xbase\xwrite64.h"
#include "..\csvpp_xbase\xcsvmake_new.h"



VariableArea_C *CurrentChangeNew(char *p_dir){
  VariableArea_C *dir = new VariableArea_C(50);
  dir->set(0,0x00);

  if (strlen(p_dir) == 0){return(dir);}

  AnsiString  cur_dir = GetCurrentDir();
  char *aa = cur_dir.c_str();
  char drv[3];
  drv[0] = *aa;
  drv[1] = *(aa+1);
  drv[2] = 0x00;

  if      ((*(p_dir+1) == ':') || ((*p_dir == '\\') && (*(p_dir+1) == '\\'))){dir->set_string(p_dir);}
  else if ((*p_dir == '\\') && (*(p_dir+1) != '\\'))                         {dir->set_string(drv); dir->cat_string(p_dir);}
  else                                                                       {dir->set_string(cur_dir.c_str()); dir->cat_string("\\"); dir->cat_string(p_dir);}
  
  return(dir);
}

//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[]){

  printf("XLS File -> CSV File Extend Version Program Ver 1.07\n\n");

  char *p_in_dir  =NULL;
  char *p_out_dir =NULL;
  char *p_filter  =NULL;
  char *p_ext     =NULL;
  int  arg_mode   = 0;

  Application->Initialize();
  csvmake_C *csvmake = new csvmake_C;
  
  for(int i=1;i<argc;i++){
    if (strcmp(argv[i],"-s"   )==0){arg_mode = 1; continue;}
    if (strcmp(argv[i],"-S"   )==0){arg_mode = 2; continue;}
    if (strcmp(argv[i],"-tmp" )==0){csvmake->tmpFlag  = true; continue;}
    if (strcmp(argv[i],"-proc")==0){csvmake->pchkFlag = true; continue;}
    if (arg_mode == 0){
      if (p_in_dir  == NULL){p_in_dir   = argv[i]; continue;}
      if (p_out_dir == NULL){p_out_dir  = argv[i]; continue;}
      if (p_filter  == NULL){p_filter   = argv[i]; continue;}
      if (p_ext     == NULL){p_ext      = argv[i]; continue;}
    }
    else {
      sChar *s_str = new sChar(argv[i]);
      if (arg_mode == 1){csvmake->sel_fp->mem_alloc ((unsigned char*)s_str);}
      if (arg_mode == 2){csvmake->esel_fp->mem_alloc((unsigned char*)s_str);}
    }
  }

  if (p_out_dir == NULL){
    printf("use:csvmake3 in_dir out_dir [filter] [ext] [-proc] [-tmp]\n");
    printf("ex :csvmake3 c:\\xls c:\\csv \n");
    printf("ex :csvmake3 c:\\xls c:\\csv csvtab txt\n");
    printf("ex :csvmake3 c:\\xls c:\\csv -s a* sheet* -S ae* sheet_a*\n");
    printf("ex :csvmake3 c:\\xls c:\\csv csvtab txt -s a* sheet* -S ae* sheet_a*\n");
    delete csvmake;
    return 1;
  }
  
  VariableArea_C *xls_name= new VariableArea_C(50);
  VariableArea_C *dir     = CurrentChangeNew(p_in_dir);
  VariableArea_C *dir_csv = CurrentChangeNew(p_out_dir);
  MemHeader_T    *it      = new MemHeader_T;
  FileGet_T      *fg      = new FileGet_T(it);
  FileGetCell_T *fgc;

  if (*(p_in_dir + strlen(p_in_dir)-1) != '\\'){dir->cat_string("\\");}
  VariableArea_C *dir_sub = new VariableArea_C(dir->cc_str());
  dir->cat_string("*.xls");
  fg->InfClear();
  fg->get(dir->cc_str(),0);

  csvmake->csvmake_begin();

  MEM_LOOP(fgc,FileGetCell_T,fg->mem_fp)
    dir->set_string(dir_sub->cc_str());
    dir->cat_string(fgc->name->c_str());
    xls_name->set_string(fgc->name->c_str());
    char *w = xls_name->cc_str();
    for(int i=strlen(w)-1;i>=0;i--){
      if (*(w+i) == '.') {
        *(w+i) = 0x00;
        break;
      }
    }

    csvmake->csvmake(dir->cc_str(),dir_csv->cc_str(),p_filter,p_ext,xls_name->cc_str());
  LOOP_END
  csvmake->csvmake_end();

  delete fg;
  delete dir;
  delete dir_sub;
  delete dir_csv;
  delete xls_name;
  delete it;

  delete csvmake;
  return 0;
  }


