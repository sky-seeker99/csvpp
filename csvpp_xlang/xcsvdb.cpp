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
//  Database for csvpp interface
//

#include <string.h>
#include <fcntl.h>
#include "xcsvdb.h"

// # Database File Poniter ---------------
void DbFile_T::ChgAxis(){
  if (wr_req == false){return;}
  di->ApiAxisStore(cur_axisno+1,cur_axisno,cur_key->c_str());
  wr_req = false;
  }
void DbFile_T::ChgAxis(char *p_handle,int p_axisno,char *p_key){
  if (strcmp(p_handle,cur_handle->c_str()) == 0)
    {
    if (strcmp(cur_key->c_str(),p_key)==0){return;}
    }
  ChgAxis();
  cur_axisno = p_axisno;
  cur_handle->set(p_handle);
  cur_key->set(p_key);
  di->ApiAxisSrch(cur_axisno+1,cur_axisno,p_key);
  }
DbFile_T::DbFile_T(char *handle,char *file,char *key,int axisno){ // Constructer
  file_name       = new sChar(file);
  cur_axisno      = axisno;
  cur_handle      = new sChar(handle);
  cur_key         = new sChar(key);
  wr_req          = false;
  di              = new DbInf_T(file,O_RDWR,ApiFileInfo,ApiRecLen);
  di->ApiAxisSrch (axisno+1,axisno,key);
  di->ApiAxisStore(axisno+1,axisno,key);
  }
DbFile_T::~DbFile_T(){
  ChgAxis();
  delete file_name;
  delete cur_handle;
  delete cur_key;
  delete di;
  }
bool DbFile_T::Err_Rd(){return(di->open_err_flg);}

// # Database File Handle -------------
DbHandle_T::DbHandle_T(char *p_handle,DbFile_T *p_dbf,int p_axisno,char *p_key){
  handle  = new sChar(p_handle);
  key     = new sChar(p_key);
  dbf     = p_dbf;
  axisno  = p_axisno;
  }
DbHandle_T::~DbHandle_T(){
  delete handle;
  delete key;
  }

// # Database Interface ----------------
CsvDb_T::CsvDb_T(MemHeader_T *p_it){
  it        = p_it;
  file_fp   = new MEM_FP(it);
  handle_fp = new MEM_FP(it);
  }
CsvDb_T::~CsvDb_T(){
  DbHandle_T *dh;
  DbFile_T   *dbf;
  MEM_LOOP(dh ,DbHandle_T,handle_fp) delete dh;  LOOP_END
  MEM_LOOP(dbf,DbFile_T  ,file_fp  ) delete dbf; LOOP_END
  delete file_fp;
  delete handle_fp;
  }
void  CsvDb_T::dbsread (char *key   ){dbf->di->ApiDtSrchRead (dh->axisno,key);}
void  CsvDb_T::dbswrite(char *key   ){dbf->di->ApiDtSrchStore(dh->axisno,key);}
void  CsvDb_T::dbsdel  (char *key   ){dbf->di->ApiDtSrchDel  (dh->axisno,key);}
void  CsvDb_T::dbwrite (            ){dbf->di->ApiDtStore(dh->axisno); dbf->di->ApiDt_Reset();}
void  CsvDb_T::cell_wr (char *buff  ){dbf->di->ApiDt_Set(buff);}
char *CsvDb_T::cell_rd (            ){++cnt; return(dbf->di->ApiDt_Rd(cnt-1));}

// ------------
// %dbopen
// ------------
bool CsvDb_T::dbopen(char *handle,char *file,char *key,int axis_no){

  // dbfile store
  it->srch_key = file;
  if (file_fp->mem_srch() == 0)
    {
    dbf = (DbFile_T *)file_fp->mem_link_ptr_rd();
    dbf->ChgAxis(handle,axis_no,key);
    }
  else
    {
    dbf = new DbFile_T(handle,file,key,axis_no);
    if (dbf->Err_Rd() == true){delete dbf; return(false);}
    it->alloc_ptr = (MM_PTR_T *)dbf;
    file_fp->mem_srch_alloc();
    }

  // handle search
  it->srch_key = handle;
  if (handle_fp->mem_srch() == 0)
    {
    dh = (DbHandle_T *)handle_fp->mem_link_ptr_rd();
    dh->dbf    = dbf;
    dh->axisno = axis_no;
    dh->key->set(key);
    }
  else
    {
    dh = new DbHandle_T(handle,dbf,axis_no,key);
    it->alloc_ptr = (MM_PTR_T *)dh;
    handle_fp->mem_srch_alloc();
    }
  return(true);
  }

// ------------
// %dbread
// ------------
bool CsvDb_T::dbread()
  {
  if (dbf->di->ApiCur_Rd(dh->axisno) == REC_EOF){return(false);}
  dbf->di->ApiDtRead(dh->axisno);
  dbf->di->ApiNext_Set(dh->axisno);
  cnt = 0;
  return(true);
  }

// -----------------------------------
// Handle Set
// kbn = 0:%dbsread/%dbswrite/%dbsdel
// kbn = 1:%dbread
// kbn = 2:%dbwrite
// kbn = 3:%dbsdel
// -----------------------------------
bool CsvDb_T::handle(char *handle,int kbn)
  {
  it->srch_key = handle;
  if (handle_fp->mem_srch() != 0){return(false);}
  dh = (DbHandle_T *)handle_fp->mem_link_ptr_rd();
  dbf = dh->dbf;

  dbf->ChgAxis(handle,dh->axisno,dh->key->c_str());
  dbf->di->ApiDt_Reset();
  cnt = 0;
  if (kbn == ApiDbRead ){dbf->di->ApiTop_Set (dh->axisno);}  // %dbread
  if (kbn == ApiDbWrite){dbf->di->ApiDtDelAll(dh->axisno);}  // %dbwrite
  if ((kbn == ApiDbWrite )
   || (kbn == ApiDbsWrite)
   || (kbn == ApiDbsDel  ))
    {
    dbf->wr_req = true;
    }

  return(true);
  }



