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
//  CSVPP EXEC CONTROL LIBRARY 
//
// ----------------
// constructor
// ----------------
ExecCtlInf_T::ExecCtlInf_T() {
  int i;
  char *env;

  // File Checking & Initialize
  mode          = 0;
//  cur_clm       = 0;
  err_cnt       = 0;
  dir           = new sChar("");
  env = getenv("csvpp_dir");
  if (env != NULL){dir->set(env);}
  fp            = NULL;
  back_fp       = NULL;
  debug_fp      = NULL;
  debug_mode    = false;
  debug_string  = new sChar("");

  msg_cmd       = new sChar(" null");
  msg_macro     = new sChar("null");
  msg_object    = new sChar("null");

  string_MAX    = 4096;

  g_w0          = new VariableArea_C(256);
  g_w1          = new VariableArea_C(256);
  g_w2          = new VariableArea_C(256);
  g_w3          = new VariableArea_C(256);
  g_w4          = new VariableArea_C(256);
  g_w5          = new VariableArea_C(256);
  g_w6          = new VariableArea_C(256);

  grep          = new sCharGrep("");
  str_ext       = new sCharEX("");
  binConv       = new binConv_C;
//  add_sel_su    = -1;

  inc_uniq_mode = false;  // Ver 1.71
  inc_uniq_fp   = new VariableArray_C(10);


  sp_push_flg   = true; // Ver 1.25

  shell_flg     = false;
  shell_default = new sChar("#default");
  pg_exec       = new PgExec_C;

// mode == 0  Class Call(TOP)
// mode == 1  Class Define
// mode == 2  Class Call
// mode == 3  List  Define
// mode == 4  Macro Local Variable Define

  // Check Patern Set
  i = 0;
  //                                      Mode0         Mode1         Mode2         Mode3         Mode4
  chks[i] = new sChar("%include"    ); chk[i][0]= 0; chk[i][1]= 0; chk[i][2]= 0; chk[i][3]= 0; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%include_dir"); chk[i][0]= 0; chk[i][1]= 0; chk[i][2]= 0; chk[i][3]= 0; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%rem"        ); chk[i][0]= 0; chk[i][1]= 0; chk[i][2]= 0; chk[i][3]= 0; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%class"      ); chk[i][0]= 1; chk[i][1]= 1; chk[i][2]= 1; chk[i][3]= 1; chk[i][4]= 1; ++i;
  chks[i] = new sChar("%classcall"  ); chk[i][0]= 2; chk[i][1]= 2; chk[i][2]= 2; chk[i][3]= 2; chk[i][4]= 2; ++i;
  chks[i] = new sChar("%list"       ); chk[i][0]=-1; chk[i][1]= 3; chk[i][2]=-1; chk[i][3]= 3; chk[i][4]= 3; ++i;
  chks[i] = new sChar("%st"         ); chk[i][0]=-1; chk[i][1]= 4; chk[i][2]=-1; chk[i][3]= 4; chk[i][4]= 4; ++i;
  chks[i] = new sChar("%var"        ); chk[i][0]= 0; chk[i][1]= 0; chk[i][2]= 0; chk[i][3]= 0; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%var_n"      ); chk[i][0]= 0; chk[i][1]= 0; chk[i][2]= 0; chk[i][3]= 0; chk[i][4]= 0; ++i; // Ver 1.64
  chks[i] = new sChar("%varlist"    ); chk[i][0]= 0; chk[i][1]= 0; chk[i][2]= 0; chk[i][3]= 0; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%idx"        ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]=-1; chk[i][3]= 0; chk[i][4]=-1; ++i;
  chks[i] = new sChar("%version"    ); chk[i][0]=-1; chk[i][1]= 0; chk[i][2]=-1; chk[i][3]=-1; chk[i][4]=-1; ++i;
  chks[i] = new sChar("%member_area"); chk[i][0]=-1; chk[i][1]= 0; chk[i][2]=-1; chk[i][3]=-1; chk[i][4]= 1; ++i;
  chks[i] = new sChar("%include_uniq");chk[i][0]= 0; chk[i][1]= 0; chk[i][2]= 0; chk[i][3]= 0; chk[i][4]= 0; ++i;  // Ver 1.71
  chks[i] = new sChar("%classset"   ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%do"         ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%casearg"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%casedo"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%casedoall"  ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%set"        ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%calc"       ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%calcfrm"    ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%calc_f"     ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.31
  chks[i] = new sChar("%calcfrm_f"  ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.31
  chks[i] = new sChar("%calc64"     ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.30
  chks[i] = new sChar("%calcfrm64"  ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.30
  chks[i] = new sChar("%if"         ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%noif"       ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%wif"        ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%wnoif"      ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%endif"      ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%printf"     ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%return"     ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%envrd"      ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%envwr"      ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%separate"   ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%separateex" ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%break"      ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%continue"   ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%textfor"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%listfor"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%endfor"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%listhead"   ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%listset"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%arywr"      ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%aryrd"      ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%arydel"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%arydelall"  ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%arycopy"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%aryfor"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%for"        ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%macro"      ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%call"       ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%debug"      ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%debugoff"   ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%arysep"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%arysepchk"  ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%arysepfix"  ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%argdef"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%argdefchk"  ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%argdeffix"  ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%argpart"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%argpartfix" ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%strsep"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%chgcode"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%calcif"     ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%calcnoif"   ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%calcif_f"   ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.31
  chks[i] = new sChar("%calcnoif_f" ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.31
  chks[i] = new sChar("%calcif64"   ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.30
  chks[i] = new sChar("%calcnoif64" ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.30
  chks[i] = new sChar("%ary_save"   ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.60
  chks[i] = new sChar("%csv_set"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.61
  chks[i] = new sChar("%ary_load"   ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.60
  chks[i] = new sChar("%url_anl"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i; // Ver 1.62
  chks[i] = new sChar("%dbswrite"   ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%dbsdel"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%alias"      ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%beta"       ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%sp_push"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%chg_once"   ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%chg_all"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%find"       ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%timenow"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%today"      ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%binary"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%dateint"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%timeint"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%intdate"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%inttime"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%fopen"      ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%fclose"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%fprintf"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%fcsvwrite"  ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%fclose"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%fsp+"       ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%fsp-"       ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%fsp"        ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%fspcnt"     ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%exec"       ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%fileget"    ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%shell"      ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%shell_begin"); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.66
  chks[i] = new sChar("%shell_end"  ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.66
  chks[i] = new sChar("%rand"       ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%seed"       ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%st_default" ); chk[i][0]=-1; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;
  chks[i] = new sChar("%sjis_utf8"  ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.47
  chks[i] = new sChar("%utf8_sjis"  ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.47
  chks[i] = new sChar("%ob_new"     ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.48
  chks[i] = new sChar("%ob_del"     ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.48
  chks[i] = new sChar("%ob_get"     ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.48
  chks[i] = new sChar("%ob_set"     ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.48
  chks[i] = new sChar("%ob_do"      ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.48
  chks[i] = new sChar("%file_anl"   ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.53
  chks[i] = new sChar("%set_bit"    ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.53
  chks[i] = new sChar("%need_bit"   ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.69
  chks[i] = new sChar("%rtn_mode"   ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.64
  chks[i] = new sChar("%class_save" ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.72
  chks[i] = new sChar("%class_load" ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0; ++i;  // Ver 1.72
  chks[i] = new sChar(""            ); chk[i][0]= 0; chk[i][1]=-1; chk[i][2]= 0; chk[i][3]=-1; chk[i][4]= 0;


  // Memory List Initialize
  it           = new MemHeader_T();
  class_fp     = new MEM_FP(it);
  classcall_fp = new MEM_FP(it);
  object_fp    = new MEM_FP(it);
  listcall_fp  = new MEM_FP(it);
//  work_fp      = new MEM_FP(it);
  mac_fp       = new MEM_FP(it);
  if_fp        = new MEM_FP(it);
  for_fp       = new MEM_FP(it);
  alias_fp     = new MEM_FP(it);
  shell_fp     = new VariableArray_C(10);  // Ver 1.66
  inc_fp       = new MEM_FP(it);
  env_fp       = new MEM_FP(it);

  // Database Interface Initialize
//  db_inf  = new CsvDb_T(it);

  // casedo Interface Initialize
  casedo_fp    = new MEM_FP(it);
  casedo_use   = false;

  // Top ClassCall Store
  cc = new Classcall_T(it,"","");
  it->alloc_ptr = (unsigned char *)cc;
  classcall_fp->mem_alloc();
  cl      = (Class_T *)MM_NULL;
  ob      = (Object_T *)MM_NULL;
//  cur_clm = 0;
  idx     = 0;

  // alias num
  alias_num = 0;

  // etc interface set
  var_ctl  = new varCtl_C(it);
  ci   = new CalcInf_T(var_ctl);
  ci_f = new CalcInf_f_T(var_ctl);  // Ver 1.31
  ci64 = new CalcInf64_T(var_ctl);  // Ver 1.30
  timectl = new Time_T();
  datectl = new Date_T();
  file_get = new FileGet_T(it);
  file_handle = new FileHandle_T(it);
  utf8_inf = new Utf8Area_C(16);
  filename_anl = new FileNameAnl_C; // Ver 1.53

  csv_anl = new CsvAnl_C; // Ver 1.61
  url_anl = new UrlNameAnl_C; // Ver 1.62

  prog_anl = new progLine_C(var_ctl);
  s_token  = new tokenAnl_C;
  s_token->setKey('['); s_token->setKeyFlag();
  s_token->setKey(':'); s_token->setKeyFlag();
  s_token->setKey(']'); s_token->setKeyFlag();

  // Ver 1.64
  var_num = 0;
  rtn_mode = true;
  firstCsvFlag=true;

  // Ver 1.66
  shell_nest = new ShellNest_T;

  // ransu hasei
  randomize();
  srand(0);
}


// ----------------
// destructor
// ----------------
ExecCtlInf_T::~ExecCtlInf_T(){
  Class_T       *cl;
  Classcall_T   *cc;
  Object_T      *ob;
  ListCall_T    *lc;
//  WorkCell_T    *wc;
  MacCallCell_T *mcc;
  IfLvlCell_T   *il;
  ForLvlCell_T  *fl;
  Alias_T       *als;
  CaseDo_T      *cd;
  int i;
  sChar         *str;
  int w_state=0;
try
  {
  w_state=0;
  delete timectl;
  w_state=1;
  delete datectl;
  w_state=2;
  delete file_get;
  w_state=3;
  delete file_handle;
  w_state=4;
  delete debug_string;
  w_state=5;
  delete ci;
  w_state=6;
  delete ci_f; // Ver 1.31
  w_state=7;
  delete ci64; // Ver 1.30

  delete prog_anl;
  delete var_ctl;

  w_state=8;
  delete msg_cmd;
  w_state=9;
  delete msg_macro;
  w_state=10;
  delete msg_object;
  delete utf8_inf;
  delete grep;
  delete str_ext;
  delete binConv;
  delete s_token;
  delete filename_anl;
  delete csv_anl; // Ver 1.61
  delete url_anl; // Ver 1.62

  w_state=10;
  MEM_LOOP(cl ,Class_T      ,class_fp    ) delete cl;  LOOP_END
  w_state=11;
  MEM_LOOP(cc ,Classcall_T  ,classcall_fp) delete cc;  LOOP_END
  w_state=12;
  MEM_LOOP(ob ,Object_T     ,object_fp   ) delete ob;  LOOP_END
  w_state=13;
  MEM_LOOP(lc ,ListCall_T   ,listcall_fp ) delete lc;  LOOP_END
  w_state=14;
//  MEM_LOOP(wc ,WorkCell_T   ,work_fp     ) delete wc;  LOOP_END
  w_state=15;
  MEM_LOOP(mcc,MacCallCell_T,mac_fp      ) delete mcc; LOOP_END
  w_state=16;
  MEM_LOOP(il ,IfLvlCell_T  ,if_fp       ) delete il;  LOOP_END
  w_state=17;
  MEM_LOOP(fl ,ForLvlCell_T ,for_fp      ) delete fl;  LOOP_END
  w_state=18;
  MEM_LOOP(als,Alias_T      ,alias_fp    ) delete als; LOOP_END
  w_state=19;
  MEM_LOOP(cd ,CaseDo_T     ,casedo_fp   ) delete cd;  LOOP_END
  w_state=20;
  MEM_LOOP(str,sChar        ,inc_fp      ) delete str; LOOP_END
  w_state=21;
  MEM_LOOP(str,sChar        ,env_fp      ) delete str; LOOP_END

  ARY_LOOP(str,sChar        ,inc_uniq_fp ) delete str; LOOP_END
  delete inc_uniq_fp;


  w_state=22;
//  if (add_sel_su > 0){
//    for(i=0;i<add_sel_su;++i){
//      if (*(add_sel+i) != MM_NULL){delete [] *(add_sel+i);}
//    }
//    delete [] add_sel;
//  }

  w_state=23;
  for(i=0;i<cmd_MAX ;++i){delete chks[i];}

  w_state=24;
  shell_exec();


  delete pg_exec;
  delete g_w0;
  delete g_w1;
  delete g_w2;
  delete g_w3;
  delete g_w4;
  delete g_w5;
  delete g_w6;

  w_state=25;
  delete shell_fp;
  w_state=26;
  delete dir;
  w_state=27;
  delete class_fp;
  w_state=28;
  delete classcall_fp;
  w_state=29;
  delete object_fp;
  w_state=30;
  delete listcall_fp;
  w_state=31;
//  delete work_fp;
  w_state=32;
  delete mac_fp;
  w_state=33;
  delete if_fp;
  w_state=34;
  delete for_fp;
  w_state=35;
  delete alias_fp;
  w_state=36;
//  delete db_inf;
  w_state=37;
  delete shell_default;
  w_state=38;
  delete casedo_fp;
  w_state=39;
  delete inc_fp;
  w_state=40;
  delete env_fp;
  w_state=41;
  delete it;

  delete shell_nest; // Ver 1.66

  }

  catch (...)
  {
    fprintf(stderr,"memory release error.(state=%d)\n",w_state);
    return;
  }
}


// ----------------
// program arg get
// ----------------
void ExecCtlInf_T::shell_exec(){
  sChar *str;
  char *w;

  if (shell_flg == false){return;}

  ARY_LOOP(str,sChar,shell_fp)
    w = str->c_str();
	if ((*w == '#') || (*w == '&')){pg_exec->prmSet(w+1,true);}
    else                           {pg_exec->prmSet(w,true);}
  LOOP_END
  if(back_fp != NULL){fclose(back_fp);  printf("shell input file close\n");}
  back_fp = NULL;

  printf("[shell]>%s\n",pg_exec->getCommand());
  pg_exec->Exec();

  ARY_LOOP(str,sChar,shell_fp)
    w = str->c_str();
    if (*w == '&'){csvfile_exec(w+1);}
    delete str;
  LOOP_END
  shell_fp->clear();
}


// ----------------
// program arg get
// ----------------
void ExecCtlInf_T::ProgramArgRead(int argc,char *argv[]){
  int i,k,max;
  char *str;
  char *env;
  StrSrchInf_T *ssc;
  sChar *sstr;
  int kbn;
  bool ff;
  sChar *cmd;
  sChar *xls_file; // Ver 1.43

  ssc = new StrSrchInf_T();
  ssc->Set(';');

  env = getenv("csvpp_dir");
  if (env != NULL){
    ssc->Main(env);
    max = ssc->GetSu();
    for(k=0;k<max;++k){
      sstr = ssc->Get(k);
      it->alloc_ptr = (unsigned char *)new sChar(sstr->c_str());
      inc_fp->mem_alloc();
    }
  }

  ff = false;
  xls_file = new sChar(""); // Ver 1.43
  bool p_flag=false;
  bool o_flag=false;  // Ver 1.70
  for(i=2;i<argc;++i){
    str = argv[i];
    if (*str != '-'){continue;}
    kbn = 0;
    if ((*(str+1) == 'P') || (*(str+1) == 'p')){p_flag=true;}
    if ((*(str+1) == 'O') || (*(str+1) == 'o')){o_flag=true;} // Ver 1.70
	if ((*(str+1) == 'S') || (*(str+1) == 's')){sp_push_flg=false;}
    if ((*(str+1) == 'I') || (*(str+1) == 'i')){kbn = 1;}
    if ((*(str+1) == 'D') || (*(str+1) == 'd')){kbn = 2;}
    if ((*(str+1) == 'B') || (*(str+1) == 'b')){kbn = 3;}
    if ((*(str+1) == 'F') || (*(str+1) == 'f')){
      ff  = true;
      xls_file->set(str+2);
    }
    if (kbn == 0){continue;}

    ssc->Main(str+2);
    max = ssc->GetSu();
    for(k=0;k<max;++k){
      sstr = ssc->Get(k);
      if (kbn == 3){string_MAX = SujiConvEx(sstr->c_str()); break;}
      it->alloc_ptr = (unsigned char *)new sChar(sstr->c_str());
      if (kbn == 1){inc_fp->mem_alloc();}
      if (kbn == 2){env_fp->mem_alloc();}
    }
  }
  delete ssc;

  if (ff == false){delete xls_file; return;}

  pg_exec->prmSet("csvfront.exe");
  pg_exec->prmSet(argv[1]);

  g_w0->set(0,0x00);
  bool first = true;
  MEM_LOOP(sstr,sChar,inc_fp)
    if (first){first = false; g_w0->set_string("-i");}
    else      {               g_w0->cat_string(";");}
    g_w0->cat_string(sstr->c_str());
  LOOP_END
  if (first == false) {
    pg_exec->prmSet(g_w0->cc_str());
  }


  first = true;
  if (strcmp(xls_file->c_str(),"") != 0){
    first = false;
    g_w0->set_string("-x");
    g_w0->cat_string(xls_file->c_str());
  }
  if (first == false) {
    pg_exec->prmSet(g_w0->cc_str());
  }

  if (p_flag){pg_exec->prmSet("-p");}
  if (o_flag){pg_exec->prmSet("-o");} // Ver 1.70
  printf("[csvfront]>%s\n",pg_exec->getCommand());
  pg_exec->Exec();
  delete xls_file;
}


// @2:Base Tool -----------------------------------------------------------
// ----------------
// Sel Atai Get
// ----------------
void  ExecCtlInf_T::SelGetReset(Program_C *pc){
  prog_anl->put(pc);
}
void  ExecCtlInf_T::SelGetReset(CsvInf_T *csvi_fp){
  prog_anl->put(csvi_fp);
}

char *ExecCtlInf_T::SelGet(){
  char *w = prog_anl->get(false);
  if (prog_anl->okCheck() == false){ErrMsg(MSG02,prog_anl->errStr);}
  return(w);
}

char *ExecCtlInf_T::SelGet_direct(){
  char *w = prog_anl->get(true);
  if (prog_anl->okCheck() == false){ErrMsg(MSG02,prog_anl->errStr);}
  return(w);
}


void ExecCtlInf_T::SelGet_skip(){
  prog_anl->resetReadPtr();
  for(;;){
    char *w = prog_anl->get(true);
    if (w == NULL) {break;}
    if (*w != 0x00) {
      int ptr = prog_anl->prog_fp->getReadPtr();
      if (ptr > 0) {ptr--;}
      prog_anl->prog_fp->setReadPtr(ptr);
      break;
    }
  }
}


// ------------------------
// Work Variable Level Add
// ------------------------
void ExecCtlInf_T::WorkVarLvlAdd(){
  var_ctl->add();
}

// ------------------------
// Work Variable Level Del
// ------------------------
void ExecCtlInf_T::WorkVarLvlDel(){
  var_ctl->del();
}

// ------------------
// Variable Search
// ------------------
VarCell_T *ExecCtlInf_T::VarSrch(char *p_key){
  return(var_ctl->srch(p_key));
}

char *ExecCtlInf_T::VarSrch_Atai(char *key){
  VarCell_T *vc;
  int up;
  int dn;
  int max;
  int i;
  int len;
  char *w;
  bool up_flg;
  bool dn_flg;
  bool rev_flg;
  bool len_flg;
  char *env;
  char fmt;

  if(*key == '\\'){
    //env = getenv(key+1);
    env = x_getenv(key+1);
    if (env == NULL){g_w6->set(0,0x00);}
    else            {g_w6->set_string(env);}
    return(g_w6->c_str());
  }

  fmt = 0x00;
  if(*key == '#'){
    len=strlen(key);
    for(i=1;i<len;++i){
      if (*(key+i) == '#'){
        // fmt = VarFormatCheck(g_w5);
        g_w6->check(g_w5->len()+25);
        if (fmt == 's'){
          if ((vc = VarSrch(key+i+1)) == (VarCell_T *)MM_NULL){return("?????");}
          sprintf(g_w6->cc_str(),g_w5->cc_str(),vc->atai->c_str());
        }else{
          sprintf(g_w6->cc_str(),g_w5->cc_str(),ci->CalcExecute(key+i+1));
        }
        return(g_w6->c_str());
      }
      if (fmt == 0x00){
        if (*(key+i) == '%'){
          if (*(key+i+1) != '%'){
            fmt = *(key+i);
          }
        }
      } else {
        if (fmt == '%'){
          if (*(key+i) == '%'){*(key+i) = 0x20;}
          if (*(key+i) == 'o'){fmt = *(key+i);}
          if (*(key+i) == 'd'){fmt = *(key+i);}
          if (*(key+i) == 'i'){fmt = *(key+i);}
          if (*(key+i) == 'x'){fmt = *(key+i);}
          if (*(key+i) == 'X'){fmt = *(key+i);}
          if (*(key+i) == 'u'){fmt = *(key+i);}
          if (*(key+i) == 'c'){fmt = *(key+i);}
          if (*(key+i) == 's'){fmt = *(key+i);}
          if (*(key+i) == 'f'){fmt = *(key+i);}
          if (*(key+i) == 'e'){fmt = *(key+i);}
          if (*(key+i) == 'E'){fmt = *(key+i);}
          if (*(key+i) == 'g'){fmt = *(key+i);}
          if (*(key+i) == 'G'){fmt = *(key+i);}
          if (*(key+i) == 'p'){fmt = *(key+i);}
          if (*(key+i) == 'n'){fmt = *(key+i);}
        }
      }
      g_w5->set(i-1,*(key+i));
      g_w5->set(i  ,0x00);
    }
    g_w6->int_set(ci->CalcExecute(key+1));
    return(g_w6->c_str());
  }


  s_token->set(key);
  max = s_token->getNum();
  if (max < 2){
    if (*key == '@'){
      if ((vc = VarSrch(key+1)) == (VarCell_T *)MM_NULL){return("?????");}
      g_w6->int_set(vc->atai->len());
      return(g_w6->c_str());
    }else{
      if ((vc = VarSrch(key)) == (VarCell_T *)MM_NULL){return("?????");}
      return(vc->atai->c_str());
    }
  }

  w = s_token->get(0);
  if (*(w) == '@'){
    len_flg = true;
    if ((vc = VarSrch(w+1)) == NULL){return("?????");}
  } else {
    len_flg = false;
    if ((vc = VarSrch(w)) == NULL){return("?????");}
  }

  len = vc->atai->len();

  w = s_token->get(1);
  if (strcmp(w,"[") != 0){return("?????");}
  g_w6->int_set(len-1);
  w = s_token->get(2);
  grep->set(w);
  grep->replace_all("@",g_w6->c_str());
  up = ci->CalcExecute(grep->c_str());

  w = s_token->get(3);
  if (strcmp(w,"]") == 0){
    if ((up < 0) && (len >= up)){
      if (len_flg == true){return("0");}
      return("");
    }
    g_w6->set(1,0x00);
    g_w6->set(0,*(vc->atai->c_str() + up));
    if (len_flg == true){return("1");}
    return(g_w6->c_str());
  }
  if (strcmp(w,":") != 0){return("?????");}

  g_w6->int_set(len-1);
  w = s_token->get(4);
  grep->set(w);
  grep->replace_all("@",g_w6->c_str());
  dn = ci->CalcExecute(grep->c_str());

  w = s_token->get(5);
  if (strcmp(w,"]") != 0){return("?????");}

  up_flg = true;
  dn_flg = true;
  rev_flg = false;
  if (up > dn){i=up; up=dn; dn=i; rev_flg = true;}
  if (up < 0) {up = 0; up_flg = false;}
  if (dn < 0) {dn = 0; dn_flg = false;}
  if (up >= len){up = len-1; up_flg = false;}
  if (dn >= len){dn = len-1; dn_flg = false;}
  if ((up_flg == false) && (dn_flg == false)){
    if (len_flg == true){return("0");}
    return("");
  }
  g_w6->check(dn-up+2);
  mem_cpy(g_w6->c_str(),vc->atai->c_str()+up,dn-up+1);
  if (rev_flg == true){bitc_ex(g_w6->c_str(),dn-up+1);}
  g_w6->set(dn-up+1,0x00);
  if (len_flg == true){g_w6->int_set(dn-up+1);}
  return(g_w6->c_str());
}

// ------------------
// String Reprace
// ------------------
//void ExecCtlInf_T::StrChg(char *rep,char *str,char sep)
// Ver 1.32
void ExecCtlInf_T::StrChg(VariableArea_C *rep,char *str,char sep){
  int i,k,l;
  int mode;       
  //char key[4096];
  char *rkey;

  if ( str == (char *)MM_NULL){rep->set(0,0x00); return;}
  if (*str == 0x00           ){rep->set(0,0x00); return;}

  VariableArea_C *key = new VariableArea_C(64);

  mode = 0;
  rep->init();
  key->init();
  int len = strlen(str);
  for(i=0;i<len;++i){
    if (*(str+i) == sep){
      if (mode == 0){mode = 1; continue;}
      // search & replace  
      key->set(0x00);
      unsigned char *w_key = key->c_str();
      if (*w_key == 0x00){rep->set(sep);}
      else{
        if ((rkey = VarSrch_Atai(w_key)) == NULL){
          rep->set(sep);
          rep->set_n(w_key,strlen((char *)w_key));
          rep->set(sep);
        } else{
          rep->set_n(rkey,strlen(rkey));
        }
      }
      mode = 0;
      key->init();
      continue;
    }
    if (mode == 0){rep->set(*(str+i));}
    else          {key->set(*(str+i));}
  }
  rep->set(0x00);
  delete key;
}

// -------------------------------
// Variable Strings -> int Change 
// -------------------------------
long ExecCtlInf_T::VarToInt(char *key){
  char *str;
  
  if ((str = VarSrch_Atai(key)) == (char *)MM_NULL){str = key;}
  return(SujiConvSuper(str));
}


// --------------
// from search
// --------------
McbArea_C *ExecCtlInf_T::from_srch(Program_C *pc,MEM_FP *prg_fp){
  McbArea_C   *from=NULL;
  int         lvl;
  Program_C  *w_pc;
  char       *w_str;

  if (pc->for_jump_addr != NULL){return(pc->for_jump_addr);}  // cache

  lvl    = 1;
  for(prg_fp->mem_mcb_next_set();;prg_fp->mem_mcb_next_set()){
    if (prg_fp->mem_mcb_ptr_rd() == MM_NULL){ErrMsg(MSG10); return(MM_NULL);}
    w_pc = (Program_C *)prg_fp->mem_link_ptr_rd();
    SelGetReset(w_pc);
    if ((w_str = SelGet()) == NULL) {continue;}
    if (strcmp(w_str,"%listfor")==0){++lvl; continue;}
    if (strcmp(w_str,"%aryfor" )==0){++lvl; continue;}
    if (strcmp(w_str,"%textfor")==0){++lvl; continue;}
    if (strcmp(w_str,"%for"    )==0){++lvl; continue;}
    if (strcmp(w_str,"%endfor" )==0){
      --lvl;
      if (lvl == 0){from = prg_fp->mem_mcb_ptr_rd(); break;}
    }  
  }
  pc->for_jump_addr = from;
  return(from);
}

// ---------------------
// class version printf
// ---------------------
void ExecCtlInf_T::VersionPrintf(){
  sChar *s_str;

  MEM_LOOP(cl,Class_T,class_fp)
    MEM_LOOP(s_str,sChar,cl->version_fp)
      printf("%s\n",s_str->c_str());
    LOOP_END
  LOOP_END
}

// @3:CsvFile Read & Structure -----------------------------------------------------------
// ------------------------
// CsvFile Read(Main)
// ------------------------
void ExecCtlInf_T::CsvFileRead(char *csv_file){
  CsvInf_T *csvi_fp;
  char     *str;
  int       no;
  int       i;
  MEM_FP   *mem_fp;
//  Alias_T  *als;

  printf("File Read(File=%s)\n",csv_file);
  if (FileExist(csv_file) == -1){++err_cnt; printf(xMSG00,csv_file); return;}

  csvi_fp  = new CsvInf_T(csv_file);
  if (csvi_fp->CsvError_Rd() != 0)
    {
    ++err_cnt;
    printf("file cannot open error. file=%s\n",csv_file);
//    CatMsg(csvi_fp->GetMsg());
    delete csvi_fp;
    return;
    }

  if (sp_push_flg){csvi_fp->sp_push_set(true);} // Ver 1.25

  mem_fp = new MEM_FP(it);
  for(;;){
    Application->ProcessMessages();  // Ver 1.28
    if (csvi_fp->CsvFgets() == -1) {break;}        // CsvFile Read
    SelGetReset(csvi_fp);                                 // Command Check
    if ((str = SelGet())==NULL){continue;}
    sp_push(str); sp_push2(str); // Ver 1.25
    for(no=0;no<cmd_MAX;++no){
      if (strcmp(chks[no]->c_str(),"" )==0){break;}
      if (strcmp(chks[no]->c_str(),str)==0){
        msg_cmd->set(str);  // message command
        break;
      }
    }
    if (chk[no][mode] == -1){ErrMsg(csvi_fp,xMSG07); continue;}

    for(i=0;;){
      if (no == i){include_rtn     (csvi_fp); break;}  ++i;
	  if (no == i){include_dir_rtn (csvi_fp); break;}  ++i;
	  if (no == i){                           break;}  ++i;
	  if (no == i){class_rtn       (csvi_fp); break;}  ++i;
	  if (no == i){classcall_rtn   (csvi_fp); break;}  ++i;
	  if (no == i){list_rtn        (csvi_fp); break;}  ++i;
	  if (no == i){st_rtn          (csvi_fp); break;}  ++i;
	  if (no == i){var_rtn         (csvi_fp); break;}  ++i;
	  if (no == i){var_n_rtn       (csvi_fp); break;}  ++i;
	  if (no == i){varlist_rtn     (csvi_fp); break;}  ++i;
	  if (no == i){idx_rtn         (csvi_fp); break;}  ++i;
	  if (no == i){version_rtn     (csvi_fp); break;}  ++i;
	  if (no == i){member_area_rtn (csvi_fp); break;}  ++i;
	  if (no == i){include_uniq_rtn(csvi_fp); break;}  
				   pg_write_rtn    (csvi_fp); break;
	}
    if (chk[no][mode] > 0){mode = chk[no][mode];}
  }

  MEM_LOOP(str,char,mem_fp)
    delete str;
  LOOP_END
//  CatMsg(csvi_fp->GetMsg());
  delete csvi_fp;
  delete mem_fp;
}

// ----------------
// %include
// ----------------
void ExecCtlInf_T::include_rtn(CsvInf_T *csvi_fp){
  char *str;
  sChar *sstr;
  sChar *w;
  char  *a;

  if ((str = SelGet()) == NULL){ErrMsg(csvi_fp,xMSG01); return;}

  bool uniq_flag = false;
  ARY_LOOP(sstr,sChar,inc_uniq_fp)
	if (strcmp(sstr->c_str(),str)==0) {
	  uniq_flag = true;
	  break;
	}
  LOOP_END

  if (inc_uniq_mode == true) {
	if (uniq_flag) {
	  printf("include file skip. file=%s\n",str);
	  return;
	}
  }

  w = new sChar("");
  bool exist=false;
  MEM_LOOP(sstr,sChar,inc_fp)
	a = sstr->c_str();
	w->set(a);
	if (*(a+strlen(a)-1) != '\\'){w->cat("\\");}
	w->cat(str);
	if (FileExist(w->c_str()) == 0){exist=true; break;}
  LOOP_END

  if (exist){CsvFileRead(w->c_str());}
  else      {CsvFileRead(str);}

  delete w;
  if (uniq_flag == true) {return;}

  sstr = new sChar(str);
  inc_uniq_fp->mem_alloc((unsigned char *)sstr);

}


// ----------------
// %include_uniq  Ver 1.71
// ----------------
void ExecCtlInf_T::include_uniq_rtn(CsvInf_T *csvi_fp){
  char *str;
  sChar *sstr;
  int max,k;



  if ((str = SelGet()) == NULL){ErrMsg(csvi_fp,xMSG07); return;}
  if (strcmp(str,"on" )==0) {inc_uniq_mode = true;  printf("inlcude uniq mode on.\n");}
  if (strcmp(str,"off")==0) {inc_uniq_mode = false; printf("inlcude uniq mode off.\n");}
  if (strcmp(str,"ON" )==0) {inc_uniq_mode = true;  printf("inlcude uniq mode on.\n");}
  if (strcmp(str,"OFF")==0) {inc_uniq_mode = false; printf("inlcude uniq mode off.\n");}


}

// ----------------
// %include_dir
// ----------------
void ExecCtlInf_T::include_dir_rtn(CsvInf_T *csvi_fp){
  char *str;
  StrSrchInf_T *ssc;
  sChar *sstr;
  int max,k;

  ssc = new StrSrchInf_T();
  ssc->Set(';');

  if ((str = SelGet()) == NULL){dir->set("");}
  else {
    dir->set(str);
    ssc->Main(str);
    max = ssc->GetSu();
    for(k=0;k<max;++k){
      sstr = ssc->Get(k);
      it->alloc_ptr =(unsigned char *) new sChar(sstr->c_str());
      inc_fp->mem_alloc();
    }
  }
  delete ssc;
}

// ----------------
// %var
// ----------------
void ExecCtlInf_T::var_rtn(CsvInf_T *csvi_fp){
  char *var;
  char *init;

  if ((var  = SelGet()) == NULL){ErrMsg(csvi_fp,xMSG02); return;}
  if ((init = SelGet()) == NULL){init = "";}
  if (mode == 0){cc->VarStore    (var,init);}  // Class Call(TOP)
  if (mode == 1){cl->VarStore    (var,init);}  // Class Define
  if (mode == 2){cc->VarStore    (var,init);}  // Class Call
  if (mode == 3){cl->ListVarStore(var,init);}  // List  Define
  if (mode == 4){cl->PrgVarStore (var,init);}  // Macro Local Variable Define
}

// ----------------
// %var_n
// ----------------
void ExecCtlInf_T::var_n_rtn(CsvInf_T *csvi_fp){
  char *var;
  char *init;
  char buf[64];

  if ((var  = SelGet()) == NULL){ErrMsg(csvi_fp,xMSG02); return;}
  if ((init = SelGet()) == NULL){
	sprintf(buf,"%d",var_num);
	init = buf;
  }
  else {
	var_num = SujiConvEx(init);
	if (var_num < 0) {
	  var_num = 0;
	}
  }
  var_num++;

  if (mode == 0){cc->VarStore    (var,init);}  // Class Call(TOP)
  if (mode == 1){cl->VarStore    (var,init);}  // Class Define
  if (mode == 2){cc->VarStore    (var,init);}  // Class Call
  if (mode == 3){cl->ListVarStore(var,init);}  // List  Define
  if (mode == 4){cl->PrgVarStore (var,init);}  // Macro Local Variable Define
}


// ----------------
// %varlist
// ----------------
void ExecCtlInf_T::varlist_rtn(CsvInf_T *csvi_fp){
  char *var;

  for(;;){
    if ((var  = SelGet()) == NULL){break;}
    if (mode == 0){cc->VarStore    (var,"");}  // Class Call(TOP)
    if (mode == 1){cl->VarStore    (var,"");}  // Class Define
    if (mode == 2){cc->VarStore    (var,"");}  // Class Call
    if (mode == 3){cl->ListVarStore(var,"");}  // List  Define
    if (mode == 4){cl->PrgVarStore (var,"");}  // Macro Local Variable Define
  }
}

// ----------------
// %idx
// ----------------
void ExecCtlInf_T::idx_rtn(CsvInf_T *csvi_fp){
  char *var;

  if ((var = SelGet()) == NULL){ErrMsg(csvi_fp,xMSG02); return;}
  if (mode == 3){cl->ListIdxStore(var);}
}

// ----------------
// %list
// ----------------
void ExecCtlInf_T::list_rtn(CsvInf_T *csvi_fp){
  char *list;

  if ((list = SelGet()) == NULL){ErrMsg(csvi_fp,xMSG03); return;}
  if (mode == 1){cl->ListStore(list);} // Class Define
  if (mode == 3){cl->ListStore(list);} // List  Define
  if (mode == 4){cl->ListStore(list);} // Macro Local Variable Define
}

// ----------------
// %st
// ----------------
void ExecCtlInf_T::st_rtn(CsvInf_T *csvi_fp){
  char *pg;

  if ((pg  = SelGet()) == NULL){ErrMsg(csvi_fp,xMSG04); return;}
  if (mode == 1){cl->PrgStore(pg);} // Class Define
  if (mode == 3){cl->PrgStore(pg);} // List  Define
  if (mode == 4){cl->PrgStore(pg);} // Macro Local Variable Define
}

// ----------------
// %class
// ----------------
void ExecCtlInf_T::class_rtn(CsvInf_T *csvi_fp){
  char *str;

  if ((str  = SelGet()) == NULL){ErrMsg(csvi_fp,xMSG05); return;}
  it->srch_key = str;
  if (class_fp->mem_srch() == 0){ErrMsg(csvi_fp,xMSG06); return;}

  cl = new Class_T(it,str);
  it->alloc_ptr = (unsigned char *)cl;
  class_fp->mem_srch_alloc();

  for(;;){
    if ((str  = SelGet()) == NULL){break;}
    cl->ClassStore(str);
  }
}

// ----------------
// %classcall
// ----------------
void ExecCtlInf_T::classcall_rtn(CsvInf_T *csvi_fp){
  char *str;
  char *obj;

  if ((str  = SelGet()) == NULL){ErrMsg(csvi_fp,xMSG05); return;}
  if ((obj  = SelGet()) == NULL){ErrMsg(csvi_fp,xMSG08); return;}

  cc = new Classcall_T(it,str,obj);
  it->alloc_ptr = (unsigned char *)cc;
  classcall_fp->mem_alloc();

  // constructor
  constructor(str);
}

// ---------------------------
// %classcall sub constructor
// ---------------------------
void ExecCtlInf_T::constructor(char *class_name){
  char *sel[2];
  sChar *s_str;
  Class_T *cl;

  // class search
  it->srch_key = class_name;
  if (class_fp->mem_srch() != 0){return;}
  cl = (Class_T *)class_fp->mem_link_ptr_rd();

  MEM_LOOP(s_str,sChar,cl->class_fp)
    constructor(s_str->c_str());
  LOOP_END

  // constructor search
  it->srch_key = cl->class_name->c_str();
  if (cl->prg_fp->mem_srch() == 0){
    sel[0] = new char[4];
    sel[1] = new char[strlen(it->srch_key)+1];
    strcpy(sel[0],"%do");
    strcpy(sel[1],it->srch_key);
    it->alloc_ptr  = (unsigned char *)new Program_C(2,sel);
    cc->prg_fp->mem_alloc();
    delete [] sel[0];
    delete [] sel[1];
  }
}

// ---------------------------
// %classcall sub destructor
// ---------------------------
void ExecCtlInf_T::destructor(char *class_name){
  char *sel[2];
  sChar *s_str;
  sChar *w_str;
  Class_T *cl;

  // class search
  it->srch_key = class_name;
  if (class_fp->mem_srch() != 0){return;}
  cl = (Class_T *)class_fp->mem_link_ptr_rd();

  // constructor search
  it->srch_key = cl->class_name->c_str();
  if (cl->prg_fp->mem_srch() == 0){
    w_str = new sChar("~");
    w_str->cat(it->srch_key);
    sel[0] = new char[4];
    sel[1] = new char[strlen(w_str->c_str())+1];
    strcpy(sel[0],"%do");
    strcpy(sel[1],w_str->c_str());
    it->alloc_ptr  = (unsigned char *)new Program_C(2,sel);
    cc->prg_fp->mem_alloc();
    delete [] sel[0];
    delete [] sel[1];
    delete w_str;
  }

  for(cl->class_fp->mem_mcb_end_set();;cl->class_fp->mem_mcb_before_set()){
    if (cl->class_fp->mem_mcb_ptr_rd() == MM_NULL){break;}
    s_str = (sChar *)cl->class_fp->mem_link_ptr_rd();
    destructor(s_str->c_str());
  }
}

// ----------------
// %version
// ----------------
void ExecCtlInf_T::version_rtn(CsvInf_T *csvi_fp){
  cl->VersionStore(csvi_fp,prog_anl->getClm());
}

// ----------------
// %member_area
// ----------------
void ExecCtlInf_T::member_area_rtn(CsvInf_T *csvi_fp){
}


// ----------------
// ELSE COMMAND
// ----------------
void ExecCtlInf_T::pg_write_rtn(CsvInf_T *csvi_fp){
  if (mode == 0) {cc->PrgLineStore(csvi_fp);}  // Class Call(TOP)
  if (mode == 2) {cc->PrgLineStore(csvi_fp);}  // Class Call
  if (mode == 4) {cl->PrgLineStore(csvi_fp);}  // Macro Local Define
}

// @4:Program Execute -----------------------------------------------------------
// ----------------
// Program Execute
// ----------------
void ExecCtlInf_T::ExecMain(FILE *out_fp){
  Var_B         *vb;
//  WorkCell_T    *wc;
  VarCell_T     *vc;
  ListCall_T    *lc;

  if (Err_Rd() > 0){return;}
  fp = out_fp;
  if (fp == NULL){return;}

  msg_cmd->set(" null");

  MEM_LOOP(cc ,Classcall_T  ,classcall_fp)
    // destructor
    destructor(cc->class_name->c_str());

    // Classcall -> Object Build
    ob = (Object_T *)MM_NULL;
    for(;;){
      if (*(cc->class_name->c_str()) == 0x00){break;}
      it->srch_key = cc->class_name->c_str();
      if (class_fp->mem_srch () != 0){ErrMsg(MSG11,it->srch_key); break;}
      it->srch_key = cc->obj_name->c_str();
      if (object_fp->mem_srch() == 0){
        ob = (Object_T *)object_fp->mem_link_ptr_rd();
        delete ob;
        object_fp->mem_del();
      }
      ob = new Object_T(it,cc->obj_name->c_str());
      it->alloc_ptr = (unsigned char *)ob;
      object_fp->mem_srch_alloc();
      cl = (Class_T *)class_fp->mem_link_ptr_rd();
      ObjectBuild(cl);
      break;
    }
    
    // Object Variable -> Work Variable
    if (ob != (Object_T *)MM_NULL){
      msg_object->set(ob->name->c_str());
      msg_macro->set("null");
      msg_cmd->set("null");
      WorkVarLvlAdd();
      MEM_LOOP(vc,VarCell_T,ob->var_fp)
        var_ctl->store(vc);
      LOOP_END
    }

    // Classcall Variable -> Work Variable
    WorkVarLvlAdd();
    if (var_ctl->store("_ClassName",cc->class_name->c_str()) == NULL){ErrMsg(MSG12,"_ClassName");}
    if (var_ctl->store("_InstName",cc->obj_name->c_str())    == NULL){ErrMsg(MSG12,"_InstName");}
    MEM_LOOP(vb,Var_B,cc->var_fp)
      if (var_ctl->store(vb->var_name->c_str(),vb->init_value->c_str()) == NULL){ErrMsg(MSG12,vb->var_name->c_str());}
    LOOP_END

    // ListCall Clear
    MEM_LOOP(lc,ListCall_T,listcall_fp)
      delete lc;
    LOOP_END
    listcall_fp->mem_del_all();

    // Classcall Program Execute(recurcive call)
    if (ob != (Object_T *)MM_NULL){ProgramExec(cc->prg_fp);}
    else {
      if (*(cc->class_name->c_str()) == 0x00){ProgramExec(cc->prg_fp);}
    }

    // Work Variable Level Delete
    if (ob != (Object_T *)MM_NULL){WorkVarLvlDel(); WorkVarLvlDel();}

  LOOP_END
  WorkVarLvlDel(); 
}

// ------------------------
// Object Build(recursive)
// ------------------------
void ExecCtlInf_T::ObjectBuild(Class_T *cl){
  Var_B      *vb;
  List_B     *lb;
  sChar      *str;
  Class_T    *w_cl;
  Program_B  *prg;

  ob->ov_mode = false;
  // Variable Build
  MEM_LOOP(vb,Var_B,cl->var_fp)
    ob->VarStore(vb->var_name->c_str(),vb->init_value->c_str());
  LOOP_END
  
  // List Build
  MEM_LOOP(lb,List_B,cl->list_fp)
    ob->ListStore(lb);
    MEM_LOOP(vb,Var_B,lb->idx_fp)
      ob->VarStore(vb->var_name->c_str(),vb->init_value->c_str());
      ob->ListIdxStore((VarCell_T *)ob->var_fp->mem_link_ptr_rd());
    LOOP_END
    MEM_LOOP(vb,Var_B,lb->var_fp)
      ob->VarStore(vb->var_name->c_str(),vb->init_value->c_str());
      ob->ListVarStore((VarCell_T *)ob->var_fp->mem_link_ptr_rd());
    LOOP_END
  LOOP_END
  
  // Program Build
  MEM_LOOP(prg,Program_B,cl->prg_fp)
    ob->PrgStore(prg);
  LOOP_END
  
  // Class inherit Recurcive
  MEM_LOOP(str,sChar,cl->class_fp)
    it->srch_key = str->c_str();
    if (class_fp->mem_srch() != 0){ErrMsg(MSG13,str->c_str());}
    else {
      w_cl = (Class_T *)class_fp->mem_link_ptr_rd();
      ObjectBuild(w_cl);
    }
  LOOP_END
}


// ---------------------------
// command select
// ---------------------------
unsigned int ExecCtlInf_T::commandSel(char *str){
  unsigned int kind = 0;

  if (strcmp(str,"%classset") == 0){kind = 1;}
  else if (strcmp(str,"%do") == 0){kind = 2;}
  else if (strcmp(str,"%casearg") == 0){kind = 3;}
  else if (strcmp(str,"%casedo") == 0){kind = 4;}
  else if (strcmp(str,"%casedoall") == 0){kind = 5;}
  else if (strcmp(str,"%set") == 0){kind = 6;}
  else if (strcmp(str,"%calc") == 0){kind = 7;}
  else if (strcmp(str,"%calcfrm") == 0){kind = 8;}
  else if (strcmp(str,"%calc_f") == 0){kind = 9;}
  else if (strcmp(str,"%calcfrm_f") == 0){kind = 10;}
  else if (strcmp(str,"%calc64") == 0){kind = 11;}
  else if (strcmp(str,"%calcfrm64") == 0){kind = 12;}
  else if (strcmp(str,"%if") == 0){kind = 13;}
  else if (strcmp(str,"%noif") == 0){kind = 14;}
  else if (strcmp(str,"%wif") == 0){kind = 15;}
  else if (strcmp(str,"%wnoif") == 0){kind = 16;}
  else if (strcmp(str,"%calcif") == 0){kind = 17;}
  else if (strcmp(str,"%calcnoif") == 0){kind = 18;}
  else if (strcmp(str,"%calcif_f") == 0){kind = 19;}
  else if (strcmp(str,"%calcnoif_f") == 0){kind = 20;}
  else if (strcmp(str,"%calcif64") == 0){kind = 21;}
  else if (strcmp(str,"%calcnoif64") == 0){kind = 22;}
  else if (strcmp(str,"%endif") == 0){kind = 23;}
  else if (strcmp(str,"%printf") == 0){kind = 24;}
  else if (strcmp(str,"%return") == 0){kind = 25;}
  else if (strcmp(str,"%break") == 0){kind = 26;}
  else if (strcmp(str,"%continue") == 0){kind = 27;}
  else if (strcmp(str,"%listfor") == 0){kind = 28;}
  else if (strcmp(str,"%for") == 0){kind = 29;}
  else if (strcmp(str,"%aryfor") == 0){kind = 30;}
  else if (strcmp(str,"%listset") == 0){kind = 31;}
  else if (strcmp(str,"%listhead") == 0){kind = 32;}
  else if (strcmp(str,"%arywr") == 0){kind = 33;}
  else if (strcmp(str,"%aryrd") == 0){kind = 34;}
  else if (strcmp(str,"%arydel") == 0){kind = 35;}
  else if (strcmp(str,"%arydelall") == 0){kind = 36;}
  else if (strcmp(str,"%arycopy") == 0){kind = 37;}
  else if (strcmp(str,"%arysep") == 0){kind = 38;}
  else if (strcmp(str,"%arysepchk") == 0){kind = 39;}
  else if (strcmp(str,"%arysepfix") == 0){kind = 40;}
  else if (strcmp(str,"%envrd") == 0){kind = 41;}
  else if (strcmp(str,"%envwr") == 0){kind = 42;}
  else if (strcmp(str,"%separate") == 0){kind = 43;}
  else if (strcmp(str,"%separateex") == 0){kind = 44;}
  else if (strcmp(str,"%textfor") == 0){kind = 45;}
  else if (strcmp(str,"%macro") == 0){kind = 46;}
  else if (strcmp(str,"%call") == 0){kind = 47;}
  else if (strcmp(str,"%debug") == 0){kind = 48;}
  else if (strcmp(str,"%debugoff") == 0){kind = 49;}
  else if (strcmp(str,"%ary_save") == 0){kind = 50;}  // Ver 1.60
  else if (strcmp(str,"%csv_set") == 0){kind = 51;}   // Ver 1.61
  else if (strcmp(str,"%ary_load") == 0){kind = 52;}  // Ver 1.60
  else if (strcmp(str,"%url_anl") == 0){kind = 53;}   // Ver 1.62
  else if (strcmp(str,"%dbswrite") == 0){kind = 54;}
  else if (strcmp(str,"%dbsdel") == 0){kind = 55;}
  else if (strcmp(str,"%alias") == 0){kind = 56;}
  else if (strcmp(str,"%beta") == 0){kind = 57;}
  else if (strcmp(str,"%sjis_utf8") == 0){kind = 58;}
  else if (strcmp(str,"%utf8_sjis") == 0){kind = 59;}
  else if (strcmp(str,"%ob_new") == 0){kind = 60;}
  else if (strcmp(str,"%ob_del") == 0){kind = 61;}
  else if (strcmp(str,"%ob_get") == 0){kind = 62;}
  else if (strcmp(str,"%ob_set") == 0){kind = 63;}
  else if (strcmp(str,"%ob_do") == 0){kind = 64;}
  else if (strcmp(str,"%sp_push") == 0){kind = 65;}
  else if (strcmp(str,"%chg_once") == 0){kind = 66;}
  else if (strcmp(str,"%chg_all") == 0){kind = 67;}
  else if (strcmp(str,"%find") == 0){kind = 68;}
  else if (strcmp(str,"%timenow") == 0){kind = 69;}
  else if (strcmp(str,"%today") == 0){kind = 70;}
  else if (strcmp(str,"%binary") == 0){kind = 71;}
  else if (strcmp(str,"%timeint") == 0){kind = 72;}
  else if (strcmp(str,"%dateint") == 0){kind = 73;}
  else if (strcmp(str,"%inttime") == 0){kind = 74;}
  else if (strcmp(str,"%intdate") == 0){kind = 75;}
  else if (strcmp(str,"%fopen") == 0){kind = 76;}
  else if (strcmp(str,"%fclose") == 0){kind = 77;}
  else if (strcmp(str,"%fprintf") == 0){kind = 78;}
  else if (strcmp(str,"%fcsvwrite") == 0){kind = 79;}
  else if (strcmp(str,"%fsp+") == 0){kind = 80;}
  else if (strcmp(str,"%fsp-") == 0){kind = 81;}
  else if (strcmp(str,"%fsp") == 0){kind = 82;}
  else if (strcmp(str,"%fspcnt") == 0){kind = 83;}
  else if (strcmp(str,"%fileexist") == 0){kind = 84;}
  else if (strcmp(str,"%exec") == 0){kind = 85;}
  else if (strcmp(str,"%file_get") == 0){kind = 86;}
  else if (strcmp(str,"%shell") == 0){kind = 87;}
  else if (strcmp(str,"%st_default") == 0){kind = 88;}
  else if (strcmp(str,"%rand") == 0){kind = 89;}
  else if (strcmp(str,"%seed") == 0){kind = 90;}
  else if (strcmp(str,"%argsep") == 0){kind = 91;}
  else if (strcmp(str,"%argsepchk") == 0){kind = 92;}
  else if (strcmp(str,"%argsepfix") == 0){kind = 93;}
  else if (strcmp(str,"%argdef") == 0){kind = 94;}
  else if (strcmp(str,"%argdefchk") == 0){kind = 95;}
  else if (strcmp(str,"%argdeffix") == 0){kind = 96;}
  else if (strcmp(str,"%argpart") == 0){kind = 97;}
  else if (strcmp(str,"%argpartfix") == 0){kind = 98;}
  else if (strcmp(str,"%strsep") == 0){kind = 99;}
  else if (strcmp(str,"%chgcode") == 0){kind = 100;}
  else if (strcmp(str,"%else") == 0){kind = 101;}
  else if (strcmp(str,"%endfor") == 0){kind = 102;}
  else if (strcmp(str,"%file_anl") == 0){kind = 103;}
  else if (strcmp(str,"%set_bit") == 0){kind = 104;}
  else if (strcmp(str,"%rtn_mode") == 0){kind = 105;}
  else if (strcmp(str,"%shell_begin") == 0){kind = 106;}  // Ver 1.66
  else if (strcmp(str,"%shell_end") == 0){kind = 107;}    // Ver 1.66
  else if (strcmp(str,"%need_bit") == 0){kind = 108;}   // Ver 1.69
  else if (strcmp(str,"%class_save") == 0){kind = 109;}   // Ver 1.72
  else if (strcmp(str,"%class_load") == 0){kind = 110;}   // Ver 1.72

  else if (strcmp(str,"%else_if"        )==0){kind = 101;}
  else if (strcmp(str,"%else_noif"      )==0){kind = 101;}
  else if (strcmp(str,"%else_wif"       )==0){kind = 101;}
  else if (strcmp(str,"%else_nowif"     )==0){kind = 101;}
  else if (strcmp(str,"%else_calcif"    )==0){kind = 101;}
  else if (strcmp(str,"%else_calcnoif"  )==0){kind = 101;}
  else if (strcmp(str,"%else_calcif_f"  )==0){kind = 101;}
  else if (strcmp(str,"%else_calcnoif_f")==0){kind = 101;}
  else if (strcmp(str,"%else_calcif64"  )==0){kind = 101;}
  else if (strcmp(str,"%else_calcnoif64")==0){kind = 101;}

  else if (strcmp(str,"%include_macro")==0){kind = 999;}  // Ver 1.76
  else if (strcmp(str,"%csvmake")==0){kind = 999;}
  else if (strcmp(str,"%csvmake_tmp")==0){kind = 999;}
  else if (strcmp(str,"%csvmake_sel")==0){kind = 999;}
  else if (strcmp(str,"%csvmake_nosel")==0){kind = 999;}
  else if (strcmp(str,"%csvmake_selclr")==0){kind = 999;}


  return(kind);
}

// ---------------------------
// Program Execute(recursive)
// ---------------------------
void ExecCtlInf_T::ProgramExec(MEM_FP *prg_fp){
  Program_C *pc;
  char *str;
  IfLvlCell_T  *il;
  ForLvlCell_T *fl;
  McbArea_C     *w_ptr;
  Alias_T *als;
  VariableArea_C *w_cmd = new  VariableArea_C(10);   // Ver 1.68

  int    sv_sel_su = 0;     // Program Sel Su
  char **sv_sel    =NULL;   // Program Sel

  //if,for level add
  il = new IfLvlCell_T (it); it->alloc_ptr = (unsigned char *)il; if_fp->mem_alloc ();
  fl = new ForLvlCell_T(it); it->alloc_ptr = (unsigned char *)fl; for_fp->mem_alloc();

  bool breakFlag=false;

  // Program Main
  MEM_LOOP(pc,Program_C,prg_fp)
	if (breakFlag) {break;}
	SelGetReset(pc);
	if ((str = SelGet()) == NULL) {continue;}

	// vvvvvv  Ver 1.68
    bool command_change_flag = false;
	if (pc->command == 0)  {
	  StrChg(w_cmd,str,'$');
	  if (strcmp(w_cmd->c_str(),str) != 0) {
		command_change_flag = true;
        pc->alias_addr = NULL;
 
        // save sel
        sv_sel_su = pc->sel_su;
        sv_sel    = new char *[sv_sel_su];
        for(int i=0;i<sv_sel_su;i++){
          st_ini(*(sv_sel+i),*(pc->sel+i));
        }
	  }
  	  str = w_cmd->c_str();

//	  printf("str=%s pc->command_change_flag=%d\n",str,command_change_flag);
	}


	// ^^^^    Ver 1.68

	Application->ProcessMessages();  // Ver 1.28

	if ((pc->alias_num == alias_num) && (pc->alias_addr != NULL)){ // alias search
	  alias_fp->mem_mcb_ptr_wr(pc->alias_addr);
	}

	it->srch_key = str;
	pc->alias_addr = NULL;
	if (alias_fp->mem_srch() == 0){
	  pc->alias_addr = alias_fp->mem_mcb_ptr_rd();
	  pc->alias_num  = alias_num;
	  als = (Alias_T *)alias_fp->mem_link_ptr_rd();
	  als->Replace(pc);
	  SelGetReset(pc);
	  str = SelGet();
	}

	if (str == NULL){continue;}
	if ((debug_mode == true) && (strcmp(debug_string->c_str(),"Trace")==0)) {printf("[%p][%s]\n",prg_fp->mem_mcb_ptr_rd(),str);}


	g_w0->set(0,0x00);
	g_w1->set(0,0x00);
    g_w2->set(0,0x00);
    g_w3->set(0,0x00);
    g_w4->set(0,0x00);
    g_w5->set(0,0x00);
    g_w6->set(0,0x00);

    if (pc->command == 0){
      pc->command = commandSel(str);
    }

//printf("[%p][%s][%d]\n",prg_fp->mem_mcb_ptr_rd(),str,pc->command);

    msg_cmd->set(str);  // message command

    switch (pc->command) {
      case 999 : printf("csvfront command = %s\n",str); break;                              // csvfront command
	  case 1: classset_rtn(pc,prg_fp);       break;  // %classset
      case 2: do_rtn      (pc,prg_fp);       break;  // %do
      case 3: casearg_rtn (pc,prg_fp);       break;  // %casearg
      case 4: casedo_rtn  (pc,prg_fp,false); break;  // %casedo
      case 5: casedo_rtn  (pc,prg_fp,true ); break;  // %casedoall
      case 6: set_rtn     (pc,prg_fp);       break;  // %set
      case 7: calc_rtn    (pc,prg_fp,true ); break;  // %calc
      case 8: calc_rtn    (pc,prg_fp,false); break;  // %calcfrm
      case 9: calc_f_rtn  (pc,prg_fp,true ); break;   // %calc_f
      case 10: calc_f_rtn  (pc,prg_fp,false); break;   // %calcfrm_f
      case 11: calc64_rtn  (pc,prg_fp,true ); break;   // %calc64
      case 12: calc64_rtn  (pc,prg_fp,false); break;   // %calcfrm64
      case 13: if_rtn      (pc,prg_fp,true ); break;  // %if
      case 14: if_rtn      (pc,prg_fp,false); break;  // %noif
      case 15: wif_rtn     (pc,prg_fp,true ); break;  // %wif
      case 16: wif_rtn     (pc,prg_fp,false); break;  // %wnoif
      case 17: calcif_rtn  (pc,prg_fp,true ); break;  // %calcif
      case 18: calcif_rtn  (pc,prg_fp,false); break;  // %calcnoif
      case 19: calcif_f_rtn  (pc,prg_fp,true ); break;   // %calcif_f
      case 20: calcif_f_rtn  (pc,prg_fp,false); break;   // %calcnoif_f
      case 21: calcif64_rtn  (pc,prg_fp,true ); break;   // %calcif64
      case 22: calcif64_rtn  (pc,prg_fp,false); break;   // %calcnoif64
      case 23:                                break;  // %endif
      case 24: printf_rtn  (pc       );       break;  // %printf
      case 25: breakFlag=true;                break;    // %return
      case 26: break_rtn   (pc,prg_fp);       break;  // %break
      case 27: continue_rtn(pc,prg_fp);       break;  // %continue
      case 28: listfor_rtn (pc,prg_fp);       break;  // %listfor
      case 29: for_rtn     (pc,prg_fp);       break;  // %for
      case 30: aryfor_rtn  (pc,prg_fp);       break;  // %aryfor
      case 31: listset_rtn (pc,prg_fp);       break;  // %listset
      case 32: listhead_rtn(pc,prg_fp);       break;  // %listhead
      case 33: ary_rtn     (pc,prg_fp,0);     break;  // %arywr
      case 34: ary_rtn     (pc,prg_fp,1);     break;  // %aryrd
      case 35: ary_rtn     (pc,prg_fp,2);     break;  // %arydel
      case 36: ary_rtn     (pc,prg_fp,3);     break;  // %arydelall
      case 37: ary_rtn     (pc,prg_fp,4);     break;  // %arycopy
      case 38: arysep_rtn  (pc,prg_fp,true ,false); break;  // %arysep
      case 39: arysep_rtn  (pc,prg_fp,true ,true ); break;  // %arysepchk
      case 40: arysep_rtn  (pc,prg_fp,false,false); break;  // %arysepfix
      case 41: env_rtn     (pc,prg_fp,0);     break;  // %envrd
      case 42: env_rtn     (pc,prg_fp,1);     break;  // %envwr
      case 43: sepa_rtn    (pc,prg_fp,false); break;  // %separate
      case 44: sepa_rtn    (pc,prg_fp,true);  break;  // %separateex
      case 45: textfor_rtn (pc,prg_fp);       break;  // %textfor
      case 46: macro_rtn   (pc,prg_fp);       break;  // %macro
      case 47: call_rtn    (pc,prg_fp);       break;  // %call
      case 48: debug_rtn   (pc,true);         break;  // %debug
      case 49: debug_rtn   (pc,false);        break;  // %debugoff
      case 50: ary_save_rtn(pc,prg_fp);       break;  // %ary_save  // Ver 1.60
      case 51: csv_set_rtn (pc,prg_fp);       break;  // %csv_set   // Ver 1.61
      case 52: ary_load_rtn(pc,prg_fp);       break;  // %ary_load  // Ver 1.60
      case 53: url_anl_rtn (pc,prg_fp);       break;  // %url_anl   // Ver 1.62
      case 54: dbswrite_rtn(pc,prg_fp);       break;  // %dbswrite
      case 55: dbsdel_rtn  (pc,prg_fp);       break;  // %dbsdel
      case 56: alias_rtn   (pc,prg_fp);       break;  // %alias
      case 57: beta_rtn    (pc,prg_fp);       break;  // %beta
      case 58: sjis_utf8_rtn(pc,prg_fp,true); break;   // %sjis_utf8
      case 59: sjis_utf8_rtn(pc,prg_fp,false); break;   // %utf8_sjis
      case 60: ob_new_rtn   (pc,prg_fp); break;   // %ob_new
      case 61: ob_del_rtn   (pc,prg_fp); break;   // %ob_del
      case 62: ob_get_rtn   (pc,prg_fp); break;   // %ob_get
      case 63: ob_set_rtn   (pc,prg_fp); break;   // %ob_set
      case 64: ob_do_rtn    (pc,prg_fp); break;   // %ob_do
      case 65: sp_push_rtn (pc,prg_fp);       break;  // %sp_push
      case 66: chg_once_rtn(pc,prg_fp);       break;  // %chg_once
      case 67: chg_all_rtn (pc,prg_fp);       break;  // %chg_all
      case 68: find_rtn    (pc,prg_fp);       break;  // %find
      case 69: timenow_rtn (pc,prg_fp);       break;  // %timenow
      case 70: today_rtn   (pc,prg_fp);       break;  // %today
      case 71: binary_rtn  (pc,prg_fp);       break;  // %binary
      case 72: dateint_rtn (pc,prg_fp,false); break;  // %timeint
      case 73: dateint_rtn (pc,prg_fp,true);  break;  // %dateint
      case 74: intdate_rtn (pc,prg_fp,false); break;  // %inttime
      case 75: intdate_rtn (pc,prg_fp,true);  break;  // %intdate
      case 76: fopen_rtn   (pc,prg_fp);       break;  // %fopen
      case 77: fclose_rtn  (pc,prg_fp);       break;  // %fclose
      case 78: fprintf_rtn (pc,prg_fp);       break;  // %fprintf
      case 79: fcsvwrite_rtn(pc,prg_fp);      break;  // %fcsvwrite
      case 80: fspp_rtn    (pc,prg_fp);       break;  // %fsp+
      case 81: fspm_rtn    (pc,prg_fp);       break;  // %fsp-
      case 82: fsp_rtn     (pc,prg_fp);       break;  // %fsp
      case 83: fspcnt_rtn  (pc,prg_fp);       break;  // %fspcnt
      case 84: fileexist_rtn(pc,prg_fp);      break;  // %fileexist
      case 85: exec_rtn    (pc,prg_fp);       break;  // %exec
      case 86: fileget_rtn (pc,prg_fp);       break;  // %file_get
      case 87: shell_rtn   (pc,prg_fp);       break;  // %shell
      case 88: st_default_rtn(pc,prg_fp);   break;  // %st_default
      case 89: rand_rtn    (pc,prg_fp);       break;  // %rand
      case 90: seed_rtn    (pc,prg_fp);       break;  // %seed
      case 91: argsep_rtn (pc,prg_fp,true ,false); break;  // %argsep
      case 92: argsep_rtn (pc,prg_fp,true ,true ); break;  // %argsepchk
      case 93: argsep_rtn (pc,prg_fp,false,false); break;  // %argsepfix
      case 94: argdef_rtn (pc,prg_fp,true ,false); break;  // %argdef
      case 95: argdef_rtn (pc,prg_fp,true ,true ); break;  // %argdefchk
      case 96: argdef_rtn (pc,prg_fp,false,false); break;  // %argdeffix
	  case 97: argpart_rtn(pc,prg_fp,false); break;   // %argpart
	  case 98: argpart_rtn(pc,prg_fp,true ); break;   // %argpartfix
	  case 99: strsep_rtn (pc,prg_fp      ); break;   // %strsep
	  case 100: chgcode_rtn(pc,prg_fp     ); break;   // %chgcode
	  case 103: file_anl_rtn(pc,prg_fp    ); break;   // %file_anl
	  case 104: set_bit_rtn(pc,prg_fp     ); break;   // %set_bit
	  case 105: rtn_mode_rtn(pc,prg_fp    ); break;   // %rtn_mode
	  case 106: shell_begin_rtn(pc,prg_fp ); break;   // %shell_begin
	  case 107: shell_end_rtn  (pc,prg_fp ); break;   // %shell_end
	  case 108: need_bit_rtn   (pc,prg_fp ); break;   // %need_bit
	  case 109: class_save_rtn (pc,prg_fp ); break;   // %class_save
	  case 110: class_load_rtn (pc,prg_fp ); break;   // %class_load
	  case 101:                                       // %else
        if ((w_ptr = (McbArea_C *)il->FromToSrch(prg_fp->mem_mcb_ptr_rd())) != MM_NULL){prg_fp->mem_mcb_ptr_wr(w_ptr);}
        break;
      case 102:                                       // %endfor
        if ((w_ptr = (McbArea_C *)fl->ListForSrch(prg_fp->mem_mcb_ptr_rd())) != MM_NULL){prg_fp->mem_mcb_ptr_wr(w_ptr);}
        break;
      default:
        sel_write_rtn(pc);
	  }
      // Ver 1.68
	  if (command_change_flag){
        // save fukki
        for(int i=0;i<pc->sel_su;i++){
          st_del(*(pc->sel+i));
        }
        delete [] pc->sel;

        pc->sel_su = sv_sel_su;
        pc->sel    = new char *[pc->sel_su];

        for(int i=0;i<pc->sel_su;i++){
          st_ini(*(pc->sel+i),*(sv_sel+i));
        }

        for(int i=0;i<sv_sel_su;i++){
          st_del(*(sv_sel+i));
        }
        delete [] sv_sel;
        sv_sel = NULL;
        sv_sel_su = 0;

        pc->command = 0;
      }
  LOOP_END

  // if,for level del
  if_fp ->mem_mcb_end_set(); il = (IfLvlCell_T  *)if_fp->mem_link_ptr_rd (); delete il; if_fp->mem_del ();
  for_fp->mem_mcb_end_set(); fl = (ForLvlCell_T *)for_fp->mem_link_ptr_rd(); delete fl; for_fp->mem_del();

  delete w_cmd;  // Ver 1.68

}

// ----------------
// %classset 
// ----------------
void ExecCtlInf_T::classset_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  Object_T   *src_ob;
  VarCell_T  *vc;
  AryCell_T  *ac;
  ListCell_T *lc;
  Program_B  *prg;

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG14); return;}
    
  StrChg(g_w0,p_str,'$');
  it->srch_key = g_w0->c_str();
  if (object_fp->mem_srch() != 0){ErrMsg(MSG15,g_w0->cc_str()); return;}
  src_ob = (Object_T *)object_fp->mem_link_ptr_rd();
  
  ob->ov_mode = true;
  // Variable Copy
  MEM_LOOP(vc,VarCell_T,src_ob->var_fp)
    ob->VarStore(vc->name->c_str(),vc->atai->c_str());
    MEM_LOOP(ac,AryCell_T,vc->ary_fp)
      ob->VarAryStore(ac->name->c_str(),ac->atai->c_str());
    LOOP_END
  LOOP_END
  
  // List Copy
  MEM_LOOP(lc,ListCell_T,src_ob->list_fp)
    ob->ListStore(lc->lb);
    MEM_LOOP(vc,VarCell_T,lc->idx_fp)
      ob->ListIdxStore(vc);
    LOOP_END
    MEM_LOOP(vc,VarCell_T,lc->var_fp)
      ob->ListVarStore(vc);
    LOOP_END
  LOOP_END
  
  // Macro Copy
  MEM_LOOP(prg,Program_B,src_ob->pg_fp)
    ob->PrgStore(prg);
  LOOP_END
}

// ----------------
// %do
// ----------------
void ExecCtlInf_T::do_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  Program_B  *prg;
//  WorkCell_T *wc;
  Var_B      *vb;
  McbArea_C   *sv_ptr;
  VarCell_T  *vc;
  int         i;
  sChar      *sv_macro;
  int         sv_cur_clm;

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG03); return;}
  StrChg(g_w0,p_str,'$');
  it->srch_key = g_w0->c_str();

  if (ob->pg_fp->mem_srch() != 0){ErrMsg(MSG04,g_w0->cc_str()); return;}
  prg = (Program_B *)ob->pg_fp->mem_link_ptr_rd();
  sv_macro = new sChar(msg_macro->c_str());
  msg_macro->set(prg->prg_name->c_str()); // message macro

  // Macro Local Variable -> Work Variable
  WorkVarLvlAdd();
  MEM_LOOP(vb,Var_B,prg->var_fp)
    var_ctl->store(vb->var_name->c_str(),vb->init_value->c_str());
  LOOP_END


  // argv,argc generation
  var_ctl->store("_MacroName",prg->prg_name->c_str());
  vc = var_ctl->store("argv","0");

  var_ctl->offset = 1;
  for(i=0;;i++){
    char *w = SelGet_direct();
    if (w == NULL) {break;}
    g_w0->int_set(i);
    StrChg(g_w1,w,'$');
    vc->AryStore(g_w0->c_str(),g_w1->c_str());
  }
  var_ctl->offset = 0;


  g_w0->int_set(i);
  var_ctl->store("argc",g_w0->cc_str());

  // Macro Program Exec
  sv_ptr = (McbArea_C *)prg_fp->mem_mcb_ptr_rd();
  ProgramExec(prg->prg_fp);
  prg_fp->mem_mcb_ptr_wr(sv_ptr);

  // message pop
  msg_macro->set(sv_macro->c_str());
  delete sv_macro;

  // Work Variable Level Delete
  WorkVarLvlDel();
  }

// ----------------
// %casearg
// ----------------
void ExecCtlInf_T::casearg_rtn(Program_C *pc,MEM_FP *prg_fp){
  int    sv_cur_clm;
  char  *p_str;
  CaseDo_T    *casedo_inf;

  if (!casedo_use){
    casedo_use = true;
    casedo_inf = new CaseDo_T(it);
    it->alloc_ptr = (unsigned char *)casedo_inf;
    casedo_fp->mem_alloc();
  } else {
    casedo_fp->mem_mcb_end_set();
    casedo_inf = (CaseDo_T *)casedo_fp->mem_link_ptr_rd();
  }
  casedo_inf->patSetTop();
  for(;;){
    char *w = SelGet_direct();
    if (w == NULL) {break;}
    StrChg(g_w1,w,'$');
    casedo_inf->patSet(g_w1->c_str());
  }
}

// ----------------
// %casedo
// ----------------
void ExecCtlInf_T::casedo_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn)
  {
  Program_C *w_pc;
  Read64_C *in_fp;
  CaseDo_T *casedo_inf;

  if (!casedo_use){return;}

  casedo_fp->mem_mcb_end_set();
  casedo_inf = (CaseDo_T *)casedo_fp->mem_link_ptr_rd();
  casedo_use = false;
  casedo_inf->preExec(kbn);
  in_fp = new Read64_C(casedo_inf->fileNameGet(),"csv",1024);
  CsvAnl_C *csvi = new CsvAnl_C;
  for(;;){
    char *buff = in_fp->read();
    if (buff == NULL){break;}
    csvi->Exec(buff);
    w_pc = new Program_C(csvi->CsvSelSu_Rd(),csvi->getBody());
    prog_anl->put(w_pc);
    do_rtn(w_pc,prg_fp);
    delete w_pc;
  }
  delete csvi;
  delete in_fp;
  casedo_inf->postExec();

  delete casedo_inf;
  casedo_fp->mem_mcb_end_set();
  casedo_fp->mem_del();
  }


// ----------------
// %set
// ----------------
void ExecCtlInf_T::set_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  StrSrchInf_T *ssc;
  VarCell_T  *vc;
  char       *w;
  int         up,dn,sv,len,max;
  bool        ex,err;

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}
  StrChg(g_w0,p_str,'$');
  if ((p_str = SelGet()) == NULL){g_w1->set(0,0x00);      len = 0x00;        g_w3->set_string("0");}
  else                           {StrChg(g_w1,p_str,'$'); len = g_w1->len(); g_w3->int_set(len-1);}

  s_token->set(g_w0->c_str());
  max = s_token->getNum();

  up = 0;
  dn = len-1;
  err = false;
  for(;;){
    w = s_token->get(0);
    vc = var_ctl->srch(w);
    if (vc==NULL) {
      vc = var_ctl->store(w,"0");
    }

    if (max == 1){
      if (len == 0x00){vc->atai->set("");}
      else            {vc->atai->set(g_w1->cc_str());}
      return;
    }
    w = s_token->get(1);
    if (strcmp(w,"[") != 0){err = true; break;}
    w = s_token->get(2);
    grep->set(w);
    grep->replace_all("@",g_w3->c_str());
    up = ci->CalcExecute(grep->c_str());
    w = s_token->get(3);
    if (strcmp(w,"]") == 0){dn = up; break;}
    if (strcmp(w,":") != 0){err = true; break;}
    w = s_token->get(4);
    grep->set(w);
    grep->replace_all("@",g_w3->c_str());
    dn = ci->CalcExecute(grep->c_str());
    w = s_token->get(5);
    if (strcmp(w,"]") != 0){err = true; break;}
    break;
  }
  if (err == true){ErrMsg(MSG02,g_w0->cc_str()); return;}

  if (up>dn){ex = true; sv=up; up=dn; dn=sv;}
  else      {ex = false;}

  str_ext->set(vc->atai->c_str());
  str_ext->set_index(g_w1->c_str(),up,dn-up+1,ex);
  vc->atai->set(str_ext->c_str());
}


// ----------------
// %envrd/%envwr
// ----------------
void ExecCtlInf_T::env_rtn(Program_C *pc,MEM_FP *prg_fp,int kbn){
  char       *p_str;
  VarCell_T  *vc;
  char       *env;

//  str  = g_w0;
//  atai = g_w1;

  if (kbn == 0) {// %envrd
    if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}
    StrChg(g_w0,p_str,'$');
    if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    if ((p_str = SelGet()) == NULL){vc->atai->set(""); return;}
    StrChg(g_w0,p_str,'$');
    //env = getenv(str);
    env = x_getenv(g_w0->c_str());
    if (env == NULL){vc->atai->set(""); return;}
    vc->atai->set(env);
    return;
  }  
    
  // %envwr
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG16); return;}
  StrChg(g_w0,p_str,'$');

  if ((p_str = SelGet()) == NULL){g_w1->set(0,0x00);}
  else                             {StrChg(g_w1,p_str,'$');}
  g_w2->set_string(g_w0->c_str());
  g_w2->cat_string("=");
  g_w2->cat_string(g_w1->c_str());
  putenv(g_w2->cc_str());
}


// -----------------
// %debug/%debugoff
// -----------------
void ExecCtlInf_T::debug_rtn(Program_C *pc,bool kbn){
  char       *p_str;

  debug_mode = kbn;
  if (debug_mode == false){return;}
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}
  StrChg(g_w0,p_str,'$');
  debug_string->set(g_w0->cc_str());
}


// ----------------
// %calc/%calcfrm
// ----------------
void ExecCtlInf_T::calc_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn){
  char       *p_str;
  VarCell_T  *vc;
//  sChar       *siki;  g_w2
//  str  = g_w0;
//  str2 = g_w1;
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}

  StrChg(g_w0,p_str,'$');
  if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}

  if (kbn == true){g_w2->set_string("%d");}
  else{
    if ((p_str = SelGet()) == NULL){ErrMsg(MSG17); return;}
    StrChg(g_w0,p_str,'$');
    g_w2->set_string(g_w0->cc_str());
  }

  if ((p_str = SelGet()) == NULL){vc->atai->set("");}
  else {
    StrChg(g_w0,p_str,'$');
    char *buff = (char *)g_w1->check(strlen(g_w2->cc_str())+30);
    sprintf(buff,g_w2->cc_str(),ci->CalcExecute(g_w0->c_str()));
    vc->atai->set(buff);
  }
//  delete siki;
}


// -------------------
// %calc_f/%calcfrm_f
// Ver 1.31
// -------------------
void ExecCtlInf_T::calc_f_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn){
  char       *p_str;
  VarCell_T  *vc;
  sChar       *siki;

//  str  = g_w0;
//  str2 = g_w1;
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}

  StrChg(g_w0,p_str,'$');
  if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}

  if (kbn == true){siki = new sChar("%f");}
  else {
    if ((p_str = SelGet()) == NULL){ErrMsg(MSG17); return;}
    StrChg(g_w0,p_str,'$');
    siki = new sChar(g_w0->cc_str());
  }

  if ((p_str = SelGet()) == NULL){vc->atai->set("");}
  else {
    StrChg(g_w0,p_str,'$');
    char *buff = (char *)g_w1->check(strlen(siki->c_str())+30);
    sprintf(buff,siki->c_str(),ci_f->CalcExecute(g_w0->c_str()));
    vc->atai->set(buff);
  }
  delete siki;
}

// -------------------
// %calc64/%calcfrm64
// Ver 1.30
// -------------------
void ExecCtlInf_T::calc64_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn){
  char       *p_str;
  VarCell_T  *vc;
  sChar       *siki;

//  str  = g_w0;
//  str2 = g_w1;
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}

  StrChg(g_w0,p_str,'$');
  if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}

  if (kbn == true){siki = new sChar("%I64d");}
  else{
    if ((p_str = SelGet()) == NULL){ErrMsg(MSG17); return;}
    StrChg(g_w0,p_str,'$');
    siki = new sChar(g_w0->cc_str());
  }

  if ((p_str = SelGet()) == NULL){vc->atai->set("");}
  else {
    StrChg(g_w0,p_str,'$');
    char *buff = (char *)g_w1->check(strlen(siki->c_str())+30);
    sprintf(buff,siki->c_str(),ci64->CalcExecute(g_w0->c_str()));
    vc->atai->set(buff);
  }
  delete siki;
}




// ----------------
// %if
// ----------------
void ExecCtlInf_T::if_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn){
  bool equal_flg = if_check_rtn(prg_fp,kbn,0);
  if (pc->if_jump == NULL){if_core_rtn (prg_fp,equal_flg,pc);}
  else                    {if_cache_rtn(prg_fp,equal_flg,pc->if_jump);}
}

// ----------------
// %wif
// ----------------
void ExecCtlInf_T::wif_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn){
  bool equal_flg = if_check_rtn(prg_fp,kbn,1);
  if (pc->if_jump == NULL){if_core_rtn (prg_fp,equal_flg,pc);}
  else                    {if_cache_rtn(prg_fp,equal_flg,pc->if_jump);}
}

// ----------------
// %calcif
// ----------------
void ExecCtlInf_T::calcif_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn){
  bool equal_flg = if_check_rtn(prg_fp,kbn,2);
  if (pc->if_jump == NULL){if_core_rtn (prg_fp,equal_flg,pc);}
  else                    {if_cache_rtn(prg_fp,equal_flg,pc->if_jump);}
}

// ----------------
// %calcif_f
// ----------------
void ExecCtlInf_T::calcif_f_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn){
  bool equal_flg = if_check_rtn(prg_fp,kbn,3);
  if (pc->if_jump == NULL){if_core_rtn (prg_fp,equal_flg,pc);}
  else                    {if_cache_rtn(prg_fp,equal_flg,pc->if_jump);}
}

