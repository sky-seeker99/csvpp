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

#ifndef _XPRG_LINE_H_
#define _XPRG_LINE_H_

#include "..\csvpp_xbase\t_area_instance.h"
#include "..\csvpp_xbase\zschar.h"
#include "..\csvpp_xbase\zlist.h"

#include "xclass.h"
#include "xobject.h"
#include "xvar_ctl.h"


// # progLine_C -------------
class progStr_C{
  public:
  char *str;
  progStr_C(char *p){str = p;}
  char *c_str(){return(str);}
  void set(char *p){str = p;}
};

// # progLine_C -------------
class progLine_C{
  public:
    VariableArray_T<progStr_C> *prog_fp;
    VariableStack_T<progStr_C> *dust_fp;
    bool                    okFlag;
    char                   *errStr;
    char                    nullData[2];
    int                     cur_clm;
    varCtl_C               *var_ctl;
    progLine_C(varCtl_C *var){
      prog_fp = new VariableArray_T<progStr_C>(10);
      dust_fp = new VariableStack_T<progStr_C>(10);
      prog_fp->delFlag = false;
      dust_fp->delFlag = false;
      okFlag   = false;
      nullData[0] = 0x00;
      cur_clm  = 0;
      var_ctl  = var;
    }
    ~progLine_C(){
      ARY_LOOP(str,progStr_C,prog_fp) delete str; LOOP_END
      ARY_LOOP(str,progStr_C,dust_fp) delete str; LOOP_END
      delete prog_fp;
      delete dust_fp;
    }
    void  put(Program_C *pc);
    void  put(CsvInf_T *csvi_fp);
    char *get(bool directFlag);
    void resetReadPtr();
    bool  okCheck(){return(okFlag);}
    int   getClm(){return(cur_clm);}
  private:
    VarCell_T *VarSrch(char *p_key);
    void store(int no,char *w);
    void clear();
};


#endif // _XPRG_LINE_H_



