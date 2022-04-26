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



