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

#include "..\csvpp_xbase\xwrite64.h"
#include "..\csvpp_xbase\xread64.h"
#include "..\csvpp_xbase\xfile_interface64.h"
#include "..\csvpp_xbase\xcsvi_anl.h"

//---------------------------------------------------------------------------

#pragma argsused

void exec(Read64_C *in_fp,Write64_C *out_fp);
void chgRtn(CsvAnl_C *csvi,Write64_C *out_fp);
__int64 g_offset;

void help(){
  fprintf(stderr,"use:csvbin in.csv out.bin [-buff buff_size] [-tag tag_name]\n");
  fprintf(stderr,"ex :csvbin aaa.csv aaa.dat\n");
  fprintf(stderr,"ex :csvbin aaa.csv aaa.dat -tag #data\n");
}

sChar *tag_name;
int main(int argc, char* argv[]){
  char *in_file = NULL;
  char *out_file = NULL;
  int buff_size = 10;
  printf("csv_file -> binary_file converter Ver 1.04\n\n");
  tag_name = new sChar("#chg");

  int mode = 0;
  for(int i=1;i<argc;i++){
	if (mode == 1) {buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
	if (mode == 2) {tag_name->set(argv[i]); mode = 0; continue;}
	if (strcmp(argv[i],"-buff")==0) {mode = 1; continue;}
	if (strcmp(argv[i],"-tag" )==0) {mode = 2; continue;}
	if (in_file  == NULL) {in_file  = argv[i]; continue;}
	if (out_file == NULL) {out_file = argv[i]; continue;}
  }

  if (out_file == NULL){help(); return 1;}

  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  if (file_inf->file_open(in_file,"csv",out_file,"wb")){
	printf("tag=%s\n",tag_name->c_str());
	exec(file_inf->in_fp,file_inf->out_fp);
  }
  file_inf->file_close();
  delete file_inf;
  delete tag_name;

  return 0;
}
//---------------------------------------------------------------------------

void exec(Read64_C *in_fp,Write64_C *out_fp){
  g_offset = (__int64)0;
  CsvAnl_C *csvi = new CsvAnl_C;
  for(;;){
	unsigned char *buff = in_fp->read();
	if (buff == NULL) {break;}
	csvi->Exec(buff);

	CSV_LOOP(csvi,str,SP_PUSH)
	  if (strcmp(str,tag_name->c_str()) == 0){chgRtn(csvi,out_fp);}
	  break;
	LOOP_END
  }
  delete csvi;
}

void chgRtn(CsvAnl_C *csvi,Write64_C *out_fp){
  char *w_offset = NULL;
  CSV_LOOP(csvi,str,SP_PUSH)


	if (w_offset == NULL) {
	  w_offset = str;
	  __int64 l_offset = SujiConvEx64(w_offset);
	  if (l_offset != g_offset) {
		g_offset = l_offset;
		out_fp->seek(g_offset);
	  }
	  continue;
    }
	// file write
	if (strcmp(str,"-") == 0){
	 ++g_offset;
	 out_fp->seek(g_offset);
	 continue;
	}
	unsigned char c = (unsigned char)SujiConvEx(str);
	out_fp->write(&c,1);
	g_offset++;
  LOOP_END
}

