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

