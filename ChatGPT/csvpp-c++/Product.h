#include <string>
#ifndef _Product_h_
#define _Product_h_
class Product{
  private:
    int id; 
    std::string name; 
    double price; 
    int stock; 
  public:
    Product(int p_id,std::string p_name,double p_price,int p_stock);
    int getId();
    std::string getName();
    double getPrice();
    int getStock();
    void setId(int value);
    void setName(std::string value);
    void setPrice(double value);
    void setStock(int value);
    bool isInStock();
    bool reduceStock(int quantity);
    bool restock(int quantity);
};
#endif  // _Product_h_
