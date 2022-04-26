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

#include "..\csvpp_xbase\xarea.h"
#include "..\csvpp_xbase\xread64.h"
#include "..\csvpp_xbase\xwrite64.h"
#include "..\csvpp_xbase\xcsvi_anl.h"

#include "text_create_core.h"
#include "text_create_core.cpp"

//---------------------------------------------------------------------------

#pragma argsused
//---------------------------------------------------------------------------


 void help()
  {
  printf("use:text_create csv_file [-buff buff_size]\n");
  printf("ex :text_create in.csv \n");
  }


int main(int argc, char* argv[])
{
  printf("text file creater Ver 1.04\n\n");
  int buff_size = 10;
  char *csv_file=NULL;
  int mode = 0;

  for(int i=1;i<argc;i++){
  	if (mode == 1) {buff_size = SujiConvEx(argv[i]); mode = 0; continue;}
	if (strcmp(argv[i],"-buff")==0) {mode = 1; continue;}
    if (csv_file == NULL){csv_file = argv[i]; continue;}
  }

  if (csv_file == NULL){help(); return 1;}
  Read64_C *in_fp = new Read64_C(csv_file,"rt",buff_size);
  if (in_fp->okCheck()){
    text_create_C *text = new text_create_C;
    text->csvRead(in_fp);
    text->output();
    delete text;
  }
  delete in_fp;

  return 0;
}
//---------------------------------------------------------------------------