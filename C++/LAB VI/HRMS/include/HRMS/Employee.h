#pragma once

#include <string>

using std::string;


class Employee 
{
private:
  string id;
  string name;
  string surname;
  string department_id;
  string position;
public:
  Employee(string _department_id,string _name, string _surname, string _position);
  Employee();
  void showYourself();
  string get_name();
  string get_surname();
  string get_department_id();
  string get_position();
  string get_id();
};