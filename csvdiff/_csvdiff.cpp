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

//---------------------------------------------------------------------------
#include <stdio.h>
#include <condefs.h>
#pragma hdrstop

#include "..\csvpp_xbase\xfile_interface64.h"
#include "..\csvpp_xbase\xcsvi_anl.h"

#include "xcsvdiff.h"
#include "xcsvdiff.cpp"

//---------------------------------------------------------------------------

#pragma argsused

// # help ########
void help_msg()
  {
  fprintf(stderr,"use:csvdiff key csv_in_file1 csv_in_file2 [-m missmatch_count] [-w width] [-d] [-dbl_no_cut] [-integer]\n");
  fprintf(stderr,"ex :csvdiff #code aaa.csv bbb.csv\n");
  fprintf(stderr," default value\n");
  fprintf(stderr,"   missmacth_cnt : 20\n");
  fprintf(stderr,"   width         : 30\n");
  }


// # main proc #####
int main(int argc, char* argv[]){
int miss_cnt    = 20;
int wid_cnt     = 30;
bool d_flag     = false;
bool dbl_no_cut = false;
char *key       = NULL;
char *file1     = NULL;
char *file2     = NULL;
bool intMode    = false;

fprintf(stderr,"csv_file diff Ver 1.03\n");

// argv,argc proc
int state = 0;
for(int i=1;i<argc;i++){
  if (state == 1){miss_cnt = SujiConvEx(argv[i]); state = 0; continue;}
  if (state == 2){wid_cnt  = SujiConvEx(argv[i]); state = 0; continue;}
  if (strcmp(argv[i],"-d") == 0   ){d_flag= true;    continue;}
  if (strcmp(argv[i],"-integer") == 0   ){intMode= true;    continue;}
  if (strcmp(argv[i],"-dbl_no_cut") == 0   ){dbl_no_cut= true;    continue;}
  if (strcmp(argv[i],"-m") == 0   ){state = 1;       continue;}
  if (strcmp(argv[i],"-w") == 0   ){state = 2;       continue;}
  if (key                  == NULL){key   = argv[i]; continue;}
  if (file1                == NULL){file1 = argv[i]; continue;}
  if (file2                == NULL){file2 = argv[i]; continue;}
}

// arg check
if (file2 == NULL){help_msg();                               return 1;}
if (miss_cnt  < 1){fprintf(stderr,"missmatch_count error."); return 1;}
if (wid_cnt   < 1){fprintf(stderr,"width error.");           return 1;}


printf("left :%s\n",file1);
printf("right:%s\n",file2);
printf("width:%d\n",wid_cnt);
printf("miss :%d\n",miss_cnt);
printf("key  :%s\n",key);


Read64_C *in_fp1 = new Read64_C(file1,"csv",10240);
Read64_C *in_fp2 = new Read64_C(file2,"csv",10240);

bool okFlg=true;
if (in_fp1->okCheck() == false){printf("file open error. (file=%s)\n",file1); okFlg=false;}
if (in_fp2->okCheck() == false){printf("file open error. (file=%s)\n",file2); okFlg=false;}

if (okFlg){
  CsvDiffInf_C *inf = new CsvDiffInf_C(dbl_no_cut,miss_cnt,wid_cnt,key,d_flag);
  inf->intMode = intMode;
  inf->Main(in_fp1,in_fp2);
  delete inf;
}

delete in_fp1;
delete in_fp2;
        return 0;
}



//---------------------------------------------------------------------------
