#include <string>
#ifndef _Customer_h_
#define _Customer_h_
class Customer{
  private:
    int id; 
    std::string name; 
    std::string email; 
  public:
    Customer(int p_id,std::string p_name,std::string p_email);
    int getId();
    std::string getName();
    std::string getEmail();
    void setEmail(std::string value);
};
#endif  // _Customer_h_
