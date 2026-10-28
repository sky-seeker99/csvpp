#include "DesignProduct.h"
Product::Product(int p_id,std::string p_name,double p_price,int p_stock){
  id = p_id;
  name = p_name;
  price = p_price;
  stock = p_stock;
}
int Product::getId(){
  return id;
}
std::string Product::getName(){
  return name;
}
double Product::getPrice(){
  return price;
}
int Product::getStock(){
  return stock;
}
void Product::setId(int value){
  id = value;
}
void Product::setName(std::string value){
  name = value;
}
void Product::setPrice(double value){
  price = value;
}
void Product::setStock(int value){
  stock = value;
}
bool Product::isInStock(){
  return stock > 0;
}
bool Product::reduceStock(int quantity){
  if (quantity <= 0) {
      return false;
  }
  if (stock < quantity) {
      return false;
  }
  stock -= quantity;
  return true;
}
