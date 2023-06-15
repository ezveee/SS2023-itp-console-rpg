#pragma once
#include "Ability.h"

class HammerSmashAttack : public Ability
{
    public:
        HammerSmashAttack(Entity* entity);
        void action(Entity* user, Entity* target) override;

        ~HammerSmashAttack();
};

