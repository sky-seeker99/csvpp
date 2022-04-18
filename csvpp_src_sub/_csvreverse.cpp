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
//  CSVPP Front End Control reverse 
// 
// # constructor #####
reverse_T::reverse_T(char *p_file){
	if (check(p_file)){reverseOut(p_file);}
}

// # destructor #####
reverse_T::~reverse_T(){
}

// # reverse exist check routine #####
bool reverse_T::check(char *p_name){
	int cnt;
	bool flg=false;
	CsvInf_T	*csvi = new CsvInf_T(p_name);
	if (csvi->CsvError_Rd() != 0){delete csvi; return(false);}
	
	for(;;){
		if (csvi->CsvFgets() == -1) {break;}
		if ((cnt=csvi->CsvSelSu_Rd()) == 0){continue;}
		for(int i=0;i<cnt;i++){
			char *str = csvi->CsvSel_Rd(i);
			if (str == MM_NULL){continue;}
			sp_push(str); sp_push2(str);
			if (strcmp(str,"%\\VVV")==0){flg=true;}
			break;
		}
	}
	
	delete csvi;
	return(flg);	
}

// # reverse out routine #####
void reverse_T::reverseOut(char *p_name){
	int cnt;
	CsvInf_T	*csvi 			= new CsvInf_T(p_name);
	if (csvi->CsvError_Rd() != 0){delete csvi; return;}
	FileTemp_T  *temp_fp		= new FileTemp_T("tmp");
	FILE        *out_fp			= temp_fp->fp;
	bool		topFlg 			= false;
	bool		btmFlg			= false;
	int 		state			= 0;
	MemHeader_T *it				= new MemHeader_T();
	MEM_FP		*mem_fp			= new MEM_FP(it);
	MEM_FP		*ary_fp;
	sChar		*s_str;

	csvi->sp_push_set(false);
        
	for(;;){
		if (csvi->CsvFgets() == -1) {break;}
		if ((cnt=csvi->CsvSelSu_Rd()) == 0){fprintf(out_fp,"\n"); continue;}
                topFlg=false;
                btmFlg=false;
		for(int i=0;i<cnt;i++){
			char *str = csvi->CsvSel_Rd(i);
			if (str == MM_NULL){continue;}
			sp_push(str); sp_push2(str);
			if (strcmp(str,"%\\VVV")==0){topFlg=true;}
			if (strcmp(str,"%\\^^^")==0){btmFlg=true;}
			break;
		}
		if (state==0){
			if (topFlg){
				topFlg=false;
				state=1;
				yoko_max=0;
				tate_max=0;
				continue;
			}
			bool first=true;
			for(int i=0;i<cnt;i++){
				char *str = csvi->CsvSel_Rd(i);
                        	if (first){first=false;}
				else	  {fprintf(out_fp,",");}

				if (str != MM_NULL){csvi->CsvWrite(out_fp,str);}
			}
                        fprintf(out_fp,"\n");
			
		}
		else if (state==1){
			if (btmFlg){
				crossWrite(csvi,mem_fp,out_fp);
				state=0;
				continue;
			}
			ary_fp = new MEM_FP(it);
			it->alloc_ptr = ary_fp;
			mem_fp->mem_alloc();
			for(int i=0;i<cnt;i++){
				char *str = csvi->CsvSel_Rd(i);
				if (str == MM_NULL) {it->alloc_ptr = new sChar("");}
				else				{it->alloc_ptr = new sChar(str);}
				ary_fp->mem_alloc();
			}
			if (cnt > yoko_max){yoko_max = cnt;}
			tate_max++;
		}
	}
	
	if (state == 1){crossWrite(csvi,mem_fp,out_fp);}
	
	delete csvi;
	delete mem_fp;
	delete it;
  	DeleteFile(p_name);
  	temp_fp->close();
  	temp_fp->TempToRename(p_name);
	delete temp_fp;
}

// # cross write routine #####
void reverse_T::crossWrite(CsvInf_T *csvi,MEM_FP *mem_fp,FILE *out_fp){
	sChar **buff;
	int i,x,y;
	sChar *s_str;
       	MEM_FP *ary_fp;

	buff = new sChar*[yoko_max*tate_max];
		for(i=0;i<yoko_max*tate_max;i++){*(buff+i) = NULL;}
	
	y=0;
	MEM_LOOP(ary_fp,MEM_FP,mem_fp)
		x=0;
		MEM_LOOP(s_str,sChar,ary_fp)
			*(buff+y*yoko_max+x) = s_str;
			x++;
		LOOP_END
		y++;
	LOOP_END

	for(y=0;y<yoko_max;y++){
                bool first=true;
		for(x=0;x<tate_max;x++){
			s_str = *(buff+x*yoko_max+y);
                        if (first){first=false;}
                        else      {fprintf(out_fp,",");}
                        
			if (s_str != NULL){
                                csvi->CsvWrite(out_fp,s_str->c_str());
                        }
		}
                fprintf(out_fp,"\n");
	}

	// delete 
	MEM_LOOP(ary_fp,MEM_FP,mem_fp)
		MEM_LOOP(s_str,sChar,ary_fp)
			delete s_str;
		LOOP_END
		delete ary_fp;
	LOOP_END
	mem_fp->mem_del_all();
	delete [] buff;
}


