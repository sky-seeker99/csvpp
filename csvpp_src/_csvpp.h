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
//  CSVPP EXEC CONTROL LIBRARY 
//

//#define cmd_MAX   103
//#define cmd_MAX   105
//#define cmd_MAX   110
//#define cmd_MAX   111
//#define cmd_MAX   113
//#define cmd_MAX   115
//#define cmd_MAX   117
//#define cmd_MAX   118
//#define cmd_MAX   119
#define cmd_MAX   121



#define mode_MAX  5

// compile error message
#define xMSG00 "C00:file no exist(File = %s)"
#define xMSG01 "C01:file name error"
#define xMSG02 "C02:variable name no define"
#define xMSG03 "C03:list name no define"
#define xMSG04 "C04:program name no define"
#define xMSG05 "C05:class name no define"
#define xMSG06 "C06:class name duplicate define"
#define xMSG07 "C07:Syntax Error"
#define xMSG08 "C08:object name no define"

// exec error message
#define MSG01 "E01:variable undefined variable name=NULL"
#define MSG02 "E02:variable undefined variable name=%s"
#define MSG03 "E03:macro undefined macro name=NULL"
#define MSG04 "E04:macro undefined macro name=%s"
#define MSG10 "E10:for - endfor nest error"
#define MSG11 "E11:class undefine. class name=%s"
#define MSG12 "E12:duplicate variable define. variable name=%s"
#define MSG13 "E13:inherit class undefined. inherit class=%s"
#define MSG14 "E14:object undefined src object name=NULL"
#define MSG15 "E15:object undefined src object name=%s"
#define MSG16 "E16:keyword undefined variable name=NULL"
#define MSG17 "E17:format NULL"
#define MSG18 "E18:if - endif nest error"
#define MSG19 "E19:expression undefined variable name=NULL"
#define MSG20 "E20:list undefined list name=NULL"
#define MSG21 "E21:list undefined variable name=%s"
#define MSG22 "E22:loop su undefined variable name=%s"
#define MSG23 "E23:loop su error loop su=%s"
#define MSG24 "E24:file name variable name=NULL"
#define MSG25 "E25:listhead undefined list name=NULL"
#define MSG26 "E26:listhead undefined variable name=%s"
#define MSG27 "E27:index undefined variable name=NULL"
#define MSG28 "E28:parameter unmatch name=NULL"
#define MSG29 "E29:file open error name=%s"
#define MSG30 "E30:database open error name=%s"
#define MSG31 "E31:database handle error name=%s"
#define MSG32 "E32:key no define"
#define MSG33 "E33:alias error"
#define MSG34 "E34:index over name=%s"
#define MSG35 "E35:not integer value=%s"
#define MSG36 "E36:classcall object not delete object=%s"
#define MSG37 "E37:shell_begin - shell_end nest error"
#define MSG38 "E38:class_save class not found  class=%s"
#define MSG39 "E39:class_load file not found  file=%s"


#define DFP fprintf(debug_fp,
//#define DFP printf(


// ---------------------------------------------
// @1:ExecCtlInf_T(MemHeader_T *p_it)
// ---------------------------------------------
class ExecCtlInf_T{
  public:
    //  Main Information List
    MemHeader_T *it;            // Mem Interface
    MEM_FP      *class_fp;      // Class Define List
    MEM_FP      *classcall_fp;  // Class Call List
    MEM_FP      *object_fp;     // Object Build List
    MEM_FP      *listcall_fp;   // List Call List
//    MEM_FP      *work_fp;       // Working Variable List
    MEM_FP      *mac_fp;        // Macro Call List
    MEM_FP      *if_fp;         // IF Statement List
    MEM_FP      *for_fp;        // FOR Statement List
    MEM_FP      *alias_fp;      // alias list
    VariableArray_C *shell_fp;  // shell command

    MEM_FP      *inc_fp;        // include sarch path list
    MEM_FP      *env_fp;        // envroment variable list

    //  Case do
    MEM_FP      *casedo_fp;     // %casedo
    bool         casedo_use;    //  =falseの時、casedo_inf を登録する必要がある。

    Utf8Area_C *utf8_inf;       // %utf-8 用 Ver 1.47

    //  Database Interface
//    CsvDb_T     *db_inf;        // Database Interface

    // grep/replace
    sCharGrep *grep; 

	// to binary
	binConv_C *binConv;

    // message
//    char msg[1000];

    // string extend
    sCharEX *str_ext;

    // program line -> string analize
    progLine_C *prog_anl;

    // varible control
    varCtl_C *var_ctl;

    // soeji token
    tokenAnl_C *s_token;

    //  Error Message
    sChar        *msg_cmd;
    sChar        *msg_macro;
    sChar        *msg_object;

