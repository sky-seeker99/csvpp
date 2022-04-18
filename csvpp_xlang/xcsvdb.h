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

