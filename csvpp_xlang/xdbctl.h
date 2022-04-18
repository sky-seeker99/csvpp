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

#ifndef _XDBCTL_H_
#define _XDBCTL_H_

#include "../csvpp_xbase/zlist.h"
#include "../csvpp_xbase/ztool.h"

#define DB_LOOP(NO,FP)  for(FP->ApiTop_Set(NO);;FP->ApiNext_Set(NO)){ \
                          if (FP->ApiCur_Rd(NO) == REC_EOF) {break;}
#define REC_T long         // pointer define
#define REC_EOF  (REC_T)-1 // NULL poniter

// ---------------- DataBase Control Area ------------------------
// Control Header
typedef struct
  {
  long	type;		// �f�[�^�x�[�X����
  REC_T	len;		// �t�@�C���̒���
  REC_T	rec_len;	// �f�[�^���̂P���R�[�h�̒���
  REC_T	ctl_link;	// ������̃|�C���^
  REC_T ctl_dust;       // ������̍폜�|�C���^
  REC_T	hd_dust;	// �w�b�_���̍폜�|�C���^
  REC_T	dt_dust;	// �f�[�^���̍폜�|�C���^
  } DbInfo_T;

// Control List Top-End Record
typedef struct
  {
  REC_T	link;		// ��|�C���^
  REC_T	head;		// �w�b�_���̃w�b�_�|�C���^
  REC_T	tail;		// �w�b�_���̃e�[���|�C���^
  } DbCtl_T;

// Data Header
typedef struct
  {
  REC_T	after;		// ��|�C���^
  REC_T	before;		// �O�|�C���^
  REC_T	link;		// �f�[�^���̃|�C���^
  } DbHd_T;

// Data
typedef struct
  {
  REC_T		len;			//	�L���f�[�^��
  REC_T		link;			//	��|�C���^
  char		dt[4];			//	�f�[�^
  } DbDt_T;

// ---------------- DataBase Control Interface -------------------
class DbInf_T{
  public:
  int		handle;		// �t�@�C���n���h��
  int           mode;           // �I�[�v�����[�h
  sChar         *file;          // �t�@�C����
  DbInfo_T	*di;            // �t�@�C�����
  int		ctl_su;		// ������
  DbCtl_T	**ctl_tbl;	// ������
  REC_T		*hd_rec;	// �J�����g�w�b�_���
  bool          open_err_flg;   // Open Error Flg
  bool          io_err_flg;     // I/O Error Flg

  int		dt_max;		// �A���P�[�V�����f�[�^�̐�
  int		dt_su;		// �f�[�^��
  sChar		**dt;		// �f�[�^�i�C���^�[�t�F�[�X�p�j

  // interface
  public:
  void  AxisRec_Wr    (REC_T rec                 );
  REC_T AxisRec_Rd    (char *str                 );
  bool  ApiSrch       (int no,          char *key);
  bool  ApiAxisSrch   (int no,int dt_no,char *key);
  void  ApiAxisRead   (int no,int dt_no          );
  void  ApiAxisStore  (int no,int dt_no,char *key);
  void  ApiAxisDel    (int no,int dt_no,char *key);
  void  ApiDtStore    (int no                    );
  void  ApiDtRead     (int no                    );
  void  ApiDtDel      (int no                    );
  void  ApiDtDelAll   (int no                    );
  void  ApiDtSrchStore(int no,char *key          );
  void  ApiDtSrchRead (int no,char *key          );
  void  ApiDtSrchDel  (int no,char *key          );
  void  ApiDt_Set     (char *buff                );
  char *ApiDt_Rd      (int idx                   );
  void  ApiDt_Reset   (                          );
  REC_T ApiTop_Set    (int no                    );
  REC_T ApiTop_Rd     (int no                    );
  REC_T ApiEnd_Set    (int no                    );
  REC_T ApiEnd_Rd     (int no                    );
  REC_T ApiNext_Set   (int no                    );
  REC_T ApiBefore_Set (int no                    );
  REC_T ApiNext_Rd    (int no                    );
  REC_T ApiBefore_Rd  (int no                    );
  void  ApiCur_Set    (int no,REC_T rec          );
  REC_T ApiCur_Rd     (int no                    );
  bool  OpenError_Rd  (                          );
  bool  IOError_Rd    (                          );

  // inner method
  private:
  void Read (REC_T p_rec,char *p_buff,int p_len);
  void Write(REC_T p_rec,char *p_buff,int p_len);

  REC_T EndSum  (int p_len);
  REC_T HdAlloc (         );
  void  HdFree  (REC_T rec);
  REC_T DtAlloc (         );
  void  DtFree  (REC_T rec);
  REC_T CtlAlloc(         );
  void  CtlFree (REC_T rec);

  void CtlSet    (int no,REC_T head,REC_T tail);
  void CtlFreeAll(          );
  void CtlExtend (int ctl_su);
  void CtlRead   (          );
  void CtlWrite  (          );

  void  HeadLink     (int no,REC_T link);
  void  HeadLinkLast (int no,REC_T link);
  void  HeadLinkChg  (int no,REC_T link);
  void  HeadDel      (int no           );
  void  HeadDelAll   (int no           );
  REC_T HeadTopSet   (int no           );
  REC_T HeadTopRd    (int no           );
  REC_T HeadEndSet   (int no           );
  REC_T HeadEndRd    (int no           );
  REC_T HeadNextSet  (int no           );
  REC_T HeadBeforeSet(int no           );
  REC_T HeadNextRd   (int no           );
  REC_T HeadBeforeRd (int no           );
  REC_T HeadLinkRead (int no           );
  REC_T HeadCur_Rd   (int no           );
  void  HeadCur_Wr   (int no,REC_T rec );
  
  REC_T DtStore     (char *buff,int len  );
  void  DtDel       (REC_T rec           );
  int   DtBuffLenSum(REC_T rec           );
  void  DtRead      (REC_T rec,char *buff);

  void  DtListRealloc(                   );
  void  DtListSet    (char *buff         );
  void  DtListReset  (                   );
  REC_T DtListWrite  (                   );
  void  DtListRead   (REC_T rec          );
  int   DtListSrch   (REC_T rec,char *key);
  char *DtList_Rd    (int no             );

  public:
  DbInf_T(char *p_file,int  p_mode,long p_file_type,int p_rec_len);
  ~DbInf_T();
  };

#endif // _XDBCTL_H_
