/*

 * Copyright (c) 2011 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
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
#include "..\csvpp_xbase\xcsvmake_new.h"

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
  Application->Initialize();

  printf("process kill Program Ver 1.00\n\n");

  if (argc == 1){
	printf("use:proc_kill process_name process_name ... process_name\n");
	printf("ex :proc_kill EXCEL.EXE\n");
	return 1;
  }

  Application->Initialize();
  csvmake_C *csvmake = new csvmake_C;
  csvmake->pchkFlag=true;
  //csvmake->excel_kill();

  for(int i=1;i<argc;i++){
	csvmake->process_check(argv[i],false);
  }

  delete csvmake;
  return 0;
}
//---------------------------------------------------------------------------


