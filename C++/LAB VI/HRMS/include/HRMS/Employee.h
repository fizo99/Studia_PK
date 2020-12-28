#pragma once

#include <string>

using std::string;

class Employee 
{
private:
  string id;
  string name;
  string surname;
  string department_id = "";
  string position;
public:
  Employee(string _name, string _surname, string _position);
  void set_department_id(string department_id);
  string get_name() const;
  string get_surname() const;
  string get_department_id() const;
  string get_position() const;
  string get_id() const;
};