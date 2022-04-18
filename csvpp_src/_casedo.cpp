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
// case do
//


// case Sting list -----------------
class CaseStringCell_T{
  public:
  sChar *str;

  CaseStringCell_T(char *p_str){
    str = new sChar(p_str);
    }
  ~CaseStringCell_T(){
    delete str;
    }
  };

// case cell list -----------------
class CaseListCell_T{
  public:
  MEM_FP *case_fp;
  CaseListCell_T(MemHeader_T *p_it) {
    case_fp   = new MEM_FP(p_it);
    }
  ~CaseListCell_T(){
    CaseStringCell_T *csc;
    MEM_LOOP(csc,CaseStringCell_T,case_fp)
      delete csc;
    LOOP_END
    delete case_fp;
    }
  };

// interface class -----------------
class CaseDo_T{
  private:
  MEM_FP *body_fp;
  MemHeader_T *it;
  MEM_FP *out_fp;
  FileTemp_T *tmp;
  FILE *fp;

  void Clear(){
    CaseListCell_T *clc;
    MEM_FP *mem_fp;
    sChar *str;
    MEM_LOOP(clc,CaseListCell_T,body_fp)
      delete clc;
    LOOP_END
    MEM_LOOP(str,sChar,out_fp)
      delete str;
    LOOP_END
    delete body_fp;
    delete out_fp;
    delete tmp;
    }
  void Init(){
    body_fp = new MEM_FP(it);
    out_fp = new MEM_FP(it);
    tmp = new FileTemp_T("csv");
    fp  = tmp->GetFp();
    g_max = 0;
    g_cnt = 0;
    }
  void output();
  void caseDoAll();
  void caseDo();

  public:
  int g_max;
  int g_cnt;
  CaseListCell_T *g_clc;
  CaseDo_T (MemHeader_T *p_it) {it = p_it; Init();}
  ~CaseDo_T()                  {Clear();          }
  void patSetTop();
  void patSet(char *str);
  void postExec();
  void preExec(bool allFlg);
  char *fileNameGet(){return(tmp->GetName());}
  };

// ------------
// pattern set
// ------------
void CaseDo_T::patSetTop()
  {
  if (g_max < g_cnt){g_max = g_cnt;}
  g_clc = new CaseListCell_T(it);
  it->alloc_ptr = (unsigned char *)g_clc;
  body_fp->mem_alloc();
  g_cnt = 0;

  }

// ------------
// pattern set
// ------------
void CaseDo_T::patSet(char *str)
  {
  CaseStringCell_T *w_csc;

  w_csc = new CaseStringCell_T(str);
  it->alloc_ptr = (unsigned char *)w_csc;
  g_clc->case_fp->mem_alloc();
  ++g_cnt;
  }

// ------------
// postExec 
// ------------
void CaseDo_T::postExec()
  {
  Clear();
  Init();
  }

// ------------
// PreExec
// ------------
void CaseDo_T::preExec(bool allFlg)
  {
  CaseListCell_T *clc;
  MEM_LOOP(clc,CaseListCell_T,body_fp)
    clc->case_fp->mem_mcb_top_set();
  LOOP_END
  body_fp->mem_mcb_top_set();
  if (allFlg){caseDoAll();}
  else {
    for(int i=0;i<g_max;++i)
      {
      caseDo();
      }
    }
  tmp->close();    
  }

// ------------
// Output 
// ------------
void CaseDo_T::output(){
  sChar *str;

//  fprintf(fp,"#do,");
  MEM_LOOP(str,sChar,out_fp)
    fprintf(fp,"%s,",str->c_str());
  LOOP_END
  fprintf(fp,"\n");
  }

// ------------
// Recursive 
// ------------
void CaseDo_T::caseDoAll()
  {
  CaseListCell_T *w_clc;
  CaseStringCell_T *w_csc;
  McbArea_C *sv_ptr;
  sChar *str;
  if (body_fp->mem_mcb_ptr_rd() == MM_NULL){output(); return;}
  w_clc = (CaseListCell_T *)body_fp->mem_link_ptr_rd();
  sv_ptr = body_fp->mem_mcb_ptr_rd();
  body_fp->mem_mcb_next_set();
  MEM_LOOP(w_csc,CaseStringCell_T,w_clc->case_fp)
    it->alloc_ptr = (unsigned char *)w_csc->str;
    out_fp->mem_alloc();
    caseDoAll();
    out_fp->mem_mcb_end_set();
    out_fp->mem_del();
  LOOP_END
  body_fp->mem_mcb_ptr_wr(sv_ptr);
  }

// ------------
// Recursive 
// ------------
void CaseDo_T::caseDo()
  {
  CaseListCell_T *w_clc;
  CaseStringCell_T *w_csc;
  sChar *str;
  McbArea_C *sv_ptr;

  if (body_fp->mem_mcb_ptr_rd() == MM_NULL){output(); return;}
  w_clc = (CaseListCell_T *)body_fp->mem_link_ptr_rd();
  sv_ptr = body_fp->mem_mcb_ptr_rd();
  body_fp->mem_mcb_next_set();
  if (w_clc->case_fp->mem_mcb_ptr_rd() == MM_NULL){w_clc->case_fp->mem_mcb_top_set();}
  w_csc = (CaseStringCell_T *)w_clc->case_fp->mem_link_ptr_rd();
  it->alloc_ptr = (unsigned char *)w_csc->str;
  out_fp->mem_alloc();
  caseDo();

  out_fp->mem_mcb_end_set();
  out_fp->mem_del();

  w_clc->case_fp->mem_mcb_next_set();

  body_fp->mem_mcb_ptr_wr(sv_ptr);
  }

