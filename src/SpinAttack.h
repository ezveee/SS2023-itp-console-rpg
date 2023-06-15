#pragma once
#include "Ability.h"

class SpinAttack : public Ability
{
    public:
        SpinAttack(Entity* entity);
        void action(Entity* user, Entity* target) override;

        ~SpinAttack();
};

