#include <string>
#ifndef _DesignProduct_h_
#define _DesignProduct_h_
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
class Customer{
  private:
    int id; 
    std::string name; 
    std::string email; 
  public:
    Customer(int p_id,std::string p_name,std::string p_email);
    int getId();
    std::string getName();
    std::string getEmail();
    void setEmail(std::string value);
};
#endif  // _DesignProduct_h_
