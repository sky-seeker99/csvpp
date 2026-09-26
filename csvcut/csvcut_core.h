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


