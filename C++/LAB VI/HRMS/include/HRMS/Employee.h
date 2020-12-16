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
  void showYourself();
  string get_id();
};