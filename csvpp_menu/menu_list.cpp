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


