#pragma once
#include "AllyAbility.h"

class HealAllAbility : public AllyAbility
{
    public:
        HealAllAbility(Entity* entity);
        void allyAction(Entity* user, Entity* target) override;

        ~HealAllAbility();
};

