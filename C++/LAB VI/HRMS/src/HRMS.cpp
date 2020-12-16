#include "HRMS.h"

HRMS::HRMS()
{

}

void HRMS::add(Employee& employee, string department_id, double salary) noexcept(false)
{
    string employee_id = employee.get_id();
    //this->employees.push_back(employee);
    
    this->employees_map[employee_id] = employee;
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
    // for (auto &s : this->employees)
    // {
    //     auto id = s.get_id();
    //     cout << "ID: " << id << "\n";
    //     cout << "Name: " << s.get_name() << "\n";
    //     cout << "Surname: " << s.get_surname() << "\n";
    //     cout << "Department ID: " << s.get_department_id() << "\n";
    //     cout << "Position: " << s.get_position() << "\n";
    //     cout << "Salary: " << this->salaries[id]<< "$\n";
    // }
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
    cout << "Salaries sorted\n";
    vector<pair<Employee, double>> sorted; 
  
    for (auto& s : this->employees_map) { 
        Employee& e = s.second;
        sorted.push_back( { e,this->salaries[e.get_id()] }); 
    } 
  
    std::sort(sorted.begin(), sorted.end(), [](pair<Employee, double>& a, pair<Employee, double>& b) {
        return a.second > b.second;
    }); 
  
    for (auto &s : sorted)
    {
        Employee& e = s.first;
        cout << "ID: " << e.get_id() << "\n";
        cout << "Name: " << e.get_name() << "\n";
        cout << "Surname: " << e.get_surname() << "\n";
        cout << "Department ID: " << e.get_department_id() << "\n";
        cout << "Position: " << e.get_position() << "\n";
        cout << "Salary: " << s.second << "$\n\n";
    }
}