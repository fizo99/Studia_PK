#include "HRMS.h"


HRMS::HRMS()
{

}

void HRMS::add(Employee& employee, string department_id, double salary) noexcept(false)
{
    employee.set_department_id(department_id);
    string employee_id = employee.get_id();
    
    //this->employees.push_back(employee);
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
void HRMS::change_salary(string employee_id, double salary) noexcept(false)
{
    // for(auto &emp: this->employees)
    // {
    //     if(emp.get_id() == employee_id)
    //     {
    //         emp.set_salary(salary);
    //         break;
    //     }
    // }
    this->salaries[employee_id] = salary;
}
void HRMS::print_salaries() noexcept
{
    cout << "\n-- Salaries --\n";
    // for (auto &s : this->employees)
    // {
    //     cout << "ID: " << s.get_id() << "\n";
    //     cout << "Name: " << s.get_name() << "\n";
    //     cout << "Surname: " << s.get_surname() << "\n";
    //     cout << "Department ID: " << s.get_department_id() << "\n";
    //     cout << "Position: " << s.get_position() << "\n";
    //     cout << "Salary: " << s.get_salary() << "$\n";
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
    cout << "\n-- Salaries sorted --\n";
    
  

    // vector<Employee> sorted(this->employees);
    // std::sort(sorted.begin(), sorted.end(), [](Employee& a,Employee& b) {
    //     return a.get_salary() > b.get_salary();
    // }); 
    vector<pair<Employee, double>> sorted; 
    for (auto& s : this->employees_map) { 
        Employee& e = s.second;
        sorted.push_back( { e,this->salaries[e.get_id()] }); 
    } 
    std::sort(sorted.begin(), sorted.end(), [this](pair<Employee, double>& a, pair<Employee,double>& b) {
        return a.second > b.second;
    }); 
    // std::sort(sorted.begin(), sorted.end(), [this](pair<string, Employee>& a, pair<string, Employee>& b) {
    //     return this->salaries[a.first] > this->salaries[b.first];
    // }); 
  

    for (auto &s : sorted)
    {
        auto& e = s.first;
        string id = e.get_id();
        cout << "ID: " << id << "\n";
        cout << "Name: " << e.get_name() << "\n";
        cout << "Surname: " << e.get_surname() << "\n";
        cout << "Department ID: " << e.get_department_id() << "\n";
        cout << "Position: " << e.get_position() << "\n";
        cout << "Salary: " << this->salaries[id] << "$\n\n";
    }
}