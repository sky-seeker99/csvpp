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
