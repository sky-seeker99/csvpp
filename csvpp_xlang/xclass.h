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
//  CLASS BUILD LIBRARY 
//
#ifndef _XCLASS_H_
#define _XCLASS_H_

#include "../csvpp_xbase/zcsvfile.h"

// # Var_B -------------
class Var_B{
  public:
    sChar *var_name;     // Variable Name
    sChar *init_value;   // Initialize Value
    Var_B(char *var,char *init);
    ~Var_B();
  };

// # List_B ------
class List_B{
  public:
    sChar   *list_name;   // List Name
    MemHeader_T *it;      // List Control Interface
    MEM_FP  *idx_fp;      // Index List
    MEM_FP  *var_fp;      // Variable List
    List_B(MemHeader_T *p_it,char *list);
    ~List_B();
    bool IdxStore(char *var);
    bool VarStore(char *var,char *init);
  };


// # Jump_C -----------
class JumpCell_C{
  public:
    int kind;           // 0:%else_if 1:%else_noif 2:%else_wif 3:%else_nowif 4:%else_calcif 5:%else_calcnoif 6:%else_calcif_f 7:%else_calcnoif_f  8:%else_calcif64 9:%else_calcnoif64 10:%else 11:%endif
    McbArea_C *addr;    // Address
    JumpCell_C(int p_kind,McbArea_C *p_addr){
      kind = p_kind;
      addr = p_addr;
    }
};


// # Program_C --------
class Program_C{
  public:
    int    sel_su;   // Program Sel Su
    char **sel;      // Program Sel
    unsigned int command; // command

    VariableArray_C *if_jump;       // cell:JumpCell_C
    unsigned int     alias_num;     // compare alias num
    McbArea_C       *alias_addr;    // alias address
    McbArea_C       *for_jump_addr; // for jump address

    Program_C(int p_sel_su,char **p_sel);
    ~Program_C();
    char *sel_rd(int idx);
    void storeJump(int kind,McbArea_C *addr);

  };

// # Program_B -------
class Program_B{
  public:
    sChar   *prg_name;    // Macro Name
    MemHeader_T *it;      // List Control Interface
    MEM_FP  *prg_fp;      // Program List
    MEM_FP  *var_fp;      // Local Variable List
    Program_B(MemHeader_T *p_it,char *prg);
    ~Program_B();
    void PrgStore(CsvInf_T *csv_fp);
    bool VarStore(char *var,char *init);
  };

// # Class_T --------
class Class_T{
  public:
    sChar   *class_name;  // Class Name
    MemHeader_T *it;      // List Control Interface
    MEM_FP  *class_fp;    // Keisyo Class List
    MEM_FP  *var_fp;      // Simple Variable List
    MEM_FP  *list_fp;     // List List
    MEM_FP  *prg_fp;      // Macro List
    MEM_FP  *version_fp;  // Version Fp
    Class_T(MemHeader_T *p_it,char *p_class);
    ~Class_T();
    bool ClassStore  (char *cl            );
    bool VarStore    (char *var,char *init);
    bool ListStore   (char *list          );
    bool ListVarStore(char *var,char *init);
    bool ListIdxStore(char *idx           );
    bool PrgStore    (char *prg           );
    void PrgLineStore(CsvInf_T *csv_fp    );
    void VersionStore(CsvInf_T *csv_fp,int cur);
    bool PrgVarStore (char *var,char *init);
  };

// # Classcall_T --------
class Classcall_T{
  public:
    sChar   *class_name;  // Class Name
    sChar   *obj_name;    // Object Name
    MemHeader_T *it;      // List Control Interface
    MEM_FP  *var_fp;      // Simple Variable List
    MEM_FP  *prg_fp;      // Macro List
    Classcall_T(MemHeader_T *p_it,char *p_class,char *obj);
    ~Classcall_T();
    void PrgLineStore(CsvInf_T *csv_fp);
    bool VarStore    (char *var,char *init);
  };

// # Alias_T ----------
class Alias_T{
  public:
    sChar   *alias_name;  // Alias Name
    int      max;         // kazu
    char    **sel;        // Sel Data
    Alias_T(Program_C *pc);
    ~Alias_T();
    void Replace(Program_C *pc);
  };

#endif // _XCLASS_H_
