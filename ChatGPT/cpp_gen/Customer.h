#include <string>
#ifndef _Customer_h_
#define _Customer_h_
class Customer{
  private:
    int id; 
    std::string name; 
    std::string email; 
    std::string phone; 
  public:
    Customer(int p_id,std::string p_name,std::string p_email,std::string p_phone);
    int getId();
    std::string getName();
    std::string getEmail();
    std::string getPhone();
    void setId(int value);
    void setName(std::string value);
    void setEmail(std::string value);
    void setPhone(std::string value);
};
#endif  // _Customer_h_
