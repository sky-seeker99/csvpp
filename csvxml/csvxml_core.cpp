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

// # CSV STORE #####
void csvxml_inf_C::CsvRead(Read64_C *in_fp){
  if (in_fp == NULL) {return;}
  if (in_fp->okCheck() == false){return;}

  for(;;){
    unsigned char *buff = in_fp->read();
    if (buff == NULL) {break;}
    csvi->Exec(buff);

    CSV_LOOP(csvi,str,SP_PUSH)
      if      (strcmp(str,"#total_tag"  ) == 0){totalTag();}
      else if (strcmp(str,"#record_tag" ) == 0){recordTag();}
      else if (strcmp(str,"#tag"        ) == 0){tag();}
      break;
    LOOP_END
  }
}


// #total_tag
void csvxml_inf_C::totalTag(){
  CSV_LOOP(csvi,str,SP_PUSH)
    total_tag->set((char *)str);
    break;
  LOOP_END
}

// #record_tag
void csvxml_inf_C::recordTag(){
  CSV_LOOP(csvi,str,SP_PUSH)
    record_tag->set((char *)str);
    break;
  LOOP_END
}

// #tag
void csvxml_inf_C::tag(){
  CSV_LOOP(csvi,str,SP_PUSH)
    tag_ary->alloc_ptr = (unsigned char *)new sChar((char *)str);
    tag_ary->mem_alloc();
    break;
  LOOP_END
}


// # MAIN ROUTINE #####
void csvxml_inf_C::Main(Read64_C *header_fp,Read64_C *csv_fp,Write64_C *out_fp){
  if (out_fp->okCheck() == false){return;}

  // header
  if (header_fp != NULL) {
    if (header_fp->okCheck()) {
      for(;;){
        unsigned char *buff = header_fp->read();
        if (buff == NULL) {break;}
        out_fp->writeln(buff);
      }
    }
  }

  if (csv_fp->okCheck() == false){return;}

  // csv -> xml
  out_fp->write("<");
  out_fp->write(total_tag->c_str());
  out_fp->writeln(">");
  for(;;){
    unsigned char *buff = csv_fp->read();
    if (buff == NULL) {break;}
    csvi->Exec(buff);
    
    out_fp->write("<");
    out_fp->write(record_tag->c_str());
    out_fp->write(">");
    
    char w[25];
    int num=0;
    CSV_LOOP_NOCHK(csvi,ustr,NON_SP_PUSH)
      sChar *tag = (sChar *)tag_ary->get(num);
  	  ustr = escape_change((char *)ustr);
      if (tag == NULL){
        sprintf(w,"TAG%d",num);
        out_fp->write("<");
        out_fp->write(w);
        out_fp->write(">");
        out_fp->write(ustr);
        out_fp->write("</");
        out_fp->write(w);
        out_fp->write(">");
      }
      else {
        out_fp->write("<");
        out_fp->write(tag->c_str());
        out_fp->write(">");
        out_fp->write(ustr);
        out_fp->write("</");
        out_fp->write(tag->c_str());
        out_fp->write(">");
      }
      num++;
    LOOP_END

    out_fp->write("</");
    out_fp->write(record_tag->c_str());
    out_fp->writeln(">");

  }
  out_fp->write("</");
  out_fp->write(total_tag->c_str());
  out_fp->writeln(">");
}

char *csvxml_inf_C::escape_change(char *str){
	if (escapeFlag == false){return(str);}
	int len = strlen(str);
	area->init();
	for(int i=0;i<len;i++){
		if      (*(str+i) == '<' ){area->set_n("&lt;"  ,4);}
		else if (*(str+i) == '>' ){area->set_n("&gt;"  ,4);}
		else if (*(str+i) == '&' ){area->set_n("&amp;" ,5);}
		else if (*(str+i) == '\"'){area->set_n("&quot;",6);}
		else if (*(str+i) == '\''){area->set_n("&apos;",6);}
		else                      {area->set(*(str+i));}
	}
	area->set(0x00);

    //printf("%s\n",area->cc_str());
	return(area->cc_str());
}
