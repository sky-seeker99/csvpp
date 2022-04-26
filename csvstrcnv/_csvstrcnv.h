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






 // # csvstrcnv class ----------------
class csvstrcnv_T{
  public:
    bool all_flg;
    bool num_flg;
    bool numex_flg;
    bool dbl_flg;
    bool single_flg;
    
    csvstrcnv_T();
    void Conv(Read64_C *in_fp,Write64_C *out_fp);

    bool Check_kanma(char *str,int max);
    bool Check_all(char *str,int max);
    bool Check_num_ex(char *str,int max);
    bool Check_num(char *str,int max);
    bool Check_dbl(char *str,int max,bool dblFlg);
    bool Check_single(char *str,int max,bool singleFlg);
    bool Check(char *str,bool singleFlg,bool dblFlg);
  };
  
  
  
