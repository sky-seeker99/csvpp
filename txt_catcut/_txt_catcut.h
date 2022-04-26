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
// binary control interface
//
class text_ctl_T{
  public:
    Read64_C  *in_fp;
	Read64_C *out_fp;
    FileTemp64_T *temp;
	bool okFlg;
	bool newFlg;
	sChar *sv_out_file;
    
	text_ctl_T(char *p_in_file,char *p_out_file,bool p_newFlg,int p_buff_size){
      int buff_size = p_buff_size * 1024;
	  char out_file[4096];
	  char in_file[4096];
	  okFlg     = false;
	  newFlg    = p_newFlg;
	  temp      = NULL;
	  in_fp     = NULL;
	  out_fp    = NULL;
	  if (_fullpath(in_file, p_in_file  , 4096) == NULL){printf("file_name error. (%s)\n",  p_in_file); return;}
	  if (_fullpath(out_file, p_out_file, 4096) == NULL){printf("file_name error. (%s)\n", p_out_file); return;}
	  sv_out_file  = new sChar(out_file);

	  // # File Open #####
	  temp      = new FileTemp64_T("tmp"   ,"wt",buff_size);
	  in_fp     = new Read64_C    (in_file ,"rt",buff_size);
	  out_fp    = new Read64_C    (out_file,"rt",buff_size);

	  // # File Check #####
	  if (in_fp->okCheck() == false){printf("read open error.(%s)\n",in_file ); return;}
	  if (newFlg == false){
		if (out_fp->okCheck() == false){printf("read open error.(%s)\n",out_file); return;}
	  }
	  okFlg = true;

	}
    
  ~text_ctl_T(){
    if (temp    != NULL){delete temp;}
    if (in_fp   != NULL){delete in_fp;}
	if (out_fp  != NULL){delete out_fp;}
	delete sv_out_file;
  }
  
  void text_ctl_T::Main(__int64 read_offset,__int64 write_offset,__int64 write_line);

};





