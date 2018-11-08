#include <iostream>
#include <memory>
#include <algorithm>
#include "company.hh"


Company::Company()
{

}

Company::~Company()
{
    personnelsDB.clear();

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
    std::map<std::string, std::shared_ptr<Employee>>::const_iterator dbIterator = personnelsDB.begin();
    //auto dbIterator = personnelsDB.begin();
    for (;dbIterator != personnelsDB.end(); dbIterator++)
    {
        to_be_printed = dbIterator->second;
        output << to_be_printed->id_ << ";" << to_be_printed->department_ << ";" << to_be_printed->time_in_service_ << std::endl;
    }

}

void Company::addRelation(const std::string &subordinate, const std::string &boss, std::ostream &output)
{
    Employee* to_be_subordinate;
    Employee* to_be_boss;

    to_be_boss = getPointer(boss);
    to_be_subordinate = getPointer(subordinate);

    to_be_boss->subordinates_.push_back(to_be_subordinate);
    to_be_subordinate->boss_ = to_be_boss;
}

void Company::printSubordinates(const std::string &id, std::ostream &output) const
{
    Employee* boss_id = getPointer(id);
    std::vector<Employee*> subordinates_ids = boss_id->subordinates_;

    std::sort(subordinates_ids.begin(),subordinates_ids.end());

    std::set<std::string> idSet = VectorToIdSet(subordinates_ids);
    std::string groupName;
    if (idSet.size() == 1)
    {
        groupName = "subordinate";
    }
    else
    {
        groupName = "subordinates";
    }
    printGroup(id, groupName, idSet, output);

}

void Company::printBoss(const std::string &id, std::ostream &output) const
{
    std::vector<std::string> bossVector;
    Employee* subordinate_id = getPointer(id);
    Employee* boss_id = subordinate_id->boss_;
    while (boss_id != nullptr)
    {
        bossVector.push_back(boss_id->id_);
        subordinate_id = getPointer(boss_id->id_);
        boss_id = subordinate_id->boss_;
    }

    std::string amount = "";

    if (bossVector.size() > 1)
    {
        amount = " bosses:";
    }
    else
    {
        amount = " boss:";
    }

    output << id << " has " << std::to_string(bossVector.size()) << amount << std::endl;
    std::sort(bossVector.begin(),bossVector.end());
    std::vector<std::string>::const_iterator bossIterator = bossVector.begin();
    for(;bossIterator != bossVector.end(); bossIterator++)
    {
        output << *bossIterator << std::endl;
    }

}

Employee* Company::getPointer(const std::string &id) const
{
    std::shared_ptr<Employee> employeePtr;
    employeePtr = personnelsDB.find(id) -> second;

    return employeePtr.get();

}

IdSet Company::VectorToIdSet(const std::vector<Employee *> &container) const
{
    std::set<std::string> idSet;
    std::vector<Employee*>::const_iterator contIterator = container.begin();
    for(;contIterator!= container.end(); contIterator++)
    {
        idSet.insert((*contIterator)->id_);
    }
    return idSet;
}

void Company::printGroup(const std::string &id, const std::string &group, const IdSet &container, std::ostream &output) const
{
    output << id << " has " << std::to_string(container.size()) << " " << group << ":" << std::endl;

    std::set<std::string>::const_iterator setIterator = container.begin();
    for(; setIterator != container.end(); setIterator++)
    {
        output << *setIterator << std::endl;
    }
}

