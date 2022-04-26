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

// # constructor #####
csvstrcnv_T::csvstrcnv_T(){
  all_flg    = false;
  num_flg    = false;
  numex_flg  = false;
  dbl_flg    = false;
  single_flg = false;

}

// # Convert #####
void csvstrcnv_T::Conv(Read64_C *in_fp,Write64_C *out_fp){
  in_fp->csvModeSet();
  CsvAnl_C *csvi = new CsvAnl_C;

  for(;;){
	unsigned char *buff = in_fp->read();
	if (buff == NULL) {break;}
	csvi->Exec(buff);
    bool first=true;
 	CSV_LOOP_NOCHK(csvi,ustr,NON_SP_PUSH)
      if (first){first=false;}
      else      {out_fp->write(",");}
      char *str = (char *)ustr;
      if (*str == 0x00){continue;}

      bool singleFlg = false;
      if ((*str == '\'') && (*(str+strlen(str)-1) == '\'')){
        singleFlg= true;
        *(str+strlen(str)-1) = 0x00;
        char *ww = new char[strlen(str)+1];
        strcpy(ww,str+1);
        strcpy(str,ww);
        delete [] ww;
      }
      bool dblFlg = csvi->dblFlgGet();
      if (Check(str,singleFlg,dblFlg)){
        out_fp->write("=\""); 
        out_fp->csvWrite_non_gawa(str); 
        out_fp->write("\""); 
        continue;
      }
      
      if (singleFlg){out_fp->write("'");}
      if (dblFlg   ){out_fp->write("\"");}
      out_fp->csvWrite_non_gawa(str);
      if (dblFlg   ){out_fp->write("\"");}
      if (singleFlg){out_fp->write("'");}
    LOOP_END
    if ((in_fp->return0dGet()) || (in_fp->return0aGet())){out_fp->writeln("");}
  }

  delete csvi;
}

// # Check (kannma)#####
bool csvstrcnv_T::Check_kanma(char *str,int max){
  bool ret = false;
  for(int i=0;i<max;i++){
    if (*(str+i) == ','){ret = true; break;}
  }
  return(ret);
}

// # Check (all)#####
bool csvstrcnv_T::Check_all(char *str,int max){
  return(true);
}


// # Check (num+':'+'/')#####
bool csvstrcnv_T::Check_num_ex(char *str,int max){
  bool ret=true;
  for(int i=0;i<max;i++){
    if ((*(str+i) >= '0') && (*(str+i) <= '9')) {continue;}
    if ((*(str+i) == '/') || (*(str+i) == ':')) {continue;}
    ret = false;
    break;
  }
  return(ret);
}


// # Check (num)#####
bool csvstrcnv_T::Check_num(char *str,int max){
  bool ret=true;
  for(int i=0;i<max;i++){
    if ((*(str+i) >= '0') && (*(str+i) <= '9')) {continue;}
    ret = false;
    break;
  }
  return(ret);
}


// # Check (double / single)#####
bool csvstrcnv_T::Check_dbl(char *str,int max,bool dblFlg){
  if (dblFlg){return(true);}
  return(false);
}

bool csvstrcnv_T::Check_single(char *str,int max,bool singleFlg){
  if (singleFlg){return(true);}
  return(false);
}



// # Check #####
bool csvstrcnv_T::Check(char *str,bool singleFlg,bool dblFlg){
  int max = strlen(str);
  if (max == 0){return(false);}
  if (Check_kanma(str,max)){return(false);}
  
  if (all_flg      && Check_all(str,max)){return(true);}
  if (num_flg      && Check_num(str,max)){return(true);}
  if (numex_flg    && Check_num_ex(str,max)){return(true);}
  if (dbl_flg      && Check_dbl(str,max,dblFlg)){return(true);}
  if (single_flg   && Check_single(str,max,singleFlg)){return(true);}
  return(false);
}



