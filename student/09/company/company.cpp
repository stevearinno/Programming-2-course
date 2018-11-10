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

    personnelsDB[id] = new_employee;
}


void Company::printEmployees(std::ostream &output) const
{
    std::shared_ptr<Employee> to_be_printed;
    std::map<std::string, std::shared_ptr<Employee>>::const_iterator dbIterator = personnelsDB.begin();
    //auto dbIterator = personnelsDB.begin();
    for (;dbIterator != personnelsDB.end(); dbIterator++)
    {
        to_be_printed = dbIterator->second;
        output << to_be_printed->id_ << ", " << to_be_printed->department_ << ", " << to_be_printed->time_in_service_ << std::endl;
    }

}

void Company::addRelation(const std::string &subordinate, const std::string &boss, std::ostream &output)
{
    Employee* to_be_subordinate;
    Employee* to_be_boss;

    to_be_boss = getPointer(boss);
    to_be_subordinate = getPointer(subordinate);

    if (to_be_boss != nullptr)
    {
        to_be_boss->subordinates_.push_back(to_be_subordinate);
    }
    to_be_subordinate->boss_ = to_be_boss;
}

void Company::printSubordinates(const std::string &id, std::ostream &output) const
{
    if (personnelsDB.find(id) == personnelsDB.end())
    {
        printNotFound(id, output);
    }
    else
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

}

void Company::printBoss(const std::string &id, std::ostream &output) const
{
    if (personnelsDB.find(id) == personnelsDB.end())
    {
        printNotFound(id, output);
    }
    else
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
}

void Company::printColleagues(const std::string &id, std::ostream &output) const
{
    if (personnelsDB.find(id) == personnelsDB.end())
    {
        printNotFound(id, output);
    }
    else
    {
        Employee* theEmployee = getPointer(id);
        Employee* theBoss = theEmployee->boss_;

        std::vector<Employee*> colleagueVector = theBoss->subordinates_;
        std::set<std::string> colleagueSet = VectorToIdSet(colleagueVector);
        colleagueSet.erase(id);
        std::string groupName;
        if ( colleagueSet.size()==1)
        {
            groupName = "colleague";
        }
        else
        {
            groupName = "colleagues";
        }
        printGroup(id, groupName, colleagueSet, output);
    }
}

void Company::printDepartment(const std::string &id, std::ostream &output) const
{
    if (personnelsDB.find(id) == personnelsDB.end())
    {
        printNotFound(id, output);
    }
    else
    {
        Employee* theEmployee = getPointer(id);
        Employee* theBoss = theEmployee->boss_;
        std::string theDepartment = theEmployee->department_;

        // checks one level up until the person with no boss is found
        while( theBoss != nullptr )
        {
            theEmployee = theBoss;
            theBoss = theEmployee->boss_;
        }

        std::vector<Employee*> allSubordinates;
        recursive_department(id, theEmployee, allSubordinates);
        std::vector<Employee*> departmentVector;
        std::vector<Employee*>::const_iterator subIterator = allSubordinates.begin();
        for (; subIterator != allSubordinates.end(); subIterator++)
        {
            if ( (*subIterator)->department_ == theDepartment )
            {
                departmentVector.push_back(*subIterator);
            }
        }

        std::set<std::string> departmentSet = VectorToIdSet(departmentVector);
        std::string groupName;
        if ( departmentSet.size()==1)
        {
            groupName = "department colleague";
        }
        else
        {
            groupName = "department colleagues";
        }
        printGroup(id, groupName, departmentSet, output);
    }
}

void Company::printLongestTimeInLineManagement(const std::string &id, std::ostream &output) const
{
    if (personnelsDB.find(id) == personnelsDB.end())
    {
        printNotFound(id, output);
    }
    else
    {
        // defines one input Employee as the longest (temporarily)
        // takes the vector of his/her subordinates and time in service
        Employee* checkedEmployee = getPointer(id);
        Employee* longestEmployee;

        recursive_longest(checkedEmployee, longestEmployee);

        std::string managerName = "their";
        if (checkedEmployee != longestEmployee)
        {
            managerName = id + "'s";
        }

        // manages the correct format for decimal points
        int longestTime = 10 * longestEmployee->time_in_service_;
        std::string longestTimeStr = std::to_string(int(longestTime/10));
        if (longestTime%10 != 0)
        {
            longestTimeStr = std::to_string(int(longestTime/10)) + "." + std::to_string((longestTime)%10);
        }

        output << "With the time of " << longestTimeStr
               << ", " << longestEmployee->id_ << " is the longest-served employee in "
               << managerName << " line management." << std::endl;
    }
}

