#include "AddressBook.h"
AddressBook::AddressBook(std::string p_name,std::string p_address,std::string p_phone,std::string p_email){
  name = p_name;
  address = p_address;
  phone = p_phone;
  email = p_email;
}
std::string AddressBook::getName(){
  return name;
}
std::string AddressBook::getAddress(){
  return address;
}
std::string AddressBook::getPhone(){
  return phone;
}
std::string AddressBook::getEmail(){
  return email;
}
void AddressBook::setName(std::string value){
  name = value;
}
void AddressBook::setAddress(std::string value){
  address = value;
}
void AddressBook::setPhone(std::string value){
  phone = value;
}
void AddressBook::setEmail(std::string value){
  email = value;
}
