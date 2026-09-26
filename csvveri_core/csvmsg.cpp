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

