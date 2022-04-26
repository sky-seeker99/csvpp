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


