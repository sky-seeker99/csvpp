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
//  State Machine (For RTL)
//  1.01:#act,#stop 追加
//  1.02:#assign 追加
//  1.03:#wire_reg 追加
//  1.04:ステートマシンがリセット優先になっていない
//  1.05:#andor 追加
//  1.07:#wire_o
//  1.16:#elseif
//

#ifndef _CSVRSTATE_H_
#define _CSVRSTATE_H_

#include "csvmsg.h"
#include "../csvpp_xbase/ztoken.h"

// assign class (Ver 1.02) ------
class Assign_T{
  public:
  sChar  *var;    // siki
  sChar  *siki;     // dainyu value
  Assign_T(char *p_var,char *p_siki);
  ~Assign_T();
  };

// reg body class ------
class Siki_T{
  public:
  sChar  *siki;    // siki
  sChar  *val;     // dainyu value
  bool    sync;    // sync?
  sChar  *idx;     // index
  sChar  *clm_msg; // csv line
  bool    reset;   // reset jyoken
  sChar  *s_name;  // State Name
  Siki_T(MemHeader_T *p_it,char *p_siki,char *p_val);
  ~Siki_T();
  };

// wire class ------
class Wire_T{
  public:
  sChar    *name;        // wire name
  sChar    *size;        // wire size
  sCharGrep *val;         // assign siki
  bool      defined_flg; // defined flg
  bool      wire_reg;    // Ver 1.03
  sChar    *clm_msg;     // csv line
  bool      wire_o_flg;  // #wire_o sikibetsu Ver 1.07
  MEM_FP   *body_fp;     // body (Siki_T)     Ver 1.07
  int       end_cnt;     // for #wire_o Ver 1.07
  sChar    *def_val;     // for #wire_o Ver 1.07
  //Wire_T(char *p_name,char *p_size,char *p_val);
  Wire_T(MemHeader_T *p_it,char *p_name,char *p_size,char *p_val,bool p_wire_o_flg); // Ver 1.07
  ~Wire_T();
  };

// reg class ------
class Reg_T{
  public:
  sChar  *name;        // reg name
  sChar  *size;        // reg size
  sChar  *clk;         // clock
  sChar  *idx;         // memory array
  MEM_FP *body_fp;     // body (Siki_T)
  bool    use_flg;     // use flg
  bool    defined_flg; // defined flg
  bool    wire_reg;    // Ver 1.03
  bool    andor_flg;   // Ver 1.05
  sChar  *andor_def;   // Ver 1.05
  sChar  *clm_msg;     // csv line
  Reg_T(MemHeader_T *p_it,char *p_name,char *p_size,char *p_clk);
  ~Reg_T();
  };


// State Machine body class ------
class Body_T{
  public:
  Reg_T  *reg;
  sChar  *idx;
  sChar  *val;
  int     cyc;
  sChar  *clm_msg; // csv line
  Body_T(Reg_T *p_reg,char *p_val,int p_cyc,char *p_idx);
  ~Body_T();
  };

// State Machine if class ------
class RStIf_T{
  public:
  sChar    *name;
  int       if_kbn;     // Ver 1.16  =0:#if  =1:#elseif  =2:#else
  MEM_FP   *act_fp;     // Ver 1.01
  MEM_FP   *stop_fp;    // Ver 1.01
  MM_PTR_T *up_ptr;
  MEM_FP   *stif_fp;
  MEM_FP   *body_fp;
  MEM_FP   *pull_fp;
  MEM_FP   *assign_fp;  // Ver 1.02
  int       max_cyc;
  sChar    *clm_msg; // csv line
  RStIf_T(MemHeader_T  *it,char *p_name,MM_PTR_T *p_up_ptr,int p_if_kbn);
  ~RStIf_T();
  };

// State Machine class ------
class RState_T{
  public:
  sChar   *name;
  sChar   *st_name;
  bool     dec_flg;
  bool     en_flg;
  sChar   *enable;
  sChar   *clk;
  sChar   *first_state;
  int      sch_cnt;
  int      init_no;
  MEM_FP  *stif_fp;
  MEM_FP  *list_fp;
  MEM_FP  *rst_fp;  // reset siki(sChar *)
  MEM_FP  *chg_fp;
  sChar   *clm_msg; // csv line
  RState_T(MemHeader_T *p_it,char *p_name,char *p_clk);
  ~RState_T();
  };

// Interface -----------------
class CsvRState_T{
  public:
  MemHeader_T  *it;
  MEM_FP   *status_fp;  // status list (cell:Status_T)
  MEM_FP   *reg_fp;     // register list (cell:Reg_T)
  MEM_FP   *wire_fp;    // wire list (cell:Wire_T)
  RState_T  *g_status;   // work
  RStIf_T   *g_stif;     // work
  int       status_no;  // status no
  Msg_T        *msg;    // Message Class
  StrSrchInf_T *ssc;    // String Separate Control
  StrSrchInf_T *ssc2;   // String Separate Control
  StrSrchInf_T *ssc3;   // String Separate Control
  StrSrchInf_T *ssc5;   // String Separate Control
  int       cur_clm;    // Current Colomn
  Reg_T     *sv_reg;    // for debug
  bool      own_flg;    // owner Flg
  VariableArea_C *work; // work

  CsvRState_T(MemHeader_T *p_it,Msg_T *p_msg);
  ~CsvRState_T();
  bool CsvRead(CsvAnl_C *csvi);
  bool ExistCheck();
  void CsvPost();
  void space      (FILE *fp,int level);

  private:
  void act_rtn    (CsvAnl_C *csvi); // Ver 1.01
  void stop_rtn   (CsvAnl_C *csvi); // Ver 1.01
  void chg_rtn    (CsvAnl_C *csvi);
  void cmd_rtn    (CsvAnl_C *csvi);
  void pull_rtn   (CsvAnl_C *csvi);
  void assign_rtn (CsvAnl_C *csvi); // Ver 1.02
  void go_rtn     (CsvAnl_C *csvi);
  void endif_rtn  (CsvAnl_C *csvi);
  void if_rtn     (CsvAnl_C *csvi,int if_kbn,bool line_kbn); // Ver 1.16
  void st_rtn     (CsvAnl_C *csvi);
  void status_rtn (CsvAnl_C *csvi);
  void wire_reg_rtn(CsvAnl_C *csvi); // Ver 1.03
  void reg_rtn    (CsvAnl_C *csvi);
  void reg_body_rtn (CsvAnl_C *csvi);
  void reg_andor_rtn(CsvAnl_C *csvi);
  void wire_rtn   (CsvAnl_C *csvi,bool wire_o_flg); // Ver 1.07
  bool reg_body   (Reg_T  *reg ,char *str);
  bool wire_body  (Wire_T *wire,char *str); // Ver 1.07
  bool body_rtn   (CsvAnl_C *csvi,int clm,char  *str,int cyc  );
  void rep        (sChar    *str);
  void CsvPostSub (RStIf_T *p_stif,char *p_siki);
  void CsvPostSub2(RStIf_T *p_stif,char *p_siki);  
  };

#endif // _CSVRSTATE_H_
