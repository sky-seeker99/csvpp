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

#include "..\csvpp_xbase\xdate.h"
#include "..\csvpp_xbase\xwildcard.h"
#include "..\csvpp_xbase\xfile_interface64.h"
#include "..\csvpp_xbase\xcsvi_anl.h"
#include "..\csvpp_xbase\xlink.h"
#include "..\csvpp_xbase\xfileinfo.h"
#include "..\csvpp_xbase\xutf_8.h"
#include "..\csvpp_xbase\zbin_conv.h"
#include "..\csvpp_xbase\xexec.h"

#include "..\csvpp_xlang\xvar_ctl.h"
#include "..\csvpp_xlang\xcalc.h"
#include "..\csvpp_xlang\xcalc64.h"
#include "..\csvpp_xlang\xcalc_f.h"
//#include "..\csvpp_xlang\xcsvdb.h"
#include "..\csvpp_xlang\xprg_line.h"

#include "_shell.cpp"
#include "_casedo.cpp"
#include "_csvpp.h"
#include "_csvpp.cpp"

#pragma hdrstop

//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[])
{
  ExecCtlInf_T *it;
  char *str;
  MEM_FP *msg_fp;
  char buff[MAX_PATH];
  FILE *out_fp;
  FILE *in_fp;
  bool ok_flg;
  bool file_wr;
  char *env;
  sCharGrep *cmd;
  char xbuff[1024];
  int rtn_cd;

  printf("CSV-file preprocessor Ver 1.77\n");

  if (argc < 2)
    {
    printf("use:csvpp csvfile \n");
    printf("ex :csvpp hdl.csv\n");
    return 1;
    }

  it = new ExecCtlInf_T();
  it->pg_exec->dirSet(argv[0]);
  it->ProgramArgRead(argc,argv);

// Library Tenkai
  env  = it->x_getenv("csvlib");

  if (env != NULL)
    {
    FileSeq(buff,"pp_z","csv");
    cmd = new sCharGrep("csvlib c ");
    cmd->cat(argv[1]);
    cmd->cat(" ");
    cmd->cat(buff);
    cmd->cat(" ");
    cmd->cat(env);
    cmd->replace_all(";"," ");
    system(cmd->c_str());
    delete cmd;

    out_fp = fopen(buff,"at");
    in_fp  = fopen(argv[1],"rt");
    if ((out_fp != NULL) && (in_fp != NULL))
      {
      for(;;)
        {
        if (fgets(xbuff,1024-1,in_fp) == 0){break;}
        fprintf(out_fp,"%s",xbuff);
        }
      }
    if (out_fp != NULL){fclose(out_fp);}
    if (in_fp  != NULL){fclose(in_fp);}

    DeleteFile(argv[1]);
    ok_flg = RenameFile(buff,argv[1]);
    if (ok_flg == false){printf("rename error(%s->%s).\n\n",buff,argv[1]);}
    }

// interface initialize

  it->CsvFileRead(argv[1]);
  it->VersionPrintf();

  // Debug
//  out_fp = fopen("debug.txt","wt");
//  it->DebugFp(out_fp);
//  it->ClassPrintf();
//  it->ClassCallPrintf();
//  fclose(out_fp);

  file_wr = false;

  char *temp;
  sChar *w_file;
  temp = getenv("TEMP");
  if (temp == NULL){w_file = new sChar("");}
  else             {w_file = new sChar(temp);}
  temp = w_file->c_str();
  if (*(temp+strlen(temp)-1) != '\\'){w_file->cat("\\");}
  w_file->cat("pp_z");

  if (it->Err_Rd() == 0)
    {
    file_wr = true;
    FileSeq(buff,w_file->c_str(),"csv");
    out_fp = fopen(buff,"wt");
    it->ExecMain(out_fp);
    fclose(out_fp);
    }
  delete w_file;

/*
  msg_fp = it->GetMsg();
  MEM_LOOP(str,char,msg_fp)
    printf("%s\n",str);
  LOOP_END
*/

  rtn_cd = it->Err_Rd();
  delete it;

  if (rtn_cd == 0)
    {
    DeleteFile(argv[1]);
    ok_flg = RenameFile(buff,argv[1]);
    if (ok_flg == false){printf("rename error(%s->%s).\n\n",buff,argv[1]);}
    else                {printf("convert complete(%s->%s).\n\n",buff,argv[1]);}
    }
  else
    {
    if (file_wr == true){DeleteFile(buff);}
    printf("convert ng(error count=%d).\n\n",it->Err_Rd());
    }

        return 0;
}










