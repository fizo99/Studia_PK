
#include <iostream>
#include "HRMS.h"
#include "Employee.h"
#include <ctime>

using std::cout;

int main() {
    HRMS hr;
    const vector<string> deps{
        "Departament I","Departament II", "Departament III"
    };
    vector<Employee> emps{
        {"Jakub","Matczak","Cleaner"},
        {"Wojciech","Nowak","Java Developer"},
        {"Jan","Kowalski","Java Developer"},
        {"Tomasz","Mazowiecki","C++ Developer"},
        {"Roman","Nowacki","Frontend Developer"},
        {"Mateusz","Gola","Senior Java Developer"},
        {"Wojciech","Mura","Principal Java Developer"},
        {"Wojciech","Mazur","DevOps Engineer"},
        {"Jakub","Kalida","Junior DevOps Engineer"},
        {"Artur","Halat","Intern"},
    };
    
    std::srand(std::time(nullptr));
    int it;
    double salary;
    for(auto &e: emps)
    {
        it = std::rand()/((RAND_MAX)/3);
        salary = (double) std::rand();
        hr.add(e,deps.at(it) , salary);
    }

    hr.print_department(deps.at(0));
    hr.print_salaries();
    hr.print_salaries_sorted();
}
