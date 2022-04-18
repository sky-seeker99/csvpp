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
//  Database Control LIBRARY for csvpp
//

#include <stdio.h>
#include <io.h>
#include <string.h>
#include <condefs.h>
#include <fcntl.h>
#include "xdbctl.h"

void  DbInf_T::ApiDt_Reset   (                          ){dt_su = 0;}
REC_T DbInf_T::ApiTop_Set    (int no                    ){return(HeadTopSet   (no));}
REC_T DbInf_T::ApiTop_Rd     (int no                    ){return(HeadTopRd    (no));}
REC_T DbInf_T::ApiEnd_Set    (int no                    ){return(HeadEndSet   (no));}
REC_T DbInf_T::ApiEnd_Rd     (int no                    ){return(HeadEndRd    (no));}
REC_T DbInf_T::ApiNext_Set   (int no                    ){return(HeadNextSet  (no));}
REC_T DbInf_T::ApiBefore_Set (int no                    ){return(HeadBeforeSet(no));}
REC_T DbInf_T::ApiNext_Rd    (int no                    ){return(HeadNextRd   (no));}
REC_T DbInf_T::ApiBefore_Rd  (int no                    ){return(HeadBeforeRd (no));}
void  DbInf_T::ApiCur_Set    (int no,REC_T rec          ){*(hd_rec + no) = rec;}
REC_T DbInf_T::ApiCur_Rd     (int no                    ){return(*(hd_rec + no));}
bool  DbInf_T::OpenError_Rd  (                          ){return(open_err_flg );}
bool  DbInf_T::IOError_Rd    (                          ){return(io_err_flg   );}
REC_T DbInf_T::HeadCur_Rd   (int no           ){return(*(hd_rec+no));}
void  DbInf_T::HeadCur_Wr   (int no,REC_T rec ){*(hd_rec+no) = rec;  }
char *DbInf_T::DtList_Rd    (int no             )
  {
  sChar *str;
  if (no >= dt_su){return(NULL);}
  str = *(dt+no);
  return(str->c_str());
  }

DbInf_T::DbInf_T(char *p_file,int  p_mode,long p_file_type,int p_rec_len) {
  bool exist;
  int i;
  FILE *fp;
  DbCtl_T *ctl;
  sChar *w;
  io_err_flg   = false;
  open_err_flg = true;
  mode         = p_mode;
  if ((mode != O_RDONLY) && (mode != O_RDWR) && (mode != O_WRONLY)){return;}
  exist = true;
  if (FileExists(p_file) == false)
    {
    exist = false;
    if (mode == O_RDONLY) {return;}
    if ((fp = fopen(p_file,"wt")) == NULL) {return;}
    fprintf(fp,"ZX Dictionary For S.Kasuya\n");
    fclose(fp);
    }
  if (mode == O_WRONLY) {mode = O_RDWR;}
  // File Open
  if ((handle = open(p_file,mode|O_BINARY)) == -1) {return;}   // For Windows
  di = new DbInfo_T;
  if (exist == true){Read(0,(char *)di,sizeof(DbInfo_T));}
  else
    {
    di->type     = p_file_type;
    di->len      = sizeof(DbInfo_T);
    di->rec_len  = p_rec_len;
    di->ctl_link = REC_EOF;
    di->hd_dust  = REC_EOF;
    di->dt_dust  = REC_EOF;
    di->ctl_dust = REC_EOF;
    }
  if (di->type  != p_file_type){delete di; close(handle); return;}
  open_err_flg = false;
  file = new sChar(p_file);
  // control read
  if (exist == true){ctl_su = 0; CtlRead();}
  else
    {
    ctl_su  = 10;
    ctl_tbl = new DbCtl_T *[ctl_su];
    hd_rec  = new REC_T    [ctl_su];
    for(i=0;i<ctl_su;++i)
      {
      ctl = new DbCtl_T;
      *(ctl_tbl+i) = ctl;
      ctl->link = REC_EOF;
      ctl->head = REC_EOF;
      ctl->tail = REC_EOF;
      *(hd_rec + i) = REC_EOF;
      }
    }
  // Data Area
  dt_max = 10;
  dt_su  = 0;
  dt     = new sChar *[dt_max];
  for(i=0;i<dt_max;++i)
    {
    w = new sChar("");
    *(dt+i) = w;
    }
  }

