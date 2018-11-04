#include <iostream>
#include <memory>
#include "cards.hh"

Company::Company(): top_(nullptr)
{
    
}

void Company::addNewEmployee(const std::__cxx11::string &id, const std::__cxx11::string &dep, const double &time, std::ostream &output)
{
    std::shared_ptr<Employee> new_employee
            = std::make_shared<Employee>(Employee{id, dep, time});

    output = new_employee;
}

bool Company::is_empty() const
{
    if (top_ == nullptr){
        return true;
    }
    else{
        return false;
    }
}