    //  Error Flg & Status Flg
    sChar        *dir;                 // Include Directory
    int           err_cnt;             // syntax error cnt
    int           mode;                // syori mode / =0:init =1:#Pclass =2:#Pclasscall =3:#Plist  =4:#Pst

    // Checking Data
    int           chk  [cmd_MAX ][mode_MAX];  // =-1:Syntax Error =0:OK  =Else:Moving Mode
    sChar        *chks [cmd_MAX ];            // Checking String

    // etc interface
    CalcInf_T    *ci;                  // calc interface
    CalcInf64_T  *ci64;                // calc interface  (64bit)   Ver 1.30
    CalcInf_f_T  *ci_f;                // calc interface  (float)   Ver 1.31
    Time_T       *timectl;             // time interface
    Date_T       *datectl;             // date interface
    FileGet_T    *file_get;            // file list get interface
    FileHandle_T *file_handle;         // file handla interface

    // Inner Routine Variables
    Class_T      *cl;                  // Current Class
    Classcall_T  *cc;                  // Current Class Call
    Object_T     *ob;                  // Current Object
    int           idx;                 // Routine Index

    // Work Area
    VariableArea_C  *g_w0,*g_w1,*g_w2,*g_w3,*g_w4,*g_w5,*g_w6; // Ver 1.40
    int           string_MAX;

    // Write File Pointer
    FILE         *fp;
    FILE         *debug_fp;
    FILE         *back_fp;

    // Debug mode
    bool          debug_mode;
    sChar        *debug_string;

    // shell exec flg
    bool shell_flg;
    sChar        *shell_default;

    //  exec interface
    PgExec_C     *pg_exec;

	// filename analizer
	FileNameAnl_C *filename_anl;

    // space push flg
    bool sp_push_flg; // Ver 1.25

    // alias count
    unsigned int alias_num;

    // %csv_set
    CsvAnl_C *csv_anl;  // Ver 1.61

    // %url_anl
	UrlNameAnl_C *url_anl;  // Ver 1.62

	// %var_n
	int var_num;

	// %rtn_mode
	bool rtn_mode;
	bool firstCsvFlag;

    // %shell_begin - %shell_end  Ver 1.66
    ShellNest_T *shell_nest;

	// %include_uniq  1.71
	bool inc_uniq_mode;
	VariableArray_C *inc_uniq_fp;

  public:
    // User Interface   
                 ExecCtlInf_T();
                ~ExecCtlInf_T();
    void        ProgramArgRead(int argc,char *argv[]);
    void        CsvFileRead    (char *csv_file);
    void        ExecMain       (FILE *out_fp);
    int         Err_Rd         (){return(err_cnt);}
    void        DebugFp        (FILE *p_fp){debug_fp = p_fp;}
    void        ClassPrintf    ();
    void        ClassCallPrintf();
    void        VersionPrintf  ();
    char       *x_getenv       (char *str);
    void        shell_exec     ();

  // Base Program
  private:
    void        SelGetReset    (CsvInf_T *csvi_fp);
    void        SelGetReset    (Program_C *pc);
    char       *SelGet         ();
    char       *SelGet_direct  ();
    void        SelGet_skip    ();
    unsigned int commandSel(char *str);