DbInf_T::~DbInf_T(){
  int i;
  if (open_err_flg == true){return;}
  delete file;
  CtlWrite();
  Write((REC_T)0,(char *)di,sizeof(DbInfo_T));
  delete di;
  close(handle);
  for(i=0;i<ctl_su;++i)
    {
    delete *(ctl_tbl + i);
    }
  delete [] ctl_tbl;
  delete [] hd_rec;
  for(i=0;i<dt_max;++i)
    {
    delete *(dt+i);
    }
  delete [] dt;
  }

// ---------------- File I/O -------------------
// file read
void DbInf_T::Read(REC_T p_rec,char *p_buff,int p_len) {
  int r_len;
  lseek(handle,p_rec,SEEK_SET);
  r_len = read(handle,p_buff,p_len);
  if (r_len != p_len){io_err_flg = true;}
  }

void DbInf_T::Write(REC_T p_rec,char *p_buff,int p_len) {
  int w_len;

//  printf("WRITE REC = %x\n",p_rec);

  lseek(handle,p_rec,SEEK_SET);
  w_len = write(handle,p_buff,p_len);
  if (w_len != p_len){io_err_flg = true;}
  }

// ---------------- record allocation control -------------------
//  File End Sum
REC_T DbInf_T::EndSum(int p_len)
  {
  REC_T out;
  out = di->len;
  di->len += (REC_T)p_len;
  return(out);
  }

// Record Alloc (Dust List Delete)
REC_T DbInf_T::HdAlloc()
  {
  DbHd_T buff;
  REC_T  out;

  if (di->hd_dust == REC_EOF) {return(EndSum(sizeof(DbHd_T)));}

  // control header change
  Read(di->hd_dust,(char *)&buff,sizeof(DbHd_T));
  out = di->hd_dust;
  di->hd_dust = buff.link;
  return(out);
  }

// Record Free (Dust List Add)
void DbInf_T::HdFree(REC_T rec)
  {
  DbHd_T buff;

  // dust rec link change
  buff.link = di->hd_dust;
  Write(rec,(char *)&buff,sizeof(DbHd_T));
  
  // control header change
  di->hd_dust = rec;
  }

// Record Alloc (Dust List Delete)
REC_T DbInf_T::DtAlloc()
  {
  DbDt_T buff;
  REC_T  out;

  if (di->dt_dust == REC_EOF) {return(EndSum(sizeof(DbDt_T)+di->rec_len));}

  // control header change
  Read(di->dt_dust,(char *)&buff,sizeof(DbDt_T));
  out = di->dt_dust;
  di->dt_dust = buff.link;
  return(out);
  }

// Record Free (Dust List Add)
void DbInf_T::DtFree(REC_T rec)
  {
  DbDt_T buff;

  // dust rec link change
  buff.link = di->dt_dust;
  Write(rec,(char *)&buff,sizeof(DbDt_T));
  
  // control header change
  di->dt_dust = rec;
  }

// Record Alloc (Dust List Delete)
REC_T DbInf_T::CtlAlloc()
  {
  DbCtl_T buff;
  REC_T  out;

  if (di->ctl_dust == REC_EOF) {return(EndSum(sizeof(DbCtl_T)));}

  // control header change
  Read(di->ctl_dust,(char *)&buff,sizeof(DbCtl_T));
  out = di->ctl_dust;
  di->ctl_dust = buff.link;
  return(out);
  }

// Record Free (Dust List Add)
void DbInf_T::CtlFree(REC_T rec)
  {
  DbCtl_T buff;

  // dust rec link change
  buff.link = di->ctl_dust;
  Write(rec,(char *)&buff,sizeof(DbCtl_T));
  
  // control header change
  di->ctl_dust = rec;
  }

// ---------------- Control List Write/Read -------------------
// Control Area Free
void DbInf_T::CtlFreeAll()
  {
  int i;
  
  for(i=0;i<ctl_su;++i){delete *(ctl_tbl + i);}
  if (ctl_tbl != (DbCtl_T **)NULL){delete [] ctl_tbl; ctl_tbl = (DbCtl_T **)NULL;}
  if (hd_rec  != (REC_T    *)NULL){delete [] hd_rec ; hd_rec  = (REC_T    *)NULL;}
  ctl_su = 0;
  }

