#include <string>
#ifndef _AddressBook_h_
#define _AddressBook_h_
class AddressBook{
  private:
    std::string name; 
    std::string address; 
    std::string phone; 
    std::string email; 
  public:
    AddressBook(std::string p_name,std::string p_address,std::string p_phone,std::string p_email);
    std::string getName();
    std::string getAddress();
    std::string getPhone();
    std::string getEmail();
    void setName(std::string value);
    void setAddress(std::string value);
    void setPhone(std::string value);
    void setEmail(std::string value);
};
#endif  // _AddressBook_h_
