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
#include <condefs.h>
#include <stdio.h>
#include <fcntl.h>
#pragma hdrstop

#include "..\csvpp_xbase\zcsvfile.h"
#include "..\csvpp_xlang\xdbctl.h"

#include "_csvlib.cpp"

//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[])
{
  DbApi_T *it;
  char *str;
  MEM_FP *msg_fp;

  printf("CSV-file preprocessor library Ver 1.02\n");

  it = new DbApi_T(argv,argc);

  it->Main();
/*
  msg_fp = it->GetMsg();
  MEM_LOOP(str,char,msg_fp)
    printf("%s\n",str);
  LOOP_END
*/
  if (it->error_flg == true)
    {
    printf("use:csvlib c in_csv out_csv lib1 lib2 - libn\n");
    printf("    csvlib a libfile csvfile1 csvfile2 - csvfilen\n");
    printf("    csvlib d libfile class1 class2 - classn\n");
    printf("    csvlib o libfile csvfile\n");
    printf("    csvlib l libfile logfile\n");
    printf("ex :csvlib c cmd.csv include.csv aaa.db bbb.db\n");
    printf("    csvlib a aaa.db a.csv b.csv c.csv\n");
    printf("    csvlib d aaa.db aaa_class bbb_class\n");
    printf("    csvlib o aaa.db out.csv\n");
    printf("    csvlib l aaa.db out.log\n");
    }

  delete it;

        return 0;
}



