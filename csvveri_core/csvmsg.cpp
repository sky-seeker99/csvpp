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

#include <stdio.h>
#include "csvmsg.h"

// Message Class -----------------
Msg_T::Msg_T(){
  err_cnt = 0;
}
void Msg_T::ErrMsg(CsvAnl_C *csvi,char *msg,int clm){
  sprintf(w_msg,"%s  command:%-8s  ",msg,csvi->CsvSel_Rd(0));
  printf("%s\n",csvi->getErrMsg(w_msg,clm));
  ++err_cnt;
}
void Msg_T::ErrMsg(char *msg,char *cmd,char *msg2){
  printf("%s  command:%-8s  %s\n",msg,cmd,msg2);
  ++err_cnt;
}
void Msg_T::WarningMsg(char *clm_msg,char *reg,char *msg){
  printf("%s  key:%-8s  %s\n",clm_msg,reg,msg);
  ++err_cnt;
}

