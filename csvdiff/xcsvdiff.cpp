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

// # csv diff main ########
void CsvDiffInf_C::Main(Read64_C *in_fp1,Read64_C *in_fp2){
  int rslt1 = 0;
  int rslt2 = 0;
  bool inh1 = false;
  bool inh2 = false;
  line1 = 0;
  line2 = 0;
  w_miss_cnt=0;
  w_check_cnt=0;

  for(;;){
    if ((rslt1 != 2) && (inh1 == false)){rslt1 = keyword_check(in_fp1,csvi1); line1++;}
    if ((rslt2 != 2) && (inh2 == false)){rslt2 = keyword_check(in_fp2,csvi2); line2++;}
    if ((rslt1 == 2) && (rslt2 == 2)){break;}
    if ((w_miss_cnt == miss_cnt) && (miss_cnt != 0)){printf("missmatch count break.\n"); break;}

    if ((inh1 == true) && (rslt2 != 1)){inh1 = false;}
    if ((inh2 == true) && (rslt1 != 1)){inh2 = false;}
    if (rslt1 == 2)                  {output(false,((rslt2==0)?K_NG:K_NOP),true );            continue;}
    if (rslt2 == 2)                  {output(true ,((rslt1==0)?K_NG:K_NOP),false);            continue;}
    if ((rslt1 == 0) && (rslt2 == 0)){output(true ,K_CHK                  ,true );            continue;}
    if ((rslt1 == 1) && (rslt2 == 1)){output(true ,K_NOP                  ,true );            continue;}
    if (rslt1 == 0)                  {output(false,K_NOP                  ,true ); inh1=true; continue;}
    if (rslt2 == 0)                  {output(true ,K_NOP                  ,false); inh2=true; continue;}
  }
  
  printf("result      : ");
  if (w_miss_cnt == 0){printf("no missmatch\n");}
  else                {printf("any missmatches\n");}
  printf("check count : %d\n",w_check_cnt);
  printf("miss  count : %d\n\n",w_miss_cnt);
  
}


// # csv key check ########
int CsvDiffInf_C::keyword_check(Read64_C *in_fp,CsvAnl_C *csvi){  // =0:hit =1:no hit =2:eof
  buff = in_fp->read();
  if (buff == NULL) {return(2);}
  csvi->Exec(buff);
  if (csvi->CsvSelSu_Rd() ==  0){return(1);}
  char *str = csvi->CsvSel_Rd(0);

  // printf("str=%s line=%d cnt=%d\n",str,csvi->CsvFileLine_Get(),csvi->CsvSelSu_Rd());

  if (strcmp(str,key) != 0){return(1);}
  return(0);
}

// # output buffer ######
void CsvDiffInf_C::output_buff(CsvAnl_C *csvi,int p_line){
  sChar *s = new sChar("");
  char format[10];
//  int cnt = csvi->CsvSelSu_Rd();
  bool first = true;
  CSV_LOOP_NOCHK(csvi,ustr,NON_SP_PUSH)
    char *str = (char *)ustr;
    if (first){first=false;}
    else      {s->cat(",");}
    s->cat(str);
  LOOP_END
  
  char *w_buff = s->c_str();
  if (strlen(w_buff) > (unsigned int)wid_cnt){*(w_buff+wid_cnt-1)=0x00;}
  sprintf(format,"%%-6d|%%-%ds",wid_cnt);
  printf(format,p_line,w_buff);
  delete s;
}

// # output NULL ######
void CsvDiffInf_C::output_null(){
  char format[10];
  char null[2];
  null[0] = 0x00;
//  sprintf(format,"      |%%%dss",wid_cnt-1);
  sprintf(format,"      |%%%ds",wid_cnt);
  printf(format,null);
}

// # csv check ######
bool CsvDiffInf_C::csv_check(){
  bool ret;
  int cnt;
  int cnt1 = csvi1->CsvSelSu_Rd();
  int cnt2 = csvi2->CsvSelSu_Rd();
  if (cnt1 < cnt2){cnt = cnt1;}
  else            {cnt = cnt2;}
  bool hit = true;
  bool skip = false;  // Ver 1.02
  for(int i=0;i<cnt;i++){
    char *str1 = csvi1->CsvSel_Rd(i);
    char *str2 = csvi2->CsvSel_Rd(i);
    if (strcmp(str1,"[SKIP]") == 0){skip = true;} // Ver 1.02
	if (strcmp(str2,"[SKIP]") == 0){skip = true;} // Ver 1.02

	if (intMode == false) {
	  if (strcmp(str1,str2) != 0){hit = false; break;}
	}
	else {
	  w1->set(str1);
	  w2->set(str2);

	  w1->push();
	  w2->push();

	  __int64 i1 = SujiConvSuper64(w1->c_str());
	  __int64 i2 = SujiConvSuper64(w2->c_str());
	  if (i1 != i2) {
		hit = false;
		break;  
	  }
	}


  }
  if ((hit  == true) && (cnt1 == cnt2)){printf("|o|");               ret = true;}
  else if (skip == true)               {printf("|-|");               ret = true;}  // Ver 1.02
  else                                 {printf("|x|"); w_miss_cnt++; ret = false;}
  w_check_cnt++;
  return(ret);
}


// # detail #####
void CsvDiffInf_C::detail_output(){
  if (d_flag == false){return;}

  sChar *s = new sChar("");

  int cnt = csvi1->CsvSelSu_Rd();
  for(int i=0;i<cnt;i++){
    char *str = csvi1->CsvSel_Rd(i);
    if (i!=0){s->cat(",");}
    s->cat(str);
  }

  char *buff = s->c_str();
  printf("%s\n",buff);

  s->set("");
  cnt = csvi2->CsvSelSu_Rd();
  for(int i=0;i<cnt;i++){
    char *str = csvi2->CsvSel_Rd(i);
    if (i!=0){s->cat(",");}
    s->cat(str);
  }

  buff = s->c_str();
  printf("%s\n",buff);

  delete s;
}

// # output #####
void CsvDiffInf_C::output(bool on1,int kbn,bool on2){
  bool flg = false;
  if (on1){output_buff(csvi1,line1);} else {output_null();}
  if      (kbn == K_CHK){csv_check(); flg=true;}
  else if (kbn == K_NOP){printf("| |");}
  else if (kbn == K_NG ){printf("|x|"); w_miss_cnt++; w_check_cnt++; flg=true;}
  if (on2){output_buff(csvi2,line2);} else {output_null();}
  printf("\n");
  if (flg){detail_output();}
}