// ----------------
// %calcif64
// ----------------
void ExecCtlInf_T::calcif64_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn){
  bool equal_flg = if_check_rtn(prg_fp,kbn,4);
  if (pc->if_jump == NULL){if_core_rtn (prg_fp,equal_flg,pc);}
  else                    {if_cache_rtn(prg_fp,equal_flg,pc->if_jump);}
}


// -----------------------
// %if/%wif/%calcif check
// -----------------------
bool ExecCtlInf_T::if_check_rtn(MEM_FP *prg_fp,bool kbn,int kind){
  bool equal_flg=false;
  WildCard_T wcc;
  char *p_str;

  if ((p_str = SelGet()) == NULL){
    if      (kind == 0){ErrMsg(MSG01);} 
    else if (kind == 1){ErrMsg(MSG01);} 
    else if (kind == 2){ErrMsg(MSG19);} 
    else if (kind == 3){ErrMsg(MSG19);} 
    else if (kind == 4){ErrMsg(MSG19);} 
    return(false);
  }
  StrChg(g_w0,p_str,'$');

  if ((kind == 0) || (kind == 1)){  // %if or %wif
    g_w1->set_string("$");
    g_w1->cat_string(g_w0->c_str());
    g_w1->cat_string("$");
    StrChg(g_w0,g_w1->c_str(),'$');
    if ((p_str = SelGet()) == NULL){g_w1->set(0,0x00);}
    else                           {StrChg(g_w1,p_str,'$');}
  }

  if (kind == 0){   // %if
    if (strcmp(g_w0->cc_str(),g_w1->cc_str()) == 0){equal_flg = true ;}
  }
  else if (kind == 1){   // %wif
    if (g_w1->getChar(0) == 0x00){
      if (g_w0->getChar(0) == 0x00){equal_flg = true ;}
    } else{
      wcc.set(g_w1->c_str());
      if (wcc.cmp(g_w0->c_str()) == true){equal_flg = true ;}
    }
  }
  else if (kind == 2){   // %calcif
    if (ci->CalcExecute  (g_w0->c_str()) == 1         ){equal_flg = true ;}
  }
  else if (kind == 3){   // %calcif_f
    if (ci_f->CalcExecute(g_w0->c_str()) == (double)1 ){equal_flg = true ;}
  }
  else if (kind == 4){   // %calcif64
    if (ci64->CalcExecute(g_w0->c_str()) == (__int64)1){equal_flg = true ;}
  }

  if (kbn == false){
    if (equal_flg == true){equal_flg = false;}
    else                  {equal_flg = true;}
  }
  return(equal_flg);
}


