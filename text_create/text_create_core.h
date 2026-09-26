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
// text create cell
//
class text_cell_C{
  public:
    sChar *key;
    VariableArea_C *left_sp; // left space
    int sp_num;
    VariableArray_C *ary;   // cell:sChar
    bool firstFlg;
    text_cell_C(char *p_key){
      key = new sChar(p_key);
      ary = new VariableArray_C(50);
      left_sp = new VariableArea_C(10);
      left_sp->set(0x00);
      sp_num = 0;
      firstFlg = true;
    }

    ~text_cell_C(){
      delete left_sp;
      sChar *w;
      delete key;
      ARY_LOOP(w,sChar,ary) delete w; LOOP_END
      delete ary;
    }
    char *spGet(){
      return(left_sp->cc_str());
    }
    char *spSet(int num){
      sp_num = num;
      left_sp->init();
      for(int i=0;i<num;i++){left_sp->set(' ');}
      left_sp->set(0x00);
      return(left_sp->cc_str());
    }
    char *spSetPlus(int num){
      int i = sp_num + num;
      return(spSet(i));
    }
    char *spSetMinus(int num){
      int i = sp_num - num;
      if (i < 0) {
        i = 0;  
      }
      return(spSet(i));
    }

};

class save_sp_C{
  public:
    sChar *key;
	int num;
	save_sp_C(char *p_key,int p_num){
	  key = new sChar(p_key);
	  num = p_num;
	}
	~save_sp_C(){
      delete key;
	}
};


//
// text create interface
//
class text_create_C{
  public:
    MemHeader_T *it;
    MEM_FP      *mem_fp; // cell:text_cell_C
	MEM_FP      *out_fp; // cell:text_cell_C
	MEM_FP      *save_fp;
	text_cell_C *w_cell;
	save_sp_C   *w_save;
	sChar       *g_file;

	void output();
	void spRtn(CsvAnl_C *csvi,int mode);
	void keyRtn(CsvAnl_C *csvi);
	void fileRtn(CsvAnl_C *csvi);
	void wrRtn(CsvAnl_C *csvi,bool flg);
	void csvRead(Read64_C *in_fp);
	void wr_fileRtn(CsvAnl_C *csvi);
	void spPushRtn(CsvAnl_C *csvi);
	void spPopRtn(CsvAnl_C *csvi);

	text_create_C(){
	  it = new MemHeader_T;
	  mem_fp = new MEM_FP(it);
	  out_fp = new MEM_FP(it);
	  save_fp= new MEM_FP(it);
	  g_file = new sChar("");
	}
	~text_create_C(){
	  MEM_LOOP(w_cell,text_cell_C,mem_fp) delete w_cell; LOOP_END
	  MEM_LOOP(w_cell,text_cell_C,out_fp) delete w_cell; LOOP_END
	  MEM_LOOP(w_save,save_sp_C  ,save_fp) delete w_save; LOOP_END
	  delete mem_fp;
	  delete out_fp;
	  delete save_fp;
      delete it;
      delete g_file;
    }
};



