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
