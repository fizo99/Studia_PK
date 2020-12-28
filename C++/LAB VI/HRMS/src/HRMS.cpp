#include <iostream>

#include "HRMS.h"

using std::cout;
using std::pair;

HRMS::HRMS(){ };

void HRMS::add(Employee& employee, string department_id, double salary) noexcept(false)
{
    employee.set_department_id(department_id);
    string employee_id = employee.get_id();

    if(this->employees_map.find(employee_id) != this->employees_map.end())
    {
        string communicate = "Employee with given id already exists - id: " + employee_id + "\n";
        throw communicate;
    }
    this->employees_map.emplace(make_pair(employee_id,employee));
    this->departments[department_id].push_back(employee_id);
    this->salaries[employee_id] = salary;
}
void HRMS::change_salary(string employee_id, double salary) noexcept(false)
{
    if(this->salaries.find(employee_id) == this->salaries.end())
    {
        string communicate = "No employee with given id - id: " + employee_id + "\n";
        throw communicate;
    }
    this->salaries[employee_id] = salary;
}
void HRMS::print_department(string department_id) noexcept(false) 
{
    if(this->departments.find(department_id) == this->departments.end())
    {
        string communicate = "No department with given id - id: " + department_id + "\n";
        throw communicate;
    }

    auto department = this->departments[department_id];    
    cout << "\n-- Employees for department " << department_id << " --\n";
    for (string &id : department)
    {
        Employee &emp = this->employees_map.find(id)->second;
        cout << id << " -> " << emp.get_name() << " " << emp.get_surname() << "\n";
    }
    cout << "\n";
}
void HRMS::print_salaries() noexcept
{
    cout << "\n-- Salaries --\n";
    for (auto &s : this->employees_map)
    {
        Employee& e = s.second;

        cout << "ID: " << e.get_id() << "\n";
        cout << "Name: " << e.get_name() << "\n";
        cout << "Surname: " << e.get_surname() << "\n";
        cout << "Department ID: " << e.get_department_id() << "\n";
        cout << "Position: " << e.get_position() << "\n";
        cout << "Salary: " << this->salaries[e.get_id()]<< "$\n\n";
    }
    
}
void HRMS::print_salaries_sorted() noexcept
{
    std::vector<pair<string, Employee>> elems(this->employees_map.begin(), this->employees_map.end());
    std::sort(elems.begin(), elems.end(), 
    [this](pair<string, Employee>& p1, pair<string, Employee>& p2)
    {
        return this->salaries[p1.first] > this->salaries[p2.first];
    });

    cout << "\n-- Salaries sorted --\n";
    for (auto &s : elems)
    {
        auto& e = s.second;
        string id = e.get_id();

        cout << "ID: " << id << "\n";
        cout << "Name: " << e.get_name() << "\n";
        cout << "Surname: " << e.get_surname() << "\n";
        cout << "Department ID: " << e.get_department_id() << "\n";
        cout << "Position: " << e.get_position() << "\n";
        cout << "Salary: " << this->salaries[id] << "$\n\n";
    }
}