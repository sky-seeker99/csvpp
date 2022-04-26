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
//  Text Control
//

// # logC #####
logC::logC(char *w ,__int64 w_line){
  s_line     = new sChar(w);
  line       = w_line;
}

logC::~logC(){
  delete s_line;
}


// # line_chgC #####
line_chgC::line_chgC(__int64 p_line,char *p_str){
  char w[50];
  unsigned long lower = (unsigned long)(p_line & 0xffffffff);
  unsigned long upper = (unsigned long)(p_line >> 32);

  sprintf(w,"%08x_%08x",upper,lower);
  //sprintf(w,"%I64016x",p_line);
  sline     = new sChar(w);
  str       = new sChar(p_str);
  line      = p_line;
}

line_chgC::~line_chgC(){
  delete sline;
  delete str;
}

// # taskC #####
taskC::taskC(char *p_str){
  name      = new sChar(p_str);
  dummy     = 0;
}

taskC::~taskC(){
  delete name;
}

// # JokenC #####
jokenC::jokenC(int p_kbn,char *p_str){
  joken_kbn = p_kbn;
  parm      = new sChar(p_str);
  aAFlg     = false; // Ver 1.04

}

jokenC::~jokenC(){
  delete parm;
}

// # execC #####
execC::execC(int p_kbn,char *p_str){
  exec_kbn = p_kbn;
  parm     = new sChar(p_str);
  parm2    = new sChar("");
  aAFlg     = false; // Ver 1.04
}

execC::~execC(){
  delete parm;
  delete parm2;
}


// # IfC #####
IfC::IfC(MemHeader_T *p_it){
  joken_fp = new MEM_FP(p_it);
  exec_fp  = new MEM_FP(p_it);
}

IfC::~IfC(){
  jokenC *j;
  execC  *e;
  MEM_LOOP(j,jokenC,joken_fp) delete j; LOOP_END
  MEM_LOOP(e,execC ,exec_fp ) delete e; LOOP_END
  delete joken_fp;
  delete exec_fp;
}


// # StateC #####
StateC::StateC(MemHeader_T *p_it,char *p_name){
  if_fp = new MEM_FP(p_it);
  state_name = new sChar(p_name);
}

StateC::~StateC(){
  IfC *ifc;
  MEM_LOOP(ifc,IfC,if_fp) delete ifc; LOOP_END
  delete if_fp;
  delete state_name;
}


// # TextCtlInf #####
TextCtlInf::TextCtlInf(){
  it         = new MemHeader_T;
  state_fp   = new MEM_FP(it);
  stack_fp   = new MEM_FP(it);
  act_fp     = new MEM_FP(it);
  acton_fp   = new MEM_FP(it);
  acton_init_fp   = new MEM_FP(it);
  line_fp    = new MEM_FP(it);
  actoff_fp  = new MEM_FP(it);
  logc_fp    = new MEM_FP(it);
  insert_fp  = new MEM_FP(it);
  insert_file_fp  = new MEM_FP(it);
  start_name = new sChar("");
  curr_state = NULL;
  w_buff     = new sCharGrep("");
  w_buff_if  = new sCharGrep("");
  need_flg  = false;
  log_fp     = NULL;
  trace_flg  = false;
  inst_flg   = false;
  retdelFlg  = false;
  fin_msg_flg= false;
}



TextCtlInf::~TextCtlInf(){
  jokenC *jkc;
  sChar  *str;
  taskC  *tsk;
  line_chgC *lc;
  logC   *lg;

  MEM_LOOP(curr_state,StateC,state_fp) delete curr_state; LOOP_END
  MEM_LOOP(jkc,jokenC,stack_fp       ) delete jkc;        LOOP_END
  MEM_LOOP(tsk,taskC,acton_fp        ) delete tsk;        LOOP_END
  MEM_LOOP(tsk,taskC,acton_init_fp   ) delete tsk;        LOOP_END
  MEM_LOOP(tsk,taskC,actoff_fp       ) delete tsk;        LOOP_END
  MEM_LOOP(lc ,line_chgC,line_fp     ) delete lc;         LOOP_END
  MEM_LOOP(lg ,logC     ,logc_fp     ) delete lg;         LOOP_END
  MEM_LOOP(str,sChar    ,insert_fp   ) delete str;        LOOP_END
  MEM_LOOP(str,sChar    ,insert_file_fp   ) delete str;        LOOP_END
  delete line_fp;
  delete logc_fp;
  delete state_fp;
  delete stack_fp;
  delete act_fp;
  delete actoff_fp;
  delete acton_fp;
  delete acton_init_fp;
  delete insert_fp;
  delete insert_file_fp;
  delete start_name;
  delete it;
  delete w_buff;
  delete w_buff_if;
  if (log_fp != NULL){delete log_fp;}
}