// Control Extended
void DbInf_T::CtlExtend(int p_ctl_su)
  {
  int i;
  DbCtl_T *ctl,*ctl2;
  DbCtl_T **w_ctl_tbl;
  REC_T   *w_hd_rec;

  w_ctl_tbl = new DbCtl_T *[p_ctl_su];
  w_hd_rec  = new REC_T [p_ctl_su];
  for(i=0;i<p_ctl_su;++i)
    {
    ctl = new DbCtl_T;
    *(w_ctl_tbl + i) = ctl;
    ctl->link   = REC_EOF;
    ctl->head   = REC_EOF;
    ctl->tail   = REC_EOF;
    *(w_hd_rec) = REC_EOF;
    }

  for(i=0;i<ctl_su;++i)
    {
    ctl  = *(w_ctl_tbl+i);
    ctl2 = *(ctl_tbl  +i);
    ctl->link   = ctl2->link;
    ctl->head   = ctl2->head;
    ctl->tail   = ctl2->tail;
    *(w_hd_rec+i) = *(hd_rec+i);
    }
  CtlFreeAll();
  ctl_su  = p_ctl_su;
  ctl_tbl = w_ctl_tbl;
  hd_rec  = w_hd_rec;
  }

void DbInf_T::CtlSet(int no,REC_T head,REC_T tail)
  {
  DbCtl_T *ctl;

  if (no >= ctl_su){CtlExtend(no+1);}
  ctl = *(ctl_tbl+no);
  ctl->head = head;
  ctl->tail = tail;
  }

// Control Read
void DbInf_T::CtlRead()
  {
  MEM_FP *fp;
  MemHeader_T *it;
  DbCtl_T *ctl;
  REC_T    rec;
  int i;

//  CtlFreeAll();
  it = new MemHeader_T();
  fp = new MEM_FP(it);
  rec = di->ctl_link;
  for(;;)
    {
    if (rec == REC_EOF){break;}
    ++ctl_su;
    ctl = new DbCtl_T;
    Read(rec,(char *)ctl,sizeof(DbCtl_T));
    it->alloc_ptr = (unsigned char *)ctl;
    fp->mem_alloc();
    rec = ctl->link;
    }
    
  ctl_tbl = new DbCtl_T *[ctl_su];
  hd_rec  = new REC_T[ctl_su];

  i = 0;
  MEM_LOOP(ctl,DbCtl_T,fp)
    *(hd_rec  + i) = REC_EOF;
    *(ctl_tbl + i) = ctl; ++i;
  LOOP_END
  delete fp;
  delete it;
  }

// Control Write
void DbInf_T::CtlWrite()
  {
  REC_T rec;
  REC_T sv_rec;
  int i;
  DbCtl_T *ctl;
  DbCtl_T w_ctl;
  
  rec = di->ctl_link;
  for(;;)
    {
    if (rec == REC_EOF){break;}
    Read(rec,(char *)&w_ctl,sizeof(DbCtl_T));
    CtlFree(rec);
    rec = w_ctl.link;
    }

  di->ctl_link = REC_EOF;
  for(i=0;i<ctl_su;++i)
    {
    rec = CtlAlloc();
    ctl = *(ctl_tbl + i);
    if (di->ctl_link == REC_EOF)
      {
      di->ctl_link = rec;
      sv_rec = rec;
      }
    else
      {
      Read (sv_rec,(char *)&w_ctl,sizeof(DbCtl_T));
      w_ctl.link = rec;
      Write(sv_rec,(char *)&w_ctl,sizeof(DbCtl_T));
      }  
    Write(rec,(char *)ctl,sizeof(DbCtl_T));  
    sv_rec = rec;  
    }
  }


