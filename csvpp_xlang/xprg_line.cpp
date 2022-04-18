/*

 * Copyright (c) 2011 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
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

#include <stdio.h>
#include <string.h>
#include "xprg_line.h"

// - all del -----------------
void progLine_C::clear(){
  ARY_LOOP(str,progStr_C,prog_fp)
    if (str == NULL){continue;}
    dust_fp->push(str);
  LOOP_END
  prog_fp->clear();
  cur_clm = 0;
}


// - store -----------------
void progLine_C::store(int no,char *w){
  if (w == NULL){prog_fp->mem_alloc(NULL); return;}
  progStr_C *str = dust_fp->pop();
  if (str == NULL){str = new progStr_C(w);}
  else            {str->set(w);       }

  if (no == -1) {
    prog_fp->mem_alloc(str);
  }
  else {
    prog_fp->mem_alloc(no,str);
  }
}

// - put -----------------
void  progLine_C::put(Program_C *pc){
  clear();
  for(int i=0;i<pc->sel_su;++i){
    store(-1,*(pc->sel+i));
  }
  prog_fp->get_init();
}


void progLine_C::put(CsvInf_T *csvi_fp){
  clear();
  for(int i=0;i<csvi_fp->CsvSelSu_Rd();++i){
    store(-1,csvi_fp->CsvSel_Rd(i));
  }
  prog_fp->get_init();
}


// - Variable Search --------------
VarCell_T *progLine_C::VarSrch(char *p_key){
  VarCell_T  *vc;
  char       *key = p_key;

  if (*key == '*'){
    if ((vc = var_ctl->srch(key+1)) == NULL){return(NULL);}
    key = vc->atai->c_str();
  }
  return(var_ctl->srch(key));
}


// - get reset ------------------
void progLine_C::resetReadPtr(){
  prog_fp->setReadPtr(0);
}


// - get ------------------
char *progLine_C::get(bool directFlag){
  char *str;
  AryCell_T *ac;

  okFlag = true;
  for(;;){
    if (prog_fp->getStorePtr() <= prog_fp->getReadPtr()) {
      break;
    }
    progStr_C *s_str = prog_fp->get();
    cur_clm++;
    if (s_str  == NULL) {
      if (directFlag) {return(nullData);}
      continue;
    }
    char  *str   = s_str->c_str();
    if (*str == 0x00) {
      if (directFlag) {return(nullData);}
      continue;
    }
    if (strcmp(str,"//") == 0){break;}

    if (*str == '$'){
      if (*(str+1) == '%'){
        VarCell_T *vc = VarSrch(str+2);
        if (vc == NULL){okFlag = false; errStr = str+2; return(NULL);}
        int sel_num=0;
        MEM_LOOP(ac,AryCell_T,vc->ary_fp) sel_num++; LOOP_END
        int no=prog_fp->getReadPtr();
        prog_fp->insert(prog_fp->getReadPtr(),sel_num);
        MEM_LOOP(ac,AryCell_T,vc->ary_fp)
          store(no,ac->atai->c_str());
          no++;
        LOOP_END
        continue;
      }
    }
    return(str);
  }

  return(NULL);
}