// ---------------------------
// %if/%wif/%calcif jump exec
// ---------------------------
void ExecCtlInf_T::if_jump_rtn(MEM_FP *prg_fp,bool equal_flg,McbArea_C *sv_ptr,McbArea_C *else_ptr,McbArea_C *end_ptr){
  if (equal_flg == false){
    if (else_ptr != MM_NULL){prg_fp->mem_mcb_ptr_wr(else_ptr);}
    else                    {prg_fp->mem_mcb_ptr_wr(end_ptr);}
  } else {
    prg_fp->mem_mcb_ptr_wr(sv_ptr);
    if (else_ptr != MM_NULL){
      if_fp->mem_mcb_end_set();
      IfLvlCell_T *ilc = (IfLvlCell_T *)if_fp->mem_link_ptr_rd();
      it->alloc_ptr = (unsigned char *)new FromTo_T(else_ptr,end_ptr);
      ilc->lvl_fp->mem_alloc();
    }
  }
}

// ----------------------
// %if/%wif/%calcif cache
// ----------------------
void ExecCtlInf_T::if_cache_rtn(MEM_FP *prg_fp,bool equal_flg,VariableArray_C *if_jump){
  Program_C  *w_pc;

  // Pointer Search
  McbArea_C *sv_ptr     = prg_fp->mem_mcb_ptr_rd();
  McbArea_C *else_ptr   = MM_NULL;
  McbArea_C *end_ptr    = MM_NULL;
  JumpCell_C *jc;
  ARY_LOOP(jc,JumpCell_C,if_jump)
    prg_fp->mem_mcb_ptr_wr(jc->addr);
    w_pc = (Program_C *)prg_fp->mem_link_ptr_rd();
    SelGetReset(w_pc);
    SelGet();

    bool ef_flag  = false;
    bool ef_kbn   = false;
    int  ef_kind  = 0;

    if  (jc->kind == 11){ // %endif
      end_ptr = jc->addr;
      break;
    }
    if      (jc->kind==0 ){ef_kbn=true;  ef_kind=0; ef_flag=true;}  // %else_if
    else if (jc->kind==1 ){ef_kbn=false; ef_kind=0; ef_flag=true;}  // %else_noif
    else if (jc->kind==2 ){ef_kbn=true;  ef_kind=1; ef_flag=true;}  // %else_wif
    else if (jc->kind==3 ){ef_kbn=false; ef_kind=1; ef_flag=true;}  // %else_nowif
    else if (jc->kind==4 ){ef_kbn=true;  ef_kind=2; ef_flag=true;}  // %else_calcif
    else if (jc->kind==5 ){ef_kbn=false; ef_kind=2; ef_flag=true;}  // %else_calcnoif
    else if (jc->kind==6 ){ef_kbn=true;  ef_kind=3; ef_flag=true;}  // %else_calcif_f
    else if (jc->kind==7 ){ef_kbn=false; ef_kind=3; ef_flag=true;}  // %else_calcnoif_f
    else if (jc->kind==8 ){ef_kbn=true;  ef_kind=4; ef_flag=true;}  // %else_calcif64
    else if (jc->kind==9 ){ef_kbn=false; ef_kind=4; ef_flag=true;}  // %else_calcnoif64
    else if (jc->kind==10){                                         // %else
      if (else_ptr == MM_NULL){else_ptr = jc->addr;}
    }

    // elseif
    if (ef_flag == true){
      if (equal_flg == true){
        if (else_ptr == MM_NULL){else_ptr = jc->addr;}
      }
      else {
        if (if_check_rtn(prg_fp,ef_kbn,ef_kind) == true){
          equal_flg = true;
          sv_ptr = jc->addr;
        }
      }
    }
  }

