#pragma once
#include "Ability.h"

class DefaultAttack : public Ability
{
    public:
        DefaultAttack(Entity* entity);
        void action(Entity* user, Entity* target) override;

        ~DefaultAttack();
};
