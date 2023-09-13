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
//
//  Cycle Task 
//

#ifndef _CSVTASK_H_
#define _CSVTASK_H_

#include "csvmsg.h"
#include "../csvpp_xbase/ztoken.h"


// #tparm class -----------------
class CsvCycParm_T{
  public:
  sChar  *name;
  sChar  *size;
  sChar  *init;
  CsvCycParm_T(char *p_name,char *p_size,char *p_init);
  ~CsvCycParm_T();
  };

// #tchg class -----------------
class CsvCycChg_T{
  public:
  sChar  *name;
  sChar  *cyc;
  sChar  *val;
  CsvCycChg_T(char *p_name,char *p_cyc,char *p_val);
  ~CsvCycChg_T();
  };

// #task class -----------------
class CsvCycTask_T{
  public:
  sChar  *name;
  sChar  *clk;
  sChar  *tcnt;
  sChar  *wcnt;
  sChar  *ccnt;
  int     kbn;
  bool    init;
  MEM_FP *cmd_fp;
  MEM_FP *chg_fp;
  MEM_FP *parm_fp;
  MEM_FP *local_fp;
  CsvCycTask_T(MemHeader_T  *p_it,int p_kbn,bool p_init,char *p_name,char *p_clk,char *p_tcnt,char *p_wcnt,char *p_ccnt);
  ~CsvCycTask_T();
  };

  
// CycTaskControlTask Class -----------------
class CsvCycTaskList_T{
  public:
  MemHeader_T  *it;
  MEM_FP       *vct_fp;
  Msg_T        *msg;
  CsvCycTask_T  *vct;
  StrSrchInf_T *ssc;
  sCharGrep    *grep;
  CsvCycTaskList_T(MemHeader_T  *p_it,Msg_T *p_msg);
  ~CsvCycTaskList_T();
  bool CsvRead   (CsvAnl_C *csvi);
  bool ExistCheck();
  void rep       (sChar *str);
  void space     (FILE *fp,int max);

  private:
  void task_rtn  (CsvAnl_C *csvi,int kbn,bool init);
  void tcmd_rtn  (CsvAnl_C *csvi);
  void tchg_rtn  (CsvAnl_C *csvi);
  void tdiff_rtn (CsvAnl_C *csvi,bool plus);
  void tparm_rtn (CsvAnl_C *csvi);
  void tlocal_rtn(CsvAnl_C *csvi);
  };
  
#endif // _CSVTASK_H_
