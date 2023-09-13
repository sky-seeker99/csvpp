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
//  Patern
//

#ifndef _CSVRMEM_H_
#define _CSVRMEM_H_

#include "csvmsg.h"
#include "csvptn.h"

// #readfile class -----------------
class CsvRFile_T{
  public:
  VariableArea_C  *file_name;
  VariableArray_C *var_fp;   // cell:Var_T
  int              ary_max;  // ary_max
  int              wid_bus;  // width
  VariableArea_C  *ptr_name; // ptr name
  VariableArea_C  *clm_msg;  // csv line
  CsvRFile_T(char *p_file_name,char *p_ary_max,char *p_ptr_name){
    file_name = new VariableArea_C(p_file_name);
    ary_max   = SujiConvEx(p_ary_max);
    wid_bus   = 0;
    ptr_name  = new VariableArea_C(p_ptr_name);
    clm_msg   = new VariableArea_C(10);
    var_fp    = new VariableArray_C(10);
  }
  ~CsvRFile_T(){
    Var_T *v;
    delete file_name;
    delete ptr_name;
    delete clm_msg;
    ARY_LOOP(v,Var_T,var_fp) delete v; LOOP_END;
    delete var_fp;
  }
};

// PaternControlTask Class -----------------
class CsvRFileList_T{
  public:
  VariableArray_C *ary_fp; // cell:CsvRFile_T
  Msg_T           *msg;
  CsvRFile_T      *g_rf;
  CsvRFileList_T(Msg_T *p_msg){
    msg    = p_msg;
    ary_fp = new VariableArray_C(10);
    g_rf   = NULL;
  }
    
  ~CsvRFileList_T(){
    ARY_LOOP(rf,CsvRFile_T,ary_fp) delete rf; LOOP_END
    delete ary_fp;
  }
  bool CsvRead(CsvAnl_C *csvi);
  private:
  void var_rtn   (CsvAnl_C *csvi);
  void head_rtn  (CsvAnl_C *csvi);
  };

#endif // _CSVRMEM_H_
