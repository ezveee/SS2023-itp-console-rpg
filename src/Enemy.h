#pragma once

#include "Entity.h"

class Enemy : public Entity
{
	public:
		Ability* chooseAbility() override;
		Entity* chooseTarget(Team* targets) override;
};

