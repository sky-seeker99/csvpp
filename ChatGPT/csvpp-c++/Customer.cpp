#include "Customer.h"
Customer::Customer(int p_id,std::string p_name,std::string p_email){
  id = p_id;
  name = p_name;
  email = p_email;
}
int Customer::getId(){
  return id;
}
std::string Customer::getName(){
  return name;
}
std::string Customer::getEmail(){
  return email;
}
void Customer::setEmail(std::string value){
  email = value;
}
