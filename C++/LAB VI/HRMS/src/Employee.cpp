#include "Employee.h"
#include "util/uuid.cpp"
#include <iostream>
using std::cout;

Employee::Employee(string _name, string _surname, string _position)
{
    this->name = _name;
    this->surname = _surname;
    this->position = _position;
    this->id = uuid::generate_uuid();
}
Employee::Employee(){}

void Employee::set_department_id(string department_id) { this->department_id = department_id; }

string Employee::get_name()          const { return this->name; }
string Employee::get_surname()       const { return this->surname; }
string Employee::get_department_id() const { return this->department_id; }
string Employee::get_position()      const { return this->position; }
string Employee::get_id()            const { return this->id; }

// double Employee::get_salary() const  { return this->salary; }