void Company::printShortestTimeInLineManagement(const std::string &id, std::ostream &output) const
{
    if (personnelsDB.find(id) == personnelsDB.end())
    {
        printNotFound(id, output);
    }
    else
    {
        // defines one input Employee as the longest (temporarily)
        // takes the vector of his/her subordinates and time in service
        Employee* checkedEmployee = getPointer(id);
        Employee* shortestEmployee = checkedEmployee;

        recursive_shortest(checkedEmployee, shortestEmployee);

        std::string managerName = "their";
        if(checkedEmployee != shortestEmployee)
        {
            managerName = id + "'s";
        }

        // manages the correct format for decimal points
        int shortestTime = 10 * shortestEmployee->time_in_service_;
        std::string shortestTimeStr = std::to_string(int(shortestTime/10));
        if (shortestTime%10 != 0)
        {
            shortestTimeStr = std::to_string(int(shortestTime/10)) + "." + std::to_string((shortestTime)%10);
        }

        output << "With the time of " << shortestTimeStr
               << ", " << shortestEmployee->id_ << " is the shortest-served employee in "
               << managerName << " line management." << std::endl;
    }
}

void Company::printSubordinatesN(const std::string &id, const int n, std::ostream &output) const
{
    if (personnelsDB.find(id) == personnelsDB.end())
    {
        printNotFound(id, output);
    }
    else
    {
        if (n < 1)
        {
            output << "Error. Level can't be less than 1." << std::endl;
        }
        else
        {
            Employee* theEmployee = getPointer(id);
            std::map<int, std::vector<Employee*>> subordinatesMap;
            recursive_subordinatesN(theEmployee, subordinatesMap, n);

            std::vector<Employee*> subordinatesVector;
            int mapSize = subordinatesMap.size();
            int counter = 0;
            while( counter<mapSize )
            {
                std::vector<Employee*>::const_iterator employeeIterator = subordinatesMap[counter].begin();
                for (; employeeIterator != subordinatesMap[counter].end(); employeeIterator++)
                {
                    subordinatesVector.push_back(*employeeIterator);
                }
                counter++;
            }
            std::sort(subordinatesVector.begin(),subordinatesVector.end());
            IdSet subordinatesSet = VectorToIdSet(subordinatesVector);
            std::string groupName = "subordinates";
            if (subordinatesVector.size() == 1)
            {
                groupName = "subordinates";
                printGroup(id, groupName, subordinatesSet, output);
            }
            else if (subordinatesVector.size() == 0)
            {
                output << id << " has no subordinates" << std::endl;
            }
            else
            {
                printGroup(id, groupName, subordinatesSet, output);
            }
        }
    }
}

void Company::printBossesN(const std::string &id, const int n, std::ostream &output) const
{
    if (personnelsDB.find(id) == personnelsDB.end())
    {
        printNotFound(id, output);
    }
    else
    {
        if (n < 1)
        {
            output << "Error. Level can't be less than 1." << std::endl;
        }
        else
        {
            Employee* theEmployee = getPointer(id);
            Employee* theBoss = theEmployee->boss_;
            std::vector<Employee*> bossVector;
            int bossNo = 0;

            if (theBoss == nullptr)
            {
                output << id << "  has no bosses." << std::endl;
            }
            else
            {
                while (theBoss != nullptr or bossNo == n)
                {
                    bossNo++;
                    bossVector.push_back(theBoss);
                    theEmployee = theBoss;
                    theBoss = theEmployee->boss_;
                }
                std::sort(bossVector.begin(),bossVector.end());
                IdSet bossSet = VectorToIdSet(bossVector);

                std::string groupName = "bosses";
                if (bossSet.size() == 1)
                {
                    groupName = "boss";
                }
                printGroup(id, groupName, bossSet, output);
            }
        }
    }
}

Employee* Company::getPointer(const std::string &id) const
{
    std::shared_ptr<Employee> employeePtr;
    if (id == "")
    {
        return nullptr;
    }
    else
    {
        employeePtr = personnelsDB.find(id) -> second;
        return employeePtr.get();
    }
}

