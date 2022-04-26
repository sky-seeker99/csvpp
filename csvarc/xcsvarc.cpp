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

#include "..\csvpp_xbase\zcsvfile.h"

#include "_csvarc.cpp"
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
Inf_T *inf;
printf("command line archiver Ver 1.02\n\n");

if (argc != 3)
  {
  printf("use:csvarc csv log\n");
  printf("ex :csvarc aaa.csv out.log\n");
  return 1;
  }

inf = new Inf_T();
inf->Main(argv[1],argv[2]);

delete inf;
        return 0;
}
//---------------------------------------------------------------------------



