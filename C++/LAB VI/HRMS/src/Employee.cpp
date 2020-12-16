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

void Employee::showYourself() 
{
    cout << this->name << " " << this->department_id << " " << this->surname << " " << this->position << " " << this->id << "\n";
}
string Employee::get_id() 
{
  char buffer[255];
  std::size_t length = this->id.copy(buffer,this->id.length(),0);
  buffer[length]='\0';

  return string(buffer);
}