// # csv file read #####
bool TextCtlInf::CsvFileRead(Read64_C *csv_fp){
  bool okFlg = true;
  bool mon_flg=false;
  IfC *ifc;
  CsvAnl_C *csvi = new CsvAnl_C;

  __int64 l=(__int64)1;
  for(;;l++){
	unsigned char *buff = csv_fp->read();
	if (buff == NULL) {break;}
	csvi->Exec(buff);
	CSV_LOOP(csvi,str,SP_PUSH)
      bool check = false;
      if      (strcmp(str,"//"      ) == 0){check = true; }
      else if (strcmp(str,"#debug"  ) == 0){check = true; mon_flg = true;}
      else if (strcmp(str,"#trace"  ) == 0){check = true; trace_flg = true;}
      else if (strcmp(str,"#itrace" ) == 0){check = true; inst_flg = true;}
      else if (strcmp(str,"#line_chg")== 0){check = true; line_chg   (csvi      );}
      else if (strcmp(str,"#st_init") == 0){check = true; st_init    (csvi      );}
      else if (strcmp(str,"#st"     ) == 0){check = true; st_proc    (csvi      );}
      else if (strcmp(str,"#if"     ) == 0){check = true; if_proc    (csvi,J_EQ );}
      else if (strcmp(str,"#noif"   ) == 0){check = true; if_proc    (csvi,J_NEQ);}
      else if (strcmp(str,"#else"   ) == 0){check = true; else_proc  (csvi      );}
      else if (strcmp(str,"#endif"  ) == 0){check = true; endif_proc (csvi      );}
      else if (strcmp(str,"#printf" ) == 0){check = true; ifc = ifc_gen(); cmd_proc_1(csvi,ifc,EX_PRINTF);}
      else if (strcmp(str,"#ins"    ) == 0){check = true; ifc = ifc_gen(); cmd_proc_1(csvi,ifc,EX_INS   );}
      else if (strcmp(str,"#ins_file")== 0){check = true; ifc = ifc_gen(); cmd_proc_1(csvi,ifc,EX_INS_FILE );}
      else if (strcmp(str,"#ins_file_after")== 0){check = true; ifc = ifc_gen(); cmd_proc_1(csvi,ifc,EX_INS_FILE_AFTER );}
      else if (strcmp(str,"#ins_after")==0){check = true; ifc = ifc_gen(); cmd_proc_1(csvi,ifc,EX_INS_AFTER);}
      else if (strcmp(str,"#chg"    ) == 0){check = true; ifc = ifc_gen(); cmd_proc_1(csvi,ifc,EX_CHG   );}
      else if (strcmp(str,"#del"    ) == 0){check = true; ifc = ifc_gen(); cmd_proc_0(csvi,ifc,EX_DEL   );}
      else if (strcmp(str,"#retdel" ) == 0){check = true; ifc = ifc_gen(); cmd_proc_0(csvi,ifc,EX_RETDEL);}
      else if (strcmp(str,"#replace") == 0){check = true; ifc = ifc_gen(); cmd_proc_2(csvi,ifc,EX_REP   );}
      else if (strcmp(str,"#log"    ) == 0){check = true; ifc = ifc_gen(); cmd_proc_2(csvi,ifc,EX_LOG   );}
      else if (strcmp(str,"#go"     ) == 0){check = true; ifc = ifc_gen(); cmd_proc_1(csvi,ifc,EX_GO    );}
      else if (strcmp(str,"#act"    ) == 0){check = true; ifc = ifc_gen(); cmd_proc_1(csvi,ifc,EX_ACT   );}
      else if (strcmp(str,"#stop"   ) == 0){check = true; ifc = ifc_gen(); cmd_proc_1(csvi,ifc,EX_STOP  );}
      if (check == false){
        printf("csv_file syntax error.[line:%d][string:%s]\n",l,str);
        okFlg = false;
      }
      break;
    LOOP_END
  }

  if ((mon_flg) && (okFlg)){
    printf("---------- [Debug Information] ---------------\n");
    printf("start_name=%s\n",start_name->c_str());
    StateC *sc;
    execC *exec;
    jokenC *jkc;

    MEM_LOOP(sc,StateC,state_fp)
      printf("State[%s]\n",sc->state_name->c_str());
      MEM_LOOP(ifc,IfC,sc->if_fp)
        printf("  if (");
        MEM_LOOP(jkc,jokenC,ifc->joken_fp)
          printf("<%d:%s>(%d)",jkc->joken_kbn,jkc->parm->c_str(),jkc->aAFlg);
        LOOP_END
        printf("){");
        MEM_LOOP(exec,execC,ifc->exec_fp)
          printf("[%d:%s:%s]",exec->exec_kbn,exec->parm->c_str(),exec->parm2->c_str());
        LOOP_END
        printf("}\n");
      LOOP_END
    LOOP_END
    printf("\n");
    }

  it->srch_key = start_name->c_str();
  if (state_fp->mem_srch() != 0){printf("state act:no state[%s]\n",start_name->c_str());}
  else{
    it->alloc_ptr = (StateC *)state_fp->mem_link_ptr_rd();
    act_fp->mem_srch_alloc();
  }
    
  delete csvi;  
  return(okFlg);
}