void Company::printNotFound(const std::string &id, std::ostream &output) const
{
    output << "Error. " << id << " not found." << std::endl;
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

void Company::recursive_department(const std::string& id, Employee* theEmployee, std::vector<Employee*>& allSubordinates) const
{
    std::vector<Employee*> theSubordinates = theEmployee->subordinates_;
    if (!theSubordinates.empty())
    {
        std::vector<Employee*>::const_iterator subIterator = theSubordinates.begin();
        for(; subIterator != theSubordinates.end(); subIterator++)
        {
            if ((*subIterator)->id_ != id)
            {
                allSubordinates.push_back(*subIterator);
            }
            recursive_department(id, *subIterator, allSubordinates);
        }
    }
}

void Company::recursive_longest(Employee* checkedEmployee, Employee*& longestEmployee) const
{
    std::vector<Employee*> checkedSubordinatesVec = checkedEmployee->subordinates_;
    double checkedTime = checkedEmployee->time_in_service_;
    double longestTime = longestEmployee->time_in_service_;

    if (longestTime < checkedTime)
    {
        longestTime = checkedTime;
        longestEmployee = checkedEmployee;
    }

    if (!checkedSubordinatesVec.empty() )
    {
        // compares the time of the above employee to all his/her subordinates time
        std::vector<Employee*>::const_iterator subIterator = checkedSubordinatesVec.begin();
        for(; subIterator != checkedSubordinatesVec.end(); subIterator++)
        {
            recursive_longest(*subIterator, longestEmployee);
        }
    }
}

void Company::recursive_shortest(Employee *checkedEmployee, Employee*& shortestEmployee) const
{
    std::vector<Employee*> checkedSubordinatesVec = checkedEmployee->subordinates_;
    double checkedTime = checkedEmployee->time_in_service_;
    double shortestTime = shortestEmployee->time_in_service_;

    if (shortestTime > checkedTime)
    {
        shortestTime = checkedTime;
        shortestEmployee = checkedEmployee;
    }

    if (!checkedSubordinatesVec.empty() )
    {
        // compares the time of the above employee to all his/her subordinates time
        std::vector<Employee*>::const_iterator subIterator = checkedSubordinatesVec.begin();
        for(; subIterator != checkedSubordinatesVec.end(); subIterator++)
        {
            recursive_shortest(*subIterator, shortestEmployee);
        }
    }
}

void Company::recursive_subordinatesN(Employee* theEmployee, std::map<int, std::vector<Employee*>> subordinatesMap, const int n) const
{
    int counter = subordinatesMap.size()+1;
    bool recursiveFlag = false;
    if (counter <= n)
    {
        // puts all the subordinates to first level of subordinates map
        if (counter = 1)
        {
            std::vector<Employee*> theSubordinates = theEmployee->subordinates_;
            std::vector<Employee*>::const_iterator subIterator = theSubordinates.begin();
            for(; subIterator != theSubordinates.end(); subIterator++)
            {
                subordinatesMap[counter].push_back(*subIterator);
                if (!recursiveFlag && !((*subIterator)->subordinates_.empty()) )
                {
                    recursiveFlag = true;
                }
            }
            if (recursiveFlag)
            {
                recursive_subordinatesN(theEmployee, subordinatesMap, n);
            }
        }
        // puts all the subordinates to 2nd level of subordinates map
        else
        {
            // checks all the employees in first level subordinates and puts in a vector
            std::vector<Employee*> theEmployees = subordinatesMap[counter-1];
            std::vector<Employee*>::const_iterator subIterator = theEmployees.begin();
            for(; subIterator != theEmployees.end(); subIterator++)
            {
                // inserts all the 2nd level subordinates of 1st level subordinates
                std::vector<Employee*> theSubordinates = (*subIterator)->subordinates_;
                std::vector<Employee*>::const_iterator subSubIterator = theSubordinates.begin();
                for (; subSubIterator != theSubordinates.end(); subSubIterator++)
                {
                    subordinatesMap[counter].push_back(*subSubIterator);
                    if (!recursiveFlag && !((*subSubIterator)->subordinates_.empty()) )
                    {
                        recursiveFlag = true;
                    }
                }
                if (recursiveFlag)
                {
                    recursive_subordinatesN(theEmployee, subordinatesMap, n);
                }
            }
        }
    }
}

