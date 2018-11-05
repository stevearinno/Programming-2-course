#include <iostream>
#include <memory>
#include "company.hh"

Company::Company()
{
    
}



void Company::addNewEmployee(const std::__cxx11::string &id, const std::__cxx11::string &dep, const double &time, std::ostream &output)
{
    std::shared_ptr<Employee> new_employee
           = std::make_shared<Employee>();


    new_employee->id_ = id;
    new_employee->department_ = dep;
    new_employee->time_in_service_ = time;

    if (personnelsDB.find(id) == personnelsDB.end())
    {
        output << "ERROR";
    }
    else
    {
        personnelsDB[id] = new_employee;
    }
}


void Company::printEmployees(std::ostream &output) const
{
    std::shared_ptr<Employee> to_be_printed;
    
}