// # command #####
void TextCtlInf::cmd_proc_0(CsvAnl_C *csvi,IfC *ifc,int kbn){
  if (ifc == NULL){return;}
  char *str;

  it->alloc_ptr = new execC(kbn,"");
  ifc->exec_fp->mem_alloc();
}


// # command #####
void TextCtlInf::cmd_proc_1(CsvAnl_C *csvi,IfC *ifc,int kbn){
  if (ifc == NULL){return;}
  CSV_LOOP(csvi,str,NON_SP_PUSH)
    it->alloc_ptr = new execC(kbn,(char *)str);
    ifc->exec_fp->mem_alloc();
    break;
  LOOP_END
}

// # command #####
void TextCtlInf::cmd_proc_2(CsvAnl_C *csvi,IfC *ifc,int kbn){
  if (ifc == NULL){return;}
  char *parm;
  parm = NULL;
  int mode = 0;
  execC *ec = NULL;
  CSV_LOOP(csvi,str,NON_SP_PUSH)
    if (mode == 0){
      if (parm == NULL){parm = str; continue;}
      ec = new execC(kbn,parm);
      ec->parm2->set((char *)str);
      it->alloc_ptr = ec;
      ifc->exec_fp->mem_alloc();
      mode = 1;
      continue;
    }
    if (strcmp(str,"aA_same") == 0){ec->aAFlg = true;} // Ver 1.04
  LOOP_END
}

// # #st #####
void TextCtlInf::st_proc(CsvAnl_C *csvi){
  CSV_LOOP(csvi,str,NON_SP_PUSH)
    if (strcmp(start_name->c_str(),"") == 0){start_name->set((char *)str);}
    it->srch_key = str;
    if (state_fp->mem_srch() == 0){curr_state = (StateC *)state_fp->mem_link_ptr_rd();}
    else{
      curr_state = new StateC(it,(char *)str);
      it->alloc_ptr = curr_state;
      state_fp->mem_srch_alloc();
    }
    break;
  LOOP_END
  jokenC *jkc;
  MEM_LOOP(jkc,jokenC,stack_fp) delete jkc; LOOP_END
  stack_fp->mem_del_all();
  need_flg = true;
}


// # #st_init #####
void TextCtlInf::st_init(CsvAnl_C *csvi){
  char *str;
  taskC *tsk;
  CSV_LOOP(csvi,str,NON_SP_PUSH)
    it->srch_key = str;
    if (acton_init_fp->mem_srch() == 0){continue;}
    tsk = new taskC((char *)str);
    it->alloc_ptr = tsk;
    acton_init_fp->mem_srch_alloc();
  LOOP_END
}

