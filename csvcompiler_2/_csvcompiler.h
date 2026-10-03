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
//  CSV COMPILER Header
//

// pass 1 message
#define MSG_000 "000,command error.."
#define MSG_001 "001,type multiple."
#define MSG_002 "002,type undefine."
#define MSG_003 "003,variable name undefine."
#define MSG_004 "004,un numeric."
#define MSG_005 "005,member multiple."
#define MSG_006 "006,type error."

// pass 2 message
#define MSG_101 "101,function multiple."
#define MSG_102 "102,function undefine."
#define MSG_103 "103,variable multiple."
#define MSG_104 "104,irq routine not parameter."
#define MSG_105 "105,irq line not define."

// pass 3 message
#define MSG_201 "201,if-endif nest unmatch."
#define MSG_202 "202,for-endfor nest unmatch."
#define MSG_203 "203,if noexist."
#define MSG_204 "204,else multiple."
#define MSG_205 "205,for noexist."
#define MSG_206 "206,call function undefined."
#define MSG_207 "207,call function noexist."
#define MSG_208 "208,paramter unmatch."
#define MSG_209 "209,start function undefined."
#define MSG_210 "210,elseif error."

// pass calc message
#define MSG_301 "301,[ - ] unmatch."
#define MSG_302 "302,( - ) unmatch."
#define MSG_303 "303,variable undefined."

// #set instruction set 
#define K_val_const 0      // 書式:レジスタA,固定値z1 ,加算値,減算値      --> レジスタA    = 固定値z1     + 加算値 - 減算値
#define K_val_preg  1      // 書式:レジスタA,レジスタB,加算値,減算値      --> レジスタA    = *(レジスタB) + 加算値 - 減算値
#define K_val_reg   2      // 書式:レジスタA,レジスタB,加算値,減算値      --> レジスタA    = レジスタB    + 加算値 - 減算値
#define K_ptr_const 3      // 書式:レジスタA,レジスタB,加算値,減算値      --> *(レジスタA) = 固定値z1     + 加算値 - 減算値
#define K_ptr_reg   4      // 書式:レジスタA,レジスタB,加算値,減算値      --> *(レジスタA) = *(レジスタB) + 加算値 - 減算値
#define K_offset_calc 5    // 書式:レジスタA,レジスタB,サイズ,オフセット  --> レジスタA = レジスタA + レジスタA * サイズ + オフセット

// 特別なレジスタ
#define V_prg_cnt   0      // プログラムカウンタ レジスタ
#define V_stk_cnt   1      // スタックポインタ レジスタ
#define V_parm_cnt  2      // パラメータ数 レジスタ
#define V_sum       3      // 条件式の結果を格納するレジスタ
#define V_val_assign 10    // ワークレジスタの初めのナンバー

// 変数区分
#define AttrVarGlobal  0   // グローバル変数
#define AttrVarParm    1   // パラメータ変数
#define AttrVarLocal   2   // ローカル変数
#define AttrVarConst   3   // 固定値


// 型定義 --------------------
class typC{
  public:
    sChar        *name;      // 型名
    int           size;      // この型のサイズ  Pass3で算出
    MemHeader_T  *it;
    MEM_FP       *member_fp; // メンバリスト(CELL:memberC)
    typC(MemHeader_T *p_it,char *p_name);
    ~typC();
};


// メンバ定義 -----------------
class memberC{
  public:
    sChar  *name;      // メンバ名
    int     size;      // このメンバのサイズ  Pass3で算出
    int     offset;    // オフセット          Pass3で算出
    int     ary_su;    // 配列数
    typC   *typ;       // 型定義（NULLの時はint)
    bool    flgPtr;    // ポインタ
    memberC(char *p_name,int p_ary,typC *p_typ,bool p_flgPtr);
    ~memberC();
};



// 変数定義 -------------------- 
class varC{
  public:
    sChar        *name;      // 変数名
    int           size;      // この変数のサイズ    Pass3で算出
    int           ary_su;    // 配列数
    typC         *typ;       // 型定義（NULLの時はint)
    int           map;       // マッピングアドレス  Pass3で算出
    bool          flgPtr;    // ポインタ
    bool          flgConst;  // 固定値
    varC(char *p_name,int p_ary,typC *p_typ,bool p_flgPtr);
    varC(char *p_name);
    ~varC();
};

// 式 --------------------
class calcC{
  public:
    sChar        *siki;      // 型名
    int           reg_su;    // 必要レジスタ数
    int           sikiNo;    // 式の番号
    calcC(char *p_siki,int p_reg_su,int p_sikiNo);
    ~calcC();
};


// 命令コード --------------------
class codeC{
  public:
    sChar        *code;      // コード名
    unsigned long parm[5];   // パラメータ
    sChar        *call_name; // 仮サブルーチンコール名
    sChar        *src;       // ソース
    codeC(char *p_code,int p0,int p1,int p2,int p3,int p4);
    codeC(char *p_code,char *p_call_name,int p0,int p1);
    ~codeC();
};


