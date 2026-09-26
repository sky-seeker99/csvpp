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

//
//  menu list control
//
// constructor / destructor
menu_cel::menu_cel(char *p_path){
  FileNameSep_T *fn;
  fn = new FileNameSep_T;
  path = new sChar(p_path);
  fn->Set(p_path);
  key  = new sChar(fn->FileGet());
  delete fn;
}
menu_cel::~menu_cel(){
  delete path;
  delete key;
}

// constructor / destructor
menu_inf::menu_inf(){
  it = new MemHeader_T;
  mem_fp = new MEM_FP(it);
}
menu_inf::~menu_inf(){
  menu_cel *c;
  MEM_LOOP(c,menu_cel,mem_fp) delete c; LOOP_END
  delete mem_fp;
  delete it;
}

// add
char *menu_inf::add_cel(char *path){
  menu_cel *c;
  c = new menu_cel(path);
  it->srch_key = c->key->c_str();
  if (mem_fp->mem_srch() == 0){
    mem_fp->mem_del();
  }
  it->alloc_ptr = c;
  mem_fp->mem_srch_alloc();
  return(c->key->c_str());
}

// delete 
void menu_inf::delete_cel(char *key){
  it->srch_key = key;
  if (mem_fp->mem_srch() == 0){
    mem_fp->mem_del();
  }
}

// srch
char *menu_inf::srch_cel(char *key){
  menu_cel *c;
  it->srch_key = key;
  if (mem_fp->mem_srch() == 0){
    c = (menu_cel *)mem_fp->mem_link_ptr_rd();
    return(c->path->c_str());
  }
  return(NULL);
}

// file read/write
void menu_inf::file_write(FILE *fp){
  menu_cel *c;
  sCharEX *w = new sCharEX("");
  MEM_LOOP(c,menu_cel,mem_fp)
    w->DblIns(c->path->c_str());
    fprintf(fp,"#path,%s\n",w->c_str());
  LOOP_END
  delete w;
}

bool menu_inf::file_read(CsvInf_T *csvinf){
  char *str,*path;
  if ((str  = csvinf->CsvSel_Rd(0)) == NULL) {return(false);}
  if ((path = csvinf->CsvSel_Rd(1)) == NULL) {return(false);}
  sp_push(str);  sp_push2(str);
  sp_push(path); sp_push2(path);
  if (strcmp(str,"#path") == 0){
    add_cel(path);
    return(true);
  }
  return(false);
}

// all clear
void menu_inf::all_clear(){
  menu_cel *c;
  MEM_LOOP(c,menu_cel,mem_fp) delete c; LOOP_END
  mem_fp->mem_del_all();
}


