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


// define table class ----------------------------------------------------------
void DefTbl_T::DefStr(char *p_str){
  it->alloc_ptr = (MM_PTR_T *)new sChar(p_str);
  prog_fp->mem_alloc();
  }
  
char *DefTbl_T::GetStrTopSet(char *p_name){
  sChar *str;
  char  *first_str;
  int i;
  ssc->Main(p_name);
  if (parm_cnt != ssc->GetSu()-1){return(NULL);}
  for(i=0;i<parm_cnt+1;++i){
    str = ssc->Get(i);
    if (i == 0){
      if (strcmp(str->c_str(),name->c_str()) != 0){return(NULL);}
      first_str = str->c_str();
      MEM_LOOP(str,sChar,parmcall_fp) delete str; LOOP_END parmcall_fp->mem_del_all();
    } else {
      it->alloc_ptr = (MM_PTR_T *)new sChar(str->c_str());
      parmcall_fp->mem_alloc();
    }
  }
  prog_fp->mem_mcb_top_set();
  return(first_str);
}
  
char *DefTbl_T::GetStr(){
  sChar *parm_str;
  sChar *val_str;
  sChar *str;
  if (prog_fp->mem_mcb_ptr_rd() == MM_NULL){return(NULL);}
  str = (sChar *)prog_fp->mem_link_ptr_rd();
  g_str->set(str->c_str());
  parmcall_fp->mem_mcb_top_set();
  MEM_LOOP(parm_str,sChar,parm_fp)
    val_str = (sChar *)parmcall_fp->mem_link_ptr_rd();
    g_str->replace_all(parm_str->c_str(),val_str->c_str());
    parmcall_fp->mem_mcb_next_set();
  LOOP_END
  prog_fp->mem_mcb_next_set();
  return(g_str->c_str());
}


// CsvFileRead class -----------------------------------------------------------
char *CsvRead_T::csvread(){
  char *str;
  if (end_flg  == true){return(NULL);}
  if (read_req == true){
    if (csv_fp->CsvFgets()    == -1) {end_flg = true; return(NULL);}
    read_req = false;
    col = 0;
  }
  if (col == csv_fp->CsvSelSu_Rd()){read_req = true; return(NULL);}
  str = csv_fp->CsvSel_Rd(col);
  ++col;
  if (str == (MM_PTR_T *)MM_NULL){return("");}
  if (noChgCnt == 0){
    if (strcmp(str,"//") == 0) {noChgCnt = 1;}
  } else {
    if (strcmp(str,"### csvfront converted file ###") == 0){noChgFlg = true; end_flg = true;}
    noChgCnt = 0;
  }
  return(str);
}


// interface class -------------------------------------------------------------
// program arg get
void Inf_T::ProgramArgRead(int argc,char *argv[]){
  int i,k,max;
  char *str;
  char *env;
  StrSrchInf_T *ssc;
  sChar *sstr;
  int kbn;

  ssc = new StrSrchInf_T();
  ssc->Set(';');

  env = getenv("csvpp_dir");
  if (env != NULL){
    ssc->Main(env);
    max = ssc->GetSu();
    for(k=0;k<max;++k){
      sstr = ssc->Get(k);
      it->alloc_ptr = new sChar(sstr->c_str());
      inc_fp->mem_alloc();
    }
  }

  for(i=2;i<argc;++i){
    str = argv[i];
    if (*str != '-'){continue;}
    kbn = 0;
    if ((*(str+1) == 'I') || (*(str+1) == 'i')){kbn = 1;}
    if ((*(str+1) == 'D') || (*(str+1) == 'd')){kbn = 2;}
    if ((*(str+1) == 'X') || (*(str+1) == 'x')){kbn = 3;}
    if ((*(str+1) == 'P') || (*(str+1) == 'p')){kbn = 4;}
    if ((*(str+1) == 'O') || (*(str+1) == 'o')){kbn = 5;}
    if (kbn == 0){continue;}
    if (kbn == 4) {
      csvmake->pchkFlag = true;
      continue;
    }
    if (kbn == 5) {
      openOfficeFlag = true;
      continue;
    }
    if (kbn == 3){
      if (arg_file_dir != NULL){delete arg_file_dir;}
      arg_file_dir= new sCharGrep(str+2);
      arg_file_dir->replace_all("\"","");
      filesep->Set(arg_file_dir->c_str());
      arg_file_dir->set(filesep->DrvGet());
      arg_file_dir->cat(filesep->DirGet());
      continue;
    }

    ssc->Main(str+2);
    max = ssc->GetSu();
    for(k=0;k<max;++k){
      sstr = ssc->Get(k);
      it->alloc_ptr = new sChar(sstr->c_str());
      if (kbn == 1){inc_fp->mem_alloc();}
      else         {env_fp->mem_alloc();}
    }
  }
  delete ssc;
}