// ---------------- Header Linking -------------------
//  Linking
void DbInf_T::HeadLink(int no,REC_T link)
  {
  DbCtl_T *ctl;
  REC_T    alloc_rec;
  DbHd_T   alloc_hd;
  REC_T    cur_rec,before_rec;
  DbHd_T   cur_hd;

  ctl = *(ctl_tbl + no);
  cur_rec       = *(hd_rec + no);
  alloc_rec     = HdAlloc();
  alloc_hd.link = link;

  if (cur_rec == REC_EOF)  // Last Link
    {
    // Last Link
    if (ctl->tail == REC_EOF)
      {
      ctl->tail        = alloc_rec;
      ctl->head        = alloc_rec;
      alloc_hd.before = REC_EOF;
      alloc_hd.after  = REC_EOF;
      Write(alloc_rec,(char *)&alloc_hd,sizeof(DbHd_T));
      }
    else
      {
      Read (ctl->tail,(char *)&cur_hd,sizeof(DbHd_T));
      cur_hd.after = alloc_rec;
      Write(ctl->tail,(char *)&cur_hd,sizeof(DbHd_T));
      alloc_hd.before = ctl->tail;
      alloc_hd.after  = REC_EOF;
      alloc_hd.link   = link;
      Write(alloc_rec,(char *)&alloc_hd,sizeof(DbHd_T));
      ctl->tail = alloc_rec;
      }
    }
  else
    {
    // Before Add
    Read (cur_rec,(char *)&cur_hd,sizeof(DbHd_T));
    if (cur_hd.before == REC_EOF)
      {
      Read (ctl->head,(char *)&cur_hd,sizeof(DbHd_T));
      cur_hd.before = alloc_rec;
      Write(ctl->head,(char *)&cur_hd,sizeof(DbHd_T));
      alloc_hd.before = REC_EOF;
      alloc_hd.after  = ctl->head;
      Write(alloc_rec,(char *)&alloc_hd,sizeof(DbHd_T));
      ctl->head  = alloc_rec;
      }
    else
      {
      before_rec    = cur_hd.before;
      cur_hd.before = alloc_rec;
      Write(cur_rec,(char *)&cur_hd,sizeof(DbHd_T));
      Read (before_rec,(char *)&cur_hd,sizeof(DbHd_T));
      cur_hd.after = alloc_rec;
      Write(before_rec,(char *)&cur_hd,sizeof(DbHd_T));
      alloc_hd.before = before_rec;
      alloc_hd.after  = cur_rec;
      Write(alloc_rec,(char *)&alloc_hd,sizeof(DbHd_T));
      }
    }
  *(hd_rec + no) = alloc_rec;
  }

//  Last Linking
void DbInf_T::HeadLinkLast(int no,REC_T link)
  {
  *(hd_rec + no) = REC_EOF;
  HeadLink(no,link);
  }
 
//  Link Change
void DbInf_T::HeadLinkChg(int no,REC_T link)
  {
  REC_T rec;
  DbHd_T hd;
  
  rec = *(hd_rec + no);
  Read (rec,(char *)&hd,sizeof(DbHd_T));
  hd.link = link;
  Write(rec,(char *)&hd,sizeof(DbHd_T));
  }
 
//  Delete
void DbInf_T::HeadDel(int no)
  {
  DbCtl_T *ctl;
  REC_T    cur_rec;
  DbHd_T   cur_hd,w_hd;

  ctl       = *(ctl_tbl + no);
  cur_rec   = *(hd_rec  + no);
  if (cur_rec == REC_EOF) {return;}
  Read(cur_rec,(char *)&cur_hd,sizeof(DbHd_T));

  if (cur_hd.before == REC_EOF){ctl->head = cur_hd.after;}
  else
    {
    Read (cur_hd.before,(char *)&w_hd,sizeof(DbHd_T));
    w_hd.after = cur_hd.after;
    Write(cur_hd.before,(char *)&w_hd,sizeof(DbHd_T));
    }

  if (cur_hd.after == REC_EOF){ctl->tail = cur_hd.before;}
  else
    {
    Read (cur_hd.after,(char *)&w_hd,sizeof(DbHd_T));
    w_hd.before = cur_hd.before;
    Write(cur_hd.after,(char *)&w_hd,sizeof(DbHd_T));
    }

  HdFree(cur_rec);
  *(hd_rec + no) = cur_hd.before;
  if (cur_hd.after != REC_EOF){*(hd_rec + no) = cur_hd.after;}
  }

//  Delete All
void DbInf_T::HeadDelAll(int no)
  {
  DbCtl_T *ctl;

  ctl = *(ctl_tbl + no);
  *(hd_rec + no) = ctl->head;

  for(;;)
    {
    if (*(hd_rec + no) == REC_EOF){break;}
    HeadDel(no);
    }
  }

// Top Set
REC_T DbInf_T::HeadTopSet(int no)
  {
  DbCtl_T *ctl;

  ctl = *(ctl_tbl + no);
  *(hd_rec + no) = ctl->head;
  return(ctl->head);
  }

// Top Read
REC_T DbInf_T::HeadTopRd(int no)
  {
  DbCtl_T *ctl;

  ctl = *(ctl_tbl + no);
  return(ctl->head);
  }

