#pragma once

#include "Entity.h"
#include <cstdlib> // for rand() and srand()

class Enemy : public Entity
{
	public:
		Ability* chooseAbility() override;
		Entity* chooseTarget(Team* targetTeam) override;
};

