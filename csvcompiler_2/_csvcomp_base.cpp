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
//  CSV COMPILER BASE
//


// -----------------------
// constructor/destructor
// -----------------------
typC::typC(MemHeader_T *p_it,char *p_name){
  name = new sChar(p_name);
  size = 0;
  it   = p_it;
  member_fp = new MEM_FP(it);
}
typC::~typC(){
  memberC *m;
  MEM_LOOP(m,memberC,member_fp) delete m; LOOP_END
  delete member_fp;
  delete name;
}


memberC::memberC(char *p_name,int p_ary,typC *p_typ,bool p_flgPtr){
  name    = new sChar(p_name);
  size    = 0;
  offset  = 0;
  ary_su  = p_ary;
  typ     = p_typ;
  flgPtr  = p_flgPtr;
}
memberC::~memberC(){
  delete name;
}


varC::varC(char *p_name,int p_ary,typC *p_typ,bool p_flgPtr){
  name   = new sChar(p_name);
  size   = 0;
  ary_su = p_ary;
  typ    = p_typ;
  map    = -1;
  flgPtr = p_flgPtr;
  flgConst = false;
}
varC::varC(char *p_name){
  name   = new sChar(p_name);
  size   = 0;
  ary_su = 0;
  typ    = NULL;
  map    = -1;
  flgPtr = false;
  flgConst = true;
}
varC::~varC(){
  delete name;
}


calcC::calcC(char *p_siki,int p_reg_su,int p_sikiNo){
  siki   = new sChar(p_siki);
  reg_su = p_reg_su;
  sikiNo = p_sikiNo;
}
calcC::~calcC(){
  delete siki;
}



codeC::codeC(char *p_code,int p0,int p1,int p2,int p3,int p4){
  code = new sChar(p_code);
  parm[0] = p0;
  parm[1] = p1;
  parm[2] = p2;
  parm[3] = p3;
  parm[4] = p4;
  call_name = NULL;
  src     = NULL;
}
codeC::codeC(char *p_code,char *p_call_name,int p0,int p1){
  code = new sChar(p_code);
  parm[0] = p0;
  parm[1] = p1;
  parm[2] = 0;
  parm[3] = 0;
  parm[4] = 0;
  call_name = new sChar(p_call_name);
  src     = NULL;
}
codeC::~codeC(){
  delete code;
  if (call_name != NULL){delete call_name;}
}


prgC::prgC(MemHeader_T *p_it,char *p_name,bool p_irq_flg,int p_irq_level,char *p_irq_line){
  name = new sChar(p_name);
  size = 0;
  parm_su  = 0;
  local_su = 0;
  it       = p_it;
  parm_fp  = new MEM_FP(it);
  local_fp = new MEM_FP(it);
  code_fp  = new MEM_FP(it);
  map      = 0;
  irq_flg  = p_irq_flg;   // Ver 1.01
  if (p_irq_flg) {
    irq_level = p_irq_level; // Ver 1.02
    irq_line  = new sChar(p_irq_line); // Ver 1.02
  }
  else {
    irq_level = -1;
    irq_line  = NULL;
  }

}
prgC::~prgC(){
  varC *v;
  codeC *c;

  MEM_LOOP(v,varC ,parm_fp  ) delete v; LOOP_END
  MEM_LOOP(v,varC ,local_fp ) delete v; LOOP_END
  MEM_LOOP(c,codeC,code_fp  ) delete c; LOOP_END
  delete parm_fp;
  delete local_fp;
  delete code_fp;
  delete name;
  if (irq_line != NULL) {delete irq_line;}
}


jmpC::jmpC(codeC *p_code,prgC *p_prg){
  code   = p_code;
  prg    = p_prg;
}


/*
ifC::ifC(codeC *p_code,bool p_ifFlg){
  svCode = p_code;
  ifFlg  = p_ifFlg;
}
*/


ifC::ifC(MemHeader_T  *p_it,codeC *p_code){
  it = p_it;
  ifKind = 0;
  svCode = p_code;
  code_fp = new MEM_FP(it);
}
ifC::~ifC(){
  delete code_fp;
}



forC::forC(MemHeader_T  *p_it,codeC *p_code,int p_loop_ptr,char *p_var){
  svCode   = p_code;
  loop_ptr = p_loop_ptr;
  it       = p_it;
  break_fp = new MEM_FP(it);
  if (p_var == NULL){var = NULL;}
  else              {var = new sChar(p_var);}
}
forC::~forC(){
  codeC *code;
  MEM_LOOP(code,codeC,break_fp)
    code->parm[0] = svCode->parm[1];
    code->parm[1] = svCode->parm[1];
  LOOP_END
  if (var != NULL){delete var;}
  delete break_fp;
}