    McbArea_C  *from_srch      (Program_C *pc,MEM_FP *prg_fp);
    void        WorkVarLvlAdd  ();
    void        WorkVarLvlDel  ();
    VarCell_T  *VarSrch        (char *key);
    char       *VarSrch_Atai   (char *key);
    void        StrChg         (VariableArea_C *rep,char *str,char sep);
    long        VarToInt       (char *key);
    void        include_rtn    (CsvInf_T *csvi_fp);
    void        include_dir_rtn(CsvInf_T *csvi_fp);
    void        include_uniq_rtn(CsvInf_T *csvi_fp);  // Ver 1.71
	void        var_rtn        (CsvInf_T *csvi_fp);
    void        var_n_rtn      (CsvInf_T *csvi_fp);
	void        varlist_rtn    (CsvInf_T *csvi_fp);
    void        idx_rtn        (CsvInf_T *csvi_fp);
    void        list_rtn       (CsvInf_T *csvi_fp);
    void        st_rtn         (CsvInf_T *csvi_fp);
    void        class_rtn      (CsvInf_T *csvi_fp);
    void        classcall_rtn  (CsvInf_T *csvi_fp);
    void        version_rtn    (CsvInf_T *csvi_fp);
    void        member_area_rtn(CsvInf_T *csvi_fp);
    void        pg_write_rtn   (CsvInf_T *csvi_fp);
    void        ObjectBuild    (Class_T *cl);
    void        ProgramExec    (MEM_FP *prg_fp);
    void        classset_rtn   (Program_C *pc,MEM_FP *prg_fp);
    void        do_rtn         (Program_C *pc,MEM_FP *prg_fp);
    void        casedo_rtn     (Program_C *pc,MEM_FP *prg_fp,bool kbn);
    void        casearg_rtn    (Program_C *pc,MEM_FP *prg_fp);
    void        set_rtn        (Program_C *pc,MEM_FP *prg_fp);
    void        calc_rtn       (Program_C *pc,MEM_FP *prg_fp,bool kbn);
    void        calc64_rtn     (Program_C *pc,MEM_FP *prg_fp,bool kbn);  // Ver 1.30
    void        calc_f_rtn     (Program_C *pc,MEM_FP *prg_fp,bool kbn);  // Ver 1.31
    void        if_rtn         (Program_C *pc,MEM_FP *prg_fp,bool kbn);
    void        wif_rtn        (Program_C *pc,MEM_FP *prg_fp,bool kbn);
    void        printf_rtn     (Program_C *pc);
    void        break_rtn      (Program_C *pc,MEM_FP *prg_fp);
    void        continue_rtn   (Program_C *pc,MEM_FP *prg_fp);
    void        for_rtn        (Program_C *pc,MEM_FP *prg_fp);
    void        listfor_rtn    (Program_C *pc,MEM_FP *prg_fp);
    void        listset_rtn    (Program_C *pc,MEM_FP *prg_fp);
    void        listhead_rtn   (Program_C *pc,MEM_FP *prg_fp);
    void        ary_rtn        (Program_C *pc,MEM_FP *prg_fp,int kbn);
    void        env_rtn        (Program_C *pc,MEM_FP *prg_fp,int kbn);
    void        macro_rtn      (Program_C *pc,MEM_FP *prg_fp);
    void        textfor_rtn    (Program_C *pc,MEM_FP *prg_fp);
    void        aryfor_rtn     (Program_C *pc,MEM_FP *prg_fp);
    void        sepa_rtn       (Program_C *pc,MEM_FP *prg_fp,bool kbn);
    void        call_rtn       (Program_C *pc,MEM_FP *prg_fp);
    void        arysep_rtn     (Program_C *pc,MEM_FP *prg_fp,bool kbn,bool chk);
    void        calcif_rtn     (Program_C *pc,MEM_FP *prg_fp,bool kbn);
    void        calcif64_rtn   (Program_C *pc,MEM_FP *prg_fp,bool kbn);  // Ver 1.30
    void        calcif_f_rtn   (Program_C *pc,MEM_FP *prg_fp,bool kbn);  // Ver 1.31
    void        ary_save_rtn   (Program_C *pc,MEM_FP *prg_fp); // Ver 1.60
    void        ary_load_rtn   (Program_C *pc,MEM_FP *prg_fp); // Ver 1.60
    void        csv_set_rtn    (Program_C *pc,MEM_FP *prg_fp); // Ver 1.61
    void        url_anl_rtn    (Program_C *pc,MEM_FP *prg_fp); // Ver 1.62
    void        dbswrite_rtn   (Program_C *pc,MEM_FP *prg_fp);
    void        dbsdel_rtn     (Program_C *pc,MEM_FP *prg_fp);
    void        alias_rtn      (Program_C *pc,MEM_FP *prg_fp);
    void        beta_rtn       (Program_C *pc,MEM_FP *prg_fp);
    void        sjis_utf8_rtn  (Program_C *pc,MEM_FP *prg_fp,bool toUtf8); // Ver 1.47
    void        ob_new_rtn     (Program_C *pc,MEM_FP *prg_fp); // Ver 1.48
    void        ob_del_rtn     (Program_C *pc,MEM_FP *prg_fp); // Ver 1.48
    void        ob_get_rtn     (Program_C *pc,MEM_FP *prg_fp); // Ver 1.48
    void        ob_set_rtn     (Program_C *pc,MEM_FP *prg_fp); // Ver 1.48
    void        ob_do_rtn      (Program_C *pc,MEM_FP *prg_fp); // Ver 1.48
    void        sp_push_rtn    (Program_C *pc,MEM_FP *prg_fp);
    void        chg_once_rtn   (Program_C *pc,MEM_FP *prg_fp);
    void        chg_all_rtn    (Program_C *pc,MEM_FP *prg_fp);
    void        find_rtn       (Program_C *pc,MEM_FP *prg_fp);
    void        fopen_rtn      (Program_C *pc,MEM_FP *prg_fp);
    void        fprintf_rtn    (Program_C *pc,MEM_FP *prg_fp);
    void        fcsvwrite_rtn  (Program_C *pc,MEM_FP *prg_fp);
    void        fclose_rtn     (Program_C *pc,MEM_FP *prg_fp);
    void        fspp_rtn       (Program_C *pc,MEM_FP *prg_fp);
    void        fspm_rtn       (Program_C *pc,MEM_FP *prg_fp);
    void        fsp_rtn        (Program_C *pc,MEM_FP *prg_fp);
    void        fspcnt_rtn     (Program_C *pc,MEM_FP *prg_fp);
    void        exec_rtn       (Program_C *pc,MEM_FP *prg_fp);
    void        fileexist_rtn  (Program_C *pc,MEM_FP *prg_fp);
    void        fileget_rtn    (Program_C *pc,MEM_FP *prg_fp);
    void        shell_rtn      (Program_C *pc,MEM_FP *prg_fp);
    void        st_default_rtn (Program_C *pc,MEM_FP *prg_fp);
    void        rand_rtn       (Program_C *pc,MEM_FP *prg_fp);
    void        seed_rtn       (Program_C *pc,MEM_FP *prg_fp);
    void        timenow_rtn    (Program_C *pc,MEM_FP *prg_fp);
    void        today_rtn      (Program_C *pc,MEM_FP *prg_fp);  
    void        binary_rtn     (Program_C *pc,MEM_FP *prg_fp);  
    void        argsep_rtn     (Program_C *pc,MEM_FP *prg_fp,bool kbn,bool chk);
    void        argdef_rtn     (Program_C *pc,MEM_FP *prg_fp,bool kbn,bool chk);
    void        argpart_rtn    (Program_C *pc,MEM_FP *prg_fp,bool fix);
    void        strsep_rtn     (Program_C *pc,MEM_FP *prg_fp);
    void        chgcode_rtn    (Program_C *pc,MEM_FP *prg_fp);
    void        dateint_rtn    (Program_C *pc,MEM_FP *prg_fp,bool mode);
    void        intdate_rtn    (Program_C *pc,MEM_FP *prg_fp,bool mode);
    void        debug_rtn      (Program_C *pc,bool kbn);
    void        sel_write_rtn  (Program_C *pc);
    void        constructor    (char      *str);
    void        destructor     (char      *str);
    char       *DblIns         (char      *str);
	void        file_anl_rtn   (Program_C *pc,MEM_FP *prg_fp);  // Ver 1.53
	void        set_bit_rtn    (Program_C *pc,MEM_FP *prg_fp);  // Ver 1.53
	void        need_bit_rtn   (Program_C *pc,MEM_FP *prg_fp);  // Ver 1.67
	void        rtn_mode_rtn   (Program_C *pc,MEM_FP *prg_fp);  // Ver 1.64
	void        shell_begin_rtn(Program_C *pc,MEM_FP *prg_fp);  // Ver 1.66
	void        shell_end_rtn  (Program_C *pc,MEM_FP *prg_fp);  // Ver 1.66

