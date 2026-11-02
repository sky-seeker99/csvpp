#include "Order.h"
Order::Order(int p_orderId,int p_customerId,int p_productId,int p_quantity,double p_unitPrice){
  orderId = p_orderId;
  customerId = p_customerId;
  productId = p_productId;
  quantity = p_quantity;
  unitPrice = p_unitPrice;
}
int Order::getOrderId(){
  return orderId;
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
double Order::getUnitPrice(){
  return unitPrice;
}
double Order::getTotalPrice(){
  return quantity * unitPrice;
}
void Order::setQuantity(int value){
  quantity = value;
}
