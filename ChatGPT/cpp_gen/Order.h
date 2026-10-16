#include <string>
#ifndef _Order_h_
#define _Order_h_
class Order{
  private:
    int id; 
    int customerId; 
    int productId; 
    int quantity; 
    double totalAmount; 
  public:
    Order(int p_id,int p_customerId,int p_productId,int p_quantity,double p_totalAmount);
    int getId();
    int getCustomerId();
    int getProductId();
    int getQuantity();
    double getTotalAmount();
    void setId(int value);
    void setCustomerId(int value);
    void setProductId(int value);
    void setQuantity(int value);
    void setTotalAmount(double value);
};
#endif  // _Order_h_
