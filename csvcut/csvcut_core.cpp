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


// # parameter get ######
void CsvCut_C::noStore(int no){
  int *w = new int;
  *w = no;
  parm->mem_alloc((unsigned char*)w);
}

void CsvCut_C::parmGet(char *p_argv){
  sChar *sstr;
  int sv_top=0;
  bool renzoku_flg = false;

  ssi->Main(p_argv);
  for(int i=0;i<ssi->GetSu();i++){
    sstr = ssi->Get(i);
    if (strcmp(sstr->c_str(),"-") == 0){renzoku_flg = true; continue;}
    if (renzoku_flg){
      renzoku_flg = false;
//      int ee = sstr->c_int();
      int ee = SujiConvEx(sstr->c_str());
      for(int j=sv_top+1;j<=ee;++j){
        noStore(j);
      }
      continue;
    }
//    sv_top = sstr->c_int();
    sv_top = SujiConvEx(sstr->c_str());
    noStore(sv_top);
  }
}



// # Main ########
void CsvCut_C::Main(Read64_C *in_fp,Write64_C *out_fp){
  CsvAnl_C *csvi = new CsvAnl_C;
  csvi->dbl_nocut_mode();

  for(;;){
    unsigned char *buff = in_fp->read();
    if (buff == NULL) {break;}
    csvi->Exec(buff);
    bool first=true;
    int *w;
    ARY_LOOP(w,int,parm)
      char *str = csvi->CsvSel_Rd(*w-1);
      if (first){first=false;}
      else      {out_fp->write((unsigned char *)",");}
      if (str != NULL) {
        out_fp->write(str);
      }
    LOOP_END
    out_fp->writeln((unsigned char *)"");
  }  
  delete csvi;
}



