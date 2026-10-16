#include "Customer.h"
Customer::Customer(int p_id,std::string p_name,std::string p_email,std::string p_phone){
  id = p_id;
  name = p_name;
  email = p_email;
  phone = p_phone;
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
std::string Customer::getPhone(){
  return phone;
}
void Customer::setId(int value){
  id = value;
}
void Customer::setName(std::string value){
  name = value;
}
void Customer::setEmail(std::string value){
  email = value;
}
void Customer::setPhone(std::string value){
  phone = value;
}
