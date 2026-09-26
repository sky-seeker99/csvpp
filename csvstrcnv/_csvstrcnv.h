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
  
  
  
