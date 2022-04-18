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
//  OBJECT BUILD LIBRARY
//

#ifndef _XOBJECT_H_
#define _XOBJECT_H_

#include "../csvpp_xbase/zlist.h"
#include "xclass.h"

// # AryCell_T ----------
class AryCell_T {
  public:
    sChar *name;  // Variable Name
    sChar *atai;  // Variable Atai
    AryCell_T(char *p_name,char * p_atai);
    ~AryCell_T();
  };

// # VarCell_T  ----------
class VarCell_T {
  public:
    sChar       *name;   // Variable Name
    sChar       *atai;   // Variable Atai
    MEM_FP      *ary_fp; // Array List
    MemHeader_T *it;     // Mem Interface
    VarCell_T (MemHeader_T *p_it,char *p_name,char *p_atai);
    ~VarCell_T();
    void AryStore(char *idx,char *atai);
  };

// # ListCell_T  ----------
class ListCell_T {
  public:
    sChar       *name;   // List Name
    List_B      *lb;     // List class
    MEM_FP      *idx_fp; // Index List
    MEM_FP      *var_fp; // Member List
    MemHeader_T *it;     // Mem Interface
    ListCell_T (MemHeader_T *p_it,List_B *p_lb);
    ~ListCell_T();
    void IdxStore(VarCell_T *var);
    void VarStore(VarCell_T *var);
  };


// # ListCallCell_T ----------
class ListCallCell_T {
  public:
    sChar       *name;   // name
    int          clm;    // colomn pointer
    VarCell_T   *vc;     // Variable Pointer
    sChar       *init;   // Initialize Value
    ListCallCell_T(int p_clm,VarCell_T *p_vc,char *p_init);
    ListCallCell_T(int p_clm,VarCell_T *p_vc);
    ~ListCallCell_T();
  };

// # ListCallIdx_T ----------------
class ListCallIdx_T {
  public:
    sChar       *idx_name; // Index Name
    int          cnt;      // Counter
    ListCallIdx_T(char *p_idx);
    ~ListCallIdx_T();
  };

// # Object_T -------------
class Object_T {
  public:
    sChar       *name;    // Object Name
    MEM_FP      *var_fp;  // Variable List
    MEM_FP      *list_fp; // List List
    MEM_FP      *pg_fp;   // Program List
    MemHeader_T *it;      // Mem Interface
    bool         ov_mode; // Variable Overwrite Mode
    Object_T (MemHeader_T *p_it,char *p_name);
    ~Object_T();
    void VarStore    (char      *name,char *atai);
    void VarAryStore (char      *name,char *atai);
    bool ListStore   (List_B    *lb             );
    void ListIdxStore(VarCell_T *var            );
    void ListVarStore(VarCell_T *var            );
    bool PrgStore    (Program_B *prg            );
    void VarPrintf   (                          );
  };

// # ListCall_T  ----------
class ListCall_T {
  public:
    sChar       *name;    // List Name
    ListCell_T  *lc;      // List Cell
    MEM_FP      *idx_fp;  // Variable List
    MEM_FP      *var_fp;  // List List
    MEM_FP      *cnt_fp;  // Program List
    MemHeader_T *it;      // Mem Interface
    ListCall_T (MemHeader_T *p_it,ListCell_T *p_lc);
    ~ListCall_T();
    void VarStore    (int clm,VarCell_T *var,char *init);
    void IdxStore    (int clm,VarCell_T *var           );
  };


// # MacCallCell_T  ----------
class MacCallCell_T {
  public:
    sChar       *name;   // Macro Name
    Program_B   *prg;    // Program
    MEM_FP      *var_fp; // Member List
    MemHeader_T *it;     // Mem Interface
    MacCallCell_T (MemHeader_T *p_it,Program_B *p_prg);
    ~MacCallCell_T();
    void VarStore(int clm,VarCell_T *var);
  };

// # FromTo_T ----------------
class FromTo_T {
  public:
    McbArea_C *from;     // Jump From Pointer
    McbArea_C *to;       // Jump To Pointer
    FromTo_T(McbArea_C *p_from,McbArea_C *p_to);
  };

// # IfLvlCell_T ---------------
class IfLvlCell_T {
  public:
    MEM_FP      *lvl_fp; // Level List
    MemHeader_T *it;     // Mem Interface
    IfLvlCell_T(MemHeader_T *p_it);
    ~IfLvlCell_T();
    void FromToStore(McbArea_C *from,McbArea_C *to);
    McbArea_C *FromToSrch(McbArea_C *cur);
  };

// # ListFor_T -------------
class ListFor_T {
  public:
    McbArea_C   *from;     // Jump From Pointer   (%listfor/%for/%aryfor/%textfor)
    McbArea_C   *to;       // Jump To Pointer     (%listfor/%for/%aryfor/%textfor)
    ListCell_T *lc;       // ListCell Pointer    (%listfor)
    VarCell_T  *cnt;      // For Counter Variable(%listfor/%for/%aryfor)
    VarCell_T  *max;      // For Max Variable    (%listfor)
    sChar      *idx;      // Index Name/Sv Name  (%listfor/%aryfor)
    int         loop_su;  // loop su             (%for)
	//FILE       *fp;       // File Pointer        (%textfor)
	Read64_C   *fp;       // File Pointer        (%textfor)
	int         mode;     // =0:%listfor =1:%for =2:%aryfor =3:%textfor
	ListFor_T(McbArea_C *p_from,McbArea_C *p_to,VarCell_T *p_var,Read64_C *p_fp);
	ListFor_T(McbArea_C *p_from,McbArea_C *p_to,VarCell_T *p_var,VarCell_T *p_max); // Ver 1.23
	ListFor_T(McbArea_C *p_from,McbArea_C *p_to,VarCell_T *p_cnt,int p_loop_su);
	ListFor_T(MemHeader_T *it,McbArea_C *p_from,McbArea_C *p_to,ListCell_T *p_lc,VarCell_T *p_cnt,VarCell_T *p_max);
    ~ListFor_T();
  };

// # ForLvlCell_T(MemHeader_T *p_it) ---------------
class ForLvlCell_T{
  public:
    MEM_FP      *lvl_fp; // Level List
    MemHeader_T *it;     // Mem Interface
    ForLvlCell_T(MemHeader_T *p_it);
    ~ForLvlCell_T();
    bool CntUp(ListFor_T *lf);
    void AryRead(ListFor_T *lf);
    McbArea_C *ListForSrch(McbArea_C *cur);
    bool ListForStore(McbArea_C *from,McbArea_C *to,ListCell_T *lc,VarCell_T *cnt,VarCell_T *max);
    bool ListForStore(McbArea_C *from,McbArea_C *to,VarCell_T *cnt,int loop_su);
    bool ListForStore(McbArea_C *from,McbArea_C *to,VarCell_T *cnt,VarCell_T *max); // Ver 1.23
    bool ListForStore(McbArea_C *from,McbArea_C *to,VarCell_T *cnt,char *file_name);
  };

#endif // _XOBJECT_H_
