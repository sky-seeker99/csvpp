/*
 * Copyright 2026 Shigeru Kasuya
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by me or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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


