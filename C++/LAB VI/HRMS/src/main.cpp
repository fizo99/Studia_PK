
#include <iostream>
#include "HRMS.h"
#include "Employee.h"

using std::cout;

int main() {
    Employee e("abc","name","surname","pos");
    Employee b("bbc","dsdd","dsd","112");
    HRMS hr;
    hr.add(e,"dep",2000.0);
    hr.add(b,"dep",3000.0);
    hr.print_department("dep");
    hr.print_salaries();
    hr.print_salaries_sorted();
}
