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
// binary_file control
//

void text_ctl_T::Main(__int64 read_offset,__int64 write_offset,__int64 write_line){
  if (okFlg == false){return;}
  
  // # Write File #####
  if (newFlg == false){
	for(__int64 i=0;;i++){
	  if ((write_offset != (__int64)-1) && (write_offset == i)){break;}
	  unsigned char *buff = out_fp->read();
	  if (buff == NULL){break;}
	  temp->out_fp->writeln(buff);
	}
  }

  // # Read File offset skip #####
  for(__int64 i=0;;i++){
	if (read_offset == 0){break;}
	if (read_offset == i+(__int64)1){break;}
	unsigned char *buff = in_fp->read();
	if (buff == NULL){break;}
  }

  // # Read File #####
  for(__int64 i=0;;i++){
	if ((write_line != (__int64)-1) && (write_line == i)){break;}
	unsigned char *buff = in_fp->read();
	if (buff == NULL){break;}
	temp->out_fp->writeln(buff);
  }

  // # Write File #####
  if (newFlg == false){
	for(;;){
	  unsigned char *buff = out_fp->read();
	  if (buff == NULL){break;}
	  temp->out_fp->writeln(buff);
	}
  }

  
  // # Temp File -> out file copy #####
  delete out_fp;
  out_fp = NULL;
  temp->tempFileToCopy(sv_out_file->c_str());

}





