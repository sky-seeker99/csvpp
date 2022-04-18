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
//  CSVPP Library Control
//

#define ApiFileInfo   0xeffe // file sikibetsu
#define ApiRecLen     20     // record length
#define ApiAxisNo     0      // axis no
#define ApiDtNo       1      // data no
#define InheritAxisNo 2      // axis no
#define InheritDtNo   3      // data no

// ---------------- DataBase Application Interface -------------------
class Cell_T{
  public:
  sChar        *class_name;  // need class
  bool          chk_flg;     // check flg
  Cell_T(char *str){class_name = new sChar(str); chk_flg = false;}
  ~Cell_T(){delete class_name;}
  };

class DbApi_T{
  public:
  MemHeader_T  *it;          // MemFp control interface
  MEM_FP       *need_fp;     // need class fp (Cell_T cell)
  MEM_FP       *define_fp;   // define class fp (Cell_T cell)
  MEM_FP       *dbfile_fp;   // database fp (DbInf_T/CsvInf_T cell)
  DbInf_T      *db_fp;       // database handler
  sChar        *include_dir; // include directory
  sChar        *csv_file;    // CSV FILE NAME
  CsvInf_T     *csv_fp;      // CSV FILE Pointer
  FILE         *txt_fp;      // Text File Pointer
  char          proc_kbn;    // process kbn
  bool          write_on;    // for C Proc 
  bool          error_flg;   // error flg
  
  DbApi_T(char *argv[],int argc){
    int i;
    error_flg = true;

    if (argc < 4){return;}
    proc_kbn = *argv[1];

    if ((proc_kbn != 'c')
     && (proc_kbn != 'a')
     && (proc_kbn != 'd')
     && (proc_kbn != 'o')
     && (proc_kbn != 'l')){return;}

    if (proc_kbn == 'c'){error_flg = C_Open(argv,argc);}
    if (proc_kbn == 'a'){error_flg = A_Open(argv,argc);}
    if (proc_kbn == 'd'){error_flg = D_Open(argv,argc);}
    if (proc_kbn == 'o'){error_flg = O_Open(argv,argc);}
    if (proc_kbn == 'l'){error_flg = O_Open(argv,argc);}
    }

  ~DbApi_T(){
    if (error_flg == true){return;}

    if (proc_kbn == 'c'){C_Close();}
    if (proc_kbn == 'a'){A_Close();}
    if (proc_kbn == 'd'){D_Close();}
    if (proc_kbn == 'o'){O_Close();}
    if (proc_kbn == 'l'){O_Close();}
    }

  bool C_Open(char **argv,int argc);
  void C_Close();
  bool A_Open(char **argv,int argc);
  void A_Close();
  bool D_Open(char **argv,int argc);
  void D_Close();
  bool O_Open(char **argv,int argc);
  void O_Close();
  void Main();
  void L_Main();
  void O_Main();
  void D_Main();
  void A_Main();
  void C_Main();
  void CsvRead(char *p_file);
  void AxisKeyWrite(char *str);
  };

// ----- Open/Close -------------------
// C Open
bool DbApi_T::C_Open(char **argv,int argc)
  {
  int   i;
  char *env;
  bool  ok_flg;
  
  if (argc < 5){return(true);}

  it          = new MemHeader_T;
  need_fp     = new MEM_FP(it);
  define_fp   = new MEM_FP(it);
  dbfile_fp   = new MEM_FP(it);
  include_dir = new sChar("");
  env         = getenv("csvpp_dir");
  if (env != NULL){include_dir->set(env);}

  csv_file    = new sChar(argv[2]);
  txt_fp      = fopen(argv[3],"wt");
  for(i=4;i<argc;++i)
    {
    it->alloc_ptr = new DbInf_T(argv[i],O_RDONLY,ApiFileInfo,ApiRecLen);
    dbfile_fp->mem_alloc();
    }

  // check
  ok_flg = true;
  if (txt_fp == NULL){printf("open error(file=%s)",argv[3]); ok_flg = false;}
  i=4;
  MEM_LOOP(db_fp,DbInf_T,dbfile_fp)
    if (db_fp->OpenError_Rd() == true)
      {
      printf("open error(file=%s)",argv[i]);
      ok_flg = false;
      }
    ++i;  
  LOOP_END
  
  if (ok_flg == false){C_Close(); return(true);}
  return(false);
  }

