#pragma once

#include "Entity.h"

class Ally : public Entity
{
	public:
		Ability* chooseAbility() override;
		Entity* chooseTarget(Team* targets) override;

	protected:
		int experience;
};

