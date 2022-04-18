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
#include "..\csvpp_xbase\xcsvmake_oo.h"


//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[]){
  printf("CSV File -> XLS File Adding Extend Version Program (Libre Office Edition) Ver 1.00\n\n");

  char *p_xlsfile  = NULL;
  char *p_csvdir   = NULL;
  char *p_filter   = NULL;
  char *p_ext      = NULL;

  Application->Initialize();
  csvmake2_oo_C *csvmake = new csvmake2_oo_C;
  int arg_mode = 0;
  for(int i=1;i<argc;i++){
//    if (strcmp(argv[i],"-proc" )==0){csvmake->pchkFlag   = true; continue;}
    if (strcmp(argv[i],"-nv"   )==0){csvmake->visual_flg = false; continue;}
//    if (strcmp(argv[i],"-new"  )==0){csvmake->delFlg     = true; continue;}
//    if (strcmp(argv[i],"-paste")==0){csvmake->pasteFlg   = true; continue;}
//    if (strcmp(argv[i],"-xml"  )==0){csvmake->xmlFlg     = true; continue;}
    if (p_xlsfile == NULL){p_xlsfile  = argv[i]; continue;}
    if (p_csvdir  == NULL){p_csvdir  = argv[i]; continue;}
    if (p_filter  == NULL){p_filter   = argv[i]; continue;}
    if (p_ext     == NULL){p_ext      = argv[i]; continue;}
  }

  if (p_csvdir == NULL) {
    printf("use:csvmake4_ooo xlsfile in_dir [filter] [ext]\n");
    printf("ex :csvmake4_ooo c:\\aaa.xls c:\\csv\n");
    delete csvmake;
    return 1;
  }

  MemHeader_T   *it = new MemHeader_T;
  FileGet_T     *fg = new FileGet_T(it);
  FileGetCell_T *fgc;
  VariableArea_C *dir_csv = new VariableArea_C(100);
  VariableArea_C *dir_sub = new VariableArea_C(100);

  // カレントディレクトリ対策
  if ((*(p_csvdir+1) == ':') || ((*p_csvdir == '\\') && (*(p_csvdir+1) == '\\'))){
    dir_csv->set_string(p_csvdir);
  }
  else {
    AnsiString cur_dir = GetCurrentDir();
    dir_csv->set_string(cur_dir.c_str());
    dir_csv->cat_string("\\");
    dir_csv->cat_string(p_csvdir);
  }

  // 入力ディレクトリの最後の文字が'\'ではない時の対処
  if (*(p_csvdir + strlen(p_csvdir)-1) != '\\'){dir_csv->cat_string("\\");}

  // 拡張子の指定
  dir_sub->set_string(dir_csv->cc_str());
  if (p_ext == NULL){dir_csv->cat_string("*.csv");}
  else              {dir_csv->cat_string("*."); dir_csv->cat_string(p_ext);}

  // シート登録
  fg->InfClear();
  fg->get(dir_csv->c_str(),0);
  MEM_LOOP(fgc,FileGetCell_T,fg->mem_fp)
    dir_csv->set_string(dir_sub->cc_str());
    dir_csv->cat_string(fgc->name->c_str());
    sChar *s_str = new sChar(dir_csv->cc_str());
    csvmake->sheet_fp->mem_alloc ((unsigned char*)s_str);
  LOOP_END


  csvmake->csvmake_begin();
  csvmake->csvmake(p_xlsfile,p_filter);
  csvmake->csvmake_end();

  delete csvmake;
  delete fg;
  delete it;
  delete dir_csv;
  delete dir_sub;

  return 0;
}