//printf("equal_flg=%d sv_ptr=%p  else_ptr=%p  end_ptr=%p\n",equal_flg,sv_ptr,else_ptr,end_ptr);
  if_jump_rtn(prg_fp,equal_flg,sv_ptr,else_ptr,end_ptr);

}




// ----------------------
// %if/%wif/%calcif core
// ----------------------
void ExecCtlInf_T::if_core_rtn(MEM_FP *prg_fp,bool equal_flg,Program_C *pc){
  Program_C  *w_pc;

  // Pointer Search
  McbArea_C *sv_ptr     = prg_fp->mem_mcb_ptr_rd();
  McbArea_C *else_ptr   = MM_NULL;
  McbArea_C *end_ptr    = MM_NULL;
  int        lvl        = 1;
  prg_fp->mem_mcb_next_set();

  pc->if_jump = new VariableArray_C(10);

  for(;;prg_fp->mem_mcb_next_set()){
    if (prg_fp->mem_mcb_ptr_rd() == MM_NULL){ErrMsg(MSG18); break;}
    w_pc = (Program_C *)prg_fp->mem_link_ptr_rd();
    SelGetReset(w_pc);
    char *str;
    bool ef_flag  = false;
    bool ef_kbn   = false;
    int  ef_kind  = 0;

    if ((str = SelGet()) == NULL) {continue;}
    if      ((strcmp(str,"%if"      )==0) || (strcmp(str,"%noif"      )==0)){++lvl;}
    else if ((strcmp(str,"%calcif"  )==0) || (strcmp(str,"%calcnoif"  )==0)){++lvl;}
    else if ((strcmp(str,"%calcif64")==0) || (strcmp(str,"%calcnoif64")==0)){++lvl;}
    else if ((strcmp(str,"%calcif_f")==0) || (strcmp(str,"%calcnoif_f")==0)){++lvl;}
    else if ((strcmp(str,"%wif"     )==0) || (strcmp(str,"%wnoif"     )==0)){++lvl;}
    else if  (strcmp(str,"%endif")==0){
      --lvl;
      if (lvl == 0){end_ptr = prg_fp->mem_mcb_ptr_rd(); pc->storeJump(11,end_ptr); break;}
    }
    // elseif Ver 1.54
    else if (lvl == 1){
      if      (strcmp(str,"%else_if"        )==0){ef_kbn=true;  ef_kind=0; ef_flag=true;}
      else if (strcmp(str,"%else_noif"      )==0){ef_kbn=false; ef_kind=0; ef_flag=true;}
      else if (strcmp(str,"%else_wif"       )==0){ef_kbn=true;  ef_kind=1; ef_flag=true;}
      else if (strcmp(str,"%else_nowif"     )==0){ef_kbn=false; ef_kind=1; ef_flag=true;}
      else if (strcmp(str,"%else_calcif"    )==0){ef_kbn=true;  ef_kind=2; ef_flag=true;}
      else if (strcmp(str,"%else_calcnoif"  )==0){ef_kbn=false; ef_kind=2; ef_flag=true;}
      else if (strcmp(str,"%else_calcif_f"  )==0){ef_kbn=true;  ef_kind=3; ef_flag=true;}
      else if (strcmp(str,"%else_calcnoif_f")==0){ef_kbn=false; ef_kind=3; ef_flag=true;}
      else if (strcmp(str,"%else_calcif64"  )==0){ef_kbn=true;  ef_kind=4; ef_flag=true;}
      else if (strcmp(str,"%else_calcnoif64")==0){ef_kbn=false; ef_kind=4; ef_flag=true;}
      else if (strcmp(str,"%else"           )==0){
        if (else_ptr == MM_NULL){else_ptr = prg_fp->mem_mcb_ptr_rd();}
        pc->storeJump(10,prg_fp->mem_mcb_ptr_rd());
      }
    }
    // elseif
    if (ef_flag == true){
      int w_kind = ef_kind*2;
      if (ef_kbn == false){w_kind++;}
      pc->storeJump(w_kind,prg_fp->mem_mcb_ptr_rd());
      if (equal_flg == true){
        if (else_ptr == MM_NULL){else_ptr = prg_fp->mem_mcb_ptr_rd();}
      }
      else {
        if (if_check_rtn(prg_fp,ef_kbn,ef_kind) == true){
          equal_flg = true;
          sv_ptr = prg_fp->mem_mcb_ptr_rd();
        }
      }
    }
  }

  if (lvl != 0){
    prg_fp->mem_mcb_ptr_wr(sv_ptr);
    return;
  }

//printf("equal_flg=%d sv_ptr=%p  else_ptr=%p  end_ptr=%p\n",equal_flg,sv_ptr,else_ptr,end_ptr);
  if_jump_rtn(prg_fp,equal_flg,sv_ptr,else_ptr,end_ptr);
}



// ----------------
// %printf
// ----------------
void ExecCtlInf_T::printf_rtn(Program_C *pc){
  char       *p_str;
  for(;;) {
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    char *w = g_w0->cc_str();

    if (*w == 0x00) {
      continue;
    }

	if ((strcmp(g_w0->cc_str(),"\\n")==0) && (rtn_mode == false)) {
	  printf("\n");
	}
	else {
	  printf("%s",g_w0->cc_str());
    }
	if (rtn_mode) {
	  printf("\n");
	}
  }
}
  
// ----------------
// %break
// ----------------
void ExecCtlInf_T::break_rtn(Program_C *pc,MEM_FP *prg_fp){
  ForLvlCell_T *fl;
  ListFor_T    *lf;

  for_fp->mem_mcb_end_set();
  fl = (ForLvlCell_T *)for_fp->mem_link_ptr_rd();
  fl->lvl_fp->mem_mcb_end_set();

  if (fl->lvl_fp->mem_mcb_ptr_rd() == MM_NULL){return;}

  lf = (ListFor_T *)fl->lvl_fp->mem_link_ptr_rd();
  prg_fp->mem_mcb_ptr_wr(lf->from);
  delete lf;
  fl->lvl_fp->mem_del();
  }

// ----------------
// %continue
// ----------------
void ExecCtlInf_T::continue_rtn(Program_C *pc,MEM_FP *prg_fp){
  ForLvlCell_T *fl;
  ListFor_T    *lf;
  McbArea_C     *sv_from;

  for_fp->mem_mcb_end_set();
  fl = (ForLvlCell_T *)for_fp->mem_link_ptr_rd();
  fl->lvl_fp->mem_mcb_end_set();

  if (fl->lvl_fp->mem_mcb_ptr_rd() == MM_NULL){return;}

  lf = (ListFor_T *)fl->lvl_fp->mem_link_ptr_rd();

  if (fl->CntUp(lf) == false){
    if (lf->mode == 0){fl->AryRead(lf);}
    prg_fp->mem_mcb_ptr_wr(lf->to);
  }else {
    sv_from = lf->from;
    delete lf;
    fl->lvl_fp->mem_del();
    prg_fp->mem_mcb_ptr_wr(sv_from);
  }
}


// -----------
// %listfor
// -----------
void ExecCtlInf_T::listfor_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  McbArea_C   *from;
  McbArea_C   *to;
  ForLvlCell_T *fl;
  ListFor_T    *lf;
  ListCell_T *lc;
  VarCell_T  *cnt;
  VarCell_T  *max;

  if ((p_str = SelGet()) == NULL){
    ErrMsg(MSG20);
    prg_fp->mem_mcb_ptr_wr(from);
    return;
  }
  StrChg(g_w0,p_str,'$');

  // from,to search
  to     = prg_fp->mem_mcb_ptr_rd();
  if ((from = from_srch(pc,prg_fp)) == MM_NULL) {return;}
  prg_fp->mem_mcb_ptr_wr(to);

  // list name search
  it->srch_key = g_w0->c_str();
  if (ob->list_fp->mem_srch() != 0){
    ErrMsg(MSG21,g_w0->cc_str());
    prg_fp->mem_mcb_ptr_wr(from);
    return;
  }

  g_w1->set_string(g_w0->c_str());
  lc = (ListCell_T *)ob->list_fp->mem_link_ptr_rd();

  // cnt,max variable store
  g_w2->set_string(g_w1->c_str()); g_w2->cat_string("_Cnt");
  g_w3->set_string(g_w1->c_str()); g_w3->cat_string("_Max");

  // count name search
  cnt = var_ctl->srchStoreLocal(g_w2->c_str(),"0");

  // max name search
  max = var_ctl->srchStoreLocal(g_w3->c_str(),"0");

  // ForList Store
  for_fp->mem_mcb_end_set();
  fl = (ForLvlCell_T *)for_fp->mem_link_ptr_rd();

//printf("cnt(%s=%s) max(%s=%s)\n",cnt->atai->c_str(),cnt->name->c_str(),max->atai->c_str(),max->name->c_str());

  if (fl->ListForStore(from,to,lc,cnt,max) == false){
    prg_fp->mem_mcb_ptr_wr(from);
    return;
  }

  fl->lvl_fp->mem_mcb_end_set();
  lf = (ListFor_T *)fl->lvl_fp->mem_link_ptr_rd();
  fl->AryRead(lf);
}

// ----------------------
// %for
// ----------------------
void ExecCtlInf_T::for_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  VarCell_T  *vc;
  McbArea_C   *from;
  McbArea_C   *to;
  int         loop_su;
  ForLvlCell_T *fl;

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}

  StrChg(g_w0,p_str,'$');
  vc = var_ctl->srchStoreLocal(g_w0->c_str(),"0");

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG22,vc->name->c_str()); return;}
  StrChg(g_w0,p_str,'$');
  if ((loop_su = SujiConvEx(g_w0->c_str())) < 0){ErrMsg(MSG23,g_w0->cc_str()); return;}

  // from,to search
  to     = prg_fp->mem_mcb_ptr_rd();
  if ((from = from_srch(pc,prg_fp)) == MM_NULL) {return;}
  prg_fp->mem_mcb_ptr_wr(to);

  // ForList Store
  for_fp->mem_mcb_end_set();
  fl = (ForLvlCell_T *)for_fp->mem_link_ptr_rd();
  if (fl->ListForStore(from,to,vc,loop_su) == false){
    prg_fp->mem_mcb_ptr_wr(from);
    return;
  }
}