extendC::extendC(char *p_format,int p_exNo,int p_parmSu,int p_regNo){
  format   = new sChar(p_format);
  exNo     = p_exNo;
  parmSu   = p_parmSu;
  regNo    = p_regNo;
}
extendC::~extendC(){
  delete format;
}



printfC::printfC(char *p_format,int p_prNo,int p_parmSu,int p_regNo){
  format   = new sChar(p_format);
  prNo     = p_prNo;
  parmSu   = p_parmSu;
  regNo    = p_regNo;
}
printfC::~printfC(){
  delete format;
}


calcSikiC::calcSikiC(MemHeader_T *p_it){
  it     = p_it;
  var_fp = new MEM_FP(it);
  siki   = NULL;
  errFlg = false;
}
calcSikiC::~calcSikiC(){
  calcVarC *var;
  MEM_LOOP(var,calcVarC,var_fp) delete var; LOOP_END
  delete var_fp;
}


calcMemC::calcMemC(char *p_name,memberC *p_mem){
  name = new sChar(p_name);
  ary  = NULL;
  mem  = p_mem;
}
calcMemC::calcMemC(char *p_name){
  name = new sChar(p_name);
  ary  = NULL;
  mem  = NULL;
}
calcMemC::~calcMemC(){
  delete name;
  if (ary != NULL){delete ary;}
}


calcVarC::calcVarC(MemHeader_T *p_it,bool p_flgPtr){
  it        = p_it;
  member_fp = new MEM_FP(it);
  varKbn    = -1;
  var       = NULL;
  errFlg    = false;
  flgPtr    = p_flgPtr;
  flgMem    = false;
  ary       = NULL;
}
calcVarC::~calcVarC(){
  calcMemC *mem;
  MEM_LOOP(mem,calcMemC,member_fp) delete mem; LOOP_END
  delete member_fp;
  if (ary != NULL){delete ary;}
}


Inf_T::Inf_T(){
  it        = new MemHeader_T;
  typ_fp    = new MEM_FP(it);
  prg_fp    = new MEM_FP(it);
  calc_fp   = new MEM_FP(it);
  global_fp = new MEM_FP(it);
  global_su = 0;
  if_fp     = new MEM_FP(it);
  if_su     = 0;
  for_fp    = new MEM_FP(it);
  for_su    = 0;
  map       = 0;
  stk_map   = 0;
  reg_max   = 0;
  g_typ     = NULL;
  g_prg     = NULL;
  prg_cnt   = 0;
  siki_cnt  = 0;
  link_fp   = new MEM_FP(it);
  start_map = 0;
  errCnt    = 0;
  line_cnt  = 0;
  printf_cnt = 0;
  printf_fp = new MEM_FP(it);
  extend_cnt = 0;
  extend_fp = new MEM_FP(it);
  jmp_fp    = new MEM_FP(it);
  src_fp    = new MEM_FP(it);
  valueFlg  = false;
  csvi      = new CsvAnl_C;
  irq_number= 0;  // Ver 1.02
}

Inf_T::~Inf_T(){
  typC  *typ;
  prgC  *prg;
  calcC *calc;
  varC  *var;
  ifC   *wif;
  forC  *wfor;
  printfC *p;
  extendC *ex;
  jmpC  *jmp;
  sChar *str;
  delete csvi;
  MEM_LOOP(typ ,typC ,typ_fp      ) delete typ;  LOOP_END
  MEM_LOOP(prg ,prgC ,prg_fp      ) delete prg;  LOOP_END
  MEM_LOOP(calc,calcC,calc_fp     ) delete calc; LOOP_END
  MEM_LOOP(var ,varC ,global_fp   ) delete var;  LOOP_END
  MEM_LOOP(wif ,ifC  ,if_fp       ) delete wif;  LOOP_END
  MEM_LOOP(wfor,forC ,for_fp      ) delete wfor; LOOP_END
  MEM_LOOP(p   ,printfC,printf_fp ) delete p;    LOOP_END
  MEM_LOOP(ex  ,extendC,extend_fp ) delete ex;   LOOP_END
  MEM_LOOP(jmp ,jmpC,jmp_fp       ) delete jmp;  LOOP_END
  MEM_LOOP(str ,sChar,src_fp      ) delete str;  LOOP_END
  delete typ_fp;
  delete prg_fp;
  delete calc_fp;
  delete global_fp;
  delete if_fp;
  delete for_fp;
  delete link_fp;
  delete printf_fp;
  delete extend_fp;
  delete jmp_fp;
  delete src_fp;
  delete it;
}


