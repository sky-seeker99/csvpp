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