// ----------------------
// %aryfor
// ----------------------
void ExecCtlInf_T::aryfor_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  VarCell_T  *vc,*vc2;
  McbArea_C   *from;
  McbArea_C   *to;
  ForLvlCell_T *fl;

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}

  StrChg(g_w0,p_str,'$');
  if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}

  vc2 = NULL;
  if ((p_str = SelGet()) != NULL){
    StrChg(g_w0,p_str,'$');
    vc2 = var_ctl->srchStoreLocal(g_w0->c_str(),"0");
  }

  // from,to search
  to     = prg_fp->mem_mcb_ptr_rd();
  if ((from = from_srch(pc,prg_fp)) == NULL) {return;}
  prg_fp->mem_mcb_ptr_wr(to);
 
  // ForList Store
  for_fp->mem_mcb_end_set();
  fl = (ForLvlCell_T *)for_fp->mem_link_ptr_rd();
  if (fl->ListForStore(from,to,vc,vc2) == false) { // chg ver 1.23
    prg_fp->mem_mcb_ptr_wr(from);
    return;
  }
}
  
// ----------------------
// %textfor
// ----------------------
void ExecCtlInf_T::textfor_rtn(Program_C *pc,MEM_FP *prg_fp){

  char       *p_str;
  VarCell_T  *vc;
  McbArea_C   *from;
  McbArea_C   *to;
  ForLvlCell_T *fl;
  char       *buff;
  int         len;
  int         i;
  ListFor_T  *lf;

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}

  StrChg(g_w0,p_str,'$');
  if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG24); return;}
  StrChg(g_w0,p_str,'$');

  // from,to search
  to     = prg_fp->mem_mcb_ptr_rd();
  if ((from = from_srch(pc,prg_fp)) == MM_NULL) {return;}
  prg_fp->mem_mcb_ptr_wr(to);

  // ForList Store
  for_fp->mem_mcb_end_set();
  fl = (ForLvlCell_T *)for_fp->mem_link_ptr_rd();
  if (fl->ListForStore(from,to,vc,g_w0->cc_str()) == false){
    prg_fp->mem_mcb_ptr_wr(from);
    return;
  }

  lf = (ListFor_T *)fl->lvl_fp->mem_link_ptr_rd();
  if ((buff = lf->fp->read()) == NULL){return;}
  vc->atai->set(buff);
}

// -----------
// %listset
// -----------
void ExecCtlInf_T::listset_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  char       *str;
  ListCall_T *lcall;
  ListCallCell_T *lcc;
  ListCallIdx_T  *lci;
  //sChar      *index;

  //str = g_w0;  
  // listhead name search
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG25); return;}

  StrChg(g_w0,p_str,'$');
  it->srch_key = g_w0->c_str();
  if (listcall_fp->mem_srch() != 0){ErrMsg(MSG26,g_w0->cc_str()); return;}
  lcall = (ListCall_T *)listcall_fp->mem_link_ptr_rd();
  
  // Index Generation
//  index = new sChar("");
  g_w1->set(0,0x00);
  MEM_LOOP(lcc,ListCallCell_T,lcall->idx_fp)
    if ((pc->sel_su > lcc->clm) && (lcc->clm >= 0)){
      if (*(pc->sel + lcc->clm) != (char *)MM_NULL){
        StrChg(g_w0,*(pc->sel + lcc->clm),'$');
        lcc->vc->atai->set(g_w0->cc_str());
      }
    }
    //index->cat(lcc->vc->atai->c_str());
    //index->cat("_");
    g_w1->cat_string(lcc->vc->atai->c_str());
    g_w1->cat_string("_");
  LOOP_END

  // Index Counter Store
  //it->srch_key = index->c_str();

  it->srch_key = g_w1->c_str();
  if (lcall->cnt_fp->mem_srch() == 0){
    lci = (ListCallIdx_T *)lcall->cnt_fp->mem_link_ptr_rd();
  } else{
    lci = new ListCallIdx_T(g_w1->cc_str());
    it->alloc_ptr = (unsigned char *)lci;
    lcall->cnt_fp->mem_srch_alloc();
  }
  //index->intcat(lci->cnt);
  g_w1->int_cat(lci->cnt);

  // Array Store
  MEM_LOOP(lcc,ListCallCell_T,lcall->var_fp)
    lcc->vc->atai->set(lcc->init->c_str());
    if ((pc->sel_su > lcc->clm) && (lcc->clm >= 0)){
      if (*(pc->sel + lcc->clm) != (char *)MM_NULL){
        StrChg(g_w0,*(pc->sel + lcc->clm),'$');
        lcc->vc->atai->set(g_w0->cc_str());
      }
    }

    lcc->vc->AryStore(g_w1->c_str(),lcc->vc->atai->c_str());
  LOOP_END

  // Count Up
  ++(lci->cnt);
  
//  delete index;
}




// -----------
// %listhead
// -----------
void ExecCtlInf_T::listhead_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  ListCell_T *lc;
  ListCall_T *lcall;
  VarCell_T  *vc;
  Var_B      *vb;
  ListCallCell_T *lcc;
  ListCallIdx_T  *lci;

//  str = g_w0;  
  // list name search
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG20); return;}
  StrChg(g_w0,p_str,'$');
  it->srch_key = g_w0->c_str();
  if (ob->list_fp->mem_srch() != 0){ErrMsg(MSG21,g_w0->cc_str()); return;}
  lc = (ListCell_T *)ob->list_fp->mem_link_ptr_rd();

  // ListCall_T store
  if (listcall_fp->mem_srch() == 0){
    lcall = (ListCall_T *)listcall_fp->mem_link_ptr_rd();
    MEM_LOOP(lci,ListCallIdx_T,lcall->cnt_fp)
      delete lci;
    LOOP_END
    lcall->cnt_fp->mem_del_all();
  } else {
    lcall = new ListCall_T(it,lc);
    it->alloc_ptr = (unsigned char *)lcall;
    listcall_fp->mem_srch_alloc();

    // index variable store
    MEM_LOOP(vc,VarCell_T,lc->idx_fp)
      lcall->IdxStore(-1,vc);
    LOOP_END

    // variable store
    MEM_LOOP(vc,VarCell_T,lc->var_fp)
      it->srch_key = vc->name->c_str();
      if (lc->lb->var_fp->mem_srch() == 0){
        vb = (Var_B *)lc->lb->var_fp->mem_link_ptr_rd();
        lcall->VarStore(-1,vc,vb->init_value->c_str());
      } else {
        lcall->VarStore(-1,vc,vb->init_value->c_str());
      }
    LOOP_END
  }

  // column set
  for(;;){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    it->srch_key = g_w0->c_str();
    if (lcall->idx_fp->mem_srch() == 0){
      lcc = (ListCallCell_T *)lcall->idx_fp->mem_link_ptr_rd();
      lcc->clm = prog_anl->getClm() - 1;
      continue;
     }
    if (lcall->var_fp->mem_srch() == 0){
      lcc = (ListCallCell_T *)lcall->var_fp->mem_link_ptr_rd();
      lcc->clm = prog_anl->getClm() - 1;
      continue;
    }
    ErrMsg(MSG21,g_w0->cc_str());
  }
}


// -----------
// %macro
// -----------
void ExecCtlInf_T::macro_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  MacCallCell_T *mcc;
  Program_B     *prg;
  VarCell_T     *vc;

//  str = g_w0;  
  // macro name search
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG03); return;}

  StrChg(g_w0,p_str,'$');
  it->srch_key = g_w0->c_str();
  if (ob->pg_fp->mem_srch() != 0){ErrMsg(MSG04,g_w0->cc_str()); return;}
  prg = (Program_B *)ob->pg_fp->mem_link_ptr_rd();
  
  if (mac_fp->mem_srch() == 0){
    mcc = (MacCallCell_T *)mac_fp->mem_link_ptr_rd();
    delete mcc;
    mac_fp->mem_del();
  }
  
  mcc = new MacCallCell_T(it,prg);
  it->alloc_ptr = (unsigned char *)mcc;
  mac_fp->mem_srch_alloc();
  
  for(;;){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); continue;}
    mcc->VarStore(prog_anl->getClm()-1,vc);
  }
}

// ------------------------------------------
// %arywr/%aryrd/%arydel/%arydelall/%arycopy
// ------------------------------------------
void ExecCtlInf_T::ary_rtn(Program_C *pc,MEM_FP *prg_fp,int kbn){
  char       *p_str;
//  char       *idx;
//  char       *atai;
  VarCell_T  *vc;
  VarCell_T  *vc2;
  AryCell_T  *ac;
//  char       *str;

//  str  = g_w0;
//  idx  = g_w0;
//  atai = g_w1;
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}

  StrChg(g_w0,p_str,'$');
  if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}

  // %arydelall
  if (kbn == 3){
    MEM_LOOP(ac,AryCell_T,vc->ary_fp)
      delete ac;
    LOOP_END
    vc->ary_fp->mem_del_all();
    return;
  }

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG27); return;}
  StrChg(g_w0,p_str,'$');

  // %arycopy
  if (kbn == 4){
    it->srch_key = g_w0->c_str();
    if ((vc2 = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    MEM_LOOP(ac,AryCell_T,vc2->ary_fp)
      vc->AryStore(ac->name->c_str(),ac->atai->c_str());
    LOOP_END
    return;
  }


  if (kbn == 0){
    if ((p_str = SelGet()) == NULL){g_w1->set(0,0x00);}
    else                             {StrChg(g_w1,p_str,'$');}
  }
  it->srch_key = g_w0->c_str();
  if (vc->ary_fp->mem_srch() == 0){
    ac = (AryCell_T *)vc->ary_fp->mem_link_ptr_rd();
    if (kbn == 0){ac->atai->set(g_w1->cc_str());}
    if (kbn == 1){vc->atai->set(ac->atai->c_str());}
    if (kbn == 2){delete ac; vc->ary_fp->mem_del();}
  } else {
    if (kbn == 0){vc->AryStore(g_w0->c_str(),g_w1->c_str());}
    if (kbn == 1){vc->atai->set("");}
  }
}



// ------------------------------------------
// %argdef/%argdefchk/%argdeffix
// ------------------------------------------
void ExecCtlInf_T::argdef_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn,bool chk){
  char       *p_str;
  VarCell_T  *vc;
  int         arg_su;
  int         i;
  VarCell_T  *vc2;
  AryCell_T  *ac;
  bool        match_flg;

  match_flg = true;
  if ((vc = VarSrch("argc")) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,"argc"); return;}
  arg_su = SujiConvEx(vc->atai->c_str());
  if (arg_su < 0){ErrMsg(MSG02,"argc"); return;}
  if ((vc = VarSrch("argv")) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,"argv"); return;}


  for(i=0;i<arg_su;++i){
    g_w1->int_set(i);
    it->srch_key = g_w1->c_str();
    if (vc->ary_fp->mem_srch() != 0){g_w1->set_string("");}
    else{
      ac = (AryCell_T *)vc->ary_fp->mem_link_ptr_rd();
      g_w1->set_string(ac->atai->c_str());
    }
    if ((kbn == true) && (*(ac->atai->c_str()) == 0x00)){continue;}
    if ((p_str = SelGet()) == NULL){match_flg = false; break;}
    StrChg(g_w0,p_str,'$');
    var_ctl->srchStoreLocal(g_w0->c_str(),g_w1->cc_str());
  }

  for(;;) {
    if ((p_str = SelGet()) == NULL){break;}
    match_flg = false;
    StrChg(g_w0,p_str,'$');
    var_ctl->srchStoreLocal(g_w0->c_str(),"");
  }
  if ((chk == true) && (match_flg == false)){ErrMsg(MSG28);}
}

// ------------------------------------------
// %argpart/%argpartfix
// ------------------------------------------
void ExecCtlInf_T::argpart_rtn(Program_C *pc,MEM_FP *prg_fp,bool fix){
  char       *p_str;
  VarCell_T  *vc;
  int         ptr;
  VarCell_T  *vc_cnt;

  int arg_su;
  VarCell_T  *vc_argv;
  char w_no[10];
  AryCell_T *ac_argv;
  AryCell_T *ac;

  int i;

  // # init parameter #####
  ptr      = -1;
  vc_cnt   = NULL;

  // # argc,argv Check #####
  if ((vc = VarSrch("argc")) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,"argc"); return;}
  arg_su = SujiConvEx(vc->atai->c_str());
  if (arg_su < 0){ErrMsg(MSG02,"argc"); return;}
  if ((vc_argv = VarSrch("argv")) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,"argv"); return;}

  for(;;){
    // # Variable #####
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    vc = var_ctl->srchStoreLocal(g_w0->c_str(),"0");

    // # pointer #####
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    ptr = SujiConvEx(g_w0->c_str());

    // # separate #####
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    g_w2->set_string(g_w0->c_str());

    // # Variable count #####
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    vc_cnt = var_ctl->srchStoreLocal(g_w0->c_str(),"0");
    break;

  }
  if (vc == NULL){
    ErrMsg(xMSG07);
    return;
  }

  // # Count Pass #####
  int init_cnt;
  init_cnt = 0;
  for(i=0;i<arg_su;++i){
    if (ptr < 1){break;}
    if (fix){init_cnt = ptr; break;}
    g_w1->int_set(i);
    it->srch_key = g_w1->c_str();
    if (vc_argv->ary_fp->mem_srch() != 0){continue;}
    ac_argv = (AryCell_T *)vc_argv->ary_fp->mem_link_ptr_rd();
    if (strcmp(ac_argv->atai->c_str(),"") == 0){continue;}
    if (init_cnt++ == ptr){init_cnt = i; break;}
  }

  int k = 0;

  MEM_LOOP(ac,AryCell_T,vc->ary_fp) delete ac; LOOP_END
  vc->ary_fp->mem_del_all();
  for(i=init_cnt;i<arg_su;++i){
    g_w1->int_set(i);
    it->srch_key = g_w1->c_str();
    if (vc_argv->ary_fp->mem_srch() != 0){continue;}
    ac_argv = (AryCell_T *)vc_argv->ary_fp->mem_link_ptr_rd();
    g_w1->set_string(ac_argv->atai->c_str());
    if (strcmp(g_w2->cc_str(),"") != 0){
      if (strcmp(g_w1->cc_str(),g_w2->cc_str()) == 0){break;}
    }

    // # ary store #####
    sprintf(w_no,"%05d",k++);
    it->srch_key = w_no;
    if (vc->ary_fp->mem_srch() == 0){
      ac = (AryCell_T *)vc->ary_fp->mem_link_ptr_rd();
      ac->atai->set(g_w1->cc_str());
    } else {
      ac = new AryCell_T(w_no,g_w1->cc_str());
      it->alloc_ptr =(unsigned char *) ac;
      vc->ary_fp->mem_srch_alloc();
    }
  }

  if (i >= arg_su) {i = arg_su -1;}
  if (vc_cnt != (VarCell_T *)NULL){
    vc_cnt->atai->intset(i+1);
  }

}


// ------------------------------------------
// %strsep
// ------------------------------------------
void ExecCtlInf_T::strsep_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  StrSrchInf_T *ssc;
  VarCell_T  *vc;

  ssc = new StrSrchInf_T();
  vc       = (VarCell_T  *)NULL;

  for(;;){
    // # Variable #####
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    vc = var_ctl->srchStoreLocal(g_w0->cc_str(),"0");

    // # Target String #####
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    g_w1->set_string(g_w0->c_str());

    // # separate #####
    for(;;){
      if ((p_str = SelGet()) == NULL){break;}
      StrChg(g_w0,p_str,'$');
      if (g_w0->getChar(0) != 0x00){ssc->Set(g_w0->getChar(0));}
    }
    break;
  }

  if (vc == (VarCell_T *)NULL){
    ErrMsg(xMSG07);
    delete ssc;
    return;
  }

  ssc->Main(g_w1->c_str());

  int k = 0;
  char w_no[10];
  AryCell_T *ac;
  sChar      *www;

  MEM_LOOP(ac,AryCell_T,vc->ary_fp) delete ac; LOOP_END

  vc->ary_fp->mem_del_all();
  for(int i=0;i<ssc->GetSu();++i){
    www = ssc->Get(i);
    // # ary store #####
    sprintf(w_no,"%05d",k++);  
    it->srch_key = w_no;

    if (vc->ary_fp->mem_srch() == 0){
      ac = (AryCell_T *)vc->ary_fp->mem_link_ptr_rd();
      ac->atai->set(www->c_str());
    } else {
      ac = new AryCell_T(w_no,www->c_str());
      it->alloc_ptr =(unsigned char *) ac;
      vc->ary_fp->mem_srch_alloc();
    }
  }


//  delete sstr;
  delete ssc;
}





// ------------------------------------------
// %argsep/%argsepchk/%argsepfix
// ------------------------------------------
void ExecCtlInf_T::argsep_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn,bool chk)
  {
  char       *p_str;
  VarCell_T  *vc;
  int         arg_su;
  int         i;
  AryCell_T  *ac;
  bool        match_flg;

  match_flg = true;
  if ((vc = VarSrch("argc")) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,"argc"); return;}
  arg_su = SujiConvEx(vc->atai->c_str());
  if (arg_su < 0){ErrMsg(MSG02,"argc"); return;}
  if ((vc = VarSrch("argv")) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,"argv"); return;}
  for(i=0;i<arg_su;++i){
    g_w1->int_set(i);
    it->srch_key = g_w1->c_str();

    bool hitFlag = false;
    if (vc->ary_fp->mem_srch() != 0){g_w1->set(0,0x00);}
    else {
      hitFlag = true;
      ac = (AryCell_T *)vc->ary_fp->mem_link_ptr_rd();
      g_w1->set_string(ac->atai->c_str());
    }
    if (hitFlag) {
      if ((kbn == true) && (*(ac->atai->c_str()) == 0x00)){continue;}
    }
    else {
      if (kbn == true) {continue;}
    }


    if ((p_str = SelGet()) == NULL){match_flg = false; break;}
    StrChg(g_w0,p_str,'$');
    var_ctl->srchStoreLocal(g_w0->c_str(),g_w1->cc_str());
  }

  for(;;){
    if ((p_str = SelGet()) == NULL){break;}
    match_flg = false;
    StrChg(g_w0,p_str,'$');
    var_ctl->srchStoreLocal(g_w0->cc_str(),"");
  }
  if ((chk == true) && (match_flg == false)){ErrMsg(MSG28);}
}


// ------------------------------------------
// %arysep/%arysepchk/%arysepfix
// ------------------------------------------
void ExecCtlInf_T::arysep_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn,bool chk)
  {
  char *p_str;

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG03); return;}
  StrChg(g_w0,p_str,'$');
  VarCell_T  *vc = var_ctl->srch(g_w0->cc_str());
  if (vc == NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}

  bool match_flg = true;
  AryCell_T  *ac;
  MEM_LOOP(ac,AryCell_T,vc->ary_fp)
    if ((kbn == true) && (*(ac->atai->c_str()) == 0x00)){continue;}
    if ((p_str = SelGet()) == NULL){match_flg = false; break;}
    StrChg(g_w0,p_str,'$');
    var_ctl->srchStoreLocal(g_w0->cc_str(),ac->atai->c_str());
  LOOP_END
  for(;;) {
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    var_ctl->srchStoreLocal(g_w0->cc_str(),"");
  }
  if ((chk == true) && (match_flg == false)){ErrMsg(MSG28);}

}



// -----------
// %call
// -----------
void ExecCtlInf_T::call_rtn(Program_C *pc,MEM_FP *prg_fp){
  char           *p_str;
  MacCallCell_T  *mcc;
  Program_B      *prg;
  ListCallCell_T *lcc;
  McbArea_C       *sv_ptr;
  Var_B          *vb;

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG03); return;}

  StrChg(g_w0,p_str,'$');
  it->srch_key = g_w0->c_str();
  if (mac_fp->mem_srch() != 0){ErrMsg(MSG04,g_w0->cc_str()); return;}
  mcc = (MacCallCell_T *)mac_fp->mem_link_ptr_rd();
  prg = mcc->prg;
  g_w1->set_string(msg_macro->c_str());
  msg_macro->set(prg->prg_name->c_str()); // message macro

  // Parameter Variable Set
  MEM_LOOP(lcc,ListCallCell_T,mcc->var_fp)
    if (pc->sel_su <= lcc->clm){continue;}
    if (*(pc->sel + lcc->clm) == (char *)MM_NULL){lcc->vc->atai->set(""); continue;}
    lcc->vc->atai->set(*(pc->sel + lcc->clm));
  LOOP_END

  // Macro Local Variable -> Work Variable
  WorkVarLvlAdd();
  MEM_LOOP(vb,Var_B,prg->var_fp)
    var_ctl->store(vb->var_name->c_str(),vb->init_value->c_str());
  LOOP_END

  // Macro Program Exec
  sv_ptr = prg_fp->mem_mcb_ptr_rd();
  ProgramExec(prg->prg_fp);
  prg_fp->mem_mcb_ptr_wr(sv_ptr);

  // Macro Program Exec
  msg_macro->set(g_w1->cc_str());
  //delete sv_macro;

  // Work Variable Level Delete
  WorkVarLvlDel();

  }



// ----------------
// %separate
// ----------------
void ExecCtlInf_T::sepa_rtn(Program_C *pc,MEM_FP *prg_fp,bool kbn){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
  VarCell_T  *vc_cnt;
  VarCell_T  *sep;
  VarCell_T  *buff;
  int i;
  int max;
  StrSrchInf_T *ssc;
//  sChar      *w;
  AryCell_T  *ac;
//  sChar      *sv_buff;

  // Parameter get
//  str  = g_w0;
  for(i=0;i<4;++i){
    if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}

    StrChg(g_w0,p_str,'$');
//    if (i==3){sv_buff = new sChar(g_w0->c_str()); break;}
    if (i==3){g_w2->set_string(g_w0->c_str()); break;}

    if ((buff = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    if (i==0){vc     = buff;}
    if (i==1){vc_cnt = buff;}
    if (i==2){sep    = buff;}
    }

  // Sep Control Setting
  ssc = new StrSrchInf_T();
//  w   = new sChar("");

  for(i=0;;++i){
    g_w1->int_set(i);
    it->srch_key = g_w1->c_str();
    if (sep->ary_fp->mem_srch() != 0){break;}
    ac = (AryCell_T *)sep->ary_fp->mem_link_ptr_rd();
    char *str = ac->atai->c_str();
    if (*str == 0x00){ssc->Set(' ');}
    else {
      ssc->Set(*str);
      if (kbn == true){ssc->SetFlg();}
    }
  }

  // Separation
  ssc->Main(g_w2->c_str());
  max = ssc->GetSu();
  for(i=0;i<max;++i){
    g_w1->int_set(i);
    sChar *w2 = ssc->Get(i);
    vc->AryStore(g_w1->c_str(),w2->c_str());
  }
  vc_cnt->atai->intset(max);

  // End Syori
  // delete w;
  delete ssc;
  //delete sv_buff;
  }
 


// ----------------
// %ary_save
// Ver 1.60
// ----------------
void ExecCtlInf_T::ary_save_rtn(Program_C *pc,MEM_FP *prg_fp){
  char      *p_str;
  VarCell_T  *vc;
  Write64_C  *out_fp=NULL;
  AryCell_T  *ac;

  // Parameter get
  for(;;) {
    if ((p_str = SelGet()) == NULL){break;}
    if (out_fp == NULL){
      StrChg(g_w0,p_str,'$');
	  out_fp = new Write64_C((char *)g_w0->c_str(),"wt",10240);
      if (out_fp->okCheck() == false){
		ErrMsg(MSG29,(char *)g_w0->c_str());
		delete out_fp;
		return;
      }
      continue;
    }
    StrChg(g_w0,p_str,'$');
    it->srch_key = g_w0->c_str();
    if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); continue;}

    out_fp->write("#var,");
    out_fp->csvWrite(vc->name->c_str());
    out_fp->write(",");
    out_fp->csvWrite(vc->atai->c_str());
    out_fp->writeln("");
    MEM_LOOP(ac,AryCell_T,vc->ary_fp)
      out_fp->write("#ary,");
      out_fp->csvWrite(ac->name->c_str());
      out_fp->write(",");
      out_fp->csvWrite(ac->atai->c_str());
      out_fp->writeln("");
    LOOP_END
  }
  
  if (out_fp == NULL){
    ErrMsg(MSG28);
  }
  else {
    delete out_fp;
  }
}