// define exist check ----------------
char *Inf_T::DefineExist(char *p_str){
  char *str;
  DefTbl_T *dt;

  MEM_LOOP(dt,DefTbl_T,define_fp)
    if ((str = dt->GetStrTopSet(p_str)) == NULL) {continue;}
    return(str);
  LOOP_END
  return(NULL);
}

// define store -----------------------
DefTbl_T *Inf_T::DefineStore(char *p_str){
  DefTbl_T *dt;
  if (DefineExist(p_str) != NULL)
    {
    dt = (DefTbl_T *)define_fp->mem_link_ptr_rd();
    delete dt;
    define_fp->mem_del();
    }
  dt = new DefTbl_T(p_str,it);
  it->alloc_ptr = (MM_PTR_T *)dt;
  define_fp->mem_alloc();
  return(dt);
}

// Select Check -----------------------
// inner val:wr_dt,mode,rett_flg
// return   :=true:continue =false:throw
bool Inf_T::Select(char *str){
  sChar *file;
  char *a;
  sChar *sstr;
  StrSrchInf_T *ssc;
  int max,k;

  for(;;){
    if (str == NULL){break;}
    if (mode == MODE_NONE){
      if (strcmp(str,"//"          )==0){mode = MODE_CMT;  }
      if (strcmp(str,"%include_macro")==0){mode = MODE_INC_MACRO; }
      if (strcmp(str,"%include_dir")==0){mode = MODE_IDIR; }
      if (strcmp(str,"%include"    )==0){mode = MODE_INC;  }
      if (strcmp(str,"%csvmake"    )==0){mode = MODE_EXCEL; csvmakeTmpFlg = false; }
      if (strcmp(str,"%csvmake_tmp")==0){mode = MODE_EXCEL; csvmakeTmpFlg = true; }
      if (strcmp(str,"%csvmake_sel")==0){mode = MODE_EXCEL_SEL;}
      if (strcmp(str,"%csvmake_nosel")==0){mode = MODE_EXCEL_NOSEL;}
      if (strcmp(str,"%csvmake_selclr")==0){mode = MODE_EXCEL_SELCLR;}
      if (strcmp(str,"%define"     )==0){mode = MODE_DEF;  wr_dt = NULL;}
      break;
    }
    if (mode == MODE_CMT){break;}

    if (mode == MODE_EXCEL_SEL){
      sChar *s_str = new sChar(str);
      if (openOfficeFlag){
        csvmake_oo->it->alloc_ptr = (unsigned char *)s_str;
        csvmake_oo->sel_fp->mem_alloc();
      }
      else {
        csvmake->sel_fp->mem_alloc((unsigned char *)s_str);
      }
      mode = MODE_NONE;
      break;
    }

    if (mode == MODE_EXCEL_NOSEL){
      sChar *s_str = new sChar(str);
      if (openOfficeFlag){
        csvmake_oo->it->alloc_ptr = (unsigned char *)s_str;
        csvmake_oo->esel_fp->mem_alloc();
      }
      else {
        csvmake->esel_fp->mem_alloc((unsigned char *)s_str);
      }
      mode = MODE_NONE;
      break;
    }

    if (mode == MODE_EXCEL_SELCLR){
      sChar *s_str;
      if (openOfficeFlag){
        MEM_LOOP(s_str,sChar,csvmake_oo->sel_fp )  delete s_str; LOOP_END
        MEM_LOOP(s_str,sChar,csvmake_oo->esel_fp)  delete s_str; LOOP_END
        csvmake_oo->sel_fp->mem_del_all();
        csvmake_oo->esel_fp->mem_del_all();
      }
      else {
        ARY_LOOP(s_str,sChar,csvmake->sel_fp )  delete s_str; LOOP_END
        ARY_LOOP(s_str,sChar,csvmake->esel_fp)  delete s_str; LOOP_END
        csvmake->sel_fp->clear();
        csvmake->esel_fp->clear();
      }
      mode = MODE_NONE;
      break;
    }



    if (mode == MODE_INC_MACRO){
      if      ((strcmp(str,"on" ) == 0) || (strcmp(str,"ON" ) == 0)){include_macro_mode=true; printf("%%include_macro option on.\n");}
      else if ((strcmp(str,"off") == 0) || (strcmp(str,"OFF") == 0)){include_macro_mode=false; printf("%%include_macro option off.\n");}
      mode = MODE_NONE;
      break;
    }


    if (mode == MODE_EXCEL){
      // Ver 1.17
      bool exist_flag = false;
      sChar *s;
      ARY_LOOP(s,sChar,uniq_fp)
        if (strcmp(s->c_str(),str) == 0){
          exist_flag = true;
          break;
        }
      LOOP_END
      if (exist_flag){
        printf("%%csvmake/%%csvmake_tmp excel-file skip. file=%s\n",str);
        mode = MODE_NONE;
        break;
      }
      s = new sChar(str);
      uniq_fp->mem_alloc((unsigned char *)s);

      sChar *out_dir = NULL;
      MEM_LOOP(sstr,sChar,inc_fp)
        out_dir = sstr;
        break;
      LOOP_END

      if (out_dir == NULL){
        printf("%%csvmake/%%csvmake_tmp output directory error. file=%s\n",str);
        mode = MODE_NONE;
        break;
      }

//      XlsCsv_C *csvmake = new XlsCsv_C;
//      csvmake->outDirSet(out_dir->c_str());
      sChar *file_name = new sChar("");
      filesep->Set(str);

      bool exchgFlag = false;
      if ((strcmp(filesep->DirGet(),"") == 0) && (strcmp(filesep->DrvGet(),"") == 0)){
        bool existOkFlg=false;
        if (arg_file_dir != NULL){
          file_name->set(arg_file_dir);
          file_name->cat(str);
          printf("Excel file find search (file=%s)\n",file_name->c_str());
          if (FileExist(file_name->c_str()) == 0){existOkFlg=true;}
        }

        if (existOkFlg){
          // csvmake->xls2csv(file_name->c_str(),NULL,"csv",csvmakeTmpFlg);
          exchgFlag=true;
        }
        else {
          existOkFlg=false;
          MEM_LOOP(sstr,sChar,inc_fp)
            file_name->set(sstr->c_str());
            file_name->cat("\\");
            file_name->cat(str);

            printf("Excel file find search (file=%s)\n",file_name->c_str());
            if (FileExist(file_name->c_str()) == 0){existOkFlg=true; break;}
          LOOP_END

          if (existOkFlg){
            //csvmake->xls2csv(file_name->c_str(),NULL,"csv",csvmakeTmpFlg);
            exchgFlag=true;
          }
          else {
            printf("%%csvmake/%%csvmake_tmp excel-file open error. file=%s\n",str);
          }
        }
      }
      else {
        //csvmake->xls2csv(str,NULL,"csv",csvmakeTmpFlg);
        file_name->set(str);
        exchgFlag=true;
      }

      if (exchgFlag) {
        if (csvmakeFirst) {
          if (openOfficeFlag){
            csvmake_oo->csvmake_begin();
          }
          else {
            bool sv = csvmake->pchkFlag;
            csvmake->pchkFlag = false;
            csvmake->csvmake_begin();
            csvmake->pchkFlag = sv;
          }
          csvmakeFirst = false;
        }
        csvmake->tmpFlag = csvmakeTmpFlg;
        if (openOfficeFlag){
          csvmake_oo->csvmake(file_name->c_str(),out_dir->c_str(),NULL,NULL);
        }
        else {
          csvmake->csvmake(file_name->c_str(),out_dir->c_str(),NULL,NULL,NULL);
        }
      }


      delete file_name;
      //delete csvmake;
      mode = MODE_NONE;
      break;
    }

    if (mode == MODE_IDIR){
      ssc = new StrSrchInf_T();
      ssc->Set(';');

      include_dir->set(str);
      ssc->Main(str);
      max = ssc->GetSu();
      for(k=0;k<max;++k){
        sstr = ssc->Get(k);
        it->alloc_ptr = new sChar(sstr->c_str());
        inc_fp->mem_alloc();
      }
      delete ssc;
      mode = MODE_NONE;
      break;
    }
    if (mode == MODE_INC){
      file = new sChar("");
      bool exist=false;
      MEM_LOOP(sstr,sChar,inc_fp)
        a = sstr->c_str();
        file->set(a);
        if (*(a+strlen(a)-1) != '\\'){file->cat("\\");}
        file->cat(str);
        if (FileExist(file->c_str()) == 0){exist=true; break;}
      LOOP_END

      mode = MODE_NONE;
//      if (exist) {CsvRead(file->c_str());}
      if (exist) {CsvRead(file->c_str(),str);}     // Ver 1.15


      delete file;
      break;
    }
    if (mode == MODE_DEF){
      if (wr_dt == NULL){wr_dt = DefineStore(str);}
      else {
        wr_dt->DefStr(str);
        if (mem_cmp(str,"%\\",2)==0){rett_flg = true;}
        else                        {rett_flg = false;}
      }
      break;
    }
  }

  if (mode == MODE_CMT) {
    if (str == NULL){mode = MODE_NONE;}
  }
  if (mode == MODE_DEF){
    if (str == NULL){
      if (rett_flg == false){mode = MODE_NONE;}
      rett_flg = false;
    }
    return(true);
  }
  return(false);
}

