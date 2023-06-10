#pragma once

#include "Entity.h"

enum RoleClass
{
	Warrior,
	Healer,
	Magician,
	Assassin
};

class Ally : public Entity
{
	public:
		Ally(Team* playerTeam, RoleClass role);
		~Ally();

		fightAction chooseAction() override;
		Ability* chooseAbility() override;
		Entity* chooseTarget(Team* targetTeam) override;

	protected:
		int experience;
};

