/*

 * Copyright (c) 2010 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
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
// T_TYPE_INT64 �� define����ƌv�Z���x��int ���� __int64 �ɕύX�ł���B
// T_TYPE_FLOAT �� define����ƌv�Z���x��int ���� double �ɕύX�ł���B
// �^����T_TYPE�ɂȂ�B

#ifndef __XEXPRESSION_H_
#define __XEXPRESSION_H_

#include "t_tool_instance.h"
#include "t_area_instance.h"


#ifdef T_TYPE_INT64
  #ifdef T_TYPE
    #undef T_TYPE
  #endif
  #define T_TYPE __int64
#endif

#ifdef T_TYPE_FLOAT
  #ifdef T_TYPE
    #undef T_TYPE
  #endif
  #define T_TYPE double
#endif

#ifndef T_TYPE
  #define T_TYPE int
#endif

/// ����
enum expCellKind {
    K_CONST,    /// �Œ�l
    K_VAR,      /// �ϐ�
    K_ENZAN,    /// ���Z�q
    K_CODE      /// �R���p�C�����ʗ�
};


// # Keisan Routine ---------------
T_TYPE CalcPlus  (T_TYPE p1,T_TYPE p2);
T_TYPE CalcMinus (T_TYPE p1,T_TYPE p2);
T_TYPE CalcMulti (T_TYPE p1,T_TYPE p2);
T_TYPE CalcDivde (T_TYPE p1,T_TYPE p2);
T_TYPE CalcAnd   (T_TYPE p1,T_TYPE p2);
T_TYPE CalcOr    (T_TYPE p1,T_TYPE p2);
T_TYPE CalcAmari (T_TYPE p1,T_TYPE p2);
T_TYPE CalcRShift(T_TYPE p1,T_TYPE p2);
T_TYPE CalcLShift(T_TYPE p1,T_TYPE p2);
T_TYPE RonriOr   (T_TYPE p1,T_TYPE p2);
T_TYPE RonriAnd  (T_TYPE p1,T_TYPE p2);
T_TYPE CompEq    (T_TYPE p1,T_TYPE p2);
T_TYPE CompNe    (T_TYPE p1,T_TYPE p2);
T_TYPE CompLt    (T_TYPE p1,T_TYPE p2);
T_TYPE CompRt    (T_TYPE p1,T_TYPE p2);
T_TYPE CompLe    (T_TYPE p1,T_TYPE p2);
T_TYPE CompRe    (T_TYPE p1,T_TYPE p2);


// # ���Z�q�̈� cell --------------
class enzanExecCell_C{
  public:
    sChar *name;    // ���Z�q
    int    num;     // ���Z�q�i���o�[
    T_TYPE  (* rtn) (T_TYPE p1,T_TYPE p2); // �v�Z�v���O����

    enzanExecCell_C(char *p_name,int p_num,T_TYPE  (* p_calc_rtn) (T_TYPE p1,T_TYPE p2)){
      name = new sChar(p_name);
      num  = p_num;
      rtn  = p_calc_rtn;
    }
    ~enzanExecCell_C(){
      delete name;
    }
};

// # �ϐ��̈� cell --------------
class varExecCell_C{
  public:
    sChar *name;   // �ϐ���
    int    num;    // �ϐ��i���o�[
    T_TYPE value;  // �l

    varExecCell_C(char *p0,int p1,T_TYPE p2){
      name  = new sChar(p0);
      num   = p1;
      value = p2;
    }
    ~varExecCell_C(){
      delete name;
    }

};


// # �ϐ�/�Œ�l/���Z�q cell --------------
class expCell_C{
  public:
    expCellKind kind;  // ����
    T_TYPE value;      // �Œ�l�̎��͒l�A�ϐ��̎��͕ϐ��z��̃C���f�b�N�X�A���Z�q�̎��͉��Z�q�i���o�[�A�R���p�C�����ʗ�̎��̓R���p�C�����ʗ�i���o�[
    bool use;
    expCell_C(expCellKind p0,T_TYPE p1){
      kind  = p0;
      value = p1;
      use = false;
    }
};

// # expCell_C �� (�R���p�C�����ʂ��i�[����expCell_C��)  ---------------------------

class expList_C{
  public:
    VariableArray_C *ary_fp; // cell:expCell_C
    expList_C(){
      ary_fp = new VariableArray_C(10);
    }
    ~expList_C(){
      delete ary_fp;   ///  ���g�͍폜���Ȃ��̂Œ���!!!
    }

    void cat(expCell_C *e);
    void cat(VariableArray_C *list);
};

// # �ϐ����T�[�` cell ----------------------
class varName_C{
  public:
    sChar *name;     /// �ϐ���
    int    num;      /// �ϐ��z��̃C���f�b�N�X
    T_TYPE init_val; /// �����l
    
    varName_C(char *p0,int p1,T_TYPE p2){
      name = new sChar(p0);
      num  = p1;
      init_val = p2;
    }
    ~varName_C(){
      delete name;
    }
};


// #  ���Z�q�T�[�` cell --------------
class enzanName_C{
  public:
    sChar *name;    // ���Z�q
    int    num;     // ���Z�q�i���o�[      
    int    power;   // �D�揇��
    
    enzanName_C(char *p0,int p1,int p2){
      name  = new sChar(p0);
      num   = p1;
      power = p2;
    }
    ~enzanName_C(){
      delete name;
    }
};


// # Expression Interface ---------------
class Expression_C{
  public:
    // ---- compile ------------
    MemHeader_T     *it;          // Mem Interface
    MEM_FP          *var_fp;      // Variable List  cell:varName_C
    int              var_num;     // Variable Total Number
    MEM_FP          *enzan_fp;    // Enzanshi List  cell:enzanName_C
    int              enzan_num;   // Enzanshi Total Number
    VariableArray_C *code_fp;     // Compile Code Array  cell:expList_C
    int              code_num;    // Compile Code Total Number
    VariableArray_C *dust_fp;     // collect Array cell:expList_C
    bool             err;         // Error Flg

    // ---- exec ---------------
    VariableArray_C *exec_var_fp;   // variable array  cell:varExecCell_C
    VariableArray_C *exec_enzan_fp; // variable array  cell:enzanExecCell_C

    // ---- debug message ---------------
    Expression_C(){
      it            = new MemHeader_T;
      var_fp        = new MEM_FP(it);
      enzan_fp      = new MEM_FP(it);
      dust_fp       = new VariableArray_C(10);
      code_fp       = new VariableArray_C(10);
      exec_var_fp   = new VariableArray_C(10);
      exec_enzan_fp = new VariableArray_C(10);

      var_num   = 0;
      enzan_num = 0;
      code_num  = 0;
      err       = false;
      EnzanStore("||",401,RonriOr   );
      EnzanStore("&&",402,RonriAnd  );
      EnzanStore("==",301,CompEq    );
      EnzanStore("!=",302,CompNe    );
      EnzanStore(">" ,303,CompLt    );
      EnzanStore("<" ,304,CompRt    );
      EnzanStore(">=",305,CompLe    );
      EnzanStore("<=",306,CompRe    );
      EnzanStore("+" ,201,CalcPlus  );
      EnzanStore("-" ,202,CalcMinus );
      EnzanStore("*" ,203,CalcMulti );
      EnzanStore("/" ,204,CalcDivde );
#ifndef T_TYPE_FLOAT
      EnzanStore("&" ,205,CalcAnd   );
      EnzanStore("|" ,206,CalcOr    );
      EnzanStore("%" ,207,CalcAmari );
      EnzanStore(">>",208,CalcRShift);
      EnzanStore("<<",209,CalcLShift);
#endif
    }
    ~Expression_C(){
      varName_C *v;
      enzanName_C *e;
      expList_C *l;
      expCell_C *exp;
      varExecCell_C *vec;
      enzanExecCell_C *eec;

      MEM_LOOP(v  ,varName_C      ,var_fp        ) delete v;   LOOP_END
      MEM_LOOP(e  ,enzanName_C    ,enzan_fp      ) delete e;   LOOP_END
      ARY_LOOP(l  ,expList_C      ,code_fp       ) delete l;   LOOP_END
      ARY_LOOP(exp,expCell_C      ,dust_fp       ) delete exp; LOOP_END
      ARY_LOOP(vec,varExecCell_C  ,exec_var_fp   ) delete vec; LOOP_END
      ARY_LOOP(eec,enzanExecCell_C,exec_enzan_fp ) delete eec; LOOP_END

      delete var_fp;
      delete enzan_fp;
      delete code_fp;
      delete dust_fp;
      delete exec_var_fp;
      delete exec_enzan_fp;
      delete it;
    }
    
  // ---- compile -----
  public:
    expList_C *compile(char *str);
    bool okCheck();
    expCellKind VarSrch(char *key,T_TYPE *outVal);
    bool VarStore(char *key,T_TYPE init_val);
    int  VarSrchStore(char *key);
  private:
    expList_C *CodeListGet(int no);
    int CodeListStore(expList_C *list);
    enzanName_C *EnzanSrch(char *key);
    bool EnzanStore(char *key,int power,T_TYPE  (* p_calc_rtn) (T_TYPE p1,T_TYPE p2));
    int CalcPower(enzanName_C *calc,enzanName_C *calc2)  ;
    int enzanshiChk(char str);
    void codeStore(expCell_C *e,expList_C *out);
    void codeStore(enzanName_C *e,expList_C *out);
    void compileMain(MEM_FP *a_fp,MEM_FP *e_fp,expList_C *out)  ;
    void compileLoop(char *str,expList_C *out);

  // ---- code exec ----
  public:
    void   codeExec_Init();
    T_TYPE codeExec(expList_C *list,bool debugFlg);
    void   codeListMon(expList_C *list);
    void   varListMon();
    void   valueWrite(int var_no,T_TYPE value);
    T_TYPE valueRead(int var_no);

  };


#endif // __XEXPRESSION_H_
