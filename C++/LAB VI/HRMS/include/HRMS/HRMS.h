#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

#include "Employee.h"

using std::vector;
using std::map;
using std::string;
using std::pair;
using std::cout;



class HRMS 
{
private:
    vector<Employee> employees;
    map<string,vector<string>> departments;
    map<string,double> salaries;
public:
    HRMS(void);
    void add(Employee employee, string department_id, double salary) noexcept(false);
    void print_department(string department_id) noexcept;
    void change_salary(string employee_id, double salary) noexcept(false);
    void print_salaries() noexcept;
    void print_salaries_sorted() noexcept;

};