// ----------------
// %csv_set
// Ver 1.61
// ----------------
void ExecCtlInf_T::csv_set_rtn(Program_C *pc,MEM_FP *prg_fp){
  char      *p_str;
  VarCell_T  *vc;
  VarCell_T  *vc_first=NULL; // Ver 1.67
  bool        firstFlag=true;

  // Parameter get
  for(;;) {
	if ((p_str = SelGet()) == NULL){break;}
	if (firstFlag){
	  firstFlag = false;
	  StrChg(g_w0,p_str,'$');
      g_w1->set_string(g_w0->cc_str());
	  csv_anl->Exec(g_w0->cc_str());
	  continue;
	}
	StrChg(g_w0,p_str,'$');
	it->srch_key = g_w0->c_str();
	if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); continue;}

	if (vc_first == NULL){vc_first = vc;} // Ver 1.67

	char *w = csv_anl->CsvSelRd(NON_SP_PUSH);
	if (w == NULL){
	  vc->atai->set("");
	}
	else {
	  vc->atai->set(w);
	}
  }

  if (firstFlag){
	ErrMsg(MSG28);
  }

  // Ver 1.67
  char w_num[32];
  AryCell_T  *ac;
  if (vc_first != NULL) {
	MEM_LOOP(ac,AryCell_T,vc_first->ary_fp)
	  delete ac;
	LOOP_END
	vc_first->ary_fp->mem_del_all();
	int i=0;
	csv_anl->Exec(g_w1->cc_str());
	CSV_LOOP_NOCHK(csv_anl,w,NON_SP_PUSH)
	  sprintf(w_num,"%d",i++);
	  if (w == NULL){
		vc_first->AryStore(w_num,"");   // Ver 1.67
	  }
	  else {
		vc_first->AryStore(w_num,w);    // Ver 1.67
	  }
	LOOP_END
    sprintf(w_num,"%d",i);
	vc_first->AryStore(w_num,"*EOF_***");   // Ver 1.67
  }
}


// ----------------
// %ary_load
// Ver 1.60
// ----------------
void ExecCtlInf_T::ary_load_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  VarCell_T  *vc;
  Read64_C   *in_fp=NULL;
  VariableArray_C *ary_fp;
  AryCell_T  *ac;

  // Parameter get
  for(;;) {
	if ((p_str = SelGet()) == NULL){break;}
	if (in_fp == NULL){
	  StrChg(g_w0,p_str,'$');
	  in_fp = new Read64_C((char *)g_w0->c_str(),"rt",10240);
	  if (in_fp->okCheck() == false){
		ErrMsg(MSG29,(char *)g_w0->c_str());
		delete in_fp;
		return;
	  }
      ary_fp = new VariableArray_C(10);
      continue;
    }
    StrChg(g_w0,p_str,'$');
    it->srch_key = g_w0->c_str();
    if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); continue;}
    ary_fp->mem_alloc((unsigned char *)vc);
  }
  if (in_fp == NULL){
    ErrMsg(MSG28);
    return;
  }
  
  vc = NULL;
  CsvAnl_C *csvi = new CsvAnl_C;
  TEXT_READ_LOOP(in_fp,str)
    csvi->Exec(str);
    char *tag = NULL;
    char *key = NULL;
    char *val = NULL;
    CSV_LOOP(csvi,w_str,NON_SP_PUSH)
      if      (tag == NULL){tag = (char *)w_str;}
      else if (key == NULL){key = (char *)w_str;}
      else if (val == NULL){val = (char *)w_str;}
    LOOP_END
	if (key == NULL){continue;}
	if (strcmp(tag,"#var") == 0){
	  vc = (VarCell_T  *)ary_fp->get();
	  if (vc == NULL){break;}
	  MEM_LOOP(ac,AryCell_T,vc->ary_fp)
		delete ac;
	  LOOP_END
	  vc->ary_fp->mem_del_all();
	  if (val == NULL) {
		vc->atai->set("");
	  }
	  else {
		vc->atai->set(val);
	  }

	}
	else if (strcmp(tag,"#ary") == 0){
	  if (vc == NULL){continue;}
	  if (val == NULL) {
		vc->AryStore(key,"");
	  }
	  else{
		vc->AryStore(key,val);
	  }
    }
  LOOP_END

  delete csvi;
  delete in_fp;
  delete ary_fp;
  
}

// ----------------
// %url_anl
// ----------------
void ExecCtlInf_T::url_anl_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  VarCell_T  *kind = NULL;
  VarCell_T  *site = NULL;
  VarCell_T  *dir  = NULL;
  VarCell_T  *file = NULL;
  VarCell_T  *ext  = NULL;
  char       *url_name = NULL;
  int         cnt;

  // Parameter get
  for(cnt=0;cnt<6;++cnt){
	if ((p_str = SelGet()) == NULL){break;}
	if      (cnt==0){StrChg(g_w0,p_str,'$'); kind = var_ctl->srchStoreLocal(g_w0->c_str(),"");}
	else if (cnt==1){StrChg(g_w0,p_str,'$'); site = var_ctl->srchStoreLocal(g_w0->c_str(),"");}
	else if (cnt==2){StrChg(g_w0,p_str,'$'); dir  = var_ctl->srchStoreLocal(g_w0->c_str(),"");}
	else if (cnt==3){StrChg(g_w0,p_str,'$'); file = var_ctl->srchStoreLocal(g_w0->c_str(),"");}
	else if (cnt==4){StrChg(g_w0,p_str,'$'); ext  = var_ctl->srchStoreLocal(g_w0->c_str(),"");}
	else if (cnt==5){StrChg(g_w1,p_str,'$'); url_name = g_w1->c_str();}
  }

  if (dir == NULL){ErrMsg(MSG01); return;}

  // process
  url_anl->set(url_name);
  kind->atai->set(url_anl->getKind());
  site->atai->set(url_anl->getSite());
  dir->atai->set (url_anl->getDir ());
  file->atai->set(url_anl->getFile());
  ext->atai->set (url_anl->getExt ());
}


// ----------------
// %dbswrite
// ----------------
void ExecCtlInf_T::dbswrite_rtn(Program_C *pc,MEM_FP *prg_fp){
/*
  char       *p_str;
//  char       *str;
  bool        err;
  int         cnt;
//  sChar      *key;

  err     = true;
  cnt     = 0;
//  key     = new sChar("");
  // Parameter get
//  str     = g_w0;
  g_w1->set(0,0x00);
  for(;;){
	if ((p_str = SelGet()) == NULL){break;}
	StrChg(g_w0,p_str,'$');
	if (cnt == 0){
	  ++cnt;
	  if (db_inf->handle(g_w0->c_str(),ApiDbsWrite) == false){ErrMsg(MSG31,g_w0->cc_str()); break;}
	  continue;
	}
	if (cnt == 1){++cnt; g_w1->set_string(g_w0->c_str());}
	db_inf->cell_wr(g_w0->c_str());
	err = false;
  }
  if (err == false){db_inf->dbswrite(g_w1->c_str());}
  else             {ErrMsg(MSG28,g_w0->cc_str());}

//  delete key;
*/
}

// ----------------
// %dbsdel
// ----------------
void ExecCtlInf_T::dbsdel_rtn(Program_C *pc,MEM_FP *prg_fp){
/*
  char       *p_str;
//  char       *str;
  bool        err;
  bool        first;

  err     = true;
  first   = true;
  // Parameter get
//  str     = g_w0;
  for(;;){
	if ((p_str = SelGet()) == NULL){break;}
	StrChg(g_w0,p_str,'$');
	if (first == true){
	  if (db_inf->handle(g_w0->c_str(),ApiDbsDel) == false){ErrMsg(MSG31,g_w0->cc_str()); break;}
	  first = false;
	  continue;
	}
	db_inf->dbsdel(g_w0->c_str());
	err = false;
  }
  if (err == true){ErrMsg(MSG28,g_w0->cc_str());}
*/
}

// ----------------
// %alias
// ----------------
void ExecCtlInf_T::alias_rtn(Program_C *pc,MEM_FP *prg_fp){
  Alias_T *als;
  Alias_T *new_als;
  char       *p_str;
//  char       *str;

//  str     = g_w0;
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG33); return;}
  StrChg(g_w0,p_str,'$');
  new_als = new Alias_T(pc);
  if (new_als->max == 0){ErrMsg(MSG33); delete new_als; return;}

  it->srch_key = g_w0->c_str();
  if (alias_fp->mem_srch() == 0){
    als = (Alias_T *)alias_fp->mem_link_ptr_rd();
    delete als;
    alias_fp->mem_del();
  }
  it->alloc_ptr = (unsigned char *) new_als;
  alias_fp->mem_srch_alloc();

  alias_num++;

}

// ----------------
// %beta
// ----------------
void ExecCtlInf_T::beta_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
  char        atai;
  int         len;
  int         cnt;

  // Parameter get
//  str  = g_w0;
  atai = ' ';
  for(cnt=0;cnt<3;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==1){len = SujiConvEx(g_w0->c_str());}
    if (cnt==2){atai = g_w0->getChar(0);}
  }
      
  if (cnt < 2){ErrMsg(MSG01); return;}
  vc->atai->beta(len,atai);
}

// ----------------
// %utf-8  Ver 1.47
// ----------------
void ExecCtlInf_T::sjis_utf8_rtn(Program_C *pc,MEM_FP *prg_fp,bool toUtf8){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
  int         cnt;
  char *w=NULL;

  // Parameter get
//  str  = g_w0;
  for(cnt=0;cnt<2;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==1){w = g_w0->c_str();}
  }

  if (w == NULL){ErrMsg(MSG01); return;}
  if (toUtf8) {
    vc->atai->set(utf8_inf->toUtf_8(w));
  }
  else {
    vc->atai->set(utf8_inf->fromUtf_8(w));
  }
}

// ----------------
// %sp_push
// ----------------
void ExecCtlInf_T::sp_push_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
  int         cnt;

  // Parameter get
//  str  = g_w0;
  for(cnt=0;cnt<1;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
  }
      
  if (cnt < 1){ErrMsg(MSG01); return;}
  vc->atai->Push();
}

// ----------------
// %chg_once
// ----------------
void ExecCtlInf_T::chg_once_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
//  char       *key;
//  char       *rep;
  int         ptr;
  int         cnt;

  // Parameter get
//  str  = g_w0;
//  key  = g_w1;
//  rep  = g_w2;

  for(cnt=0;cnt<4;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==1){g_w1->set_string(g_w0->c_str());}
    if (cnt==2){g_w2->set_string(g_w0->c_str());}
    if (cnt==3){ptr = SujiConvEx(g_w0->c_str());}
  }

  if (cnt < 4){ErrMsg(MSG01); return;}

//  vc->atai->replace(g_w1->c_str(),g_w2->c_str(),ptr);
  grep->set(vc->atai->c_str());
  grep->replace(g_w1->c_str(),g_w2->c_str(),ptr);
  vc->atai->set(grep->c_str());
}


// ----------------
// %chg_all
// ----------------
void ExecCtlInf_T::chg_all_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
//  char       *key;
//  char       *rep;
  int         cnt;

  // Parameter get
//  str  = g_w0;
//  key  = g_w1;
//  rep  = g_w2;
  for(cnt=0;cnt<3;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==1){g_w1->set_string(g_w0->c_str());}
    if (cnt==2){g_w2->set_string(g_w0->c_str());}
  }
      
  if (cnt < 3){ErrMsg(MSG01); return;}
//  vc->atai->replace_all(g_w1->c_str(),g_w2->c_str());
  grep->set(vc->atai->c_str());
  grep->replace_all(g_w1->c_str(),g_w2->c_str());
  vc->atai->set(grep->c_str());


}



// ------------------- kokomade -------------------






// ----------------
// %find
// ----------------
void ExecCtlInf_T::find_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  VarCell_T  *vc;
  int         ptr;
  int         cnt;

  for(cnt=0;cnt<4;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==1){g_w2->set_string(g_w0->c_str());}
    if (cnt==2){g_w1->set_string(g_w0->c_str());}
    if (cnt==3){ptr = SujiConvEx(g_w0->c_str());}
    }

  if (cnt < 4){ErrMsg(MSG01);  return;}

  grep->set(g_w2->cc_str());
  cnt = grep->grep(g_w1->c_str(),ptr);

  if (cnt == -1){vc->atai->set("");}
  else          {vc->atai->intset(cnt);}
  }
 



// ------------------
// %timenow
// ------------------
void ExecCtlInf_T::timenow_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
  int         cnt;
  TDateTime DateTime;
  unsigned short h,m,s,ms;

  DateTime = Time();
  DateTime.DecodeTime(&h,&m,&s,&ms);

  // Parameter get
//  str  = g_w0;
  for(cnt=0;cnt<4;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    if (cnt==0){vc->atai->intset(h );}
    if (cnt==1){vc->atai->intset(m );}
    if (cnt==2){vc->atai->intset(s );}
    if (cnt==3){vc->atai->intset(ms);}
  }
}


// ------------------
// %today
// ------------------
void ExecCtlInf_T::today_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  // char       *str;
  VarCell_T  *vc;
  int         cnt;
  TDateTime DateTime;
  unsigned short y,m,d;

  DateTime = Date();
  DateTime.DecodeDate(&y,&m,&d);

  // Parameter get
  //str  = g_w0;
  for(cnt=0;cnt<3;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    if (cnt==0){vc->atai->intset(y);}
    if (cnt==1){vc->atai->intset(m);}
    if (cnt==2){vc->atai->intset(d);}
  }
}

// ------------------
// %binary (Ver 1.26)
// ------------------
void ExecCtlInf_T::binary_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  VarCell_T  *left_vc;
  VarCell_T  *right_vc;
  int         cnt;
  char w[256];

  // Parameter get
  //str  = g_w0;
  for(cnt=0;cnt<2;++cnt){
	if ((p_str = SelGet()) == NULL){break;}
	StrChg(g_w0,p_str,'$');
	if (cnt == 0){
	  if ((left_vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
	  continue;
	}
/*
	g_w1->init();
	int len = strlen(g_w0->c_str());
	char *w2 = g_w0->c_str();
	bool hit = false;
	for(int i=0;i<len;i++){
	  if (*(w2+i) == '\'') {
		hit = true;
		g_w1->set(0x00);
		break;
	  }
	  g_w1->set(*(w2+i));
	}
	if (hit == false) {
	  g_w1->init();
	  g_w1->set_string("32");
	}

	__int64 val2 = SujiConvEx64(g_w0->c_str());
	sprintf(w,"%s'h%I64x",g_w1->c_str(),val2);
	char *s = binConv->conv(w);
*/

	char *s = binConv->conv(g_w0->c_str());
	if (s == NULL){ErrMsg(MSG35,g_w0->cc_str()); return;}
	left_vc->atai->set(s);
    bitc_ex(left_vc->atai->c_str(),left_vc->atai->len());
    break;
  }
}

// ------------------
// %dateint/%timeint
// ------------------
void ExecCtlInf_T::dateint_rtn(Program_C *pc,MEM_FP *prg_fp,bool mode){
  char       *p_str;
//  char       *str;
//  char       *key;
  VarCell_T  *vc;
  int         cnt;

  // Parameter get
//  str  = g_w0;
//  key  = g_w1;
  for(cnt=0;cnt<2;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==1){g_w1->set_string(g_w0->c_str());}
  }

  if (cnt < 2){ErrMsg(MSG01); return;}

  if (mode == true){
    if (datectl->StrSet(g_w1->c_str()) == true){vc->atai->intset(datectl->value);}
    else                                       {vc->atai->set("");}
  } else {
    if (timectl->StrSet(g_w1->c_str()) == true){vc->atai->intset(timectl->value);}
    else                                       {vc->atai->set("");}
  }
}

// ------------------
// %intdate/%inttime
// ------------------
void ExecCtlInf_T::intdate_rtn(Program_C *pc,MEM_FP *prg_fp,bool mode){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc0;
  VarCell_T  *vc1;
  VarCell_T  *vc2;
  int value;
  int         cnt;

  // Parameter get
//  str  = g_w0;
  for(cnt=0;cnt<4;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc0 = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==1){
      if ((vc1 = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==2){
      if ((vc2 = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==3){value = SujiConvEx(g_w0->c_str()); if (value < 0){ErrMsg(MSG02,g_w0->cc_str());}}
  }

  if (cnt < 4){ErrMsg(MSG01); return;}

  if (mode == true){
    datectl->IntSet(value);
    vc0->atai->intset(datectl->yy);
    vc1->atai->intset(datectl->mm);
    vc2->atai->intset(datectl->dd);
  } else {
    timectl->IntSet(value);
    vc0->atai->intset(timectl->hh);
    vc1->atai->intset(timectl->mm);
    vc2->atai->intset(timectl->ss);
  }
}


// ------------------
// %fopen
// ------------------
void ExecCtlInf_T::fopen_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
//  sChar      *mode;
//  sChar      *file;
//  sChar      *ext;
  VarCell_T  *vc;
  int         cnt;

//  file = new sChar("");  g_w1
//  ext  = new sChar("");  g_w2
//  mode = new sChar("");  g_w3
  // Parameter get
//  str  = g_w0;

  for(cnt=0;cnt<4;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==1){g_w1->set_string(g_w0->c_str());}
    if (cnt==2){g_w3->set_string(g_w0->c_str());}
    if (cnt==3){g_w2->set_string(g_w3->c_str()); g_w3->set_string(g_w0->c_str());}
  }

  if (cnt < 3){ErrMsg(MSG01); return;}
  char *str = file_handle->Fopen(g_w1->c_str(),g_w2->c_str(),g_w3->c_str());
  if (str == NULL){vc->atai->set("");}
  else            {vc->atai->set(str);}  
//  delete mode; delete file; delete ext;
  firstCsvFlag=true;   
}

// ------------------
// %fprintf
// ------------------
void ExecCtlInf_T::fprintf_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
//  sChar      *cmd;
  int         cnt;
  VarCell_T  *vc;
  char w[3];
  w[0] = 0x0a;
  w[1] = 0x00;
  w[2] = 0x00;

  // Parameter get
//  str    = g_w0;
//  cmd    = new sChar("");
  g_w1->set(0,0x00);
  for(cnt=0;;++cnt){
	if ((p_str = SelGet()) == NULL){break;}
	StrChg(g_w0,p_str,'$');
	if (cnt==0){
	  if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
	}
	else{
	  if ((strcmp(g_w0->cc_str(),"\\n")==0) && (rtn_mode == false)) {
		g_w1->cat_string(w);
		firstCsvFlag=true;
	  }
	  else {
		g_w1->cat_string(g_w0->c_str());
	  }
	}
  }

  if (cnt < 1){ErrMsg(MSG01); return;}
  file_handle->Fwrite(vc->atai->c_str(),g_w1->c_str(),rtn_mode);
  if (rtn_mode) {
	firstCsvFlag=true;
  }

  //  delete cmd;
}



// ------------------
// %fcsvwrite
// ------------------
void ExecCtlInf_T::fcsvwrite_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  VarCell_T  *vc=NULL;
//  bool firstFlag=true;
  char w[3];
  w[0] = 0x0a;
  w[1] = 0x00;
  w[2] = 0x00;

  g_w1->set(0,0x00);
  for(;;){
	if (vc == NULL){
	  if ((p_str = SelGet()) == NULL){break;}
	  StrChg(g_w0,p_str,'$');
	  if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
	}
	else {
	  if ((p_str = SelGet_direct()) == NULL){break;}
	  StrChg(g_w0,p_str,'$');
	  if ((strcmp(g_w0->cc_str(),"\\n")==0) && (rtn_mode == false)) {
		g_w1->cat_string(w);
		firstCsvFlag=true;
		continue;
	  }

	  str_ext->DblIns(g_w0->cc_str());
	  if (firstCsvFlag){firstCsvFlag=false;}
	  else          {g_w1->cat_string(",");}
	  g_w1->cat_string(str_ext->c_str());
	}
  }
  if (vc == NULL){ErrMsg(MSG01); return;}

  file_handle->Fwrite(vc->atai->c_str(),g_w1->c_str(),rtn_mode);
  if (rtn_mode) {
	firstCsvFlag=true;
  }
}

// ------------------
// %fclose
// ------------------
void ExecCtlInf_T::fclose_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
  int         cnt;

  // Parameter get
//  str    = g_w0;
  for(cnt=0;cnt<1;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
  }

  if (cnt < 1){ErrMsg(MSG01); return;}
  file_handle->Fclose(vc->atai->c_str());
}

// ------------------
// %fsp+
// ------------------
void ExecCtlInf_T::fspp_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
  int         cnt;

  // Parameter get
//  str    = g_w0;
  for(cnt=0;cnt<1;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
  }

  if (cnt < 1){ErrMsg(MSG01); return;}
  file_handle->ClmPlus(vc->atai->c_str());
}

// ------------------
// %fsp-
// ------------------
void ExecCtlInf_T::fspm_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
  int         cnt;

  // Parameter get
//  str    = g_w0;
  for(cnt=0;cnt<1;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
  }

  if (cnt < 1){ErrMsg(MSG01); return;}
  file_handle->ClmMinus(vc->atai->c_str());
}

// ------------------
// %fsp
// ------------------
void ExecCtlInf_T::fsp_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
  int         cnt;
  int         suji;

  // Parameter get
//  str    = g_w0;
  suji   = -1;
  for(cnt=0;cnt<2;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==1){
      suji = SujiConvEx(g_w0->c_str());
    }
  }

  if (suji == -1){ErrMsg(MSG01); return;}
  file_handle->ClmSet(vc->atai->c_str(),suji);
}

// ------------------
// %fspcnt
// ------------------
void ExecCtlInf_T::fspcnt_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
  VarCell_T  *vc;
  int         cnt;
  int         suji;

  // Parameter get
//  str    = g_w0;
  suji   = -1;
  for(cnt=0;cnt<2;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    }
    if (cnt==1){
      suji = SujiConvEx(g_w0->c_str());
    }
  }

  if (suji == -1){ErrMsg(MSG01); return;}
  file_handle->CntSet(vc->atai->c_str(),suji);
}


// ------------------
// %exec
// ------------------
void ExecCtlInf_T::exec_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  sChar      *cmd;

  for(;;){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
	pg_exec->prmSet((char *)g_w0->c_str(),true);
  }
  printf("[exec]>%s\n",pg_exec->getCommand());
  pg_exec->Exec();
}

// ------------------
// %shell
// ------------------
void ExecCtlInf_T::shell_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  sChar      *w;

  shell_exec();
  shell_flg = false;
  for(;;){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if ((back_fp == NULL) && (g_w0->getChar(0) == '#')){
      char *str = g_w0->c_str();
      back_fp = fopen(str+1,"wt");
      printf("shell input file open(file=%s)\n",str+1);
    }
    sChar *s_w = new sChar(g_w0->cc_str());
    shell_fp->mem_alloc((unsigned char *)s_w);
    shell_flg = true;
  }
  if (shell_flg == false){
    ARY_LOOP(w,sChar,shell_fp) delete w; LOOP_END
    shell_fp->clear();
  }
}


// ------------------
// %shell_begin
// Ver 1.66
// ------------------
void ExecCtlInf_T::shell_begin_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  sChar      *w;

  shell_nest->push(back_fp,shell_fp,shell_flg);

  shell_flg = false;
  for(;;){
	if ((p_str = SelGet()) == NULL){break;}
	StrChg(g_w0,p_str,'$');
	if (g_w0->getChar(0) == '#'){
	  char *str = g_w0->c_str();
	  back_fp = fopen(str+1,"wt");
	  printf("shell input file open(file=%s)\n",str+1);
	}
	sChar *ww = new sChar(g_w0->cc_str());
	shell_fp->mem_alloc((unsigned char *)ww);
	shell_flg = true;
  }
  if (shell_flg == false){
	ARY_LOOP(w,sChar,shell_fp) delete w; LOOP_END
	shell_fp->clear();
  }
}

// ------------------
// %shell_end
// ------------------
void ExecCtlInf_T::shell_end_rtn(Program_C *pc,MEM_FP *prg_fp){
  sChar *w;
  shell_exec();

  ARY_LOOP(w,sChar,shell_fp) delete w; LOOP_END
  shell_fp->clear();
  if (shell_nest->pop(shell_fp) == false){
	ErrMsg(MSG37);
	return;
  }
  back_fp = shell_nest->getFp();
  shell_flg = shell_nest->getFlag();
}


// ------------------
// %st_default
// ------------------
void ExecCtlInf_T::st_default_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  int         i1;

  // Parameter get
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}
  StrChg(g_w0,p_str,'$');
  shell_default->set(g_w0->cc_str());
}

