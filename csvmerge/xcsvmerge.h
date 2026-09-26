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


