#include "BankAccount.h"
BankAccount::BankAccount(std::string p_accountNumber,std::string p_accountHolder,double p_balance){
  accountNumber = p_accountNumber;
  accountHolder = p_accountHolder;
  balance = p_balance;
}
std::string BankAccount::getAccountNumber(){
  return accountNumber;
}
std::string BankAccount::getAccountHolder(){
  return accountHolder;
}
double BankAccount::getBalance(){
  return balance;
}
void BankAccount::setAccountNumber(std::string value){
  accountNumber = value;
}
void BankAccount::setAccountHolder(std::string value){
  accountHolder = value;
}
void BankAccount::setBalance(double value){
  balance = value;
}
bool BankAccount::deposit(double amount){
  if (amount <= 0){
    return(false);
  }
  balance += amount;
  return(true);
}
bool BankAccount::withdraw(double amount){
  if (amount <= 0 || amount > balance){
    return(false);
  }
  balance -= amount;
  return(true);
}