// ------------------
// %rand
// ------------------
void ExecCtlInf_T::rand_rtn(Program_C *pc,MEM_FP *prg_fp){
  VarCell_T  *vc;
  char       *p_str;
  sChar      *w;
  int         i1;
  int         i2;
  int         sv;

  // Parameter get
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}
  StrChg(g_w0,p_str,'$');
  vc = var_ctl->srchStoreLocal(g_w0->cc_str(),"0");

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}
  StrChg(g_w0,p_str,'$');
  i1 = SujiConvEx(g_w0->c_str());
  if (i1 < 0){ErrMsg(xMSG07); return;}

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}
  StrChg(g_w0,p_str,'$');
  i2 = SujiConvEx(g_w0->c_str());
  if (i2 < 0){ErrMsg(xMSG07); return;}

  if (i1 > i2){sv = i1; i1 = i2; i2 = sv;}
  i1 = (rand() % (i2 - i1 + 1)) + i1;
  vc->atai->intset(i1);
}

// ------------------
// %seed
// ------------------
void ExecCtlInf_T::seed_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  int         i1;

  // Parameter get
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG01); return;}
  StrChg(g_w0,p_str,'$');
  i1 = SujiConvEx(g_w0->c_str());
  if (i1 < 0){ErrMsg(xMSG07); return;}
  srand(i1);
}

// ------------------
// %fileexist
// ------------------
void ExecCtlInf_T::fileexist_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
//  sChar      *file;
  VarCell_T  *vc;
  int         cnt;

  // Parameter get
//  str  = g_w0;
//  file = new sChar("");
  g_w1->set(0,0x00);
  for(cnt=0;;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    } else {
      g_w1->cat_string(g_w0->c_str());
    }
  }

  if (cnt < 1){ErrMsg(MSG01); return;}
  
  if (FileExist(g_w1->c_str()) == 0){vc->atai->set(g_w1->cc_str());}
  else                              {vc->atai->set("");}
//  delete file;
}


// ------------------------------------------
// %chgcode
// ------------------------------------------
void ExecCtlInf_T::chgcode_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;

  VarCell_T  *vc;
//  sChar      *sstr;
//  sChar       *w_kbn;

  vc    = (VarCell_T  *)NULL;
//  w_kbn = (char *)NULL;
//  sstr  = new sChar("");  g_w1
//  w_kbn = new sChar("");  g_w2
//  str   = g_w0;
  g_w2->set(0,0x00);
  g_w1->set(0,0x00);
  for(;;){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');

    // # Variable #####
    if (g_w2->getChar(0) == 0x00){
      g_w2->set_string(g_w0->cc_str());
      continue;
    }

    if (vc == (VarCell_T  *)NULL){
	  if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){break;}
      continue;
	}
    g_w1->cat_string(g_w0->c_str());
  }

  if (vc == (VarCell_T *)NULL){ErrMsg(xMSG07); return;}

  int kbn=-1;
  if (strcmp(g_w2->cc_str(),"lower") == 0){kbn = 0;}
  if (strcmp(g_w2->cc_str(),"upper") == 0){kbn = 1;}

  if (kbn == -1){ErrMsg(xMSG07); return;}

  char c;
  char *str = g_w1->c_str();

  for(;;str++){
    c = *str; 
    if (c == 0x00){break;}
    if ((kbn == 0) && (c >= 'A') && (c <= 'Z')){c = c - 'A' + 'a';}
    if ((kbn == 1) && (c >= 'a') && (c <= 'z')){c = c - 'a' + 'A';}
    *str = c;
  }

  vc->atai->set(g_w1->cc_str());
}


// ------------------
// %file_get
// ------------------
void ExecCtlInf_T::fileget_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
//  char       *str;
//  sChar      *file;
//  sChar      *w;
  VarCell_T  *vc;
  FileGetCell_T *fgc;
  AryCell_T *ac;
  int       cnt;
  int       i;

  // Parameter get
//  str  = g_w0;
//  file = new sChar(""); g_w1
  bool detFlg = false;
  g_w1->set(0,0x00);
  for(cnt=0;;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
    if (strcmp("-d",g_w0->c_str())==0) {  // Ver 1.46
      detFlg = true;
      continue;
    }

    if (cnt==0){
      if ((vc = VarSrch(g_w0->c_str())) == (VarCell_T *)MM_NULL){ErrMsg(MSG02,g_w0->cc_str()); return;}
    } else {
      if (cnt==1) {
        g_w3->set_string((char*)g_w0->c_str()); // Ver 1.44
      }
      g_w1->cat_string(g_w0->c_str());
    }
  }

  if (cnt < 1){ErrMsg(MSG01); return;}

  file_get->get(g_w1->c_str(),FA_DIREC | FA_ARCH);

  MEM_LOOP(ac,AryCell_T,vc->ary_fp) delete ac; LOOP_END
  vc->ary_fp->mem_del_all();
  cnt = 0;

  link_C *link = NULL;   // Ver 1.44
  FileNameSep_T *nameSep = new FileNameSep_T;   // Ver 1.45
  fileinfo_C *fi = new  fileinfo_C; // Ver 1.46
//  w = new sChar("");  g_w2
  g_w2->set(0,0x00);
  MEM_LOOP(fgc,FileGetCell_T,file_get->mem_fp)
    g_w1->set_string("name"); g_w1->int_cat(cnt); vc->AryStore(g_w1->c_str(),fgc->name->c_str());
    g_w1->set_string("size"); g_w1->int_cat(cnt); g_w2->int_set(fgc->size); vc->AryStore(g_w1->c_str(),g_w2->c_str());
    g_w1->set_string("time"); g_w1->int_cat(cnt);
    i = (fgc->time & 0xf800)/2048; g_w2->int_set(i); g_w2->cat_string(":");
    i = (fgc->time & 0x7e0 )/32;   g_w2->int_cat(i); g_w2->cat_string(":");
    i = (fgc->time & 0x1f  );      g_w2->int_cat(i);
    vc->AryStore(g_w1->c_str(),g_w2->c_str());
    g_w1->set_string("date"); g_w1->int_cat(cnt);
    i = (fgc->date & 0xfe00)/512;  g_w2->int_set(i+1980); g_w2->cat_string("/");
    i = (fgc->date & 0x1e0 )/32;   g_w2->int_cat(i);      g_w2->cat_string("/");
    i = (fgc->date & 0x1f  );      g_w2->int_cat(i);
    vc->AryStore(g_w1->c_str(),g_w2->c_str());
    g_w1->set_string("attr"); g_w1->int_cat(cnt);
    if ((fgc->attr & FA_RDONLY) != 0){g_w2->set_string("R");} else {g_w2->set_string("_");}
    if ((fgc->attr & FA_HIDDEN) != 0){g_w2->cat_string("H");} else {g_w2->cat_string("_");}
    if ((fgc->attr & FA_SYSTEM) != 0){g_w2->cat_string("S");} else {g_w2->cat_string("_");}
    if ((fgc->attr & FA_LABEL ) != 0){g_w2->cat_string("L");} else {g_w2->cat_string("_");}
    if ((fgc->attr & FA_DIREC ) != 0){g_w2->cat_string("D");} else {g_w2->cat_string("_");}
    if ((fgc->attr & FA_ARCH  ) != 0){g_w2->cat_string("A");} else {g_w2->cat_string("_");}
    vc->AryStore(g_w1->c_str(),g_w2->c_str());

    // Ver 1.46
    if (detFlg){
      g_w1->set_string((char *)g_w3->c_str());
      g_w1->cat_string(fgc->name->c_str());

      if (fi->Get((char *)g_w1->c_str())) {
        g_w1->set_string("acc_time"); g_w1->int_cat(cnt);
        g_w2->int_set(fi->a_Hour);    g_w2->cat_string(":");
        g_w2->int_cat(fi->a_Minute);  g_w2->cat_string(":");
        g_w2->int_cat(fi->a_Second);
        vc->AryStore(g_w1->c_str(),g_w2->c_str());
        g_w1->set_string("acc_date"); g_w1->int_cat(cnt);
        g_w2->int_set(fi->a_Year);    g_w2->cat_string("/");
        g_w2->int_cat(fi->a_Month);   g_w2->cat_string("/");
        g_w2->int_cat(fi->a_Day);
        vc->AryStore(g_w1->c_str(),g_w2->c_str());
        g_w1->set_string("create_time"); g_w1->int_cat(cnt);
        g_w2->int_set(fi->c_Hour);    g_w2->cat_string(":");
        g_w2->int_cat(fi->c_Minute);  g_w2->cat_string(":");
        g_w2->int_cat(fi->c_Second);
        vc->AryStore(g_w1->c_str(),g_w2->c_str());
        g_w1->set_string("create_date"); g_w1->int_cat(cnt);
        g_w2->int_set(fi->c_Year);    g_w2->cat_string("/");
        g_w2->int_cat(fi->c_Month);   g_w2->cat_string("/");
        g_w2->int_cat(fi->c_Day);
        vc->AryStore(g_w1->c_str(),g_w2->c_str());
      }
      // Ver 1.46

      // Ver 1.45
      nameSep->Set(fgc->name->c_str());
      char *w = nameSep->ExtGet();
      if ((strcmp(w,"lnk") == 0) || (strcmp(w,"pif") == 0)){

        if (link == NULL) {
          link = new link_C;
        }
        // Ver 1.44
        g_w1->set_string((char *)g_w3->c_str());
        g_w1->cat_string(fgc->name->c_str());
        char *link_dest = link->Get(g_w1->c_str());
        if (link_dest != NULL) {
          g_w1->set_string("link");
          g_w1->int_cat(cnt);
          vc->AryStore(g_w1->c_str(),link_dest);
          if (link->dirHantei()) {
            g_w1->set_string("link_attr");
            g_w1->int_cat(cnt);
            vc->AryStore(g_w1->c_str(),"D");
          }
        }
        // Ver 1.44
      }
    }
    ++cnt;
  LOOP_END
  delete nameSep; // Ver 1.45
  delete fi; // Ver 1.46
  if (link != NULL){delete link;} // Ver 1.45
//  delete file;
//  delete w;
  }


// ----------------
// %ob_new 
// Ver 1.48
// ----------------
void ExecCtlInf_T::ob_new_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  char       *object_name=NULL;
  char       *class_name=NULL;
  int         cnt;
  Object_T   *sv_ob;

  // Parameter get
  for(cnt=0;cnt<2;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    if      (cnt==0){StrChg(g_w0,p_str,'$'); object_name = g_w0->c_str();}
    else if (cnt==1){StrChg(g_w1,p_str,'$'); class_name  = g_w1->c_str();}
  }
      
  if (class_name == NULL){ErrMsg(MSG01); return;}
  
  // process
  if (strcmp(cc->obj_name->c_str(),object_name) == 0){ErrMsg(MSG36,object_name); return;}
  it->srch_key = class_name;
  if (class_fp->mem_srch() != 0) {ErrMsg(MSG11,class_name); return;}
  Class_T *w_cl = (Class_T *)class_fp->mem_link_ptr_rd();

  it->srch_key = object_name;
  sv_ob = ob;
  if (object_fp->mem_srch() == 0){
    ob = (Object_T *)object_fp->mem_link_ptr_rd();
    delete ob;
    object_fp->mem_del();
  }
  ob = new Object_T(it,object_name);
  it->alloc_ptr = (unsigned char *)ob;
  object_fp->mem_srch_alloc();
  ObjectBuild(w_cl);
  ob = sv_ob;
}

// ----------------
// %ob_del
// Ver 1.48
// ----------------
void ExecCtlInf_T::ob_del_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  char       *object_name=NULL;
  int         cnt;
  Object_T   *sv_ob;

  // Parameter get
  for(cnt=0;cnt<1;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    if (cnt==0){StrChg(g_w0,p_str,'$'); object_name = g_w0->c_str();}
  }
      
  if (object_name == NULL){ErrMsg(MSG01); return;}
  
  // process
  if (strcmp(cc->obj_name->c_str(),object_name) == 0){ErrMsg(MSG36,object_name); return;}
  
  it->srch_key = object_name;
  if (object_fp->mem_srch() != 0){ErrMsg(MSG15,object_name); return;}
  sv_ob = ob;
  ob = (Object_T *)object_fp->mem_link_ptr_rd();

  delete ob;
  object_fp->mem_del();

  ob = sv_ob;
}

// ----------------
// %ob_get
// Ver 1.48
// ----------------
void ExecCtlInf_T::ob_get_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  char       *object_name=NULL;
  char       *object_var_name=NULL;
  char       *var_name=NULL;
  int         cnt;
  Object_T   *sv_ob;

  // Parameter get
  for(cnt=0;cnt<3;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    if      (cnt==0){StrChg(g_w0,p_str,'$'); object_name     = g_w0->c_str();}
    else if (cnt==1){StrChg(g_w1,p_str,'$'); object_var_name = g_w1->c_str();}
    else if (cnt==2){StrChg(g_w2,p_str,'$'); var_name        = g_w2->c_str();}
  }
      
  if (var_name == NULL){ErrMsg(MSG01); return;}
  
  // process
  it->srch_key = object_name;
  if (object_fp->mem_srch() != 0){ErrMsg(MSG15,object_name); return;}
  
  sv_ob = ob;
  ob = (Object_T *)object_fp->mem_link_ptr_rd();
  ob->it->srch_key = object_var_name;
  if (ob->var_fp->mem_srch() != 0){ErrMsg(MSG02,object_var_name);}
  VarCell_T  *vc = (VarCell_T *)ob->var_fp->mem_link_ptr_rd();
  var_ctl->srchStoreLocal(g_w2->cc_str(),vc->atai->c_str());
  ob = sv_ob;

}

// ----------------
// %ob_set
// Ver 1.48
// ----------------
void ExecCtlInf_T::ob_set_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  char       *object_name=NULL;
  char       *object_var_name=NULL;
  char       *value=NULL;
  int         cnt;
  Object_T   *sv_ob;

  // Parameter get
  for(cnt=0;cnt<3;++cnt){
    if ((p_str = SelGet()) == NULL){break;}
    if      (cnt==0){StrChg(g_w0,p_str,'$'); object_name     = g_w0->cc_str();}
    else if (cnt==1){StrChg(g_w1,p_str,'$'); object_var_name = g_w1->cc_str();}
    else if (cnt==2){StrChg(g_w2,p_str,'$'); value           = g_w2->cc_str();}
  }
      
  if (value == NULL){ErrMsg(MSG01); return;}
  
  // process
  it->srch_key = object_name;
  if (object_fp->mem_srch() != 0){ErrMsg(MSG15,object_name); return;}
  
  sv_ob = ob;
  ob = (Object_T *)object_fp->mem_link_ptr_rd();
  ob->it->srch_key = object_var_name;
  if (ob->var_fp->mem_srch() != 0){ErrMsg(MSG02,object_var_name);}
  VarCell_T  *vc = (VarCell_T *)ob->var_fp->mem_link_ptr_rd();
  vc->atai->set(value);
  
  ob = sv_ob;
  
}

// ----------------
// %ob_do
// Ver 1.48
// ----------------
void ExecCtlInf_T::ob_do_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  Program_B  *prg;
  Var_B      *vb;
  McbArea_C   *sv_ptr;
  VarCell_T  *vc;
  int         i;
  int         max;
  sChar      *sv_macro;
  int         sv_cur_clm;

  Object_T   *sv_ob;

  // object search
  if ((p_str = SelGet()) == NULL){ErrMsg(MSG03); return;}
  StrChg(g_w0,p_str,'$');
  it->srch_key = g_w0->c_str();
  if (object_fp->mem_srch() != 0){ErrMsg(MSG15,g_w0->cc_str()); return;}

  sv_ob = ob;
  ob = (Object_T *)object_fp->mem_link_ptr_rd();

  if ((p_str = SelGet()) == NULL){ErrMsg(MSG03); ob=sv_ob; return;}
  StrChg(g_w0,p_str,'$');
  it->srch_key = g_w0->c_str();

  if (ob->pg_fp->mem_srch() != 0){ErrMsg(MSG04,g_w0->cc_str()); ob=sv_ob; return;}
  prg = (Program_B *)ob->pg_fp->mem_link_ptr_rd();
  sv_macro = new sChar(msg_macro->c_str());
  msg_macro->set(prg->prg_name->c_str()); // message macro

  // Object Variable -> Work Variable
  msg_object->set(ob->name->c_str());
  msg_macro->set("null");
  msg_cmd->set("null");
  WorkVarLvlAdd();
  MEM_LOOP(vc,VarCell_T,ob->var_fp)
	var_ctl->store(vc);
  LOOP_END

  // Macro Local Variable -> Work Variable
  WorkVarLvlAdd();
  MEM_LOOP(vb,Var_B,prg->var_fp)
	var_ctl->store(vb->var_name->c_str(),vb->init_value->c_str());
  LOOP_END

  // argv,argc generation
  var_ctl->store("_MacroName",prg->prg_name->c_str());
  vc = var_ctl->store("argv","0");
  var_ctl->offset = 1;
  for(i=0;;i++){
	char *w = SelGet_direct();
	if (w == NULL) {break;}
	g_w0->int_set(i);
	StrChg(g_w1,w,'$');
	vc->AryStore(g_w0->c_str(),g_w1->c_str());
  }
  var_ctl->offset = 0;

  g_w0->int_set(i);
  var_ctl->store("argc",g_w0->cc_str());

  // Macro Program Exec
  sv_ptr = prg_fp->mem_mcb_ptr_rd();
  ProgramExec(prg->prg_fp);
  prg_fp->mem_mcb_ptr_wr(sv_ptr);

  // message pop
  msg_macro->set(sv_macro->c_str());
  delete sv_macro;

  // Work Variable Level Delete
  WorkVarLvlDel();

  // Work Variable Level Delete (for Object)
  WorkVarLvlDel();

  // save back
   ob=sv_ob;

}


// ----------------
// %file_anl_rtn
// Ver 1.53
// ----------------
void ExecCtlInf_T::file_anl_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  VarCell_T  *drv=NULL;
  VarCell_T  *dir=NULL;
  VarCell_T  *file=NULL;
  VarCell_T  *ext=NULL;
  char       *file_name=NULL;
  int         cnt;

  // Parameter get
  for(cnt=0;cnt<5;++cnt){
	if ((p_str = SelGet()) == NULL){break;}
	if      (cnt==0){StrChg(g_w0,p_str,'$'); drv = var_ctl->srchStoreLocal(g_w0->c_str(),"");}
	else if (cnt==1){StrChg(g_w0,p_str,'$'); dir = var_ctl->srchStoreLocal(g_w0->c_str(),"");}
	else if (cnt==2){StrChg(g_w0,p_str,'$'); file= var_ctl->srchStoreLocal(g_w0->c_str(),"");}
	else if (cnt==3){StrChg(g_w0,p_str,'$'); ext = var_ctl->srchStoreLocal(g_w0->c_str(),"");}
	else if (cnt==4){StrChg(g_w1,p_str,'$'); file_name = g_w1->c_str();}
  }

  if (ext == NULL){ErrMsg(MSG01); return;}

  // process
  filename_anl->set(file_name);
  drv->atai->set(filename_anl->getDrive());
  dir->atai->set(filename_anl->getDir());
  file->atai->set(filename_anl->getFile());
  ext->atai->set(filename_anl->getExt());

}



// ----------------
// %rtn_mode
// Ver 1.64
// ----------------
void ExecCtlInf_T::rtn_mode_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;

  // Parameter get
  for(;;){
	if ((p_str = SelGet()) == NULL){break;}
    StrChg(g_w0,p_str,'$');
	rtn_mode = false;
	if      (strcmp(g_w0->c_str(),"ON")==0) {rtn_mode = true;}
	else if (strcmp(g_w0->c_str(),"on")==0) {rtn_mode = true;}
	if (rtn_mode) {
	  printf("return insert mode.\n");
	}
	else {
	  printf("return not insert mode.\n");
    }
	break;
  }
  firstCsvFlag=true;
}

// ----------------
// %set_bit
// Ver 1.53
// ----------------
void ExecCtlInf_T::set_bit_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  VarCell_T  *v=NULL;
  __int64     val;
  __int64     val2;
  int         up=-1;
  int         dn=-1;
  int         cnt;
  char        w[128];

  // Parameter get
  for(cnt=0;cnt<4;++cnt){
	if ((p_str = SelGet()) == NULL){break;}
	if      (cnt==0){StrChg(g_w0,p_str,'$'); v   = var_ctl->srch(g_w0->c_str());}
	else if (cnt==1){StrChg(g_w0,p_str,'$'); val = SujiConvEx64(g_w0->c_str());}
	else if (cnt==2){StrChg(g_w0,p_str,'$'); up  = SujiConvEx(g_w0->c_str());}
	else if (cnt==3){StrChg(g_w0,p_str,'$'); dn  = SujiConvEx(g_w0->c_str());}
  }

  if (v == NULL){ErrMsg(MSG01); return;}

  // process
  if (dn < 0) {
	dn = up;
  }
  if (dn > 32) {
	dn = 32;
  }
  if (up > 32) {
	up = 32;
  }
  if (up < dn) {
	int sv = up;
	up = dn;
	dn = sv;
  }

  int s = up-dn+1;
  if (s > 32) {
	s = 32;
  }
  unsigned long mask = 0;
  unsigned long mask2 = 0;
  if      (s == 1){mask = 0x00000001;}
  else if (s == 2){mask = 0x00000003;}
  else if (s == 3){mask = 0x00000007;}
  else if (s == 4){mask = 0x0000000f;}
  else if (s == 5){mask = 0x0000001f;}
  else if (s == 6){mask = 0x0000003f;}
  else if (s == 7){mask = 0x0000007f;}
  else if (s == 8){mask = 0x000000ff;}
  else if (s == 9){mask = 0x000001ff;}
  else if (s == 10){mask = 0x000003ff;}
  else if (s == 11){mask = 0x000007ff;}
  else if (s == 12){mask = 0x00000fff;}
  else if (s == 13){mask = 0x00001fff;}
  else if (s == 14){mask = 0x00003fff;}
  else if (s == 15){mask = 0x00007fff;}
  else if (s == 16){mask = 0x0000ffff;}
  else if (s == 17){mask = 0x0001ffff;}
  else if (s == 18){mask = 0x0003ffff;}
  else if (s == 19){mask = 0x0007ffff;}
  else if (s == 20){mask = 0x000fffff;}
  else if (s == 21){mask = 0x001fffff;}
  else if (s == 22){mask = 0x003fffff;}
  else if (s == 23){mask = 0x007fffff;}
  else if (s == 24){mask = 0x00ffffff;}
  else if (s == 25){mask = 0x01ffffff;}
  else if (s == 26){mask = 0x03ffffff;}
  else if (s == 27){mask = 0x07ffffff;}
  else if (s == 28){mask = 0x0fffffff;}
  else if (s == 29){mask = 0x1fffffff;}
  else if (s == 30){mask = 0x3fffffff;}
  else if (s == 31){mask = 0x7fffffff;}
  else if (s == 32){mask = 0xffffffff;}
  mask2 = (mask<<dn) ^ 0xffffffff;
  val = val & (__int64)mask;
  val = val << (__int64)dn;

  val2 = SujiConvEx64(v->atai->c_str());

//printf("val=%I64x val2=%I64x \n",val,val2);

  val2 = (val2 & mask2) | val;
  sprintf(w,"%I64d",val2);
  v->atai->set(w);
}


// ----------------
// %need_bit
// Ver 1.69
// ----------------
void ExecCtlInf_T::need_bit_rtn(Program_C *pc,MEM_FP *prg_fp){
  char       *p_str;
  VarCell_T  *v=NULL;
  int         cnt;
  char       *s = NULL;
  char        w[512];
  strcpy(w,"0");
  s = w;

  // Parameter get
  for(cnt=0;cnt<4;++cnt){
	if ((p_str = SelGet()) == NULL){break;}
	if      (cnt==0){StrChg(g_w0,p_str,'$'); v   = var_ctl->srch(g_w0->c_str());}
	else if (cnt==1){
	  StrChg(g_w0,p_str,'$');
	  __int64 val2 = SujiConvEx64(g_w0->c_str());
	  sprintf(w,"64'h%I64x",val2);
	  s = binConv->conv(w);
	  }
  }

  if (v == NULL){ErrMsg(MSG01); return;}


  int len=0;

  

  for(int i=0;;i++){
	if (*(s+i) == 0x00) {
	  break;
	}
	if (*(s+i) == '1') {
      len = i+1;  
	}
  }

  sprintf(w,"%d",len);

  v->atai->set(w);
}



