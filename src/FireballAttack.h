#pragma once
#include "Ability.h"

class FireballAttack : public Ability
{
    public:
        FireballAttack(Entity* entity);
        void action(Entity* user, Entity* target) override;

        ~FireballAttack();
};

