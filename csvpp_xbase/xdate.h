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
// Date/Time Class
//
#ifndef _XDATE_H_
#define _XDATE_H_

//#include "xstr.h"
#include "ztool.h"
#include "ztoken.h"

// # Date Class -----------------
class Date_T{
  public:
    int yy;    // 年
    int mm;    // 月
    int dd;    // 日
    int value; // 値
    StrSrchInf_T *ssc; // String Separate Control
    Date_T();
    ~Date_T();
    int  Conv(int y,int m,int d);
    bool StrSet(char *str);
    void IntSet(int p_value);
  };

// # Time Class ------------------
class Time_T{
  public:
  int hh;    // 時
  int mm;    // 分
  int ss;    // 秒
  int value; // 値
  StrSrchInf_T *ssc; // String Separate Control
  Time_T();
  ~Time_T();
  int  Conv(int h,int m,int s);
  bool StrSet(char *str);
  void IntSet(int p_value);
  };


#endif // _XDATE_H_
