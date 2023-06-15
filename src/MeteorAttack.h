#pragma once
#include "Ability.h"

class MeteorAttack : public Ability
{
    public:
        MeteorAttack(Entity* entity);
        void action(Entity* user, Entity* target) override;

        ~MeteorAttack();
};

