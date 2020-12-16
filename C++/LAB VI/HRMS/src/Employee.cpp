#include "Employee.h"
#include "util/uuid.cpp"
#include <iostream>
using std::cout;

Employee::Employee(string _department_id,string _name, string _surname, string _position)
{
    this->department_id = _department_id;
    this->name = _name;
    this->surname = _surname;
    this->position = _position;
    this->id = uuid::generate_uuid();
}
Employee::Employee()
{
  
}

void Employee::showYourself() 
{
    cout << this->name << " " << this->department_id << " " << this->surname << " " << this->position << " " << this->id << "\n";
}
string Employee::get_name()
{
  return this->name;
}
string Employee::get_surname()
{
  return this->surname;
}
string Employee::get_department_id()
{
  return this->department_id;
}
string Employee::get_position()
{
  return this->position;
}
string Employee::get_id() 
{
  return this->id;
}