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
  // double salary;
public:
  Employee(string _name, string _surname, string _position);
  Employee();
  void set_department_id(string department_id);
  // void set_salary(double salary);
  // double get_salary() const;
  string get_name() const;
  string get_surname() const;
  string get_department_id() const;
  string get_position() const;
  string get_id() const;
};