// C Close
void DbApi_T::C_Close()
  {
  Cell_T *str;

  MEM_LOOP(str  ,Cell_T ,need_fp  ) delete str;   LOOP_END
  MEM_LOOP(str  ,Cell_T ,define_fp) delete str;   LOOP_END
  MEM_LOOP(db_fp,DbInf_T,dbfile_fp) delete db_fp; LOOP_END
  delete dbfile_fp;
  delete define_fp;
  delete need_fp;
  delete it;
  delete include_dir;
//  delete csv_fp;
  delete csv_file;
  if (txt_fp != NULL){fclose(txt_fp);}
  }
  
// A Open
bool DbApi_T::A_Open(char **argv,int argc)
  {
  int   i;
  bool  ok_flg;
  
  it          = new MemHeader_T;
  dbfile_fp   = new MEM_FP(it);
  db_fp       = new DbInf_T(argv[2],O_RDWR,ApiFileInfo,ApiRecLen);
  for(i=3;i<argc;++i)
    {
    it->alloc_ptr = new CsvInf_T(argv[i]);
    dbfile_fp->mem_alloc();
    }
  
  // check
  ok_flg = true;
  if (db_fp->OpenError_Rd() == true)
    {
    printf("open error(file=%s)",argv[2]);
    ok_flg = false;
    }

  i=3;
  MEM_LOOP(csv_fp,CsvInf_T,dbfile_fp)
    if (csv_fp->CsvError_Rd() != 0)
      {
      printf("open error(file=%s)",argv[i]);
      ok_flg = false;
      }
    ++i;  
  LOOP_END
  
  if (ok_flg == false){A_Close(); return(true);}
  return(false);
  }

// A Close
void DbApi_T::A_Close()
  {
  MEM_LOOP(csv_fp,CsvInf_T,dbfile_fp)
    delete csv_fp;
  LOOP_END
  delete dbfile_fp;
  delete it;
  delete db_fp;
  }

// D Open
bool DbApi_T::D_Open(char **argv,int argc)
  {
  int   i;
  bool  ok_flg;
  
  it          = new MemHeader_T;
  define_fp   = new MEM_FP(it);
  db_fp       = new DbInf_T(argv[2],O_RDWR,ApiFileInfo,ApiRecLen);
  for(i=3;i<argc;++i)
    {
    it->alloc_ptr = new sChar(argv[i]);
    define_fp->mem_alloc();
    }
  
  // check
  ok_flg = true;
  if (db_fp->OpenError_Rd() == true)
    {
    printf("open error(file=%s)",argv[2]);
    ok_flg = false;
    }

  if (ok_flg == false){D_Close(); return(true);}
  return(false);
  }

// D Close
void DbApi_T::D_Close()
  {
  sChar *str;
  
  MEM_LOOP(str,sChar,define_fp)
    delete str;
  LOOP_END
  delete define_fp;
  delete it;
  delete db_fp;
  }

// O Open
bool DbApi_T::O_Open(char **argv,int argc)
  {
  bool  ok_flg;
  
  if (argc != 4){return(true);}
  db_fp  = new DbInf_T(argv[2],O_RDONLY,ApiFileInfo,ApiRecLen);
  txt_fp = fopen(argv[3],"wt");

  // check
  ok_flg = true;
  if (txt_fp == NULL){printf("open error(file=%s)",argv[3]); ok_flg = false;}
  if (db_fp->OpenError_Rd() == true){printf("open error(file=%s)",argv[2]); ok_flg = false;}
  if (ok_flg == false){O_Close(); return(true);}
  return(false);
  }

// O Close
void DbApi_T::O_Close()
  {
  delete db_fp;
  if (txt_fp != NULL){fclose(txt_fp);}
  }
  

// ----- Main --------------
void DbApi_T::Main()
  {
  if (error_flg == true){return;}
  if (proc_kbn == 'c'){C_Main();}
  if (proc_kbn == 'a'){A_Main();}
  if (proc_kbn == 'd'){D_Main();}
  if (proc_kbn == 'o'){O_Main();}
  if (proc_kbn == 'l'){L_Main();}
  }
  

// ----- Parts Main ----------
// L Main 
void DbApi_T::L_Main()
  {
  char *str;
  
  fprintf(txt_fp,"------- class list --------\n");
  DB_LOOP(ApiAxisNo,db_fp)
    db_fp->ApiAxisRead(ApiAxisNo,ApiDtNo);
    str = db_fp->ApiDt_Rd(0);
    fprintf(txt_fp,"%s\n",str);
  LOOP_END
  }

