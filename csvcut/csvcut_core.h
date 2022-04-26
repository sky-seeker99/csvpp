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

//---------------------------------------------------------------------------

class CsvCut_C{
  public:
    VariableArray_C *parm;
    StrSrchInf_T *ssi;

    CsvCut_C(){
      parm  = new VariableArray_C(50);
      ssi = new StrSrchInf_T;
      ssi->Set(','); 
      ssi->Set('-'); 
      ssi->SetFlg();
    } 
  
    ~CsvCut_C(){
       delete ssi;
       int *w;
       ARY_LOOP(w,int,parm) delete w; LOOP_END
       delete parm;
    }

  void noStore(int no);
  void parmGet(char *p_argv);
  void Main(Read64_C *in_fp,Write64_C *out_fp);
};


