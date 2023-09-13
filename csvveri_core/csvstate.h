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
//  State Machine 
//  1.01:#act,#stop ’Ç‰Á
//

#ifndef _CSVSTATE_H_
#define _CSVSTATE_H_

#include <string.h>
#include <stdio.h>

#include "../csvpp_xbase/t_tool_instance.h"
#include "../csvpp_xbase/ztoken.h"
#include "../csvpp_xbase/ztool.h"
#include "../csvpp_xbase/zbin_conv.h"
#include "csvmsg.h"

#define StCmdKbn 0
#define StIfKbn  1
#define StChgKbn 2
// Ver 1.01
#define StActKbn 3
#define StStopKbn 4
#define StExecKbn 5

// change command list cell information (Ver 1.01)------
class ChgCmdCell_T{
  public:
  sChar *cmd;     // command (sort)
  int    no;      // command no
  ChgCmdCell_T(char *p_cmd,int p_no);
  ~ChgCmdCell_T();
  };

// clock list information (Ver 1.01)------
class ChgClkList_T{
  public:
  sChar    *clk;        // clock
  ChgClkList_T(char *p_clk);
  ~ChgClkList_T();
  };

// line change list information (Ver 1.01)------
class ChgLineList_T{
  public:
  sChar    *name;        // clock + line (sort)
  sChar    *clk;         // clock
  sChar    *line;        // line
  int       line_no;     // line no
  int       size;        // line size
  ChgLineList_T(char *p_clk,char *p_line,int p_line_no);
  ~ChgLineList_T();
  };

// change command list information (Ver 1.01)------
class ChgCmdList_T{
  public:
  sChar  *clk;    // clock (sort)
  MEM_FP *cmd_fp; // ChgCmdCell_T memory list
  int     cmd_no; // command no
  ChgCmdList_T(MemHeader_T *p_it,char *p_clk);
  ~ChgCmdList_T();
  };

// #sparm/#slocal class -----------------
class StParm_T{
  public:
  sChar  *name;
  sChar  *size;
  sChar  *init;
  sChar    *clm_msg;     // csv line
  StParm_T(char *p_name,char *p_size,char *p_init);
  ~StParm_T();
  };


// value set class ------
class ValChg_T{
  public:
  sChar    *name;        // line name
  sChar    *val;         // value
  sChar    *cyc;         // cycle
  ValChg_T(char *p_name,char *p_val,char *p_cyc);
  ~ValChg_T();
  };

// change information------
class Chg_T{
  public:
  sChar    *clk;         // clock
  MEM_FP   *val_fp;      // ValChg list
  int       chg_cnt_no;  // change count no
  sChar    *clm_msg;     // csv line
  Chg_T(MemHeader_T  *it,char *p_clk,int p_chg_cnt_no);
  ~Chg_T();
  };

// linking cell ------------------
class LinkCell_T{
  public:
  int kbn;       // StCmdKbn,StIfKbn,StChgKbn
  MM_PTR_T *ptr; // sChar,Chg_T,StIf_T
  sChar    *clm_msg;     // csv line
  LinkCell_T(int p_kbn,MM_PTR_T *p_ptr);
  ~LinkCell_T();
  };

// #if/#st class -----------------
class StIf_T{
  public:
  sChar    *str;         // Status name/If sentense
  int       if_kbn;      // Ver 1.16  =0:#if  =1:#elseif  =2:#else
  sChar    *status_name; // Status name Ver 1.01
  sChar    *clk;         // Clock name (#if -> "")
  int       no;          // Status no for verilog (#if -> -1)
  MM_PTR_T *up_ptr;      // If_T/St_T pointer
  MEM_FP   *link_fp;     // LinkCell_T
  bool      next_else;   // next else exist
  sChar    *clm_msg;     // csv line
  void init(MemHeader_T  *it,char *p_str,char *p_clk,int p_no,MM_PTR_T *p_up_ptr,char *p_st_name,int p_if_kbn); // Ver 1.01
  StIf_T(MemHeader_T  *it,char *p_str,char *p_clk,int p_no,MM_PTR_T *p_up_ptr,int p_if_kbn);
  StIf_T(MemHeader_T  *it,char *p_str,MM_PTR_T *p_up_ptr,char *p_st_name,int p_if_kbn); // Ver 1.01
  ~StIf_T();
  };

// #status class ---------------------
class Status_T{
  public:
  sChar  *name;
  sChar  *cur_st_name;  // Current #st Name Ver 1.01
  sChar  *clk;          // Clock Name Ver 1.01
  int     init_no;
  MEM_FP *st_fp;
  MEM_FP *st_sub_fp;
  MEM_FP *parm_fp;
  MEM_FP *local_fp;
  MEM_FP *chg_fp;
  sChar  *clm_msg;     // csv line
  Status_T(MemHeader_T  *it,char *p_name);
  ~Status_T();
  };

// Interface -----------------
class CsvState_T{
  public:
  MemHeader_T  *it;
  MEM_FP   *status_fp;  // status list (cell:Status_T)
  MEM_FP   *chg_fp;     // Chg_T all
  MEM_FP   *stif_fp;    // StIf_T all
  MEM_FP   *cmd_fp;     // sChar all
  MEM_FP   *chgline_fp; // change line list (cell:ChgLineList_T) ver 1.01
  MEM_FP   *chgcmd_fp;  // change command list (cell:ChgCmdList_T) ver 1.01
  MEM_FP   *chgclk_fp;  // change clock list (cell:ChgClkList_T) ver 1.01
  int       chgline_cnt; // change line count
  Status_T *g_status;   // work
  StIf_T   *g_stif;     // work
  int       chgseq_cnt; // work
  int       status_no;  // status no
  Msg_T        *msg;
  StrSrchInf_T *ssc;    // String Separate Control
  int       cur_clm;    // Current Colomn
  sChar     *chg_trap;  // Schedule cycle no trap
  sChar     *ary_max;   // Schedule array max
  sCharGrep *grep;
  binConv_C *bin_conv;

  CsvState_T(MemHeader_T *p_it,Msg_T *p_msg);
  ~CsvState_T();
  bool CsvRead(CsvAnl_C *csvi);
  bool ExistCheck();
  void space      (FILE *fp,int level);
  void rep        (sChar    *str);

  private:
  void chg_rtn    (CsvAnl_C *csvi);
  void cmd_rtn    (CsvAnl_C *csvi);
  void go_rtn     (CsvAnl_C *csvi);
  void endif_rtn  (CsvAnl_C *csvi);
  void if_rtn     (CsvAnl_C *csvi,int if_kbn,bool line_kbn);
  void st_rtn     (CsvAnl_C *csvi);
  void status_rtn (CsvAnl_C *csvi);
  void sparm_rtn  (CsvAnl_C *csvi);
  void slocal_rtn (CsvAnl_C *csvi);
  void chgtrap_rtn(CsvAnl_C *csvi);
  void chgmax_rtn (CsvAnl_C *csvi);
  void st_move_rtn(CsvAnl_C *csvi,int kbn); // Ver 1.01
  };

#endif // _CSVSTATE_H_
