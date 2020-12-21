#pragma once
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>

#include "Employee.h"

using std::vector;
using std::map;
using std::unordered_map;
using std::string;
using std::pair;
using std::cout;
using std::set;


class HRMS 
{
private:
    unordered_map<string,vector<string>> departments;
    unordered_map<string,double> salaries;
//  struct cmp {
//      bool operator()(const Employee& a, const Employee& b) const {
//          return a.get_salary() > b.get_salary();
//      }
//  };
    unordered_map<string,Employee> employees_map;
    
public:
    HRMS(void);
    void add(Employee& employee, string department_id, double salary) noexcept(false);
    void print_department(string department_id) noexcept;
    void change_salary(string employee_id, double salary) noexcept(false);
    // double get_salary(const string& id);
    void print_salaries() noexcept;
    void print_salaries_sorted() noexcept;
};