// End Set
REC_T DbInf_T::HeadEndSet(int no)
  {
  DbCtl_T *ctl;

  ctl = *(ctl_tbl + no);
  *(hd_rec + no) = ctl->tail;
  return(ctl->tail);
  }

// End Read
REC_T DbInf_T::HeadEndRd(int no)
  {
  DbCtl_T *ctl;

  ctl = *(ctl_tbl + no);
  return(ctl->tail);
  }

// Next Set
REC_T DbInf_T::HeadNextSet(int no)
  {
  DbHd_T hd;
  if (*(hd_rec + no) == REC_EOF){return(REC_EOF);}
  Read(*(hd_rec + no),(char *)&hd,sizeof(DbHd_T));
  *(hd_rec + no) = hd.after;
  return(hd.after);
  }

// Before Set
REC_T DbInf_T::HeadBeforeSet(int no)
  {
  DbHd_T hd;
  if (*(hd_rec + no) == REC_EOF){return(REC_EOF);}
  Read(*(hd_rec + no),(char *)&hd,sizeof(DbHd_T));
  *(hd_rec + no) = hd.before;
  return(hd.before);
  }

// Next Read
REC_T DbInf_T::HeadNextRd(int no)
  {
  DbHd_T hd;
  if (*(hd_rec + no) == REC_EOF){return(REC_EOF);}
  Read(*(hd_rec + no),(char *)&hd,sizeof(DbHd_T));
  return(hd.after);
  }

// Before Read
REC_T DbInf_T::HeadBeforeRd(int no)
  {
  DbHd_T hd;
  if (*(hd_rec + no) == REC_EOF){return(REC_EOF);}
  Read(*(hd_rec + no),(char *)&hd,sizeof(DbHd_T));
  return(hd.before);
  }


// Link Read
REC_T DbInf_T::HeadLinkRead(int no)
  {
  DbHd_T hd;
  Read(*(hd_rec + no),(char *)&hd,sizeof(DbHd_T));
  return(hd.link);
  }

// ---------------- Data -------------------
//  Data Store
REC_T DbInf_T::DtStore(char *buff,int len)
  {
  DbDt_T *dt,w_dt;
  REC_T   top_rec,rec,sv_rec;
  int     w_len;
  char   *ww;
  int     ptr;
  
  ww = new char[sizeof(DbDt_T)+di->rec_len];
  dt = (DbDt_T *)ww;
  top_rec = REC_EOF;
  w_len = len;
  
  ptr = 0;
  for(;;)
    {
    if (w_len <= 0){break;}
    rec = DtAlloc();
    if (top_rec == REC_EOF){top_rec = rec; sv_rec = rec;}
    else
      {
      Read (sv_rec,(char *)&w_dt,sizeof(DbDt_T));
      w_dt.link = rec;
      Write(sv_rec,(char *)&w_dt,sizeof(DbDt_T));
      }
    if (w_len >= di->rec_len){dt->len = di->rec_len;}  
    else                     {dt->len = w_len;}
    w_len -= di->rec_len;
    dt->link = REC_EOF;
    mem_cpy(&(dt->dt[0]),buff+ptr,dt->len); 
    Write(rec,(char *)dt,sizeof(DbDt_T)+di->rec_len);
    sv_rec = rec;
    ptr   += dt->len;
    }
  delete [] ww;
  return(top_rec);
  }

//  Data Delete
void DbInf_T::DtDel(REC_T rec)
  {
  REC_T  cur_rec;
  DbDt_T w_dt;
  
  cur_rec = rec;
  for(;;)
    {
    if (cur_rec == REC_EOF){break;}
    Read(cur_rec,(char *)&w_dt,sizeof(DbDt_T));
    DtFree(cur_rec);
    cur_rec = w_dt.link;
    }
  }
  
//  Data Read Check
int DbInf_T::DtBuffLenSum(REC_T rec)
  {
  REC_T  w_rec;
  DbDt_T dt;
  int len;
  
  w_rec = rec;
  len   = 0;
  for(;;)
    {
    if (w_rec == REC_EOF){break;}
    Read(w_rec,(char *)&dt,sizeof(DbDt_T));
    len  += dt.len;
    w_rec = dt.link;
    }
  return(len);  
  }
  
