#include "HRMS.h"

bool cmp(pair<string, double>& a, pair<string, double>& b) 
{ 
    return a.second > b.second; 
} 

HRMS::HRMS()
{

}

void HRMS::add(Employee employee, string department_id, double salary) noexcept(false)
{
    string employee_id = employee.get_id();

    this->employees.push_back(employee);
    this->departments[department_id].push_back(employee_id);
    this->salaries[employee_id] = salary;
}
void HRMS::print_department(string department_id) noexcept
{
    cout << "Employees for department " << department_id << "\n";
    auto department = this->departments[department_id];
    for (string &s : department)
    {
        cout << s << "\n";
    }
}
void HRMS::change_salary(string employee_id, double salary) noexcept(false)
{
    this->salaries[employee_id] = salary;
}
void HRMS::print_salaries() noexcept
{
    cout << "Salaries\n";
    for (auto &s : this->salaries)
    {
        cout << s.first << " : " << s.second << "$\n";
    }
}
void HRMS::print_salaries_sorted() noexcept
{
    cout << "Salaries sorted\n";
    vector<pair<string, double>> sorted; 
  
    for (auto& s : this->salaries) { 
        sorted.push_back(s); 
    } 
  
    std::sort(sorted.begin(), sorted.end(), cmp); 
  
    for (auto& s : sorted) { 
        cout << s.first << " : " << s.second << "$\n";
    } 
}