// ---------------
// log
// ---------------
void Inf_T::Log(bool ok,char *code,char *msg){
  if (ok == false){++errCnt;}
  printf("[line:%d] %s [%s]\n",line_cnt+1,code,msg);
}

// ---------------
// reg_max set
// ---------------
void Inf_T::regMax_set(int val){
  if (reg_max < val){reg_max = val;}
}

// ---------------
// code gen
// ---------------
codeC *Inf_T::codeAdd(char *p_code,int p0,int p1,int p2,int p3,int p4){
  codeC *code;

  ++(g_prg->size);

  code = new codeC(p_code,p0,p1,p2,p3,p4);
  code->src = src_str;
  src_str   = NULL;
  it->alloc_ptr = (MM_PTR_T *)code;
  g_prg->code_fp->mem_alloc();

  if (strcmp(p_code,"#set") != 0){return(code);}
  if (p0 == K_val_const  ) {regMax_set(p1);                }
  if (p0 == K_val_preg   ) {regMax_set(p1); regMax_set(p2);}
  if (p0 == K_val_reg    ) {regMax_set(p1); regMax_set(p2);}
  if (p0 == K_ptr_const  ) {regMax_set(p1);                }
  if (p0 == K_ptr_reg    ) {regMax_set(p1); regMax_set(p2);}
  if (p0 == K_offset_calc) {regMax_set(p1); regMax_set(p2);}

  return(code);
}

codeC *Inf_T::codeAdd(char *p_code,char *parm,int p0,int p1){
  codeC *code;

  ++(g_prg->size);
  code = new codeC(p_code,parm,p0,p1);
  it->alloc_ptr = (MM_PTR_T *)code;
  g_prg->code_fp->mem_alloc(); 
  return(code);
}

// ------------------
// if nest control
// ------------------
void Inf_T::if_nest_add(codeC *code){
  ifC *wif;

  wif = new ifC(it,code);
  it->alloc_ptr = (MM_PTR_T *)wif;
  if_fp->mem_alloc();
  ++if_su;
}

bool Inf_T::if_nest_del(int size){
  ifC *wif = getIfCell();
  if (wif == NULL){return(false);}

  if (wif->ifKind == 0){
	wif->svCode->parm[1] = size;
  }
  if (wif->ifKind == 2){
	wif->svCode->parm[0] = size;
	wif->svCode->parm[1] = size;
  }

  codeC *code;
  MEM_LOOP(code,codeC,wif->code_fp)
	code->parm[0] = size;
    code->parm[1] = size;
  LOOP_END

  if_fp->mem_del();
  delete wif;
  --if_su;
  return(true);
}

ifC *Inf_T::getIfCell(){
  ifC *wif=NULL;

  if_fp->mem_mcb_end_set();
  if (if_fp->mem_mcb_ptr_rd() != NULL){
    wif = (ifC *)if_fp->mem_link_ptr_rd();
  }
  return(wif);
}


/*
void Inf_T::if_nest_add(codeC *code,bool flg){
  ifC *wif;

  wif = new ifC(code,flg);
  it->alloc_ptr = (MM_PTR_T *)wif;
  if_fp->mem_alloc();
  ++if_su;
}

bool Inf_T::if_nest_del(int size){
  ifC *wif;
  bool ret;


  if_fp->mem_mcb_end_set();
  wif = (ifC *)if_fp->mem_link_ptr_rd();

  ret = wif->ifFlg;
  if (wif->ifFlg == false){wif->svCode->parm[0] = size;}
  wif->svCode->parm[1] = size;
  if_fp->mem_del();
  delete wif;
  --if_su;

  return(ret);
}

*/

// ------------------
// for nest control
// ------------------
void Inf_T::for_nest_add(codeC *code,int sv_loop_ptr,char *var){
  forC  *wfor;

  wfor = new forC(it,code,sv_loop_ptr,var);
  it->alloc_ptr = (MM_PTR_T *)wfor;
  for_fp->mem_alloc();
  ++for_su;
}

void Inf_T::for_nest_del(){
  forC  *wfor;

  for_fp->mem_mcb_end_set();
  wfor = (forC *)for_fp->mem_link_ptr_rd();

  wfor->svCode->parm[1] = g_prg->size;
  for_fp->mem_del();
  delete wfor;
  --for_su;
}

void Inf_T::break_list_add(codeC *code){
  forC  *wfor;

  for_fp->mem_mcb_end_set();
  wfor = (forC *)for_fp->mem_link_ptr_rd();
  it->alloc_ptr = (MM_PTR_T *)code;
  wfor->break_fp->mem_alloc();
}