	void        class_save_rtn (Program_C *pc,MEM_FP *prg_fp);  // Ver 1.72
	void        class_load_rtn (Program_C *pc,MEM_FP *prg_fp);  // Ver 1.72


    void        if_core_rtn    (MEM_FP *prg_fp,bool equal_flg,Program_C *pc);
    void        if_cache_rtn   (MEM_FP *prg_fp,bool equal_flg,VariableArray_C *if_jump);
    bool        if_check_rtn   (MEM_FP *prg_fp,bool kbn,int kind);
    void        if_jump_rtn    (MEM_FP *prg_fp,bool equal_flg,McbArea_C *sv_ptr,McbArea_C *else_ptr,McbArea_C *end_ptr);


    void        ObjVerPrintf();
    void        csvfile_exec(char *csv_file);
    void        csvfile_exec_sub(CsvInf_T *csvi);

    // Error Message
    void        ErrMsg(CsvInf_T *csvi_fp,char *msg);
    void        ErrMsg(char *format,char *str);
	void        ErrMsg(char *format);


	Class_T *class_load_class_begin(CsvAnl_C *csvi);
	bool class_load_inherit(CsvAnl_C *csvi,Class_T *cl);
	bool class_load_member(CsvAnl_C *csvi,Class_T *cl);
	List_B *class_load_list_begin(CsvAnl_C *csvi,Class_T *cl);
	bool class_load_index(CsvAnl_C *csvi,List_B *lb);
	bool class_load_variable(CsvAnl_C *csvi,List_B *lb);
	Program_B *class_load_program_begin(CsvAnl_C *csvi,Class_T *cl,bool overFlag);
	bool class_load_local(CsvAnl_C *csvi,Program_B *pb);
	bool class_load_program(CsvAnl_C *csvi,Program_B *pb);

};

