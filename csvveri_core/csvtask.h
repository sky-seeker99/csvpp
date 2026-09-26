/*
 * Copyright 2026 Shigeru Kasuya
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by me or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
