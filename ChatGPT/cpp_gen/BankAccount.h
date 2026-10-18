#include <string>
#ifndef _BankAccount_h_
#define _BankAccount_h_
class BankAccount{
  private:
    std::string accountNumber; 
    std::string accountHolder; 
    double balance; 
  public:
    BankAccount(std::string p_accountNumber,std::string p_accountHolder,double p_balance);
    std::string getAccountNumber();
    std::string getAccountHolder();
    double getBalance();
    void setAccountNumber(std::string value);
    void setAccountHolder(std::string value);
    void setBalance(double value);
    bool deposit(double amount);
    bool withdraw(double amount);
};
#endif  // _BankAccount_h_
