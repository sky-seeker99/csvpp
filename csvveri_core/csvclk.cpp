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
//  Clock Class
//

#include <string.h>
#include <stdio.h>
#include "csvclk.h"

// #clk --------------------
Clk_T::Clk_T(char *p_name,char *p_cyc,char *p_chg1,char *p_chg2,char *p_init,char *p_line){
  name = new sChar(p_name);
  cyc  = new sChar(p_cyc );
  chg1 = new sChar(p_chg1);
  chg2 = new sChar(p_chg2);
  init = new sChar(p_init);
  line = new sChar(p_line);
  clm_msg = new sChar("");
  }
Clk_T::~Clk_T(){
  delete name;
  delete cyc;
  delete chg1;
  delete chg2;
  delete init;
  delete line;
  delete clm_msg;
  }

// #sequence class -----------------
CsvClk_T::CsvClk_T(MemHeader_T *p_it,Msg_T *p_msg){
  it         = p_it;
  clk_fp     = new MEM_FP(it);
  msg        = p_msg;
  clk        = NULL;
  }

CsvClk_T::~CsvClk_T(){
  Clk_T *clk;
  MEM_LOOP(clk,Clk_T,clk_fp) delete clk; LOOP_END
  delete clk_fp;
  }

bool CsvClk_T::ExistCheck(){if (clk == NULL){return(false);} return(true);}

// Main Loop
bool CsvClk_T::CsvRead(CsvAnl_C *csvi)  // true:hit false:none hit
  {
  bool flg;
  char *command;

  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}

  if (strcmp(command,"#clk"     ) == 0){flg=true; clk_rtn (csvi  );  }
  return(flg);
  }

// #clk
void CsvClk_T::clk_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *name;
  char *cyc;
  char *chg1;
  char *chg2;
  char *init;

  name  = NULL;
  cyc   = NULL;
  chg1  = NULL;
  chg2  = NULL;
  init  = NULL;

  int clm=0;
  for(i=1;i<csvi->CsvSelSu_Rd();++i){
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
	if (name == NULL){
	  clm = i;
	  name = str;
	  it->srch_key = name;
	  if (clk_fp->mem_srch() == 0){msg->ErrMsg(csvi,E070,i); return;}
	  continue;
	}
	if (cyc  == NULL){cyc  = str; continue;}
	if (chg1 == NULL){chg1 = str; continue;}
	if (chg2 == NULL){chg2 = str; continue;}
	if (init == NULL){init = str; continue;}

	clk = new Clk_T(name,cyc,chg1,chg2,init,str);

	clk->clm_msg->set(csvi->getClmMsg(i));
	it->alloc_ptr = (MM_PTR_T *)clk;
	clk_fp->mem_srch_alloc();
	return;
  }
  msg->ErrMsg(csvi,E000,clm);
}


