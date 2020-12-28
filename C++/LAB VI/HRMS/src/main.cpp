#include <ctime>
#include <iostream>

#include "HRMS.h"
#include "Employee.h"

using std::cout;

int main() {
    HRMS hr;
    vector<string> deps{
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

        try
        {
            hr.add(e,deps.at(it),salary);
        }
        catch(string& comm)
        {
            cout << comm;
        }
    }

    try
    {
        hr.print_department(deps.at(0));
    }
    catch(string& comm)
    {
        cout << comm;
    }

    hr.print_salaries();
    hr.print_salaries_sorted();
}