// O Main
void DbApi_T::O_Main()
  {
  char *str;

  DB_LOOP(ApiAxisNo,db_fp)
    db_fp->ApiAxisRead(ApiAxisNo,ApiDtNo);
    DB_LOOP(ApiDtNo,db_fp)
      db_fp->ApiDtRead(ApiDtNo);
      str = db_fp->ApiDt_Rd(0);
      fprintf(txt_fp,"%s",str);
    LOOP_END
  LOOP_END
  }

// D Main 
void DbApi_T::D_Main()
  {
  sChar *w;
  
  MEM_LOOP(w,sChar,define_fp)
    if (db_fp->ApiAxisSrch(ApiAxisNo,ApiDtNo,w->c_str()) == false){continue;}
    db_fp->ApiDtDelAll(ApiDtNo);
    db_fp->ApiAxisDel(ApiAxisNo,ApiDtNo,w->c_str());
  LOOP_END
  }


// A Main 
void DbApi_T::A_Main()
  {
  int i;
  char *str;
  sChar *sv_str;
  char *www;
  bool flg;

  sv_str = new sChar("");
  write_on = false;
  MEM_LOOP(csv_fp,CsvInf_T,dbfile_fp)
    for(;;)
      {
      if (csv_fp->CsvFgets() == -1) {break;}
      if (csv_fp->CsvSelSu_Rd() == 0) {continue;}
      for(i=0;i<csv_fp->CsvSelSu_Rd();++i){if ((str = csv_fp->CsvSel_Rd(i)) != MM_NULL){break;}}
      if (str == MM_NULL){continue;}
      if (strcmp(str,"%classcall")==0){AxisKeyWrite(sv_str->c_str()); continue;}
      if (strcmp(str,"%class")==0)
        {
        AxisKeyWrite(sv_str->c_str());
        str = (char *)MM_NULL;
        for(++i;i<csv_fp->CsvSelSu_Rd();++i){if ((str = csv_fp->CsvSel_Rd(i)) != MM_NULL){break;}}
        if (str == MM_NULL){continue;}
        write_on = true;
        sv_str->set(str);
        if (db_fp->ApiAxisSrch(ApiAxisNo    ,ApiDtNo,str    ) == true){db_fp->ApiDtDelAll(ApiDtNo    );}
        
        // Inherit Store
        if (db_fp->ApiAxisSrch(InheritAxisNo,InheritDtNo,str) == true){db_fp->ApiDtDelAll(InheritDtNo);}
        flg = false;
        for(++i;i<csv_fp->CsvSelSu_Rd();++i)
          {
          if ((str = csv_fp->CsvSel_Rd(i)) == MM_NULL){continue;}
          db_fp->ApiDt_Reset();
          db_fp->ApiDt_Set(str);
          db_fp->ApiDtStore(InheritDtNo);
          flg = true;
          }
        if (flg == true){db_fp->ApiAxisStore(InheritAxisNo,InheritDtNo,sv_str->c_str());}
        
        }
      if (write_on == true)
        {
        db_fp->ApiDt_Reset();
        www = csv_fp->xFgetsBuff_Rd();
        db_fp->ApiDt_Set(www);
        db_fp->ApiDtStore(ApiDtNo);
        }
      }
    AxisKeyWrite(sv_str->c_str());
  LOOP_END
  delete sv_str;
  }

// Axis Key Write
void DbApi_T::AxisKeyWrite(char *str)
  {
  if (write_on == true){db_fp->ApiAxisStore(ApiAxisNo,ApiDtNo,str);}
  write_on = false;
  }


