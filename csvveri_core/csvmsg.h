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
//  Message
//

#ifndef _CSVMSG_H_
#define _CSVMSG_H_

#include "../csvpp_xbase/zcsvfile.h"

// Error Message (for #status)-----------------
#define E000 "E000:syntax error"
#define E001 "E001:state machine multiple define"
#define E002 "E002:register multiple define"
#define E003 "E003:undefine #status"
#define E004 "E004:state multiple define"
#define E005 "E005:undefine #if/#else - #endif combination error or undefine #st"
#define E006 "E006:schedule cycle unnumelic"
#define E007 "E007:undefine #reg"
#define E008 "E008:wire multiple define"

// Error Message (for #sub)----------
#define E020 "E020:undefine #sub"

// Error Message (for #function)----------
#define E030 "E030:undefine #function"

// Error Message (for #gate)----------
#define E040 "E040:undefine #gate"
#define E041 "E041:port unmatch"

// Error Message (for #con)----------
#define E050 "E050:undefine #define"
#define E051 "E051:undefine #line"
#define E052 "E052:header undefine"
#define E053 "E053:undefine #con_head"
#define E054 "E054:module undefine"
#define E055 "E055:instance multiple define"
#define E056 "E056:module define error"
#define E057 "E057:connection error"

// Error Message (for #task)----------
#define E060 "E060:task multiple define"
#define E061 "E061:undefine #task or #taskn or #taskx"

// Error Message (for #clk)----------
#define E070 "E070:clock multiple define"

// Error Message (for #patern)----------
#define E080 "E080:undefine #patern"
#define E081 "E081:undefine #p_patern"
#define E082 "E082:undefine #r_patern"

// Error Message (for top)----------
#define E090 "E090:undefine #module"
   
// Error Message (for #inf)----------
#define E100 "E100:undefine #inf_send/#inf_recv"
#define E101 "E101:multiple define #inf_send/#inf_recv"

// Error Message (for #readmemh)----------
#define E110 "E110:undefine #readmemh"




// Warning Message (for csvrtl)-----------------
#define W000 "W000:state machine undefine"
#define W001 "W001:undefine #wire"

// Message Class -----------------
class Msg_T {
  public:
  int err_cnt;
  char w_msg[1024];
  Msg_T();
  void ErrMsg(CsvAnl_C *csvi,char *msg,int clm);
  void ErrMsg(char *msg,char *cmd,char *msg2);
  void WarningMsg(char *clm_msg,char *reg,char *msg);
  };


#endif // _CSVMSG_H_