// CSV-File Write -------------------
// inner_reg:top_flg
void Inf_T::Write(char *str,CsvRead_T *ci){
  if (str != NULL) {
    if ((*str == 0x00) && (retNeedFlg)){return;}
    if (strcmp (str,"%\\-") == 0   ){retNeedFlg = false; return;}
  }
  if (retNeedFlg                 ){ci->wr("\n");                   retNeedFlg = false;}
  if (str                 == NULL){top_flg = true;                 retNeedFlg = true;              return;}
  if (mode            == MODE_CMT){top_flg = false;                ci->csvwr(str);   ci->wr("," ); return;}
  if (mem_cmp(str,"%\\",2)== 0   ){top_flg = true;                 retNeedFlg = true;              return;}
  if (mem_cmp(str,"%%" ,2)== 0   ){top_flg = false;                ci->csvwr(str+1); ci->wr("," ); return;}
  if (*str                != '%' ){top_flg = false;                ci->csvwr(str);   ci->wr("," ); return;}
  if (DefineExist(str+1)  == NULL){
    if (top_flg == false){ci->wr("\n" );}
    top_flg = false;
    ci->csvwr(str);
    ci->wr("," );
    return;
    }
  DefRead((DefTbl_T *)define_fp->mem_link_ptr_rd(),ci);
}