// # #line_chg #####
void TextCtlInf::line_chg(CsvAnl_C *csvi){
  char *str;
  line_chgC *lc;
  char *w_line=NULL;
  char *w_str=NULL;

//printf("line_chg\n");

  CSV_LOOP(csvi,str,NON_SP_PUSH)
    if (w_line == NULL){w_line = str; continue;}
    w_str  = str;
    break;
  LOOP_END

  if (w_line == NULL){
    printf("[csv_file] line error #line_chg line = [NULL]\n");
    return;
  }

  __int64 w_suji = SujiConvEx64(w_line);
  char w[50];

  unsigned long lower = (unsigned long)(w_suji & 0xffffffff);
  unsigned long upper = (unsigned long)(w_suji >> 32);

  sprintf(w,"%08x_%08x",upper,lower);
  //sprintf(w,"%I64016x",w_suji);

  if (w_suji < (__int64)1){
    printf("[csv_file] line error #line_chg line = [%s]\n",w_line);
    return;
  }

//printf("line=%I64d\n",w_suji);

  it->srch_key = w;
  if (line_fp->mem_srch() == 0){line_fp->mem_del();}
  if (w_str == NULL){lc = new line_chgC(w_suji,"");}
  else              {lc = new line_chgC(w_suji,w_str);}
  it->alloc_ptr = lc;
  line_fp->mem_srch_alloc();
}

// # #if / #noif #####
void TextCtlInf::if_proc(CsvAnl_C *csvi,int if_kbn){
  char *str;
  int mode = 0;
  jokenC *jkc = NULL;
  CSV_LOOP(csvi,str,NON_SP_PUSH)
    if (mode == 0){
      jkc = new jokenC(if_kbn,(char *)str);
      it->alloc_ptr = jkc;
      stack_fp->mem_alloc();
      need_flg = true;
      mode = 1;
      continue;
    }
    if (strcmp(str,"aA_same") == 0){jkc->aAFlg = true;} // Ver 1.04
  LOOP_END
}
  

// # #else #####
void TextCtlInf::else_proc(CsvAnl_C *csvi){
  stack_fp->mem_mcb_end_set();
  if (stack_fp->mem_mcb_ptr_rd() == MM_NULL){return;}
  jokenC *jkc;
  jkc = (jokenC *)stack_fp->mem_link_ptr_rd();
  if (jkc->joken_kbn == J_EQ ){jkc->joken_kbn = J_NEQ;}
  else if (jkc->joken_kbn == J_NEQ){jkc->joken_kbn = J_EQ ;}

//printf("else %d-%s\n",jkc->joken_kbn,jkc->parm->c_str());

  need_flg = true;
}
  
// # #endif #####
void TextCtlInf::endif_proc(CsvAnl_C *csvi){
  stack_fp->mem_mcb_end_set();
  if (stack_fp->mem_mcb_ptr_rd() == MM_NULL){return;}
  jokenC *jkc;
  jkc = (jokenC *)stack_fp->mem_link_ptr_rd();
  delete jkc;
  stack_fp->mem_del();
  need_flg = true;
}

// # Ifc sansyutsu #####
IfC *TextCtlInf::ifc_gen(void){
  IfC *ifc;
  if (curr_state == NULL){return(NULL);}

  if (need_flg == false)
    {
    curr_state->if_fp->mem_mcb_end_set();
    if (curr_state->if_fp->mem_mcb_ptr_rd() == MM_NULL)
      {
      ifc = new IfC(it);
      it->alloc_ptr = ifc;
      curr_state->if_fp->mem_alloc();
      }
    else
      {
      ifc = (IfC *)curr_state->if_fp->mem_link_ptr_rd();
      }
    }
  else
    {
    ifc = new IfC(it);
    it->alloc_ptr = ifc;
    curr_state->if_fp->mem_alloc();
    jokenC *jkc;
    jokenC *new_jkc;
    MEM_LOOP(jkc,jokenC,stack_fp)
      new_jkc = new jokenC(jkc->joken_kbn,jkc->parm->c_str());
      new_jkc->aAFlg = jkc->aAFlg;
      it->alloc_ptr = new_jkc;


//printf("keishyo  %d-%s\n",jkc->joken_kbn,jkc->parm->c_str());


      ifc->joken_fp->mem_alloc();
    LOOP_END

//printf("---\n");


    need_flg = false;
    }  
    
  return(ifc);
}
  

