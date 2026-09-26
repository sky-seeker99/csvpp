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

#include <stdio.h>
#include <condefs.h>
#pragma hdrstop

#include "..\csvpp_xbase\ztool.h"
#include "..\csvpp_xbase\zfile.h"


//---------------------------------------------------------------------------
#pragma argsused

void exec_rtn(char *file);
int main(int argc, char* argv[])
{
FileGet_T *fg;
MemHeader_T *it;
FileGetCell_T *fgc;
sChar *dir;

  printf("comment delete Program Ver 1.01\n");
  if (argc != 3)
    {
    printf("use:comment_del directory mask\n");
    printf("ex :comment_del c:\\csv\\ *.v\n");
    return 1;
    }

  it  = new MemHeader_T;
  fg  = new FileGet_T(it);
  dir = new sChar(argv[1]);
  dir->cat(argv[2]);
  fg->InfClear();
  fg->get(dir->c_str(),0);

  MEM_LOOP(fgc,FileGetCell_T,fg->mem_fp)
    dir->set(argv[1]);
    dir->cat(fgc->name->c_str());
    exec_rtn(dir->c_str());
  LOOP_END

  delete dir;
  delete it;
  delete fg;
        return 0;
}

// -------------------
// exec
// -------------------
void exec_rtn(char *in_file)
  {
  FILE *in_fp;
  FILE *out_fp;
  char *buff;
  char file_name[512];
  bool ok_flg;
  xFgets_T *xf;
  sCharGrep *str;
  int ptr;
  FileSeq(file_name,"tmp$$$","tmp");
  out_fp = fopen(file_name,"wt");
  in_fp  = fopen(in_file,"rt");

  ok_flg = true;
  if(in_fp  == NULL){ok_flg = false; printf("file open error(file=%s)\n",in_file);}
  if(out_fp == NULL){ok_flg = false; printf("file open error(file=%s)\n",file_name);}
  if (ok_flg == false)
    {
    if (in_fp  != NULL){fclose(in_fp);}
    if (out_fp != NULL){fclose(out_fp);   DeleteFile(file_name);}
    return;
    }

  printf("%s->",in_file);
  xf  = new xFgets_T(256);
  str = new sCharGrep("");
  for(;;)
    {
    buff = xf->xFgets(in_fp);  // =NULL:End Of File
    if (buff == NULL){break;}
    str->set(buff);

    ptr = str->grep("// _CELL",0);
    if (ptr >= 0)
      {
      *(buff+ptr) = 0x00;
	  sp_push(buff);
      fprintf(out_fp,"%s\n",buff);
      }
    else
      {
      fprintf(out_fp,"%s",buff);
      }
    }

  delete str;
  delete xf;
  fclose(in_fp);
  fclose(out_fp);
  DeleteFile(in_file);
  rename(file_name,in_file);
  printf("complete.\n");

  }