// --------------
// command else
// --------------
void ExecCtlInf_T::sel_write_rtn(Program_C *pc){
  g_w0->set(0,0x00);
  bool firstFlag  = true;

  SelGet_skip();
  for(;;){
    char *str = SelGet_direct();
	if (str == NULL) {break;}
    if (firstFlag){firstFlag = false;}
    else          {g_w0->cat_string(",");}
    StrChg(g_w1,str,'$');
    str_ext->DblIns(g_w1->cc_str());
    g_w0->cat_string(str_ext->c_str());
  }
  if (back_fp == NULL){fprintf(fp,"%s\n",g_w0->c_str());}
  else                {fprintf(back_fp,"%s\n",g_w0->c_str());}
}



// ----------------
// %class_save
// ----------------
void ExecCtlInf_T::class_save_rtn(Program_C *pc,MEM_FP *prg_fp){
  Class_T *cl;
  Var_B   *vb;
  List_B  *lb;
  Program_B *pb;
  sChar *sctr;
  int i;
  char       *p_str;


  // Parameter get
  for(int c=0;c<2;c++){
    if ((p_str = SelGet()) == NULL){
	  ErrMsg(MSG01);
	  return;
	}
	if (c == 0){StrChg(g_w0,p_str,'$');}
	if (c == 1){StrChg(g_w1,p_str,'$');}
  }

  it->srch_key = g_w0->c_str();
  if (class_fp->mem_srch() != 0) {
	ErrMsg(MSG38,g_w0->cc_str());
	return;
  }
  cl = (Class_T *)class_fp->mem_link_ptr_rd();

  Write64_C *w_fp = new Write64_C(g_w1->cc_str(),"wt",10240);
  printf("class file save. (file=%s)(class=%s)\n",g_w1->c_str(),g_w0->c_str());

  McbArea_C *sv_ptr = prg_fp->mem_mcb_ptr_rd();


//  MEM_LOOP(cl,Class_T,class_fp)
	w_fp->write  ("#class_begin,");
	w_fp->writeln(cl->class_name->c_str());
	MEM_LOOP(sctr,sChar,cl->class_fp)
	  w_fp->write  ("#inherit,");
	  w_fp->writeln(sctr->c_str());
	LOOP_END
	MEM_LOOP(vb,Var_B,cl->var_fp)
	  w_fp->write  ("#member,");
	  w_fp->write  (vb->var_name->c_str());
	  w_fp->write  (",");
	  w_fp->writeln(vb->init_value->c_str());
	LOOP_END
	MEM_LOOP(lb,List_B,cl->list_fp)
	  w_fp->write  ("#list_begin,");
	  w_fp->writeln(lb->list_name->c_str());
	  MEM_LOOP(vb,Var_B,lb->idx_fp)
		w_fp->write  ("#index,");
		w_fp->writeln(vb->var_name->c_str());
	  LOOP_END
	  MEM_LOOP(vb,Var_B,lb->var_fp)
		w_fp->write  ("#variable,");
		w_fp->write  (vb->var_name->c_str());
		w_fp->write  (",");
		w_fp->writeln(vb->init_value->c_str());
	  LOOP_END
	  w_fp->writeln("#list_end");
	LOOP_END
	MEM_LOOP(pb,Program_B,cl->prg_fp)
	  w_fp->write  ("#program_begin,");
	  w_fp->writeln(pb->prg_name->c_str());
	  MEM_LOOP(pc,Program_C,pb->prg_fp)
		w_fp->write("#program,");
		for(i=0;i<pc->sel_su;++i){
		  if (i>0){
			w_fp->write(",");
		  }
		  if (*(pc->sel+i) != (char *)MM_NULL){
			w_fp->csvWrite(*(pc->sel+i));
		  }
		}
		w_fp->writeln("");
	  LOOP_END
	  MEM_LOOP(vb,Var_B,pb->var_fp)
		w_fp->write  ("#local,");
		w_fp->write  (vb->var_name->c_str());
		w_fp->write  (",");
		w_fp->writeln(vb->init_value->c_str());
	  LOOP_END
	  w_fp->writeln("#program_end");
	LOOP_END
	w_fp->writeln("#class_end");
//  LOOP_END

  prg_fp->mem_mcb_ptr_wr(sv_ptr);

  delete w_fp;

}



// ----------------
// %class_load
// ----------------
void ExecCtlInf_T::class_load_rtn(Program_C *pc,MEM_FP *prg_fp){
  Class_T *cl;
  Var_B   *vb;
  List_B  *lb;
  Program_B *pb;
  sChar *sctr;
  char       *p_str;
  int i;
  bool deleteFlag = true;
  bool overFlag = false;  // Ver 1.74
  bool okFlag = false;
  McbArea_C *sv_ptr = prg_fp->mem_mcb_ptr_rd();

  // Parameter get
  for(int c=0;;c++){
	if ((p_str = SelGet()) == NULL){
	  break;
	}
	if (c == 0){StrChg(g_w0,p_str,'$');}
	if (c == 1){StrChg(g_w1,p_str,'$'); okFlag=true;}
	if (c >= 2){
	  StrChg(g_w2,p_str,'$');
	  if (strcmp(g_w2->c_str(),"add")==0) {  // Ver 1.73
		deleteFlag = false;
	  }
	  if (strcmp(g_w2->c_str(),"over")==0) {  // Ver 1.73
		overFlag = true;
	  }
	}
  }

  if (okFlag == false) {
	ErrMsg(MSG01);
	return;
  }

  // - CLASS DELETE ------------------------------------
  if (deleteFlag) {
	it->srch_key = g_w0->c_str();
	if (class_fp->mem_srch() == 0){
	  cl = (Class_T *) class_fp->mem_link_ptr_rd();
	  delete cl;
      class_fp->mem_del();
	}
  }
  
  // - file Search -----------------------------------
  bool exist=false;
  sChar *sstr;
  MEM_LOOP(sstr,sChar,inc_fp)
	unsigned char *a = sstr->c_str();
	g_w2->set_string(a);
	if (*(a+strlen(a)-1) != '\\'){g_w2->cat_string("\\");}
	g_w2->cat_string(g_w1->cc_str());
	printf("file search..  file=%s\n",g_w2->c_str());
	if (FileExist(g_w2->c_str()) == 0){exist=true; break;}
  LOOP_END

  if (exist == false){
	printf("file search..  file=%s\n",g_w1->c_str());
	g_w2->set_string(g_w1->cc_str());
  }



  // - CLASS LOAD ------------------------------------
  int mode = 0;
  bool ok_flag = true;
  Read64_C *r_fp = new Read64_C(g_w2->cc_str(),"csv",10240);

  if (r_fp->okCheck() == false){
	delete r_fp;
	ErrMsg(MSG39,g_w2->cc_str());
    return;
  }

  printf("class file load. (file=%s)(class=%s)\n",g_w2->c_str(),g_w0->c_str());
  CsvAnl_C *csvi = new CsvAnl_C;
  TEXT_READ_LOOP(r_fp,str)
    if (ok_flag == false){break;}
    csvi->Exec(str);
    CSV_LOOP(csvi,w,NON_SP_PUSH)
      if (strcmp(w,"#class_begin") == 0){
        mode = 1; 
        cl = class_load_class_begin(csvi); 
        if (cl == NULL){ok_flag = false;}
        break;
      }
      if (strcmp(w,"#class_end"  ) == 0){
        mode = 0; 
        break;
      }
      if (mode == 0){break;}
      
      if (strcmp(w,"#inherit") == 0){
        if (class_load_inherit(csvi,cl) == false){ok_flag = false;}
        break;
      }

      if (strcmp(w,"#member") == 0){
        if (class_load_member(csvi,cl) == false){ok_flag = false;}
        break;
      }

      if (strcmp(w,"#list_begin") == 0){
        mode = 2; 
        lb = class_load_list_begin(csvi,cl); 
        if (lb == NULL){ok_flag = false;}
        break;
      }

      if (strcmp(w,"#list_end"  ) == 0){
        mode = 1; 
        break;
      }

      if (mode == 2){
        if (strcmp(w,"#index") == 0){
          if (class_load_index(csvi,lb) == false){ok_flag = false;}
          break;
        }
        if (strcmp(w,"#variable") == 0){
          if (class_load_variable(csvi,lb) == false){ok_flag = false;}
          break;
        }
      }

      if (strcmp(w,"#program_begin") == 0){
        mode = 3; 
        pb = class_load_program_begin(csvi,cl,overFlag);   // Ver 1.74
        if (pb == NULL){ok_flag = false;}
        break;
      }

      if (strcmp(w,"#program_end"  ) == 0){
        mode = 1; 
        break;
      }

      if (mode == 3){
        if (strcmp(w,"#local"  ) == 0){
          if (class_load_local(csvi,pb) == false){ok_flag = false;}
          break;
        }
        if (strcmp(w,"#program"  ) == 0){
          if (class_load_program(csvi,pb) == false){ok_flag = false;}
          break;
        }
      }
    LOOP_END
  LOOP_END
  delete r_fp;
  delete csvi;
  prg_fp->mem_mcb_ptr_wr(sv_ptr);

}

 


// ----------------
// %class_load sub
// ----------------
Class_T *ExecCtlInf_T::class_load_class_begin(CsvAnl_C *csvi){
  Class_T *cl=NULL;
  CSV_LOOP_(csvi,w,NON_SP_PUSH)
	it->srch_key = w;
	if (class_fp->mem_srch() == 0){
	  cl = (Class_T *)class_fp->mem_link_ptr_rd();
	}
	else {
	  cl = new Class_T(it,w);
	  it->alloc_ptr = (MM_PTR_T *)cl;
	  class_fp->mem_srch_alloc();
    }
	break;
  LOOP_END
  if (cl == NULL){ErrMsg(MSG01);}
  return(cl);
}


bool ExecCtlInf_T::class_load_inherit(CsvAnl_C *csvi,Class_T *cl){
  CSV_LOOP_(csvi,w,NON_SP_PUSH)
    sChar *w_inherit = new sChar(w);
    it->alloc_ptr = (MM_PTR_T *)w_inherit;
    cl->class_fp->mem_alloc();
    return(true);
  LOOP_END
  ErrMsg(MSG01);
  return(false);        
}

bool ExecCtlInf_T::class_load_member(CsvAnl_C *csvi,Class_T *cl){
  char *p0 = NULL;
  char *p1 = NULL;
  CSV_LOOP(csvi,w,NON_SP_PUSH)
    if (p0 == NULL){p0 = w; continue;}
    if (p1 == NULL){p1 = w; continue;}
  LOOP_END
  
  if (p0 == NULL){ErrMsg(MSG01); return(false);}
  
  it->srch_key = p0;
  Var_B *vb;
  if (cl->var_fp->mem_srch() == 0){
    vb = (Var_B *)cl->var_fp->mem_link_ptr_rd();
    if (p1 == NULL){
	  vb->init_value->set("");
    }
    else {
      vb->init_value->set(p1);
    }
  }
  else {
    if (p1 == NULL){
      vb = new Var_B(p0,"");
    }
    else {
      vb = new Var_B(p0,p1);
    }
    it->alloc_ptr = (MM_PTR_T *)vb;
    cl->var_fp->mem_srch_alloc();
  }  

  return(true);        
}


List_B *ExecCtlInf_T::class_load_list_begin(CsvAnl_C *csvi,Class_T *cl){
  List_B *lb=NULL;
  CSV_LOOP_(csvi,w,NON_SP_PUSH)
    it->srch_key = w;
    if (cl->list_fp->mem_srch() == 0){
      lb = (List_B *)cl->list_fp->mem_link_ptr_rd();
    }
    else {
      lb = new List_B(it,w);
      it->alloc_ptr = (MM_PTR_T *)lb;
      cl->list_fp->mem_srch_alloc();
    }

    break;
  LOOP_END
  if (lb == NULL){ErrMsg(MSG01);}
  return(lb);
}

bool ExecCtlInf_T::class_load_index(CsvAnl_C *csvi,List_B *lb){
  CSV_LOOP(csvi,w,NON_SP_PUSH)
    lb->IdxStore(w);
    return(true);
  LOOP_END
  ErrMsg(MSG01);
  return(false);        
}

bool ExecCtlInf_T::class_load_variable(CsvAnl_C *csvi,List_B *lb){
  char *p0 = NULL;
  char *p1 = NULL;
  CSV_LOOP(csvi,w,NON_SP_PUSH)
    if (p0 == NULL){p0 = w; continue;}
    if (p1 == NULL){p1 = w; continue;}
  LOOP_END
  
  if (p0 == NULL){ErrMsg(MSG01); return(false);}
  if (p1 == NULL){
    lb->VarStore(p0,"");
  }
  else {
    lb->VarStore(p0,p1);
  }

  return(true);        
}

Program_B *ExecCtlInf_T::class_load_program_begin(CsvAnl_C *csvi,Class_T *cl,bool overFlag){
  Program_B *pb=NULL;
  g_w3->set_string("~");
  g_w3->cat_string(cl->class_name->c_str());

  CSV_LOOP_(csvi,w,NON_SP_PUSH)
	it->srch_key = w;
	bool flag = overFlag;
	if (strcmp(w,cl->class_name->c_str()) == 0) {
	  flag = false;
	}
	if (strcmp(w,g_w3->c_str()) == 0) {
	  flag = false;
	}

	if (cl->prg_fp->mem_srch() == 0){
	  pb = (Program_B *)cl->prg_fp->mem_link_ptr_rd();
	  if (flag) {
		delete pb;
		pb = new Program_B(it,w);
		it->alloc_ptr = (MM_PTR_T *)pb;
		cl->prg_fp->mem_srch_alloc();
	  }
	}
	else {
	  pb = new Program_B(it,w);
	  it->alloc_ptr = (MM_PTR_T *)pb;
	  cl->prg_fp->mem_srch_alloc();
	}

    break;
  LOOP_END
  if (pb == NULL){ErrMsg(MSG01);}
  return(pb);
}

bool ExecCtlInf_T::class_load_local(CsvAnl_C *csvi,Program_B *pb){
  char *p0 = NULL;
  char *p1 = NULL;
  CSV_LOOP(csvi,w,NON_SP_PUSH)
    if (p0 == NULL){p0 = w; continue;}
    if (p1 == NULL){p1 = w; continue;}
  LOOP_END
  
  if (p0 == NULL){ErrMsg(MSG01); return(false);}
  
  it->srch_key = p0;
  Var_B *vb;
  if (pb->var_fp->mem_srch() == 0){
    vb = (Var_B *)pb->var_fp->mem_link_ptr_rd();
	if (p1 == NULL){
	  vb->init_value->set("");
    }
    else {
      vb->init_value->set(p1);
    }
  }
  else {
    if (p1 == NULL){
      vb = new Var_B(p0,"");
    }
    else {
      vb = new Var_B(p0,p1);
    }
    it->alloc_ptr = (MM_PTR_T *)vb;
    pb->var_fp->mem_srch_alloc();
  }  

  return(true);        
}

bool ExecCtlInf_T::class_load_program(CsvAnl_C *csvi,Program_B *pb){
  int    sel_su = csvi->CsvSelSu_Rd()-1;   // Program Sel Su
  char **sel    = new char *[sel_su];      // Program Sel
  
  int ptr=0;
  CSV_LOOP_NOCHK(csvi,w,NON_SP_PUSH)
    if (w == NULL){
      *(sel+ptr) = MM_NULL;
    }
    else {
      *(sel+ptr) = new char[strlen(w)+1];
      strcpy(*(sel+ptr),w);
    }
    ptr++;
  LOOP_END
  
  Program_C *pc = new Program_C(sel_su,sel);
  it->alloc_ptr = (MM_PTR_T *)pc;
  pb->prg_fp->mem_alloc();
  return(true);
}

  
    
    
// DEBUG MODE  -----------------------------------------------------  
// --------------
// Class Printf
// -------------- 
void ExecCtlInf_T::ClassPrintf()
  {
  Class_T *cl;
  Var_B   *vb;
  List_B  *lb;
  Program_B *pb;
  Program_C *pc;
  sChar *sctr;
  int i;

  if (debug_fp == NULL){return;}
  
  DFP"[Class_T]----------------------------------------\n");
  MEM_LOOP(cl,Class_T,class_fp)
    DFP" [class]:%s\n",cl->class_name->c_str());
    MEM_LOOP(sctr,sChar,cl->class_fp)
      DFP"  [inherit]:%s\n",sctr->c_str());
    LOOP_END
    MEM_LOOP(vb,Var_B,cl->var_fp)
      DFP"  [var/init]:%s/%s\n",vb->var_name->c_str(),vb->init_value->c_str());
    LOOP_END
    MEM_LOOP(lb,List_B,cl->list_fp)
      DFP"  [list]:%s\n",lb->list_name->c_str());
      MEM_LOOP(vb,Var_B,lb->idx_fp)
        DFP"   [idx]:%s\n",vb->var_name->c_str());
      LOOP_END
      MEM_LOOP(vb,Var_B,lb->var_fp)
        DFP"   [var/init]:%s/%s\n",vb->var_name->c_str(),vb->init_value->c_str());
      LOOP_END
    LOOP_END
    MEM_LOOP(pb,Program_B,cl->prg_fp)
      DFP"  [program]:%s\n",pb->prg_name->c_str());
      MEM_LOOP(pc,Program_C,pb->prg_fp)
        DFP"   [selsu]:%d\n",pc->sel_su);
        for(i=0;i<pc->sel_su;++i)
          {
          if (*(pc->sel+i) == (char *)MM_NULL)
            {
            DFP"   [sel_%d]:NULL\n",i);
            }
          else
            {
            DFP"   [sel_%d]:%s\n",i,*(pc->sel+i));
            }
          }
      LOOP_END
      MEM_LOOP(vb,Var_B,pb->var_fp)
        DFP"   [var/init]:%s/%s\n",vb->var_name->c_str(),vb->init_value->c_str());
      LOOP_END
    LOOP_END
  LOOP_END
  }

// -----------------
// ClassCall Printf
// ----------------
void ExecCtlInf_T::ClassCallPrintf()
  {
  Classcall_T *cc;
  Var_B   *vb;
  Program_C *pc;
  int i;

  if (debug_fp == NULL){return;}

  DFP"[Classcall_T]----------------------------------------\n");
  MEM_LOOP(cc,Classcall_T,classcall_fp)
    DFP" [class/object]:%s/%s\n",cc->class_name->c_str(),cc->obj_name->c_str());
    MEM_LOOP(vb,Var_B,cc->var_fp)
      DFP"  [var/init]:%s/%s\n",vb->var_name->c_str(),vb->init_value->c_str());
    LOOP_END
    MEM_LOOP(pc,Program_C,cc->prg_fp)
      DFP"  [selsu]:%d\n",pc->sel_su);
      for(i=0;i<pc->sel_su;++i)
        {
        if (*(pc->sel+i) == (char *)MM_NULL)
          {
          DFP"   [sel_%d]:NULL\n",i);
          }
        else
          {
          DFP"   [sel_%d]:%s\n",i,*(pc->sel+i));
          }
        }
    LOOP_END
  LOOP_END
  }

// -----------------
// Version Printf
// ----------------
void ExecCtlInf_T::ObjVerPrintf()
  {
  Object_T *w_ob;
  VarCell_T *vc;

  MEM_LOOP(w_ob ,Object_T     ,object_fp   )
    MEM_LOOP(vc,VarCell_T,w_ob->var_fp)
      printf("%s:%s\n",w_ob->name->c_str(),vc->name->c_str());
    LOOP_END
  LOOP_END
  }


// -----------------
// Error Message
// ----------------
void ExecCtlInf_T::ErrMsg(char *format)
  {
  char msg[1000];

  ++err_cnt;
  printf(format);
  printf(" [command:%s / macro:%s / object:%s]\n",msg_cmd->c_str()+1,msg_macro->c_str(),msg_object->c_str());
  }

void ExecCtlInf_T::ErrMsg(char *format,char *str)
  {
  ++err_cnt;
  printf(format,str);
  printf(" [command:%s / macro:%s / object:%s]\n",msg_cmd->c_str()+1,msg_macro->c_str(),msg_object->c_str());
//  printf(msg,str);
  }

void ExecCtlInf_T::ErrMsg(CsvInf_T *csvi_fp,char *str)
  {
  ++err_cnt;
  printf("%s [command:%s]\n",str,msg_cmd->c_str()+1);
  }


// ----------------
// csvfile exec
// ----------------
void ExecCtlInf_T::csvfile_exec(char *csv_file){
  CsvInf_T *csvi;
  printf("CsvFile Read(File=%s)\n",csv_file);
  csvi         = new CsvInf_T(csv_file);
  if (csvi->CsvError_Rd() != 0){delete csvi; return;}
  if (sp_push_flg){csvi->sp_push_set(true);}   // Ver 1.25

  for(;;){
    if (csvi->CsvFgets() == -1) {break;}
    if (csvi->CsvSelSu_Rd() == 0) {continue;}
    if (csvi->CsvSel_Rd(0) == MM_NULL) {continue;}
	csvfile_exec_sub(csvi);
  }
  delete csvi; // Ver 1.29
}


// ----------------
// csvfile exec
// ----------------
void ExecCtlInf_T::csvfile_exec_sub(CsvInf_T *csvi){
  char       *p_str;
  Program_B  *prg;
  Var_B      *vb;
  McbArea_C   *sv_ptr;
  VarCell_T  *vc;
  int         i;
  VariableArray_C *mem_fp;
  sChar      *a_str;
  int         max;
  int         sv_cur_clm;
  char       **sel;
  int        sel_su;
  bool       default_flg;

  default_flg = false;
  it->srch_key = csvi->CsvSel_Rd(0);
  if (ob->pg_fp->mem_srch() != 0){
	default_flg = true;
	it->srch_key = shell_default->c_str();
	if (ob->pg_fp->mem_srch() != 0){return;}
  }
  prg = (Program_B *)ob->pg_fp->mem_link_ptr_rd();
  g_w1->set_string(msg_macro->c_str());

  msg_macro->set(prg->prg_name->c_str()); // message macro

  mem_fp = new VariableArray_C(5);

  for(i=0;i<csvi->CsvSelSu_Rd();++i)
	{
	p_str = csvi->CsvSel_Rd(i);
	if (p_str == (char *)MM_NULL)
	  {
	  a_str = new sChar("");
	  mem_fp->alloc_ptr = (unsigned char *)a_str;
	  mem_fp->mem_alloc();
	  continue;
	  }
//	if (strcmp((char *)p_str,"//")==0){break;}  // Ver 1.65
//	StrChg(g_w0,p_str,'$');                     // Ver 1.65
    g_w0->set_string(p_str);

	a_str = new sChar(g_w0->cc_str());
	mem_fp->alloc_ptr = (unsigned char *)a_str;
	mem_fp->mem_alloc();
	}
  max = i;

  // Macro Local Variable -> Work Variable
  WorkVarLvlAdd();
  MEM_LOOP(vb,Var_B,prg->var_fp)
	var_ctl->store(vb->var_name->c_str(),vb->init_value->c_str());
  LOOP_END

  // argv,argc generation
  var_ctl->store("_MacroName",prg->prg_name->c_str());
  vc = var_ctl->store("argv","0");
  i = 0;
  ARY_LOOP(a_str,sChar,mem_fp)
	if (i==0){
	  if (default_flg == false){++i; continue;}
	  else                     {++i;}
	}
	g_w0->int_set(i-1);
	++i;
	vc->AryStore(g_w0->c_str(),a_str->c_str());
  LOOP_END

  g_w0->int_set(max);
  var_ctl->store("argc",g_w0->cc_str());

  ARY_LOOP(a_str,sChar,mem_fp)
	delete a_str;
  LOOP_END
  delete mem_fp;

  // Macro Program Exec
  ProgramExec(prg->prg_fp);

  // message pop
  msg_macro->set(g_w1->cc_str());
//  delete sv_macro;

  // Work Variable Level Delete
  WorkVarLvlDel();
}


// ----------------
// csvfile exec
// ----------------
char *ExecCtlInf_T::x_getenv(char *str){
  char *env;
  StrSrchInf_T *ssc;
  sChar *sstr;
  sChar *sstr2;
  int max,k;

  env = getenv(str);
  if (env != NULL){return(env);}

  if (strcmp(str,"csvpp_dir") == 0){
    MEM_LOOP(sstr,sChar,inc_fp)
      return(sstr->c_str());
    LOOP_END
  }

  ssc = new StrSrchInf_T();
  ssc->Set('=');
  MEM_LOOP(sstr,sChar,env_fp)
    ssc->Main(sstr->c_str());
    max = ssc->GetSu();
    if (max > 2){continue;}
    sstr2 = ssc->Get(0);
    if (strcmp(str,sstr2->c_str()) != 0){continue;}
    env = sstr->c_str()+strlen(sstr2->c_str())+1;
    delete ssc;
    return(env);
  LOOP_END
  delete ssc;
  return(NULL);
}


