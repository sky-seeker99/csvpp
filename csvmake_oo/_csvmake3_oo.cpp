/*

 * Copyright (c) 2008 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <condefs.h>
#include <vcl/utilcls.h>
#include "..\csvpp_xbase\zlist.h"
#include "..\csvpp_xbase\zfile.h"

#include "..\csvpp_xbase\xcsvmake_oo.h"
#include "..\csvpp_xbase\xcsvmake_oo.cpp"

//---------------------------------------------------------------------------
#pragma argsused

int main(int argc, char* argv[]){
  printf("XLS File -> CSV File Extend Version Program(OpenOffice.org Edition) Ver 1.04\n\n");

  Application->Initialize();

  char *filter  = NULL;
  char *ext     = NULL;
  char *in_dir  = NULL;
  char *out_dir = NULL;

  csvmake_oo_C *c = new csvmake_oo_C;
  for(int i=1;i<argc;i++){
    if (strcmp(argv[i],"-U") == 0){c->moji_kind = 2; continue;}
    if (strcmp(argv[i],"-E") == 0){c->moji_kind = 1; continue;}
    if (in_dir  == NULL){in_dir   = argv[i]; continue;}
    if (out_dir == NULL){out_dir  = argv[i]; continue;}
    if (filter  == NULL){filter   = argv[i]; continue;}
    if (ext     == NULL){ext      = argv[i]; continue;}
  }

  if (out_dir == NULL){
    printf("use:csvmake3_ooo in_dir out_dir [filter] [ext] [-U] [-E]\n");
    printf("ex :csvmake3_ooo c:\\xls c:\\csv \n");
    printf("ex :csvmake3_ooo c:\\xls c:\\csv csvtab txt\n");
    delete c;
    return 1;
  }

  char drv[3];
  AnsiString cur_dir = GetCurrentDir();
  char *aa = cur_dir.c_str();
  drv[0] = *aa;
  drv[1] = *(aa+1);
  drv[2] = 0x00;

  sChar *dir;
  sChar *dir_sub;
  sChar *dir_csv;
  MemHeader_T *it = new MemHeader_T;
  FileGet_T *fg   = new FileGet_T(it);
  FileGetCell_T *fgc;

  // 入力ディレクトリからxlsファイルリスト作成
  aa = argv[1];
  if ((*(aa+1) == ':') || ((*aa == '\\') && (*(aa+1) == '\\'))){dir = new sChar(in_dir);}
  else{
    if ((*aa == '\\') && (*(aa+1) != '\\')){
      dir = new sChar(drv);
      dir->cat(in_dir);
    } else {
      dir = new sChar(cur_dir.c_str());
      dir->cat("\\");
      dir->cat(in_dir);
    }
  }
  if (*(in_dir + strlen(in_dir)-1) != '\\'){dir->cat("\\");}
  dir_sub = new sChar(dir->c_str());
  dir->cat("*.xls");
  fg->InfClear();
  fg->get(dir->c_str(),0);

  // 出力ディレクトリの作成
  aa = out_dir;
  out_dir = out_dir;
  if ((*(aa+1) == ':') || ((*aa == '\\') && (*(aa+1) == '\\'))){dir_csv = new sChar(out_dir);}
  else{
    if ((*aa == '\\') && (*(aa+1) != '\\')){
      dir_csv = new sChar(drv);
      dir_csv->cat(out_dir);
    } else {
      dir_csv = new sChar(cur_dir.c_str());
      dir_csv->cat("\\");
      dir_csv->cat(out_dir);
    }
  }

  c->csvmake_begin();
  MEM_LOOP(fgc,FileGetCell_T,fg->mem_fp)
    dir->set(dir_sub->c_str());
    dir->cat(fgc->name->c_str());
    c->csvmake(dir->c_str(),out_dir,filter,ext);
  LOOP_END
  c->csvmake_end();

  delete fg;
  delete dir;
  delete dir_sub;
  delete it;
  delete c;
  return 0;
}



