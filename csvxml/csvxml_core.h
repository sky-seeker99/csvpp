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


