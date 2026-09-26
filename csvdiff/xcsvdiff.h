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

//---------------------------------------------------------------------------
#define K_CHK 0
#define K_NOP 1
#define K_NG  2

class CsvDiffInf_C{
  public:
    unsigned char *buff;
    CsvAnl_C *csvi1;
    CsvAnl_C *csvi2;
    int line1;
    int line2;
    int w_miss_cnt;
    int w_check_cnt;
    // parameter 
    int   miss_cnt;
    int   wid_cnt;
    char *key;
	bool  d_flag;
	bool  intMode;  // Ver 1.03
	sChar *w1;
	sChar *w2;

    void Main(Read64_C *in_fp1,Read64_C *in_fp2);

    CsvDiffInf_C(bool dbl_no_cut,int p_miss_cnt,int p_wid_cnt,char *p_key,bool p_d_flag){
      miss_cnt   = p_miss_cnt;
      wid_cnt    = p_wid_cnt;
      key        = p_key;
      d_flag     = p_d_flag;
      w_miss_cnt =0;
      w_check_cnt=0;
      csvi1 = new CsvAnl_C;
      csvi2 = new CsvAnl_C;
      if (dbl_no_cut) {csvi1->dbl_nocut_mode(); csvi2->dbl_nocut_mode();}
      line1 = 0;
	  line2 = 0;
	  intMode = false; // Ver 1.03
	  w1 = new sChar("");
	  w2 = new sChar("");
	}
    ~CsvDiffInf_C(){
      delete csvi1;
	  delete csvi2;
	  delete w1;
	  delete w2;
    }
    
  private:
    void output(bool on1,int kbn,bool on2);
    void detail_output();
    bool csv_check();
    void output_null();
    void output_buff(CsvAnl_C *csvi,int p_line);
    int  keyword_check(Read64_C *in_fp,CsvAnl_C *csvi);  // =0:hit =1:no hit =2:eof
    
};


