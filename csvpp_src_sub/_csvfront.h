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
//  CSVPP Front End Control
//

#define MODE_NONE 0
#define MODE_IDIR 1
#define MODE_INC  2
#define MODE_DEF  3
#define MODE_CMT  4
#define MODE_EXCEL 5
#define MODE_EXCEL_SEL 6
#define MODE_EXCEL_NOSEL 7
#define MODE_EXCEL_SELCLR 8
#define MODE_INC_MACRO  9

// define table class ----------------------------------------------------------
class DefTbl_T{
  private:
  sChar  *name;
  int     parm_cnt;
  MEM_FP *parm_fp;
  MEM_FP *parmcall_fp;
  MEM_FP *prog_fp;
  MemHeader_T *it;
  StrSrchInf_T *ssc;
  sCharGrep  *g_str;
  
  public:
  DefTbl_T(char *p_name,MemHeader_T *p_it){
    int i;
    sChar *str;
    ssc = new StrSrchInf_T;
    ssc->Set('_');
    ssc->Main(p_name);
    parm_cnt = ssc->GetSu()-1;
    it       = p_it;
    parm_fp  = new MEM_FP(it);
    parmcall_fp  = new MEM_FP(it);
    prog_fp  = new MEM_FP(it);
    for(i=0;i<parm_cnt+1;++i)
      {
      str = ssc->Get(i);
      if (i == 0){name = new sChar(str->c_str()); continue;}
      it->alloc_ptr = (MM_PTR_T *)new sChar(str->c_str());
      parm_fp->mem_alloc();
      }
    g_str = new sCharGrep("");
    }
  ~DefTbl_T(){
    sChar *str;
    
    delete name;
    delete ssc;  
    MEM_LOOP(str,sChar,parm_fp) delete str; LOOP_END delete parm_fp;
    MEM_LOOP(str,sChar,prog_fp) delete str; LOOP_END delete prog_fp;
    MEM_LOOP(str,sChar,parmcall_fp) delete str; LOOP_END delete parmcall_fp;
    delete g_str;
    }
    
  void DefStr(char *p_str);    
  char *GetStrTopSet(char *p_name);    
  char *GetStr();
};


// CsvFileRead class -----------------------------------------------------------
class CsvRead_T{
  public:
  sChar       *name;
  CsvInf_T    *csv_fp;
  FileTemp_T  *temp_fp;
  FILE        *out_fp;
  bool         read_req;
  bool         end_flg;
  int          col;
  bool         noChgFlg;
  int          noChgCnt;

  CsvRead_T(char *p_name,bool include_macro_mode,char *key){
    csv_fp   = new CsvInf_T(p_name);
    if (csv_fp->CsvError_Rd() != 0){delete csv_fp; csv_fp = (CsvInf_T *)NULL; return;}
    name     = new sChar(p_name);
    temp_fp  = new FileTemp_T("tmp");
    out_fp   = temp_fp->fp;
    end_flg  = false;
    read_req = true;
    noChgFlg = false;
    noChgCnt = 0;
    fprintf(out_fp,"//,### csvfront converted file ###\n");

    if (include_macro_mode == true){
      int len = strlen(key);
      char sv;
      if (len > 4){
        sv = key[len-4];
        key[len-4] = 0;
      }


      fprintf(out_fp,"%%st,%s\n",key);

      if (len > 4){
        key[len-4] = sv;
      }

    }

  }
  ~CsvRead_T(){
    if (csv_fp == (CsvInf_T *)NULL){return;}
    delete csv_fp;

    if (noChgFlg == false){
      DeleteFile(name->c_str());
      temp_fp->close();
      temp_fp->TempToRename(name->c_str());
    }
    else{
      temp_fp->close();
    }
    delete name;
    delete temp_fp;
  }

  char *csvread();
  bool csveof(         ){return(end_flg);}
  void csvwr (char *str){csv_fp->CsvWrite(out_fp,str);}
  void wr    (char *str){fprintf(out_fp,"%s",str);}
  };


// interface class -------------------------------------------------------------
class Inf_T{
  public:
  sChar       *include_dir;
  MEM_FP      *define_fp;
  MEM_FP      *inc_fp;
  MEM_FP      *env_fp;
  MemHeader_T *it;
  int          mode;
  DefTbl_T    *wr_dt;
  bool         rett_flg;
  bool         top_flg;
  bool         retNeedFlg;
  bool         csvmakeTmpFlg;
  FileNameSep_T *filesep;
  sCharGrep       *arg_file_dir;
  csvmake_C       *csvmake;
  csvmake_oo_C    *csvmake_oo;
  bool         openOfficeFlag;

  VariableArray_C *uniq_fp;  // Ver 1.17

  bool         csvmakeFirst;

  bool         include_macro_mode; // Ver 1.15

  Inf_T(){
    if (getenv("csvpp_dir") == NULL){include_dir = new sChar("");}
    else                            {include_dir = new sChar(getenv("csvpp_dir"));}
    it          = new MemHeader_T;
    define_fp   = new MEM_FP(it);
    inc_fp      = new MEM_FP(it);
    env_fp      = new MEM_FP(it);
    uniq_fp     = new VariableArray_C(10); // Ver 1.17
    mode        = MODE_NONE;
    rett_flg    = false;
    top_flg     = true;
    retNeedFlg  = false;
    filesep = new FileNameSep_T; 
    arg_file_dir      = NULL;
    csvmake           = new  csvmake_C;
    csvmake->pchkFlag = true;
    csvmake->process_get();
    csvmake->pchkFlag = false;
    csvmakeFirst      = true;
    csvmake_oo        = new csvmake_oo_C;
    openOfficeFlag    = false;
    include_macro_mode = false;  // Ver 1.15
    }
  ~Inf_T(){
    DefTbl_T *dt;
    sChar *str;
    delete include_dir;
    MEM_LOOP(dt ,DefTbl_T,define_fp) delete dt;  LOOP_END
    MEM_LOOP(str,sChar   ,inc_fp   ) delete str; LOOP_END
    MEM_LOOP(str,sChar   ,env_fp   ) delete str; LOOP_END
    ARY_LOOP(str,sChar   ,uniq_fp  ) delete str; LOOP_END // Ver 1.17

    delete uniq_fp;  // Ver 1.17
    delete define_fp;
    delete inc_fp;
    delete env_fp;
    delete it;
    delete filesep;
    if (arg_file_dir != NULL){delete arg_file_dir;}
    if (csvmakeFirst == false) {
      if (openOfficeFlag){
        csvmake_oo->csvmake_end();
      }
      else {
        csvmake->csvmake_end();
      }
    }
    delete csvmake;
    delete csvmake_oo;
    }
  void      DefRead    (DefTbl_T *dt,CsvRead_T *ci);
  void      CsvRead    (char *p_file,char *str);
  void      Write      (char *str,CsvRead_T *ci);
  bool      Select     (char *str);
  DefTbl_T *DefineStore(char *str);
  char     *DefineExist(char *str);
  void      ProgramArgRead(int argc,char *argv[]);
};


