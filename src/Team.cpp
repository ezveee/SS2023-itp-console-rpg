#include "Team.h"
#include <iostream>

Team::Team()
{
    
}

Team::~Team()
{
    std::wcout << "= = = = = Deleting Team = = = = =\n" << std::endl;
    for (int i = 0; i < this->members.size(); i++)
    {
        Entity* currentEnemy = this->members[i];
        delete currentEnemy;
    }

    this->members.clear();
    std::wcout << "\n= = = = = Team deleted = = = = =" << std::endl;
}

void Team::addMember(Entity* member)
{
    this->members.push_back(member);
}

bool Team::isTeamAlive()
{
    for (int i = 0; i < this->members.size(); i++)
    {
        if (this->members[i]->isAlive())
            return true;
    }

    return false;
}
