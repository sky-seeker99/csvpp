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
//  Function Table
//   1.09 : #function_case , #function_direct
//

#include <string.h>
#include <stdio.h>
#include "csvfunc.h"

// table class -----------------
Tbl_T::Tbl_T(MemHeader_T  *it,char *p_val){
  val      = new sChar(p_val);
  inptn_fp = new MEM_FP(it);
  clm_msg = new sChar("");
  }
Tbl_T::~Tbl_T(){
  sChar *str;
  delete val;
  MEM_LOOP(str,sChar,inptn_fp) delete str; LOOP_END
  delete inptn_fp;
  delete clm_msg;
  }

// #ftable class -----------------
Func_T::Func_T(MemHeader_T  *it,char *p_name,int p_clm,char *p_case_str,char *p_direct){   // Ver 1.09
  name     = new sChar(p_name);
  clm      = p_clm;
  table_fp = new MEM_FP(it);
  in_fp    = new MEM_FP(it);
  clm_msg = new sChar("");
  case_str = new sChar(p_case_str);  // Ver 1.09
  direct   = new sChar(p_direct  );  // Ver 1.09
  }
Func_T::~Func_T(){
  sChar *clm;
  Tbl_T *tbl;
  delete name;
  MEM_LOOP(tbl,Tbl_T,table_fp) delete tbl; LOOP_END
  delete table_fp;
  MEM_LOOP(clm,sChar,in_fp) delete clm; LOOP_END
  delete in_fp;
  delete clm_msg;
  delete case_str; // Ver 1.09
  delete direct;   // Ver 1.09
  }

// #function class -----------------
Clm_T::Clm_T(char *p_name,int p_clm){
  name = new sChar(p_name);
  clm  = p_clm;
  clm_msg = new sChar("");
  }
Clm_T::~Clm_T(){
  delete name;
  delete clm_msg;
  }

// Function Class -----------------
Function_T::Function_T(MemHeader_T  *p_it,Msg_T *p_msg){
  it       = p_it;
  fdefi_fp = new MEM_FP(it);
  fdefo_fp = new MEM_FP(it);
  func_fp  = new MEM_FP(it);
  msg      = p_msg;
  case_str = new sChar("case");  // Ver 1.09
  direct   = new sChar("");      // Ver 1.09
  }
Function_T::~Function_T(){
  Clm_T  *cl;
  Func_T *fn;
  MEM_LOOP(cl ,Clm_T ,fdefi_fp) delete cl;  LOOP_END
  MEM_LOOP(fn ,Func_T,func_fp ) delete fn;  LOOP_END
  delete fdefi_fp;
  delete fdefo_fp;
  delete func_fp;
  delete case_str; // Ver 1.09
  delete direct;   // Ver 1.09
  }

// Main Loop
bool Function_T::CsvRead(CsvAnl_C *csvi) // true:hit false:none hit
  {
  bool flg;
  char *command;

  flg = false;
  command = csvi->CsvSel_Rd(0);
  if (csvi->blankCheck(command)) {return(false);}
  if (strcmp(command,"#function_case"  ) == 0){flg=true; function_str_rtn(csvi,0);}  // Ver 1.09
  if (strcmp(command,"#function_direct") == 0){flg=true; function_str_rtn(csvi,1);}  // Ver 1.09
  if (strcmp(command,"#function") == 0){flg=true; function_rtn(csvi);}
  if (strcmp(command,"#ftable"  ) == 0){flg=true; ftable_rtn  (csvi);}
  return(flg);
  }

// #function_case,#function_direct   Ver 1.09
void Function_T::function_str_rtn(CsvAnl_C *csvi,int kbn)
  {
  int i;
  char *str;
  
  if (kbn == 0){case_str->set("");}
  else         {direct->set("");}

  // main loop
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)) {continue;}
    if (kbn == 0){case_str->cat(str);}
    else         {direct->cat(str);}
    }
  }


// #function
void Function_T::function_rtn(CsvAnl_C *csvi)
  {
  int i;
  int cnt;
  char *str;
  Clm_T *cl;
  Clm_T *clm;
  Func_T *fn;
  Clm_T *ccc;

  // fdefi/fdefo delete
  MEM_LOOP(cl,Clm_T,fdefi_fp) delete cl; LOOP_END
  fdefi_fp->mem_del_all();
  fdefo_fp->mem_del_all();

  // main loop
  cnt = 0;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
	str = csvi->CsvSel_Rd(i);
	if (csvi->blankCheck(str)){continue;}
    if (cnt == 0) // input
      {
      if (strcmp(str,":") == 0){cnt = 1; continue;}
	  ccc = new Clm_T(str,i);
	  it->alloc_ptr = (MM_PTR_T *)ccc;
	  ccc->clm_msg->set(csvi->getClmMsg(i));
	  fdefi_fp->mem_alloc();
      }
    else    // output
      {
      it->srch_key  = str;
      if (func_fp->mem_srch() == 0){msg->ErrMsg(csvi,E030,i); continue;}
      fn = new Func_T(it,str,i,case_str->c_str(),direct->c_str());  // Ver 1.09
      fn->clm_msg->set(csvi->getClmMsg(i));
      MEM_LOOP(clm,Clm_T,fdefi_fp)
        it->alloc_ptr = (MM_PTR_T *)new sChar(clm->name->c_str());
        fn->in_fp->mem_alloc();
      LOOP_END
      it->alloc_ptr = (MM_PTR_T *)fn;
      func_fp->mem_srch_alloc();
      fdefo_fp->mem_srch_alloc();
      }
    }
  }


// #ftable
void Function_T::ftable_rtn(CsvAnl_C *csvi)
  {
  Clm_T  *cl;
  Tbl_T  *tbl;
  sChar  *str;
  Func_T *fn;

  MEM_LOOP(fn,Func_T,fdefo_fp)
	char *ww = csvi->CsvSel_Rd(fn->clm);
	if (csvi->blankCheck(ww)){continue;}
    tbl = new Tbl_T(it,csvi->CsvSel_Rd(fn->clm));
    tbl->clm_msg->set(csvi->getClmMsg(fn->clm));
    it->alloc_ptr = (MM_PTR_T *)tbl;
    fn->table_fp->mem_alloc();
	MEM_LOOP(cl,Clm_T,fdefi_fp)
	  char *www = csvi->CsvSel_Rd(cl->clm);
	  if (csvi->blankCheck(www)){str = new sChar("");}
	  else                      {str = new sChar(csvi->CsvSel_Rd(cl->clm));}
      it->alloc_ptr = str;
      tbl->inptn_fp->mem_alloc();
    LOOP_END
  LOOP_END
  }


