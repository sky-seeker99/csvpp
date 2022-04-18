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
//
//  Variable Calcration
//

#ifndef _T_CALC_H_
#define _T_CALC_H_

#include "../csvpp_xbase/t_expression_instance.h"
#include "xobject.h"

// # Siki Cell --------------
template <class T_TYPE,class T_EXP>
class CalcCell_T{
  public:
    sChar             *siki_str;
    expList_T<T_TYPE> *siki;
    bool               okFlag;
    CalcCell_T(char *str,T_EXP *calcCore){
      siki_str = new sChar(str);
      siki     = calcCore->compile(str);
      okFlag   = calcCore->okCheck();
    }
    ~CalcCell_T(){
       delete siki_str;
    }
};


// # Calc Interface ---------------
template <class T_TYPE,class T_EXP>
class CalcTemplate_T{
  public:
    T_EXP                                     *calcCore;  // Expression Core
    VariableListHeader_C                      *s_it;      // Mem Interface
    VariableList_T<CalcCell_T<T_TYPE,T_EXP> > *calc_fp;   // siki List  
    varCtl_C                                  *var_ctl;

    CalcTemplate_T(varCtl_C *var){
      calcCore = new T_EXP;
      s_it     = new VariableListHeader_C;
      calc_fp  = new VariableList_T<CalcCell_T<T_TYPE,T_EXP> >(s_it);
      var_ctl  = var;
    }
    ~CalcTemplate_T(){
      delete calcCore;
      delete calc_fp;
      delete s_it;
    }

    T_TYPE VarToInt(char *key){
      char *str;
      T_TYPE ans = (T_TYPE)0;

      if (convStrNumCheck<T_TYPE>(key) == true){
        ans = convStrNum<T_TYPE>(key);
      }
      else {
        VarCell_T *vc = var_ctl->srch(key);
        if (vc == NULL){ans = (T_TYPE)0;}
        else           {ans = convStrNum<T_TYPE>(vc->atai->c_str());}
      }
      return(ans);
    }

    T_TYPE CalcExecute(char *str){
      sp_push3(str);
      CalcCell_T<T_TYPE,T_EXP> *cc;
      s_it->srch_key = str;
      if (calc_fp->mem_srch() == 0){
        cc = calc_fp->mem_link_ptr_rd();
      }
      else {
        cc = new CalcCell_T<T_TYPE,T_EXP>(str,calcCore);
        s_it->alloc_ptr = cc;
        calc_fp->mem_srch_alloc();
        calcCore->codeExec_Init();
      }
      if (cc->okFlag == false){return((T_TYPE)0);}

      bool flag=true;

//calcCore->varListMon();
//calcCore->codeListMon(cc->siki);

      for(;;){
        char *key = calcCore->codeExecBefore_begin(cc->siki,&flag);
        if (key == NULL){break;}
        T_TYPE val = VarToInt(key);
        calcCore->codeExecBefore_end(val);
      }
      T_TYPE ans = calcCore->codeExec(cc->siki,false);
//      T_TYPE ans = calcCore->codeExec(cc->siki,true);
      return(ans);
    }

  };

#endif // _T_CALC_H_
