#include <string>
#ifndef _Employee_h_
#define _Employee_h_
class Employee{
  private:
    int id; 
    std::string name; 
    int age; 
    double salary; 
  public:
    Employee(int p_id,std::string p_name,int p_age,double p_salary);
    int getId();
    std::string getName();
    int getAge();
    double getSalary();
    void setId(int value);
    void setName(std::string value);
    void setAge(int value);
    void setSalary(double value);
};
#endif  // _Employee_h_
