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
  //double salary;
public:
  Employee(string _name, string _surname, string _position);
  Employee();
  void showYourself();
  //void set_salary(double salary);
  void set_department_id(string department_id);
  //double get_salary();
  string get_name();
  string get_surname();
  string get_department_id();
  string get_position();
  string get_id();
};