// csv file read (recurcive)
void Inf_T::CsvRead(char *p_file,char *key){

  // Ver 1.07
  csvretchg_T *retchg = new csvretchg_T(p_file,"@@@^^^[return]---");
  delete retchg;
  
  // Ver 1.06
  reverse_T *rev = new reverse_T(p_file);
  delete rev;
  
  CsvRead_T *ci;
  char *str;
  bool sv_retNeedFlg;

  bool cmtFlg; // Ver 1.03a

  cmtFlg = false;
  ci = new CsvRead_T(p_file,include_macro_mode,key);
  if (ci->csv_fp == NULL){delete ci; return;}
  sv_retNeedFlg     = retNeedFlg;
//  retNeedFlg     = false; Ver 1.12
  retNeedFlg     = true; // Ver 1.12
  top_flg        = true; // Ver 1.12

  for(;;){
    str = ci->csvread();
    if (ci->csveof() == true){break;}
    if (Select(str)  == true){continue;}

    if      (str == NULL          ){cmtFlg = false;} // Ver 1.03a
    else if (strcmp(str,"//") == 0){cmtFlg = true; }

    if (cmtFlg == false){    // Ver 1.03a
      Write(str,ci);
    }
  }
  if (retNeedFlg){ci->wr("\n");}
  retNeedFlg     = sv_retNeedFlg;

  delete ci;
}

// define read (recurcive)
void Inf_T::DefRead(DefTbl_T *dt,CsvRead_T *ci){
  char *str;
  for(;;){
    str = dt->GetStr();
    if (str == NULL){break;}
    if (Select(str) == true){continue;}
    Write(str,ci);
  }
}




