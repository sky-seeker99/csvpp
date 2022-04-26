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

// # file store ########
void CsvMergeInf_C::Store(char *file){
  Read64_C *in_fp = new Read64_C(file,"csv",10240);
  if (in_fp->okCheck() == false){printf("file open error. (file=%s)\n",file); delete in_fp; return;}
  CsvAnl_C *csvi = new CsvAnl_C;
  csvi->dbl_nocut_mode();

  int width = 0;
  int line_max = 0;
  for(;;){
	unsigned char *buff = in_fp->read();
	if (buff == NULL) {break;}
	csvi->Exec(buff);
	if (width < csvi->CsvSelSu_Rd()){width = csvi->CsvSelSu_Rd();}
    //if ((in_fp->return0dGet()) || (in_fp->return0aGet())){line_max++;}
    line_max++;
  }

//printf("%s %d %d\n",file,width,line_max);

  ary_fp->alloc_ptr = (unsigned char  *)new CsvFileCell_C(file,width,line_max);
  ary_fp->mem_alloc();
  delete csvi;
  delete in_fp;
}

// # Main ########
void CsvMergeInf_C::Main(){
  CsvFileCell_C *cf;
  int line_max = 0;
  // file open
  ARY_LOOP(cf,CsvFileCell_C,ary_fp)
    cf->fileOpen();
    if (line_max < cf->line_max){line_max = cf->line_max;}
  LOOP_END

  // merge
  CsvAnl_C *csvi = new CsvAnl_C;
  csvi->dbl_nocut_mode();

  for(int line=0;line<line_max;line++){
    bool first_flg=true;
    ARY_LOOP(cf,CsvFileCell_C,ary_fp)
      if (cf->eofFlg){
        for(int i=0;i<cf->width;i++){
          if (first_flg){first_flg=false;}
          else          {printf(",");}
        }
        continue;
      }
      unsigned char *buff = cf->in_fp->read();
      if (buff == NULL) {
        cf->eofFlg = true;
        for(int i=0;i<cf->width;i++){
          if (first_flg){first_flg=false;}
          else          {printf(",");}
        }
        continue;
      }

      csvi->Exec(buff);
      for(int i=0;i<cf->width;i++){
        char *w = csvi->CsvSel_Rd(i);
        if (first_flg){first_flg=false;}
        else         {printf(",");}
        if (w == NULL) {printf("");}
        else           {printf("%s",w);}
      }

    LOOP_END
    printf("\n");
  }  
  delete csvi;
}

