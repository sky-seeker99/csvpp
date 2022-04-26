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

class CsvFileCell_C{
  public:
    sChar *file_name;
    int  width;
    int  line_max;
    Read64_C *in_fp;
    bool eofFlg;

    CsvFileCell_C(char *file,int p_width,int p_line_max){
      file_name = new sChar(file);
      width     = p_width;
      line_max  = p_line_max;
      in_fp     = NULL;
      eofFlg    = true;
    }
    ~CsvFileCell_C(){
      delete file_name;
      if (in_fp != NULL){delete in_fp;}
    }
    fileOpen(){
      in_fp = new Read64_C(file_name->c_str(),"csv",10240);
      if (in_fp->okCheck()) {
        eofFlg = false;  
      }
    }
};

class CsvMergeInf_C{
  public:
    VariableArray_C *ary_fp; // CsvFileCell_C

    void Main();
    void Store(char *file);

    CsvMergeInf_C(){
      ary_fp = new VariableArray_C(20);
    }

    ~CsvMergeInf_C(){
      CsvFileCell_C *cf;
      ARY_LOOP(cf,CsvFileCell_C,ary_fp) delete cf; LOOP_END
      delete ary_fp;
    }
    
};


