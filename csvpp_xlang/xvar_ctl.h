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

#ifndef _XVAR_CTL_H_
#define _XVAR_CTL_H_

#include "..\csvpp_xbase\t_area_instance.h"
#include "..\csvpp_xbase\zschar.h"
#include "..\csvpp_xbase\zlist.h"

#include "xclass.h"
#include "xobject.h"

//#define VAR_CTL_DEBUG 


// # varCrlCell_C ------------------
class varCrlCell_C {
  public:
    bool                       local;  // true:local variable false:object pointer
    VariableList_T<VarCell_T> *var_fp; // variable List

    varCrlCell_C(VariableListHeader_C *it){
      local = true;
      var_fp = new VariableList_T<VarCell_T>(it);   // local = false‚ÌŽž‚Í“à—e‚Ííœ‚µ‚È‚¢B
      var_fp->delFlag = false;
    }
    ~varCrlCell_C(){
      delete var_fp;
    }
};


// # varCtl_C -------------
class varCtl_C{
  public:
    VariableStack_T<varCrlCell_C> *stack_fp;
    VariableStack_T<varCrlCell_C> *stack_dust_fp;
    VariableStack_T<VarCell_T>    *var_dust_fp;
    VariableListHeader_C *it;
    MemHeader_T          *old_it;
    int     offset;

    varCtl_C(MemHeader_T *p_old_it){
      old_it        = p_old_it;
      it            = new VariableListHeader_C;
      stack_fp      = new VariableStack_T<varCrlCell_C>(10);
      stack_dust_fp = new VariableStack_T<varCrlCell_C>(10);
      var_dust_fp   = new VariableStack_T<VarCell_T>(10);
      stack_fp->delFlag = false;
      stack_dust_fp->delFlag = false;
      var_dust_fp->delFlag = false;
      offset = 0;
    }

    ~varCtl_C(){
      varCrlCell_C *vcc;
      VarCell_T    *vc;
      ARY_LOOP(vcc,varCrlCell_C,stack_fp)      delete vcc; LOOP_END
      ARY_LOOP(vcc,varCrlCell_C,stack_dust_fp) delete vcc; LOOP_END
      ARY_LOOP(vc ,VarCell_T   ,var_dust_fp)   delete vc ; LOOP_END

      delete stack_fp;
      delete stack_dust_fp;
      delete var_dust_fp;
      delete it;
    }
    void          del();
    void          add();
    varCrlCell_C *getCurrent();
    VarCell_T    *srch(char *p_key);
    VarCell_T    *srchLocal(char *p_key);
    VarCell_T    *store(char *var,char *init);
    VarCell_T    *store(VarCell_T *vc);
    VarCell_T    *srchStoreLocal(char *var,char *init);
    VarCell_T    *srchStore(char *var,char *init);

};


#endif // _XVAR_CTL_H_