//  Data Read 
void DbInf_T::DtRead(REC_T rec,char *buff)
  {
  REC_T  w_rec;
  char *ww;
  DbDt_T *dt;
  int ptr;

  ww = new char[sizeof(DbDt_T)+di->rec_len];
  dt = (DbDt_T *)ww;
  w_rec = rec;
  ptr   = 0;
  for(;;)
    {
    if (w_rec == REC_EOF){break;}
    Read(w_rec,(char *)dt,sizeof(DbDt_T)+di->rec_len);
    mem_cpy(buff+ptr,&(dt->dt[0]),dt->len);
    ptr  += dt->len;
    w_rec = dt->link;
    }
  delete [] ww;
  }
  
// ---------------- Data List -------------------
// Reallocation 
void DbInf_T::DtListRealloc()
  {
  sChar **w_dt;
  sChar *w,*w2;
  int i;
  
  w_dt = new sChar *[dt_max*2];
  for(i=0;i<dt_max*2;++i)
    {
    w = new sChar("");
    *(w_dt + i) = w;
    }
  for(i=0;i<dt_max;++i)
    {
    w  = *(w_dt + i);
    w2 = *(dt   + i);
    w->set(w2->c_str());
    delete w2;
    }
  delete []dt;
  dt = w_dt;  
  dt_max = dt_max * 2;
  }

// Data List Set   
void DbInf_T::DtListSet(char *buff)
  {
  sChar *w;
  if (dt_su == dt_max -1){DtListRealloc();}
  w = *(dt+dt_su);
  w->set(buff);
  ++dt_su;
  }

// Data List Reset  
void DbInf_T::DtListReset(){dt_su = 0;}  

// Data Write
REC_T DbInf_T::DtListWrite()
  {
  int len;
  int i;
  char *buff;
  char *str;
  sChar *w;
  REC_T top_rec;
  
  len = 0;
  for(i=0;i<dt_su;++i)
    {
    w = *(dt + i);
    len += w->len()+1;
    }
  buff = new char[len];
  
  len = 0;
  for(i=0;i<dt_su;++i)
    {
    w = *(dt + i);
    str = w->c_str();
    mem_cpy(buff+len,str,w->len());
    len += w->len();
    *(buff+len)=0x00;
    ++len;
    }
  top_rec = DtStore(buff,len);
  delete [] buff;
  return(top_rec);
  }

// Data Read
void DbInf_T::DtListRead(REC_T rec)
  {
  int len,i;
  char *buff;
  bool flg;
  
  len = DtBuffLenSum(rec);
  buff = new char[len];
  DtRead(rec,buff);
  
  DtListReset();
  flg = true;
  for(i=0;i<len-1;++i)
    {
    if (flg == true){DtListSet(buff+i); flg = false;}
    if (*(buff+i) == 0x00){flg = true;}
    }
  
  delete [] buff;
  }
  
// Key Srch
int DbInf_T::DtListSrch(REC_T rec,char *key)
  {
  DbDt_T *dt;
  char   *ww;
  int     i,j;
  int     out;

  ww  = new char[sizeof(DbDt_T)+di->rec_len];
  dt  = (DbDt_T *)ww;

  j = 0;
  i = 0;
  dt->len = 0;
  for(;;)
    {
    if (i == dt->len)
      {
      if (rec == REC_EOF){out = 1; break;}
      Read(rec,(char *)dt,sizeof(DbDt_T)+di->rec_len);
      i = 0;
      rec = dt->link;
      if (dt->len == 0){continue;}
      }
    if (dt->dt[i] < *(key+j)) {out =  1; break;}
    if (dt->dt[i] > *(key+j)) {out = -1; break;}
    if (*(key+j)==0x00)       {out =  0; break;}
    ++j; ++i;
    }

  delete [] ww;
  return(out);
  }

// ---------------- Axis Key -------------------
// Axis Link Record Change
void DbInf_T::AxisRec_Wr(REC_T rec)
  {
  char w[10];

  if (rec == REC_EOF){DtListSet("REC_EOF");}
  else               {sprintf(w,"%d",rec); DtListSet(w);}
  }

REC_T DbInf_T::AxisRec_Rd(char *str)
  {
  if (strcmp(str,"REC_EOF")==0){return(REC_EOF);}
  return(SujiConvEx(str));
  }

