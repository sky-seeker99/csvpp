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
//  TEXT Control LIBRARY
//
         
// # syori kubun #####
#define EX_PRINTF 0
#define EX_GO     1
#define EX_ACT    2
#define EX_STOP   3
#define EX_INS    4
#define EX_CHG    5
#define EX_DEL    6
#define EX_REP    7
#define EX_LOG    8
#define EX_RETDEL 9
#define EX_INS_AFTER 10
#define EX_INS_FILE 11
#define EX_INS_FILE_AFTER 12

// # log cell #####
class logC {
  public:
    sChar *s_line;
    __int64 line;
    logC(char *w ,__int64 w_line);
    ~logC();
};

// # line_chg cell #####
class line_chgC {
  public:
    sChar *sline;
    __int64 line;
    sChar *str;
    line_chgC(__int64 p_line,char *p_name);
    ~line_chgC();
};


// # task cell #####
class taskC {
  public:
    sChar *name;             // state name
    int dummy;               // dummy
    taskC(char *p_name);
    ~taskC();
    char *c_str(){return(name->c_str());}
};


// # joken kubun #####
#define J_EQ  10
#define J_NEQ 11

// # joken cell #####
class jokenC {
  public:
    sChar *parm;             // parameter
    int joken_kbn;           // joken kubun
    bool aAFlg;              // Ver 1.04 ‘å•¶Žš/¬•¶Žš“¯ˆê
    jokenC(int p_kbn,char *p_str);
    ~jokenC();
};

// # exec cel #####
class execC {
  public:
    sChar  *parm;            // parameter
    sChar  *parm2;            // parameter
    int exec_kbn;            // syori kubun
    bool aAFlg;              // Ver 1.04 ‘å•¶Žš/¬•¶Žš“¯ˆê
    ~execC();
    execC(int p_kbn,char *p_str);
};    

// # If cel #####
class IfC {
  public:
    MEM_FP  *joken_fp;       // joken list (jokenC) list
    MEM_FP  *exec_fp;        // exec list (execC) list
    IfC(MemHeader_T *p_it);
    ~IfC();
};

// # State Machine Cell #####
class StateC {
  public:
    sChar   *state_name;     // state name
    MEM_FP  *if_fp;          // if list (IfC) list
    StateC(MemHeader_T *p_it,char *p_name);
    ~StateC();
};



// # Text Controler #####
class TextCtlInf {
  public:
    MemHeader_T *it;         // MEM_FP Header
    MEM_FP   *state_fp;      // State List (StateC)  search list
    MEM_FP   *stack_fp;      // joken stack list (jokenC)
    MEM_FP   *act_fp;        // Active State (jokenC)
    MEM_FP   *acton_fp;      // Active On State (sChar)
    MEM_FP   *actoff_fp;     // Active Off State (sChar)
    MEM_FP   *acton_init_fp; // Active On Initial State
    MEM_FP   *line_fp;       // LINE CHG
    MEM_FP   *logc_fp;       // log number fp
    MEM_FP   *insert_fp;     // #ins_after
    MEM_FP   *insert_file_fp; // #ins_file_after

    sChar    *start_name;    // default start state name
    StateC   *curr_state;    // current State
    bool      need_flg;
//    bool      d_flg;         // 0x0d Flag
//    bool      a_flg;         // 0x0a Flag
    bool      NULL_flg;      // NULL Flag
    sCharGrep    *w_buff;        // Work Buffer
    sCharGrep    *w_buff_if;     // Work Buffer
    __int64    g_line;        // output line
    Write64_C *out_fp;       // output file pointer
    Write64_C *log_fp;       // output file pointer
    bool      text_del_flg;  // delete flag
    bool      fin_flg;       // finish flag
    bool      trace_flg;
    bool      inst_flg;
    bool      fin_msg_flg;
    bool       retdelFlg;

    TextCtlInf();
    ~TextCtlInf();
    bool CsvFileRead(Read64_C *csvi);
    void cmd_proc_2(CsvAnl_C *csvi,IfC *ifc,int kbn);
    void cmd_proc_1(CsvAnl_C *csvi,IfC *ifc,int kbn);
    void cmd_proc_0(CsvAnl_C *csvi,IfC *ifc,int kbn);
    void st_init(CsvAnl_C *csvi);
    void st_proc(CsvAnl_C *csvi);
    void if_proc(CsvAnl_C *csvi,int if_kbn);
    void else_proc(CsvAnl_C *csvi);
    void endif_proc(CsvAnl_C *csvi);
    IfC *ifc_gen(void);
    void MainLoop(Read64_C *in_fp,Write64_C *p_out_fp,char *file_name);
    void exec_state();
    bool joken_check(IfC *ifc);
    void exec(IfC *ifc);
    Write64_C *logfile(char *file){
      printf("log_file = %s\n",file);
      log_fp = new Write64_C(file,"wt",10240);
      if (log_fp->okCheck() == false){delete log_fp; log_fp = NULL;}
      return(log_fp);
    }
    void line_chg(CsvAnl_C *csv_fp);
    void logc_store(__int64 p_line);
    void ins_after(Write64_C *out_fp);
};




