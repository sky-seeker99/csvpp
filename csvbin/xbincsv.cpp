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

#include "..\csvpp_xbase\ztool.h"
#include "..\csvpp_xbase\xwrite64.h"
#include "..\csvpp_xbase\xread64.h"
#include "..\csvpp_xbase\xfile_interface64.h"

//---------------------------------------------------------------------------

#pragma argsused
#define K_DEC 0
#define K_HEX 1
#define K_BIN 2

__int64 g_size;
__int64 g_addr;
int     g_kbn;
void exec(Read64_C *in_fp,Write64_C *out_fp,int count);

void help(){
  fprintf(stderr,"use:bincsv [-d|-b] binary_file csv_file  [-start start_address] [-size size] [-buff buff_size] [-width width_size]\n");
  fprintf(stderr,"ex :bincsv aaa.dat aaa.csv\n");
  fprintf(stderr,"ex :bincsv -d aaa.dat aaa.csv\n");
  fprintf(stderr,"ex :bincsv -b aaa.dat aaa.csv\n");
}

int main(int argc, char* argv[]){
  printf("binary_file -> csv_file converter Ver 1.03\n\n");
  char *in_file=NULL;
  char *out_file=NULL;
  int   buff_size = 10;
  int   mode = 0;
  int   count = 16;

  g_size = (__int64)0;
  g_addr = (__int64)0;
  g_kbn=K_HEX;
  for(int i=1;i<argc;++i){
	char *w = argv[i];
	if (mode==1) {buff_size = SujiConvEx(w); mode = 0; continue;}
	if (mode==2) {g_addr    = SujiConvEx(w); mode = 0; continue;}
	if (mode==3) {g_size    = SujiConvEx(w); mode = 0; continue;}
	if (mode==4) {count     = SujiConvEx(w); mode = 0; continue;}
	if (strcmp(w,"-buff" ) == 0){mode = 1;  continue;}
	if (strcmp(w,"-start") == 0){mode = 2;  continue;}
	if (strcmp(w,"-size" ) == 0){mode = 3;  continue;}
	if (strcmp(w,"-width") == 0){mode = 4;  continue;}
	if (strcmp(w,"-d") == 0   ){g_kbn = K_DEC;  continue;}
	if (strcmp(w,"-b") == 0   ){g_kbn = K_BIN;  continue;}
	if (in_file        == NULL){in_file  = w; continue;}
	if (out_file       == NULL){out_file = w; continue;}
  }

  if (out_file == NULL){help(); return 1;}

  fileInf64_C *file_inf = new fileInf64_C(buff_size);
  if (file_inf->file_open(in_file,"rb",out_file,"wt")){
	exec(file_inf->in_fp,file_inf->out_fp,count);
  }
  file_inf->file_close();
  delete file_inf;
  return 0;
}


//---------------------------------------------------------------------------
void exec(Read64_C *in_fp,Write64_C *out_fp,int count){
  if (g_size == (__int64)0) {g_size = in_fp->sizeGet();}

  in_fp->seek(g_addr);
  sprintf(out_fp->buff,"#size,%I64d\n",g_size); out_fp->write();
  sprintf(out_fp->buff,"#head,ADDRESS   ");
  out_fp->write();

  for(int i=0;i<count;i++){
	sprintf(out_fp->buff,",'h%02x",i);
	out_fp->write();
  }
  out_fp->writeln((unsigned char *)"");

  int cnt = 0;
  __int64 addr = g_addr;
  unsigned char c;
  for(;;){
	if (g_size == (__int64)0) {break;}
	if (in_fp->read(&c,1)==0) {break;}
	if (cnt == 0){sprintf(out_fp->buff,"#chg,'h%09I64X",addr); out_fp->write();}
	out_fp->write((unsigned char *)",");
	if (g_kbn == K_HEX){sprintf(out_fp->buff,"'h%02X",c); out_fp->write();}
	if (g_kbn == K_DEC){sprintf(out_fp->buff,"%03d"  ,c); out_fp->write();}
	if (g_kbn == K_BIN){
	  char sstr[9];
	  sstr[8] = 0x00;
	  long_bitc(sstr,(long)c,8);
	  bitc_ex(sstr,8);
	  sprintf(out_fp->buff,"'b%s",sstr);
	  out_fp->write();
	}
	++cnt;
	if (cnt == count){out_fp->writeln((unsigned char *)""); cnt = 0;}
	g_size--;
	addr++;
  }
}

