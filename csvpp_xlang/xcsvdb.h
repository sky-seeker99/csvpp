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
//  Database for csvpp interface 
//

#ifndef _XCSVDB_H_
#define _XCSVDB_H_

#include "../csvpp_xbase/zlist.h"
#include "xdbctl.h"

#define ApiFileInfo   0xeffc // file sikibetsu
#define ApiRecLen     20     // record length
#define ApiDbsRead    0
#define ApiDbsWrite   1
#define ApiDbsDel     2
#define ApiDbRead     3
#define ApiDbWrite    4

// # Database File Poniter -------------
class DbFile_T{
  public:
  sChar        *file_name;        // Database Filename
  int           cur_axisno;       // Current Axisno
  sChar        *cur_key;          // Current KEy
  sChar        *cur_handle;       // Current handle name
  bool          wr_req;           // Write Request Flag
  DbInf_T      *di;               // Database Pointer
  void ChgAxis();
  void ChgAxis(char *p_handle,int p_axisno,char *p_key);
  DbFile_T(char *handle,char *file,char *key,int axisno);
  ~DbFile_T();
  bool Err_Rd();
  };

// # Database File Handle ----------------
class DbHandle_T{
  public:
  sChar       *handle;           // handle name
  DbFile_T    *dbf;              // DbFile_T
  int          axisno;           // axisno = axisno+1 dtno = axisno
  sChar       *key;              // key
  DbHandle_T(char *p_handle,DbFile_T *p_dbf,int p_axisno,char *p_key);
  ~DbHandle_T();
  };

// # Database Interface -----------------
class CsvDb_T{
  public:
  MemHeader_T *it;        // Mem Interface
  MEM_FP      *file_fp;   // Database File Pointer List
  MEM_FP      *handle_fp; // Database Handle List
  DbFile_T    *dbf;
  DbHandle_T  *dh;
  int          cnt;
  CsvDb_T(MemHeader_T *p_it);
  ~CsvDb_T();
  bool  dbopen  (char *handle,char *file,char *key,int axis_no);
  bool  handle  (char *handle,int kbn);
  void  dbsread (char *key   );
  void  dbswrite(char *key   );
  void  dbsdel  (char *key   );
  bool  dbread  (            );
  void  dbwrite (            );
  void  cell_wr (char *buff  );
  char *cell_rd (            );
  };

#endif // _XCSVDB_H_

