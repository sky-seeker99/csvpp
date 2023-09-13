//
//  wire analyze
//

#include "wire_anl.h"

// # search #####
bool wireAnl_C::srch(char *p){
  bool ret=false;
  sChar *str;
  ARY_LOOP(str,sChar,sense_fp)
    if (strcmp(str->c_str(),p) == 0){ret=true; break;} 
  LOOP_END
  return(ret);
}

// # clean #####
void wireAnl_C::clean(){
  sChar *str;
  ARY_LOOP(str,sChar,sense_fp) delete str; LOOP_END
  sense_fp->clear();
  sense_fp->get_init();

}

// # exec #####
void wireAnl_C::exec(char *p_str){
  clean();
  ssc->set(p_str);
  for(int i=0;i<ssc->getNum();i++){
    char *str = ssc->get(i);
    if (srch(str)){continue;}
    sChar *s = new sChar(str);
    sense_fp->mem_alloc((unsigned char *)s);
  }
}

// # get #####
char *wireAnl_C::get(int no){
  sChar *s = (sChar *)sense_fp->get(no);
  if (s == NULL){return(NULL);}
  return(s->c_str());
}