// Axis Key Search Sub
bool DbInf_T::ApiSrch(int no,char *key)
  {
  int kbn;
  int sv;
  REC_T sv_rec,rec;

  if (HeadCur_Rd(no) == REC_EOF) {HeadTopSet(no);}
  sv = 0;
  sv_rec = REC_EOF;
  for(;;)
    {
    if ((rec = HeadCur_Rd(no)) == REC_EOF){break;}
    kbn = DtListSrch(HeadLinkRead(no),key);
    if (kbn == 0){return(true);}
    if (sv == 0){sv = kbn;}
    if (sv != kbn){break;}
    if (kbn == -1){HeadBeforeSet(no);}
    else          {HeadNextSet  (no);}
    sv_rec = rec;
    }
  if (sv == -1){HeadCur_Wr(no,sv_rec);}
  return(false);
  }

// Axis Key Search
bool DbInf_T::ApiAxisSrch(int no,int dt_no,char *key)
  {
  if (ApiSrch(no,key) == true)
    {
    DtListRead(HeadLinkRead(no));
    CtlSet(dt_no,AxisRec_Rd(DtList_Rd(1)),AxisRec_Rd(DtList_Rd(2)));
    return(true);
    }
  CtlSet(dt_no,REC_EOF,REC_EOF);
  return(false);
  }

// Store
void DbInf_T::ApiAxisStore(int no,int dt_no,char *key)
  {
  DbCtl_T *ctl;

  ctl = *(ctl_tbl+dt_no);
  DtListReset();
  DtListSet(key);
  AxisRec_Wr(ctl->head);
  AxisRec_Wr(ctl->tail);
  if (ApiSrch(no,key) == true)
    {
    DtDel(HeadLinkRead(no));
    HeadLinkChg(no,DtListWrite());
    }
  else
    {
    HeadLink(no,DtListWrite());
    }
  }

// Delete
void  DbInf_T::ApiAxisDel(int no,int dt_no,char *key)
  {
  if (ApiSrch(no,key) == true){DtDel(HeadLinkRead(no)); HeadDel(no);}
  CtlSet(dt_no,REC_EOF,REC_EOF);
  }

// Read
void  DbInf_T::ApiAxisRead(int no,int dt_no)
  {
  REC_T rec;
  rec = HeadLinkRead(no);
  if (rec == REC_EOF){return;}
  DtListRead(rec);
  CtlSet(dt_no,AxisRec_Rd(DtList_Rd(1)),AxisRec_Rd(DtList_Rd(2)));
  }

// Data Read
void  DbInf_T::ApiDtRead(int no)
  {
  REC_T rec;
  rec = HeadLinkRead(no);
  if (rec == REC_EOF){DtListReset(); return;}
  DtListRead(rec);
  }

// Search Read
void  DbInf_T::ApiDtSrchRead(int no,char *key)
  {
  if (ApiSrch(no,key) == true){DtListRead(HeadLinkRead(no));}
  else                               {DtListReset();}
  }


// Data Write  
void  DbInf_T::ApiDtStore(int no)
  {
  if (dt_su == 0){return;}
  HeadLinkLast (no,DtListWrite());
  }

// Search Write
void  DbInf_T::ApiDtSrchStore(int no,char *key)
  {
  if (dt_su == 0){return;}
  if (ApiSrch(no,key) == true){DtDel(HeadLinkRead(no)); HeadLinkChg(no,DtListWrite());}
  else                               {HeadLink(no,DtListWrite());}
  }

// Data Delete
void  DbInf_T::ApiDtDel(int no)
  {
  REC_T rec;
  rec = HeadLinkRead(no);
  if (rec == REC_EOF){return;}
  DtDel(HeadLinkRead(no)); HeadDel(no);
  }

// Data Delete All
void  DbInf_T::ApiDtDelAll(int no)
  {
  REC_T rec;
  
  ApiTop_Set(no);
  rec = ApiCur_Rd(no);
  for(;;)
    {
    if (rec==REC_EOF){break;}
    rec = HeadNextRd(no);
    ApiDtDel(no);
    ApiCur_Set(no,rec);
    }
  }


// Data Search Delete
void  DbInf_T::ApiDtSrchDel(int no,char *key)
  {
  if (ApiSrch(no,key) == true){DtDel(HeadLinkRead(no)); HeadDel(no);}
  }
  
// Read Data Get
char *DbInf_T::ApiDt_Rd (int idx)
  {
  return(DtList_Rd(idx));
  }
  
// Write Data Set
void  DbInf_T::ApiDt_Set(char *buff)
  {
  sChar *w;

  for(;;)
    {
    if (dt_su >= dt_max)
      {
      DtListRealloc();
      continue;
      }
    break;
    }
  w = *(dt+dt_su);
  w->set(buff);
  ++dt_su;
  }  
  
