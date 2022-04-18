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
// shell_begin - shell_end
// Ver 1.66
//


// shell data -----------------
class ShellCell_T{
  public:
  FILE           *back_fp;    // FILE
  VariableArray_C *shell_fp;   // cell:sChar
  bool             shell_flag;

  ShellCell_T(){
    back_fp = NULL;
	shell_fp = new VariableArray_C(10);
	shell_flag = false;
  }
  ~ShellCell_T(){
    delete shell_fp;
  }
};

class ShellNest_T{
  public:
  VariableStack_C *stack_fp;  // cell:ShellCell_T
  ShellCell_T *c;
  bool shell_flag;
  FILE *back_fp;

  ShellNest_T(){
	stack_fp = new VariableStack_C(10);
  }
  ~ShellNest_T(){
	for(;;){
	  c = (ShellCell_T *)stack_fp->pop();
	  if (c == NULL){break;}
	  sChar *str;
	  ARY_LOOP(str,sChar,c->shell_fp) delete str; LOOP_END
	  delete c;
	}
	delete stack_fp;
  }

  void push(FILE *fp,VariableArray_C *mem_fp,bool f){
	sChar *w;
	c = new ShellCell_T();
	c->back_fp = fp;
	c->shell_flag = f;
	ARY_LOOP(w,sChar,mem_fp)
	  c->shell_fp->mem_alloc((unsigned char *)w);
	LOOP_END
	mem_fp->clear();
	stack_fp->push((unsigned char *)c);
  }

  bool pop(VariableArray_C *mem_fp){
	sChar *w;
	c = (ShellCell_T *)stack_fp->pop();
	if (c == NULL){return(false);}
	ARY_LOOP(w,sChar,c->shell_fp)
	  mem_fp->mem_alloc((unsigned char *)w);
	LOOP_END
	shell_flag = c->shell_flag;
	back_fp = c->back_fp;
	delete c;
	return(true);
  }

  FILE *getFp(){return(back_fp);}
  bool  getFlag(){return(shell_flag);}
  
};



