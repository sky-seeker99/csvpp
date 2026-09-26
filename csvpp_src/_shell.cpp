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



