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

//#define DEBUG_CALC 1

#include "_csvcompiler.h"
#include "_csvcomp_base.cpp"
#include "_csvcalc.cpp"
#include "_csvcomp_pass1.cpp"
#include "_csvcomp_pass2.cpp"
#include "_csvcomp_pass3.cpp"
#include "_csvcomp_pass4.cpp"
#include "_csvcomp_pass5.cpp"


//---------------------------------------------------------------------------

#pragma argsused
void help(){
  printf("use:csvcompiler in out lst\n");
  printf("ex :csvcompiler in.csv out.csv lst.csv\n");
}

int main(int argc, char* argv[]){
  Inf_T *inf;
  printf("csv-compiler II Ver 0.94\n");

  if (argc != 4){help(); return 1;}


  Read64_C *in_fp = new Read64_C(argv[1],"csv",4096);
  if (in_fp->okCheck() == false){
    printf("file not open (file=%s)\n",argv[1]);
    delete in_fp; 
    return(false);
  }

  inf = new Inf_T();

  bool ok_flg = false;
  printf("%s -> %s/%s compile\n",argv[1],argv[2],argv[3]);
  for(;;){
    if (inf->Pass1(in_fp) == false){break;}
    if (inf->errCnt > 0){break;}
    if (inf->Pass2(in_fp) == false){break;}
    if (inf->errCnt > 0){break;}
    inf->Pass3();
    if (inf->Pass4(in_fp,"main") == false){break;}
    if (inf->errCnt > 0){break;}
    if (inf->Pass5(argv[2]) == false){break;}
    if (inf->Pass5_list(argv[3]) == false){break;}
    ok_flg = true;
    break;
  }

  if (ok_flg == true){printf("complete.\n");}
  else               {printf("no good.\n");}

  delete inf;
  delete in_fp; 
  return 0;
}
//---------------------------------------------------------------------------