// # Main Loop #####
void TextCtlInf::MainLoop(Read64_C *in_fp,Write64_C *p_out_fp,char *file_name){
  out_fp = p_out_fp;
  fin_flg = false;
  bool fn_firstFlg = true;

  // # active state list initialize #####
  act_fp->mem_del_all();

  // # initialize state machine set #####
  fin_msg_flg = false;
  bool hit_flg = false;
  taskC *d_tsk;
  taskC *s_tsk;
  MEM_LOOP(s_tsk,taskC,acton_init_fp)
    hit_flg = true;
    taskC *d_tsk = new taskC(s_tsk->c_str());
    it->alloc_ptr = d_tsk;
    it->srch_key  = s_tsk->c_str();
    acton_fp->mem_srch_alloc();
  LOOP_END

  if (hit_flg == false){
    if (strcmp(start_name->c_str(),"") != 0){
      d_tsk = new taskC(start_name->c_str());
      it->alloc_ptr = d_tsk;
      it->srch_key  = start_name->c_str();
      acton_fp->mem_srch_alloc();
    }
  }

  // # line chg init #####
  line_fp->mem_mcb_top_set();

  // # file read main loop #####
  for(g_line=(__int64)1;;g_line++){
    if (fin_flg){break;}

    // file read
    char *buff = in_fp->read();
    if (buff == NULL){break;}
    //if (*buff == 0x00){continue;}
    w_buff->set(buff);

//printf("[%I64d][%s]\n",g_line,buff);

    // # exec #####
    exec_state();

    if (out_fp != NULL){
      if (text_del_flg == false){
        sprintf(out_fp->buff,"%s",w_buff->c_str()); out_fp->write();
        if (retdelFlg == false){
          if (in_fp->return0dGet() | in_fp->return0aGet()){out_fp->writeln((unsigned char *)"");}
        }
      } else {g_line--;}
    }
    ins_after(out_fp);
  }
  ins_after(out_fp);

  // # log output #####
  logC *lg;
  if (log_fp != NULL){
    in_fp->seek((__int64)0);
    logc_fp->mem_mcb_top_set();
    for(g_line=1;;g_line++){
      if (logc_fp->mem_mcb_ptr_rd() == MM_NULL){break;}
      else{
        lg = (logC*)logc_fp->mem_link_ptr_rd();
      }
      
      char *buff = in_fp->read();
      if (buff == NULL){break;}
//      if (*buff == 0x00){continue;}

      if (lg->line == g_line){

        if (fn_firstFlg){
          fn_firstFlg = false;
          log_fp->write((unsigned char *)"#FILE,");
          log_fp->csvWrite(file_name);
          log_fp->writeln((unsigned char *)"");
        }


        sprintf(log_fp->buff,"#line_chg,%I64d,",g_line); log_fp->write();
        log_fp->csvWrite(buff);
        log_fp->writeln((unsigned char *)"");
        logc_fp->mem_mcb_next_set();
      }
    }
    log_fp->writeln((unsigned char *)"");
    MEM_LOOP(lg,logC,logc_fp) delete lg; LOOP_END
    logc_fp->mem_del_all();
  }
}


// # insert_after(#ins_after/#ins_file_after) #####
void TextCtlInf::ins_after(Write64_C *out_fp){
  if (out_fp == NULL){return;}
  sChar *s_str;
  MEM_LOOP(s_str,sChar,insert_fp)
    out_fp->writeln((unsigned char *)s_str->c_str());
    g_line++;
    delete s_str;
  LOOP_END
  insert_fp->mem_del_all();

  MEM_LOOP(s_str,sChar,insert_file_fp)
    Read64_C *fp = new  Read64_C(s_str->c_str(),"rt",10240);
    if (fp->okCheck()) {
      for(;;){
        char *b = fp->read();
        if (b == NULL) {
          break;
        }
        out_fp->writeln((unsigned char *)b);
        g_line++;
      }
    }
    else {
      printf("[%I64d]file open error. file = %s\n",g_line,s_str->c_str());
    }
    delete fp;
    delete s_str;
  LOOP_END
  insert_file_fp->mem_del_all();

  }

