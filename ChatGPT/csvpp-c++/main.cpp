#include "Product.h"
#include "Customer.h"
#include <iostream>

int main()
{
    Product product(1, "PC", 100000, 10);
    Customer customer(1, "Taro", "taro@example.com");

    std::cout << product.getName() << std::endl;
    std::cout << customer.getName() << std::endl;

    return 0;
}


