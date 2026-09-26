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
 

bool g_dbl_no_cut=false;
 
void cellStringReplace(Read64_C *in_fp,Write64_C *out_fp,char *srch_key,char *rep_key){
  CsvAnl_C *csvi = new CsvAnl_C;
  sCharGrep *w = new sCharGrep("");
  if (g_dbl_no_cut) {csvi->dbl_nocut_mode();}
  for(;;){
	unsigned char *buff = in_fp->read();
	if (buff == NULL) {break;}
	csvi->Exec(buff);
    bool first=true;
	CSV_LOOP_NOCHK(csvi,str,NON_SP_PUSH)
      w->set((char *)str);
      w->replace_all(srch_key,rep_key);
      if (first) {first=false;}
      else       {out_fp->write((unsigned char *)",");}
      if (g_dbl_no_cut){
        out_fp->write((unsigned char *)w->c_str());
      }
      else {
        out_fp->csvWrite((unsigned char *)w->c_str());
      }
    LOOP_END

    if ((in_fp->return0dGet()) || (in_fp->return0aGet())){out_fp->writeln((unsigned char *)"");}
  }



  delete csvi;
  delete w;
}

 
void cellStringReplaceDouble(Read64_C *in_fp,Write64_C *out_fp,char *srch_key,char *srch_key2,char *rep_key){
  CsvAnl_C *csvi = new CsvAnl_C;
  if (g_dbl_no_cut) {csvi->dbl_nocut_mode();}
  sCharGrep *w = new sCharGrep("");
  for(;;){
	unsigned char *buff = in_fp->read();
	if (buff == NULL) {break;}
	csvi->Exec(buff);
    bool first=true;
	CSV_LOOP_NOCHK(csvi,str,NON_SP_PUSH)
      w->set((char *)str);
      w->replace_all(srch_key,rep_key);
      w->replace_all(srch_key2,rep_key);
      if (first) {first=false;}
      else       {out_fp->write((unsigned char *)",");}
      if (g_dbl_no_cut){
        out_fp->write((unsigned char *)w->c_str());
      }
      else {
        out_fp->csvWrite((unsigned char *)w->c_str());
      }
    LOOP_END

    if ((in_fp->return0dGet()) || (in_fp->return0aGet())){out_fp->writeln((unsigned char *)"");}
  }



  delete csvi;
  delete w;
}