// # Exec #####
void TextCtlInf::exec_state(){
  taskC *tsk;

  Application->ProcessMessages();  // Ver 1.00

  // # State Off #####
  MEM_LOOP(tsk,taskC,actoff_fp)
    it->srch_key = tsk->c_str();
    if (act_fp->mem_srch() != 0){printf("state stop:no state[%s]\n",tsk->c_str()); continue;}
    act_fp->mem_del();
  LOOP_END

  // # State On #####
  MEM_LOOP(tsk,taskC,acton_fp)
    it->srch_key = tsk->c_str();
    if (state_fp->mem_srch() != 0){printf("state act:no state[%s]\n",tsk->c_str()); continue;}
    if (act_fp->mem_srch() != 0)
      {
      it->alloc_ptr = (StateC *)state_fp->mem_link_ptr_rd();
      act_fp->mem_srch_alloc();
      }
  LOOP_END

  // # state on/off list delete #####
  MEM_LOOP(tsk,taskC,acton_fp ) delete tsk; LOOP_END
  MEM_LOOP(tsk,taskC,actoff_fp) delete tsk; LOOP_END
  acton_fp->mem_del_all();
  actoff_fp->mem_del_all();

  // # State Machine Exec #####
  text_del_flg = false;
  retdelFlg    = false;
  IfC *ifc;
  bool hit_flg = false;

  w_buff_if->set(w_buff);
  MEM_LOOP(curr_state,StateC,act_fp)
    if (trace_flg){
      printf("[%I64d][%-8s][%s]\n",g_line,curr_state->state_name->c_str(),w_buff->c_str());
      //printf("[%-8s][%s]\n",curr_state->state_name->c_str(),w_buff->c_str());
    }

    hit_flg = true;
    MEM_LOOP(ifc,IfC,curr_state->if_fp)
      if (joken_check(ifc)){exec(ifc);}
    LOOP_END
  LOOP_END

  // # line chg exec #####
  line_chgC *lc;

  if (line_fp->mem_mcb_ptr_rd() != MM_NULL){
    lc = (line_chgC *)line_fp->mem_link_ptr_rd();

    if (lc->line == g_line){
      printf("#line_chg exec[line:%I64d][%s]\n",lc->line,lc->str->c_str());
      w_buff->set(lc->str->c_str());
      line_fp->mem_mcb_next_set();
      hit_flg = true;
    }
  }

  if (out_fp == NULL){
    if (hit_flg == false){fin_flg = true;}
  }

  if ((fin_msg_flg == false) && (hit_flg == false)){
    printf("active state none.\n");
    fin_msg_flg = true;
  }
}

// # joken check #####
bool TextCtlInf::joken_check(IfC *ifc){
  jokenC *jc;

  MEM_LOOP(jc,jokenC,ifc->joken_fp)

    if (jc->joken_kbn == J_EQ){
      if (jc->aAFlg){  // Ver 1.04
        if (w_buff_if->grepAa_same(jc->parm->c_str(),0) == -1){return(false);}
      } else {
        if (w_buff_if->grep(jc->parm->c_str(),0) == -1){return(false);}
      }
    }
    if (jc->joken_kbn == J_NEQ){
      if (jc->aAFlg){  // Ver 1.04
        if (w_buff_if->grepAa_same(jc->parm->c_str(),0) != -1){return(false);}
      } else {
        if (w_buff_if->grep(jc->parm->c_str(),0) != -1){return(false);}
      }
    }
  LOOP_END
  return(true);
}

