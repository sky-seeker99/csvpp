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
//  CSV COMPILER PASS3(variable mapping)
//  ・タイプのサイズ算出
//  ・メンバのサイズ、オフセット算出
//  ・グローバル変数のマッピング
//  ・パラメータ変数のマッピング
//  ・ローカル変数のマッピング
//

// ---------------
// Pass 3 Main
// ---------------
void Inf_T::Pass3(){
  typC *typ;
  memberC *mem;
  varC *var;
  prgC *prg;
  int i;

  printf(" pass3(variable mapping).\n");

  line_cnt = 0;
  // 型宣言のサイズ算出
  MEM_LOOP(typ,typC,typ_fp)
    if (typ->size > 0){continue;}
    MEM_LOOP(mem,memberC,typ->member_fp)
      typ->size += memberSum(mem);
    LOOP_END
  LOOP_END

  // メンバー変数のオフセット算出
  MEM_LOOP(typ,typC,typ_fp)
    i = 0;
    MEM_LOOP(mem,memberC,typ->member_fp)
      mem->offset = i;
      i += mem->size;
    LOOP_END
  LOOP_END

  // グローバル変数のサイズの算出
  MEM_LOOP(var,varC,global_fp)
    if (var->flgPtr){var->size = var->ary_su;}
    else {
      if (var->typ == NULL){var->size = var->ary_su;}
      else                 {var->size = var->typ->size * var->ary_su;}
    }
    var->map  = stk_map;
    stk_map  += var->size;
  LOOP_END

  // パラメータ変数、ローカル変数のサイズの算出
  MEM_LOOP(prg,prgC,prg_fp)
    MEM_LOOP(var,varC,prg->parm_fp)
      var->size   = 1;
      ++(prg->map);
    LOOP_END
    MEM_LOOP(var,varC,prg->local_fp)
      if (var->flgPtr){var->size = var->ary_su;}
      else{
        if (var->typ == NULL){var->size = var->ary_su;}
        else                 {var->size = var->typ->size * var->ary_su;}
      }
      var->map  = prg->map;
      prg->map += var->size;
    LOOP_END
  LOOP_END

}

// ---------------
// member calc
// ---------------
int Inf_T::memberSum(memberC *mem){
  if ((mem->typ == NULL) || (mem->flgPtr)){mem->size = mem->ary_su;}
  else                                    {mem->size = mem->ary_su*typeSum(mem->typ);}
  return(mem->size);
}

// ---------------
// type calc
// ---------------
int Inf_T::typeSum(typC *typ){
  memberC *mem;

  // member size calc
  if (typ->size == 0){
    MEM_LOOP(mem,memberC,typ->member_fp)
      typ->size += memberSum(mem);
    LOOP_END
  }
  return(typ->size);
}


