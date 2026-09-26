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