// プログラム --------------------
class prgC{
  public:
    sChar        *name;      // プログラム名
    int           size;      // プログラムの大きさ
    int           parm_su;   // パラメータ数
    int           local_su;  // ローカル数
    bool          irq_flg;   // IRQルーチン  Ver 1.01
    int           irq_level; // IRQルーチンの優先レベル Ver 1.02
    sChar        *irq_line;  // IRQにアサインされている割り込み信号 Ver 1.02


    MemHeader_T  *it;
    MEM_FP       *parm_fp;   // パラメータ変数リスト(CELL:varC)
    MEM_FP       *local_fp;  // ローカル変数リスト(CELL:varC)
    MEM_FP       *code_fp;   // コードリスト(CELL:codeC)
    int           map;       // パラメータとローカル変数で使用する領域サイズ Pass3で算出
    prgC(MemHeader_T *p_it,char *p_name,bool p_irq_flg,int p_irq_level,char *p_irq_line);
    ~prgC();
};


// 相対ジャンプ計算 --------------------
class jmpC{
  public:
    codeC        *code;    // 未解決コード
    prgC         *prg;     // 未解決プログラム
    jmpC(codeC *p_code,prgC *p_prg);

};

/*
// ＩＦ制御 --------------------
class ifC{
  public:
    codeC        *svCode;    // ＩＦ／ＥＬＳＥ未解決コード
    bool          ifFlg;     // ＩＦ／ＥＬＳＥを表示するフラグ
    ifC(codeC *p_code,bool p_ifFlg);
};
*/

// ＩＦ制御 --------------------
class ifC{
  public:
    MemHeader_T  *it;
    codeC        *svCode;    // ＩＦ／ＥＬＳＥ未解決コード
    MEM_FP       *code_fp;   // 未解決コードリスト(CELL:codeC)
    int           ifKind;    // =0:if =1:else if =2:else
    ifC(MemHeader_T  *p_it,codeC *p_code);
    ~ifC();
};




// ＦＯＲ制御 --------------------
class forC{
  public:
    codeC        *svCode;    // ＦＯＲ未解決コード
    int           loop_ptr;  // loop戻り位置（continue実行位置）
    sChar        *var;       // カウント変数
    MemHeader_T  *it;
    MEM_FP       *break_fp;  // ＢＲＥＡＫ未解決コードリスト(CELL:codeC)
    forC(MemHeader_T  *p_it,codeC *p_code,int p_loop_ptr,char *p_var);
    ~forC();
};

// ＥＸＴＥＮＤ制御 --------------------
class extendC{
  public:
    sChar        *format;    // ディスプレイフォーマット
    int           exNo;      // Ｐｒｉｎｔｆ　Ｎｏ
    int           parmSu;    // パラメータ数
    int           regNo;     // スタートレジスタＮｏ
    extendC(char *p_format,int p_exNo,int p_parmSu,int p_regNo);
    ~extendC();
};

// ＰＲＩＮＴＦ制御 --------------------
class printfC{
  public:
    sChar        *format;    // ディスプレイフォーマット
    int           prNo;      // Ｐｒｉｎｔｆ　Ｎｏ
    int           parmSu;    // パラメータ数
    int           regNo;     // スタートレジスタＮｏ
    printfC(char *p_format,int p_prNo,int p_parmSu,int p_regNo);
    ~printfC();
};

// 式-解析結果格納 --------------------
class calcSikiC{
  public:
    bool          errFlg;   // エラーあり／なし
    MemHeader_T  *it;
    MEM_FP       *var_fp;   // 変数-解析結果が引数として代入されている。(CELL:calcVarC)
    calcC        *siki;     // 式実体へのリンク
    calcSikiC(MemHeader_T *p_it);
    ~calcSikiC();
};

// メンバ変数-解析結果格納 --------------------
class calcMemC{
  public:
    sChar     *name;    // メンバ名、又は変数名
    calcSikiC *ary;     // 配列のインデックスの式（ない時はＮＵＬＬ）
    memberC   *mem;     // メンバ実態へのリンク（変数の時はＮＵＬＬ）
    calcMemC(char *p_name,memberC *p_mem);
    calcMemC(char *p_name);
    ~calcMemC();
};


// 変数-解析結果格納 --------------------
class calcVarC{
  public:
    bool          errFlg;    // エラーあり／なし
    MemHeader_T  *it;
    MEM_FP       *member_fp; // aaa[x].bbb[y].ccc[z]の時、aaa,bbb,cccに対しての階層メンバ情報がリストで格納されている。(CELL:calcMemC)
    int           varKbn;    // 変数区分（AttrVarGlobal/AttrVarParmVal/AttrVarParmPtr/AttrVarLocal)
    bool          flgPtr;    // @変数の時true
    bool          flgMem;    // メンバあり
    varC         *var;       // 変数実体へのリンク
    calcSikiC    *ary;       // 配列のインデックスの式（ない時はＮＵＬＬ）
    calcVarC(MemHeader_T *p_it,bool p_flgPtr);
    ~calcVarC();
};


