/*

 * Copyright (c) 2009 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
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


