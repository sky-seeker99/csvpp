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

#include <stdio.h>
#include <string.h>
#pragma hdrstop

#include "..\csvpp_xbase\xfile_interface64.h"
#include "..\csvpp_xbase\xcsvi_anl.h"
#include "..\csvpp_xbase\ztoken.h"

#include "..\csvveri_soket\csvverilog.h"
#include "..\csvveri_soket\wire_anl.h"
#include "..\csvveri_soket\csv2csv.h"

#include "..\csvveri_soket\csvverilog.cpp"
#include "..\csvveri_soket\wire_anl.cpp"
#include "..\csvveri_soket\csv2csv.cpp"

#include "_csvveri.cpp"
#include "_csv2csv.cpp"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[])
{
  char *csv_file=NULL;
  char *out_file=NULL;
  int   mode=0;

  printf("Csv-Verilog Maker II Ver 1.28\n");
  for(int i=1;i<argc;i++){
	if (strcmp(argv[i],"-csvout")==0) {mode = 1; continue;}
	if (csv_file == NULL) {csv_file = argv[i]; continue;}
	if (out_file == NULL) {out_file = argv[i]; continue;}
  }

  if (out_file == NULL){
	printf("use:csvveri csvfile verilog_file\n");
	printf("ex :csvveri aaa.csv aaa.v\n");
	return 1;
  }
  if (mode == 0) {
	VOutTop_T *it = new VOutTop_T(csv_file,out_file);
	delete it;
  }
  else {
	csvOutTop_T *it = new csvOutTop_T(csv_file,out_file);
	it->main();
	it->output();
	delete it;
  }

  return 0;
}


