#include <string>
#ifndef _Order_h_
#define _Order_h_
class Order{
  private:
    int orderId; 
    int customerId; 
    int productId; 
    int quantity; 
    double unitPrice; 
  public:
    Order(int p_orderId,int p_customerId,int p_productId,int p_quantity,double p_unitPrice);
    int getOrderId();
    int getCustomerId();
    int getProductId();
    int getQuantity();
    double getUnitPrice();
    double getTotalPrice();
    void setQuantity(int value);
};
#endif  // _Order_h_
