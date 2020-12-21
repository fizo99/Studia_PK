#include "HRMS.h"
#include <functional>

HRMS::HRMS(){ };

void HRMS::add(Employee& employee, string department_id, double salary) noexcept(false)
{
    employee.set_department_id(department_id);
    string employee_id = employee.get_id();

    this->employees_map[employee_id] = employee;
    this->departments[department_id].push_back(employee_id);
    this->salaries[employee_id] = salary;
}
void HRMS::print_department(string department_id) noexcept
{
    cout << "\n-- Employees for department " << department_id << " --\n";
    auto department = this->departments[department_id];
    for (string &s : department)
    {
        cout << s << " -> " << this->employees_map[s].get_name() << " "
             << this->employees_map[s].get_surname() << "\n";
    }
    cout << "\n";
}
// double HRMS::get_salary(const string& id) 
// {
//     return this->salaries[id];
// }
void HRMS::change_salary(string employee_id, double salary) noexcept(false)
{
    this->salaries[employee_id] = salary;
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
    cout << "\n-- Salaries sorted --\n";
    std::vector<pair<string, Employee>> elems(this->employees_map.begin(), this->employees_map.end());
    std::sort(elems.begin(), elems.end(), 
    [this](pair<string, Employee>& p1, pair<string, Employee>& p2)
    {
        return this->salaries[p1.first] > this->salaries[p2.first];
    });
  
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