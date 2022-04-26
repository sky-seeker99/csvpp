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

// #wr,key,string
// #file,file_name
// #key,key


void text_create_C::csvRead(Read64_C *in_fp){
  CsvAnl_C *csvi = new CsvAnl_C;
  for(;;){
	unsigned char *buff = in_fp->read();
	if (buff == NULL) {break;}
	csvi->Exec(buff);

	CSV_LOOP(csvi,str,SP_PUSH)
	  if      (strcmp(str,"#wr_file") == 0){wr_fileRtn(csvi);}
	  else if (strcmp(str,"#write"  ) == 0){wrRtn(csvi,false);}
	  else if (strcmp(str,"#writeln") == 0){wrRtn(csvi,true);}
	  else if (strcmp(str,"#file"   ) == 0){fileRtn(csvi);}
	  else if (strcmp(str,"#key"    ) == 0){keyRtn(csvi);}
	  else if (strcmp(str,"#sp"     ) == 0){spRtn(csvi,0);}
	  else if (strcmp(str,"#sp--"   ) == 0){spRtn(csvi,1);}
	  else if (strcmp(str,"#sp++"   ) == 0){spRtn(csvi,2);}
	  else if (strcmp(str,"#sp_push") == 0){spPushRtn(csvi);}
	  else if (strcmp(str,"#sp_pop" ) == 0){spPopRtn(csvi);}
	  break;
	LOOP_END
  }
  delete csvi;
}

void text_create_C::spPushRtn(CsvAnl_C *csvi){
  char *key = NULL;
  char *www = NULL;
  CSV_LOOP(csvi,str,NON_SP_PUSH)
	if (key == NULL){key = (char*)str; continue;}
	if (www == NULL){www = (char*)str; continue;}
  LOOP_END
  if (www==NULL) {
	return;
  }

  // key search
  int num = 0;
  it->srch_key = key;
  if (mem_fp->mem_srch() == 0){
	w_cell = (text_cell_C *)mem_fp->mem_link_ptr_rd();
	num = w_cell->sp_num;
  }

  // num store
  it->srch_key = www;
  if (save_fp->mem_srch() == 0){
	w_save = (save_sp_C *)save_fp->mem_link_ptr_rd();
	w_save->num = num;
  }
  else {
	w_save = new save_sp_C(www,num);
	it->alloc_ptr = (MM_PTR_T *)w_save;
	save_fp->mem_srch_alloc();
  }
}


void text_create_C::spPopRtn(CsvAnl_C *csvi){
  char *key = NULL;
  char *www = NULL;

  CSV_LOOP(csvi,str,NON_SP_PUSH)
	if (key == NULL){key = (char*)str; continue;}
	if (www == NULL){www = (char*)str; continue;}
  LOOP_END
  if (www==NULL) {
	return;
  }

  // key search
  it->srch_key = www;
  if (save_fp->mem_srch() != 0){return;}
  w_save = (save_sp_C *)save_fp->mem_link_ptr_rd();

  // num get 
  it->srch_key = key;
  if (mem_fp->mem_srch() == 0){
	w_cell = (text_cell_C *)mem_fp->mem_link_ptr_rd();
	w_cell->spSet(w_save->num);
  }

}



void text_create_C::spRtn(CsvAnl_C *csvi,int mode){
  char *key = NULL;
  char *www = NULL;
  CSV_LOOP(csvi,str,NON_SP_PUSH)
	if (key == NULL){key = (char*)str; continue;}
	if (www == NULL){www = (char*)str; break;}
  LOOP_END
  if (www==NULL) {
	return;
  }
  int num = SujiConvEx(www);
  if (num < 0) {
      return;
  }

  // key search
  it->srch_key = key;
  if (mem_fp->mem_srch() == 0){
    w_cell = (text_cell_C *)mem_fp->mem_link_ptr_rd();
  }
  else {
    w_cell = new text_cell_C(key);
    it->alloc_ptr = (MM_PTR_T *)w_cell;
    mem_fp->mem_srch_alloc();
  }
  if (mode == 0) {
    w_cell->spSet(num);
  }
  else if (mode == 1) {
    w_cell->spSetMinus(num);
  }
  else if (mode == 2) {
    w_cell->spSetPlus(num);
  }

}

