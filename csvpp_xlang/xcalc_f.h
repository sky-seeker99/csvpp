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
//  Variable Calcration
//

#ifndef _XCALC_F_H_
#define _XCALC_F_H_

#include "t_calc.h"
#include "xvar_ctl.h"

// # Calc Interface ---------------
class CalcInf_f_T : public CalcTemplate_T<double,ExpressionFloat_T<double> > {
  public:
    CalcInf_f_T(varCtl_C *var) : CalcTemplate_T<double,ExpressionFloat_T<double> >(var){}
};

#endif // _XCALC_F_H_
