
#include <iostream>
#include "HRMS.h"
#include "Employee.h"

using std::cout;

int main() {
    Employee e("abc","name","surname","pos");
    Employee b("bbc","dsdd","dsd","112");
    Employee c("bbc","dsdd","dsd","112");
    Employee d("bbc","dsdd","dsd","112");
    HRMS hr;
    hr.add(e,"dep",2000.0);
    hr.add(b,"dep",3000.0);
    hr.add(d,"dep",23000.0);
    hr.add(c,"dep",300330.0);

    hr.print_department("dep");
    hr.print_salaries();
    hr.print_salaries_sorted();
}