void text_create_C::wrRtn(CsvAnl_C *csvi,bool flg){
  char *key = NULL;
  char *www = NULL;
  CSV_LOOP(csvi,str,NON_SP_PUSH)
    if (key == NULL){key = (char*)str; continue;}
    if (www == NULL){www = (char*)str; break;}
  LOOP_END
  if (key==NULL) {
    return;  
  }
  // key search
  it->srch_key = key;
  if (mem_fp->mem_srch() == 0){
    w_cell = (text_cell_C *)mem_fp->mem_link_ptr_rd();
  }
  else {
    w_cell = new text_cell_C(key);
    it->alloc_ptr = (MM_PTR_T *)w_cell;
    mem_fp->mem_srch_alloc();
  }
  // string store
  if (www==NULL) {
    www="";  
  }
  sChar *s = new sChar("");
  if (flg) {
    s->set("@");
  }
  else{
    s->set("-");
  }
  if (w_cell->firstFlg) {
	char *sp = w_cell->spGet();
    s->cat(sp);
    w_cell->firstFlg = false;
  }
  s->cat(www);
  w_cell->ary->alloc_ptr = (unsigned char *)s;
  w_cell->ary->mem_alloc();
  if (flg) {
    w_cell->firstFlg = true;
  }
}

void text_create_C::wr_fileRtn(CsvAnl_C *csvi){
  char *key = NULL;
  char *www = NULL;
  CSV_LOOP(csvi,str,NON_SP_PUSH)
	if (key == NULL){key = (char*)str; continue;}
	if (www == NULL){www = (char*)str; break;}
  LOOP_END
  if (www==NULL) {
	return;
  }
  // key search
  it->srch_key = key;
  if (mem_fp->mem_srch() == 0){
	w_cell = (text_cell_C *)mem_fp->mem_link_ptr_rd();
  }
  else {
	w_cell = new text_cell_C(key);
	it->alloc_ptr = (MM_PTR_T *)w_cell;
	mem_fp->mem_srch_alloc();
  }

  Read64_C *in_fp = new  Read64_C(www,"rt",10240);
  if (in_fp->okCheck()) {
	for(;;){
	  unsigned char *b = in_fp->read();
	  if (b == NULL) {break;}
	  sChar *s = new sChar("");
	  s->set("@");
	  if (w_cell->firstFlg) {
		char *sp = w_cell->spGet();
		s->cat(sp);
		w_cell->firstFlg = false;
	  }
	  s->cat(b);
	  w_cell->ary->alloc_ptr = (unsigned char *)s;
	  w_cell->ary->mem_alloc();
	  w_cell->firstFlg = true;
	}
  }


}



void text_create_C::fileRtn(CsvAnl_C *csvi){
  CSV_LOOP(csvi,str,NON_SP_PUSH)
    g_file->set((char *)str);
    break;
  LOOP_END
}

void text_create_C::keyRtn(CsvAnl_C *csvi){
  char *key = NULL;
  CSV_LOOP(csvi,str,NON_SP_PUSH)
    if (key == NULL){key = (char*)str; break;}
  LOOP_END
  // key search
  if (strcmp(g_file->c_str(),"") == 0){return;}
  if (key==NULL) {return;}
  it->srch_key = g_file->c_str();
  if (out_fp->mem_srch() == 0){
    w_cell = (text_cell_C *)out_fp->mem_link_ptr_rd();
  }
  else {
    w_cell = new text_cell_C(g_file->c_str());
    it->alloc_ptr = (MM_PTR_T *)w_cell;
    out_fp->mem_srch_alloc();
  }

  // string store
  w_cell->ary->alloc_ptr = (unsigned char *)new sChar(key);
  w_cell->ary->mem_alloc();
}

void text_create_C::output(){
  text_cell_C *file_cell;
  sChar *key;
  sChar *str;


  MEM_LOOP(file_cell,text_cell_C,out_fp)
    Write64_C *out_fp = new Write64_C(file_cell->key->c_str(),"wt",1024);
    if (out_fp->okCheck() == false){delete out_fp; printf("%s cannot open.\n",file_cell->key->c_str()); continue;}
    printf("%s file open.\n",file_cell->key->c_str());
    ARY_LOOP(key,sChar,file_cell->ary)
      it->srch_key = key->c_str();
      if (mem_fp->mem_srch() != 0){printf(" [%s] not found.\n",key->c_str()); continue;}
      printf(" [%s] output.\n",key->c_str());

      w_cell = (text_cell_C *)mem_fp->mem_link_ptr_rd();
      ARY_LOOP(str,sChar,w_cell->ary)
        char *w = str->c_str();
        if (*w == '@') {
          out_fp->writeln(w+1);
        }
        else {
          out_fp->write(w+1);
        }
      LOOP_END
//printf("g_ary_get_ptr = %d  g_ary_store_ptr = %d\n",file_cell->ary->g_ary_get_ptr,file_cell->ary->g_ary_store_ptr);



    LOOP_END
    delete out_fp;
  LOOP_END
}