// インターフェース --------------------
class Inf_T{
  public:
    MemHeader_T  *it;
    MEM_FP       *typ_fp;    // 型名リスト(CELL:typC)
    MEM_FP       *prg_fp;    // プログラムリスト(CELL:prgC)
    MEM_FP       *calc_fp;   // プログラムリスト(CELL:calcC)
    MEM_FP       *global_fp; // プログラムリスト(CELL:varC)
    int           global_su; // グローバル数
    MEM_FP       *if_fp;     // IFネスト用制御リスト(CELL:ifC)
    int           if_su;     // IFネストチェック数
    MEM_FP       *for_fp;    // FORネスト用制御リスト(CELL:forC)
    int           for_su;    // FORネストチェック数
    int           map;       // マッピング
    int           stk_map;   // グローバルスタックマップ
    int           reg_max;   // 必要レジスタ最大数
    CsvAnl_C     *csvi;      // ＣＳＶファイル制御インターフェース
    typC         *g_typ;     // タイプ
    prgC         *g_prg;     // プログラム
    int           prg_cnt;   // プログラムカウンタ
    int           siki_cnt;  // 式番号
    MEM_FP       *link_fp;   // 未解決コード(CELL:codeC)
    int           start_map; // スタートマップ
    int           errCnt;    // エラーカウント
    int           line_cnt;  // 行カウンタ
    int           printf_cnt; // ＰＲＩＮＴＦ文用カウンタ
    MEM_FP       *printf_fp;  // ＰＲＩＮＴＦ文用リスト(CELL:printfC)
    int           extend_cnt; // ＥＸＴＥＮＤ文用カウンタ
    MEM_FP       *extend_fp;  // ＥＸＴＥＮＤ文用リスト(CELL:extendC)
    MEM_FP       *jmp_fp;    // 未解決相対ジャンプリスト(CELL:jmpC)
    MEM_FP       *src_fp;    // ソースコード
    sChar        *src_str;   // ソース文字列
    bool          valueFlg;  // 値代入フラグ
    int           irq_number; // IRQルーチンの数


    // コンストラクタ/デストラクタ
    Inf_T();
    ~Inf_T();

    // プロトタイプ宣言（式解析）
    calcSikiC *calcPass1_Siki      (char *p_str);
    calcVarC  *calcPass1_varCheck  (char *p_str);
    bool       calcPass1_enzanCheck(char  c);
    int        calcPass1_constCheck(char *str);
    void       calcPass2_Siki(calcSikiC *siki          ,int p_reg_no);
    bool       calcPass2_Ptr (calcVarC *var            ,int p_reg_no);
    void       calcPass2_Var (calcVarC *var            ,int p_reg_no);
    void       calcPass2_Val (calcVarC *var            ,int p_reg_no);
    bool       calcApi_Ptr   (char *p_var              ,int p_reg_no);
    bool       calcApi_Var   (char *p_var              ,int p_reg_no);
    bool       calcApi_Siki  (char *p_siki             ,int p_reg_no);
    bool       calcApi_Set   (char *p_var ,char *p_siki,int p_reg_no);
    bool       calcApi_PtrSet(char *p_var ,char *p_siki,int p_reg_no);
    bool       calcApi_If    (char *p_siki             ,int p_reg_no);

    // プロトタイプ宣言（ベース）
    void   Log           (bool ok,char *code,char *msg                 );
    void   regMax_set    (int val                                      );
    codeC *codeAdd       (char *code,int p0,int p1,int p2,int p3,int p4);
    codeC *codeAdd       (char *code,char *parm,int p0,int p1          );
    void   if_nest_add   (codeC *code                                  );
    bool   if_nest_del   (int size                                     );
    ifC   *getIfCell     (                                             );
//  void   if_nest_add   (codeC *code,bool flg                         );
//  bool   if_nest_del   (int size                                     );
    void   for_nest_add  (codeC *code,int sv_loop_ptr,char *var        );
    void   for_nest_del  (                                             );
    void   break_list_add(codeC *code                                  );

    // プロトタイプ宣言（インターフェース）
    bool   Pass1(Read64_C *in_fp                 );
    bool   Pass2(Read64_C *in_fp                 );
    void   Pass3(                                );
    bool   Pass4(Read64_C *in_fp,char *start_func);
    bool   Pass5(char *file                      );
    bool   Pass5_list(char *file                 );

    // プロトタイプ宣言（コンパイルメイン処理）
    bool   cmdCheck     (char *str   );
    void   type_rtn     (            );
    void   member_rtn   (            );
    void   func_rtn     (bool irq    );
    void   var_rtn      (int kbn     );
    int    memberSum    (memberC *mem);
    int    typeSum      (typC *typ   );
    void   func_code    (            );
    void   if_code      (            );
    void   elseif_code  (            );
    void   else_code    (            );
    void   endif_code   (            );
    void   for_code     (            );
    void   break_code   (            );
    void   continue_code(            );
    void   endfor_code  (            );
    void   return_code  (            );
    void   call_code    (            );
    void   user_code    (            );
    void   printf_code  (            );
    void   set_code     (bool flgPtr );
    void   extend_code  (            );
    void   reg          (FILE *fp,int no,bool flgPtr);

};


