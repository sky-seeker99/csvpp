//
//  wire analyze
//

#ifndef _WIRE_ANL_H_
#define _WIRE_ANL_H_

class wireAnl_C{
  public:
    VariableArray_C *sense_fp;  // sChar 
    tokenAnl_C *ssc;

    char *get(int no);
    void  exec(char *str);
    void  clean();
    bool  srch(char *p);

    wireAnl_C(){
      ssc = new tokenAnl_C();
      ssc->setKey(' ');
      ssc->setKey('+');
      ssc->setKey('-');
      ssc->setKey('*');
      ssc->setKey('/');
      ssc->setKey('&');
      ssc->setKey('|');
      ssc->setKey('%');
      ssc->setKey('>');
      ssc->setKey('<');
      ssc->setKey('=');
      ssc->setKey('!');
      ssc->setKey('~');
      ssc->setKey('|');
      ssc->setKey('(');
      ssc->setKey(')');
      ssc->setKey('{');
      ssc->setKey('}');
      sense_fp = new VariableArray_C(10);
    }
    
    ~wireAnl_C(){
      clean();
      delete sense_fp;
      delete ssc;
    }
  };

#endif // _WIRE_ANL_H_  
