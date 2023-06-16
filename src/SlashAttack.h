#pragma once
#include "Ability.h"

class SlashAttack : public Ability
{
    public:
        SlashAttack(Entity* entity);
        void action(Entity* user, Entity* target) override;

        ~SlashAttack();
};

