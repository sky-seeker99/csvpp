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

#ifndef _XCALC_H_
#define _XCALC_H_

#include "t_calc.h"
#include "xvar_ctl.h"

// # Calc Interface ---------------
class CalcInf_T : public CalcTemplate_T<int,Expression_T<int> > {
  public:
    CalcInf_T(varCtl_C *var) : CalcTemplate_T<int,Expression_T<int> >(var){}
};

#endif // _XCALC_H_
