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
//  SubRoutine
//

#ifndef _CSVSUB_H_
#define _CSVSUB_H_

#include "csvmsg.h"
#include "csvstate.h"


// #if class -----------------
class If_T{
  public:
  sChar    *str;         // If sentense(DummyIf->"")
  MM_PTR_T *up_ptr;      // If_T pointer(DummyIf->NULL)
  MEM_FP   *link_fp;     // LinkCell_T
  bool      next_else;   // next else exist
  sChar    *clm_msg;     // csv line
  If_T(MemHeader_T  *it,char *p_str,MM_PTR_T *p_up_ptr);
  ~If_T();
  };


// #sub/#event class ---------------------
class Sub_T{
  public:
  sChar  *name;
  sChar  *sub_name;  // =#sub->retbit =#event->event script
  MEM_FP *parm_fp;
  MEM_FP *local_fp;
  If_T   *dmy_if;
  sChar  *event;
  sChar  *opt;
  sChar  *clm_msg;     // csv line
  Sub_T(MemHeader_T  *it,char *p_name,char *p_sub_name);
  ~Sub_T();
  };

// Interface -----------------
class CsvSub_T{
  public:
  MemHeader_T  *it;
  MEM_FP   *sub_fp;     // #sub list (cell:Sub_T)
  MEM_FP   *if_fp;      // If_T all
  MEM_FP   *cmd_fp;     // sChar all  
  Sub_T    *g_sub;      // work
  If_T     *g_if;       // work
  Msg_T    *msg;
  int       cur_clm;    // Current Colomn
  bool      csvsub_flg; // csvsub/csvstate select flg
  CsvSub_T(MemHeader_T *p_it,Msg_T *p_msg);
  ~CsvSub_T();
  bool CsvRead(CsvAnl_C *csvi);
  bool ExistCheck();
  void space      (FILE *fp,int level);

  private:
  void event_rtn  (CsvAnl_C *csvi);
  void opt_rtn    (CsvAnl_C *csvi);
  void cmd_rtn    (CsvAnl_C *csvi);
  void endif_rtn  (CsvAnl_C *csvi);
  void if_rtn     (CsvAnl_C *csvi,bool if_kbn,bool line_flg);
  void sub_rtn    (CsvAnl_C *csvi);
  void sparm_rtn  (CsvAnl_C *csvi);
  void slocal_rtn (CsvAnl_C *csvi);
  };

#endif // _CSVSUB_H_
