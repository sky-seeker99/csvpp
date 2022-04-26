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

#include "..\csvpp_xbase\xfile_interface.h"
#include "..\csvpp_xbase\xkanji.h"

//---------------------------------------------------------------------------

#pragma argsused

#define SJIS_EUC 0
#define EUC_SJIS 1

void help()
  {
  printf("use:eucsjis2 sjis_euc|euc_sjis in_file out_file\n");
  printf("ex :eucsjis2 sjis_euc aaa_sjis.txt aaa_euc.txt\n");
  printf("ex :eucsjis2 euc_sjis aaa_euc.txt aaa_sjis.txt\n");
  printf("ex :eucsjis2 sjis_euc_win aaa_sjis.txt aaa_euc.txt\n");
  printf("ex :eucsjis2 euc_sjis_win aaa_euc.txt aaa_sjis.txt\n");
  printf("ex :eucsjis2 sjis_euc_unix aaa_sjis.txt aaa_euc.txt\n");
  printf("ex :eucsjis2 euc_sjis_unix aaa_euc.txt aaa_sjis.txt\n");
  printf("ex :type aaa_euc.txt | eucsjis2 euc_sjis - - > aaa_sjis.txt\n");
  }


int main(int argc, char* argv[])
{
fprintf(stderr,"sjis <-> euc changer part2 Ver 1.03\n\n");

if (argc != 4){help(); return 1;}

int kbn = -1;
int ret_kbn = 0;
if (strcmp(argv[1],"sjis_euc"     ) == 0){kbn = SJIS_EUC; ret_kbn=K_UNIX;}
if (strcmp(argv[1],"euc_sjis"     ) == 0){kbn = EUC_SJIS; ret_kbn=K_WIN;}
if (strcmp(argv[1],"sjis_euc_win" ) == 0){kbn = SJIS_EUC; ret_kbn=K_WIN;}
if (strcmp(argv[1],"euc_sjis_win" ) == 0){kbn = EUC_SJIS; ret_kbn=K_WIN;}
if (strcmp(argv[1],"sjis_euc_unix") == 0){kbn = SJIS_EUC; ret_kbn=K_UNIX;}
if (strcmp(argv[1],"euc_sjis_unix") == 0){kbn = EUC_SJIS; ret_kbn=K_UNIX;}
if (kbn == -1){help(); return 1;}
if      (kbn == SJIS_EUC){fprintf(stderr,"convert mode:sjis -> euc\n");}
else                     {fprintf(stderr,"convert mode:euc -> sjis\n");}


FileNameSep_T *fn   = new FileNameSep_T();
char *xx;
fn->Set(argv[0]);
sChar *ini_file = new sChar("");
xx = fn->DrvGet();
ini_file->cat(xx);
xx = fn->DirGet();
ini_file->cat(xx);
ini_file->cat("eucsjis.csv");
delete fn;


file_inf file_inf;
kanji_T  kanji;
kanji.return_code_setting(ret_kbn);
file_inf.file_open(argv[2],argv[3]);

if (file_inf.out_con_flg){kanji.return_code_setting(K_UNIX);}

FILE *c_fp = fopen(ini_file->c_str(),"rt");
if (c_fp != NULL){
  fclose(c_fp);
  kanji.gaiji_setting(ini_file->c_str());
}


if (kbn == SJIS_EUC){kanji.sjis_euc_conv(file_inf.in_fp,file_inf.out_fp);}
else                {kanji.euc_sjis_conv(file_inf.in_fp,file_inf.out_fp);}
file_inf.file_close();
delete ini_file;

return 0;
}
//---------------------------------------------------------------------------
