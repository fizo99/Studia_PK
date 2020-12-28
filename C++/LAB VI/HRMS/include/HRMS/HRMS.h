#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

#include "Employee.h"

using std::vector;
using std::unordered_map;
using std::string;

class HRMS 
{
private:
    unordered_map<string,vector<string>>    departments;
    unordered_map<string,double>            salaries;
    unordered_map<string,Employee>          employees_map;
public:
    HRMS(void);
    void add(Employee& employee, string department_id, double salary) noexcept(false);
    void print_department(string department_id) noexcept(false);
    void change_salary(string employee_id, double salary) noexcept(false);
    void print_salaries() noexcept;
    void print_salaries_sorted() noexcept;
};