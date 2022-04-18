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
#include <stdlib.h>
#include <string.h>
#include <condefs.h>
#include <windows.h>
#include <process.h>
#include <tlhelp32.h>
#pragma hdrstop

#include "..\csvpp_xbase\zcsvfile.h"
#include "..\csvpp_xbase\xwildcard.h"
#include "..\csvpp_xbase\xexec.h"
#include "..\csvpp_xbase\xread64.h"
#include "..\csvpp_xbase\xwrite64.h"
#include "..\csvpp_xbase\xtemp_file64.h"
#include "..\csvpp_xbase\xcsvmake_new.h"
#include "..\csvpp_xbase\xcsvmake_oo.h"


#include "_csvretchg.h"
#include "_csvretchg.cpp"
#include "_csvreverse.h"
#include "_csvreverse.cpp"
#include "_csvfront.h"
#include "_csvfront.cpp"

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
Inf_T *inf;

printf("CSV-File preprocessor frontend Program Ver 1.18\n");

if (argc < 2)
  {
  printf("use:csvfront csvfile\n");
  printf("ex :csvfront c:\\csv\\cmd.csv\n");
  return 1;
  }

Application->Initialize();
inf = new Inf_T;

inf->ProgramArgRead(argc,argv);
inf->CsvRead(argv[1],"");
delete inf;

        return 0;
}
//---------------------------------------------------------------------------
 
