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
//  function coverage
//

#include <string.h>
#include <stdio.h>
#include "csvcover.h"

// #coverage cell class -----------------
CsvCoverCell_T::CsvCoverCell_T(int p_no,char *p_clk,char *p_siki){ 
  no     = p_no;
  clk    = new sChar(p_clk);
  siki   = new sChar(p_siki);
  }
CsvCoverCell_T::~CsvCoverCell_T(){
  delete clk;
  delete siki;
  }



// #coverage Class -----------------
CsvCover_T::CsvCover_T(MemHeader_T  *p_it,Msg_T *p_msg){
  it     = p_it;
  mem_fp = new MEM_FP(it);
  msg    = p_msg; 
  no     = 0;
  }
CsvCover_T::~CsvCover_T(){  
  CsvCoverCell_T *ccc;
  MEM_LOOP(ccc,CsvCoverCell_T ,mem_fp) delete ccc;  LOOP_END
  delete mem_fp;
  }

// Main Loop
bool CsvCover_T::CsvRead(CsvAnl_C *csvi) // true:hit false:none hit
  {
  bool flg;
  char *command;
  
  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)){return(false);}
  if (strcmp(command,"#coverage") == 0){flg = true; cover_rtn(csvi);}
  return(flg);
  }

// #coverage
void CsvCover_T::cover_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *clk;
  char *siki;

  clk = NULL;
  siki = NULL;

  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)){continue;}
    if (clk  == NULL){clk  = str; continue;}
    if (siki == NULL){siki = str; break;}
    }

  if (siki == NULL){msg->ErrMsg(csvi,E000,0); return;}
  it->alloc_ptr = (CsvCoverCell_T *)new CsvCoverCell_T(no,clk,siki);  
  no++;
  mem_fp->mem_alloc();
  }