// C Main 
void DbApi_T::C_Main()
  {
  Cell_T *cell;
  char   *w;
  bool    flg;
  bool    hit;

  CsvRead(csv_file->c_str());

  MEM_LOOP(cell,Cell_T,define_fp)
    it->srch_key = cell->class_name->c_str();
    if (need_fp->mem_srch() == 0)
      {
      cell = (Cell_T *)need_fp->mem_link_ptr_rd();
      delete cell;
      need_fp->mem_del();
      }
  LOOP_END
  
  flg = true;
  for(;;)
    {
    if (flg == false){break;}
    flg = false;
    MEM_LOOP(cell,Cell_T,need_fp)
      if (cell->chk_flg == true){continue;}
      cell->chk_flg = true;
      hit=false;
      MEM_LOOP(db_fp,DbInf_T,dbfile_fp)
        if (db_fp->ApiAxisSrch(InheritAxisNo,InheritDtNo,cell->class_name->c_str()) == true){hit=true; break;}
      LOOP_END
      if (hit == false){continue;}
      DB_LOOP(InheritDtNo,db_fp)
        db_fp->ApiDtRead(InheritDtNo);
        w = db_fp->ApiDt_Rd(0);
        it->srch_key = w;
        if (need_fp->mem_srch() == 0){continue;}
        it->alloc_ptr = new Cell_T(w);
        need_fp->mem_srch_alloc();
        flg = true;
      LOOP_END
    LOOP_END
    }

  MEM_LOOP(cell,Cell_T,need_fp)
    hit=false;
    MEM_LOOP(db_fp,DbInf_T,dbfile_fp)
      if (db_fp->ApiAxisSrch(ApiAxisNo,ApiDtNo,cell->class_name->c_str()) == true){hit=true; break;}
    LOOP_END
    if (hit == false){continue;}

    DB_LOOP(ApiDtNo,db_fp)
      db_fp->ApiDtRead(ApiDtNo);
      w = db_fp->ApiDt_Rd(0);
      fprintf(txt_fp,"%s",w);
    LOOP_END
  LOOP_END
  }


// csv file read (recurcive)
void DbApi_T::CsvRead(char *p_file)
  {
  CsvInf_T *csv_fp;
  sChar    *file;
  char     *str;
  int       i;

  csv_fp = new CsvInf_T(p_file);
  if (csv_fp->CsvError_Rd() != 0){delete csv_fp; printf("open error(file=%s)",p_file); return;}
  file = new sChar("");
  for(;;)
    {
    if (csv_fp->CsvFgets() == -1) {break;}
    if (csv_fp->CsvSelSu_Rd() == 0) {continue;}
    for(i=0;i<csv_fp->CsvSelSu_Rd();++i){if ((str = csv_fp->CsvSel_Rd(i)) != MM_NULL){break;}}
    if (str == MM_NULL){continue;}
    if (strcmp(str,"%include_dir")==0)
      {
      str = (char *)MM_NULL;
      for(++i;i<csv_fp->CsvSelSu_Rd();++i){if ((str = csv_fp->CsvSel_Rd(i)) != MM_NULL){break;}}
      if (str == MM_NULL){continue;}
      include_dir->set(str);
      continue;
      }
    if (strcmp(str,"%include")==0)
      {
      str = (char *)MM_NULL;
      for(++i;i<csv_fp->CsvSelSu_Rd();++i){if ((str = csv_fp->CsvSel_Rd(i)) != MM_NULL){break;}}
      if (str == MM_NULL){continue;}
      file->set(include_dir->c_str());
      file->cat(str);
      CsvRead(file->c_str());
      continue;
      }
    if (strcmp(str,"%class")==0)
      {
      str = (char *)MM_NULL;
      for(++i;i<csv_fp->CsvSelSu_Rd();++i){if ((str = csv_fp->CsvSel_Rd(i)) != MM_NULL){break;}}
      if (str == MM_NULL){continue;}
      it->srch_key  = str;
      if (define_fp->mem_srch() == 0){continue;}
      it->alloc_ptr = new Cell_T(str);
      define_fp->mem_srch_alloc();

      for(++i;i<csv_fp->CsvSelSu_Rd();++i)
        {
        if ((str = csv_fp->CsvSel_Rd(i)) == MM_NULL){continue;}
        it->srch_key  = str;
        if (need_fp->mem_srch() == 0){continue;}
        it->alloc_ptr = new Cell_T(str);
        need_fp->mem_srch_alloc();
        }
      continue;
      }
    if (strcmp(str,"%classcall")==0)
      {
      str = (char *)MM_NULL;
      for(++i;i<csv_fp->CsvSelSu_Rd();++i){if ((str = csv_fp->CsvSel_Rd(i)) != MM_NULL){break;}}
      if (str == MM_NULL){continue;}
      it->srch_key  = str;
      if (need_fp->mem_srch() == 0){continue;}
      it->alloc_ptr = new Cell_T(str);
      need_fp->mem_srch_alloc();
      continue;
      }
    }

  delete csv_fp;
  delete file;
  }




