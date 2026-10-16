#include "Order.h"
Order::Order(int p_id,int p_customerId,int p_productId,int p_quantity,double p_totalAmount){
  id = p_id;
  customerId = p_customerId;
  productId = p_productId;
  quantity = p_quantity;
  totalAmount = p_totalAmount;
}
int Order::getId(){
  return id;
}
int Order::getCustomerId(){
  return customerId;
}
int Order::getProductId(){
  return productId;
}
int Order::getQuantity(){
  return quantity;
}
double Order::getTotalAmount(){
  return totalAmount;
}
void Order::setId(int value){
  id = value;
}
void Order::setCustomerId(int value){
  customerId = value;
}
void Order::setProductId(int value){
  productId = value;
}
void Order::setQuantity(int value){
  quantity = value;
}
void Order::setTotalAmount(double value){
  totalAmount = value;
}
