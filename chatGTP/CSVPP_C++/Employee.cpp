#include "Employee.h" 
Employee::Employee(int p_id,std::string p_name,int p_age,double p_salary){
  id = p_id;
  name = p_name;
  age = p_age;
  salary = p_salary;
}
int Employee::getId(){
  return id;
}
std::string Employee::getName(){
  return name;
}
int Employee::getAge(){
  return age;
}
double Employee::getSalary(){
  return salary;
}
void Employee::setId(int value){
  id = value;
}
void Employee::setName(std::string value){
  name = value;
}
void Employee::setAge(int value){
  age = value;
}
void Employee::setSalary(double value){
  salary = value;
}
