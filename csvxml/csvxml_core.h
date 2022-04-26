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
// interface
//
class csvxml_inf_C{
  public:
    sChar       *total_tag;   // 全体のタグ名
    sChar       *record_tag;  // レコードのタグ名
    VariableArray_C *tag_ary; // タグ名 cell:sChar
    CsvAnl_C        *csvi;    // CSV解析
    bool         escapeFlag;  // エスケープ
	VariableArea_C  *area;
    csvxml_inf_C(){
      total_tag   = new sChar("DOC");
      record_tag  = new sChar("REC");
      tag_ary     = new VariableArray_C(10);
      csvi        = new CsvAnl_C;
      escapeFlag  = true;
      area        = new VariableArea_C(100);
    }
    ~csvxml_inf_C(){
      sChar *w_str;
      ARY_LOOP(w_str,sChar,tag_ary) delete w_str; LOOP_END 
      delete total_tag;
      delete record_tag;
      delete tag_ary;
      delete csvi;
      delete area;
    }
    void CsvRead(Read64_C *in_fp);
	char *escape_change(char *str);
    void recordTag();
    void totalTag();
    void tag();
    void Main(Read64_C *header_fp,Read64_C *csv_fp,Write64_C *out_fp);
};