// # exec #####
void TextCtlInf::exec(IfC *ifc){
  execC *ec;

  MEM_LOOP(ec,execC,ifc->exec_fp)

    if (inst_flg){
      if (ec->exec_kbn == EX_PRINTF   ){printf("[exec:EX_PRINTF   ]");}
      if (ec->exec_kbn == EX_GO       ){printf("[exec:EX_GO       ]");}
      if (ec->exec_kbn == EX_ACT      ){printf("[exec:EX_ACT      ]");}
      if (ec->exec_kbn == EX_STOP     ){printf("[exec:EX_STOP     ]");}
      if (ec->exec_kbn == EX_INS      ){printf("[exec:EX_INS      ]");}
      if (ec->exec_kbn == EX_INS_FILE ){printf("[exec:EX_INS_FILE ]");}
      if (ec->exec_kbn == EX_INS_FILE_AFTER ){printf("[exec:EX_INS_FILE_AFTER]");}
      if (ec->exec_kbn == EX_INS_AFTER){printf("[exec:EX_INS_AFTER]");}
      if (ec->exec_kbn == EX_CHG      ){printf("[exec:EX_CHG      ]");}
      if (ec->exec_kbn == EX_DEL      ){printf("[exec:EX_DEL      ]");}
      if (ec->exec_kbn == EX_REP      ){printf("[exec:EX_REP      ]");}
      if (ec->exec_kbn == EX_LOG      ){printf("[exec:EX_LOG      ]");}
      if (ec->exec_kbn == EX_RETDEL   ){printf("[exec:EX_RETDEL   ]");}

      printf("[parm1:%s][parm2:%s]\n",ec->parm->c_str(),ec->parm2->c_str());
    }

    if (ec->exec_kbn == EX_PRINTF){
      printf("[%I64d]%s : %s\n",g_line,ec->parm->c_str(),w_buff->c_str());
    }
    if (ec->exec_kbn == EX_GO){
      it->srch_key  = ec->parm->c_str();
      if (acton_fp->mem_srch() != 0){
        it->alloc_ptr = new taskC(ec->parm->c_str());
        acton_fp->mem_srch_alloc();
      }

      it->srch_key  = curr_state->state_name->c_str();
      if (actoff_fp->mem_srch() != 0){
        it->alloc_ptr = new taskC(curr_state->state_name->c_str());
        actoff_fp->mem_alloc();
      }
    }
    if (ec->exec_kbn == EX_ACT){
      it->srch_key  = ec->parm->c_str();
      if (acton_fp->mem_srch() != 0){
        it->alloc_ptr = new taskC(ec->parm->c_str());
        acton_fp->mem_alloc();
      }
    }
    if (ec->exec_kbn == EX_STOP){
      it->srch_key  = ec->parm->c_str();
      if (actoff_fp->mem_srch() != 0){
        it->alloc_ptr = new taskC(ec->parm->c_str());
        actoff_fp->mem_alloc();
      }
    }
    if (ec->exec_kbn == EX_INS){
      if (out_fp != NULL){
        out_fp->writeln((unsigned char *)ec->parm->c_str());
        g_line++;
      }
    }

    if (ec->exec_kbn == EX_INS_FILE){
      if (out_fp != NULL){
        Read64_C *fp = new  Read64_C(ec->parm->c_str(),"rt",10240);
        if (fp->okCheck()) {
          for(;;){
            char *b = fp->read();
            if (b == NULL) {
              break;
            }
            out_fp->writeln((unsigned char *)b);
            g_line++;
          }
        }
        else {
          printf("[%I64d]file open error. file = %s\n",g_line,ec->parm->c_str());
        }
        delete fp;
      }
    }

    if (ec->exec_kbn == EX_INS_AFTER){
      if (out_fp != NULL){
        sChar *s_str = new sChar(ec->parm->c_str());
        it->alloc_ptr = s_str;
        insert_fp->mem_alloc();
      }
    }
    if (ec->exec_kbn == EX_INS_FILE_AFTER){
      if (out_fp != NULL){
        sChar *s_str = new sChar(ec->parm->c_str());
        it->alloc_ptr = s_str;
        insert_file_fp->mem_alloc();
      }
    }
    if (ec->exec_kbn == EX_DEL){
      text_del_flg = true;
    }

    if (ec->exec_kbn == EX_RETDEL){
      retdelFlg = true;
    }

    if (ec->exec_kbn == EX_CHG){
      sCharGrep *w = new sCharGrep(ec->parm->c_str());
      w->replace_all("#@@#",w_buff->c_str());
      w_buff->set(w->c_str());
      delete w;
    }

    if (ec->exec_kbn == EX_REP){
      if (ec->aAFlg){ // Ver 1.04
        w_buff->replace_allAa_same(ec->parm->c_str(),ec->parm2->c_str());
       } else {
        w_buff->replace_all(ec->parm->c_str(),ec->parm2->c_str());
       }
    }
    if (ec->exec_kbn == EX_LOG){
      if (log_fp != NULL){
        __int64 back_cnt = SujiConvEx64(ec->parm->c_str());
        __int64 next_cnt = SujiConvEx64(ec->parm2->c_str());
        for(__int64 i=(__int64)0;i<back_cnt;i++){logc_store(g_line-back_cnt+i);}
        logc_store(g_line);
        for(__int64 i=(__int64)0;i<next_cnt;i++){logc_store(g_line+i+1);}
      }
    }
  LOOP_END
}

// # logc_store #####
void TextCtlInf::logc_store(__int64 p_line){
  logC *lg;
  char w[10];
  if (p_line < (__int64)1){return;}

  unsigned long lower = (unsigned long)(p_line & 0xffffffff);
  unsigned long upper = (unsigned long)(p_line >> 32);

  sprintf(w,"%08x_%08x",upper,lower);
  //printf("%08x_%08x\n",upper,lower);

  //sprintf(w,"%I64016x",p_line);

  it->srch_key = w;
  if (logc_fp->mem_srch() != 0){
    lg = new logC(w,p_line);
    it->alloc_ptr = lg;
    logc_fp->mem_srch_alloc();
  }
}

  
