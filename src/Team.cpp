#include "Team.h"

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
