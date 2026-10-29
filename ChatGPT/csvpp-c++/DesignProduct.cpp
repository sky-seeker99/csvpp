#include "DesignProduct.h"
Customer::Product(int p_id,std::string p_name,double p_price,int p_stock){
  id = p_id;
  name = p_name;
  price = p_price;
  stock = p_stock;
}
int Customer::getId(){
  return id;
}
std::string Customer::getName(){
  return name;
}
double Customer::getPrice(){
  return price;
}
int Customer::getStock(){
  return stock;
}
void Customer::setId(int value){
  id = value;
}
void Customer::setName(std::string value){
  name = value;
}
void Customer::setPrice(double value){
  price = value;
}
void Customer::setStock(int value){
  stock = value;
}
bool Customer::isInStock(){
  return stock > 0;
}
bool Customer::reduceStock(int quantity){
  if (quantity <= 0) {
    return false;
  }
  if (stock < quantity) {
    return false;
  }
  stock -= quantity;
  return true;
}
bool Customer::restock(int quantity){
  if (quantity <= 0) {
    return false;
  }
  stock += quantity;
}
