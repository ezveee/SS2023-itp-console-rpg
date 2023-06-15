#pragma once
#include "Ability.h"

class AllyAbility : public Ability
{
public:
    void action(Entity* user, Entity* target) override;
    virtual void allyAction(Entity* user, Entity* target) = 0;

    virtual ~AllyAbility() = default;
};

