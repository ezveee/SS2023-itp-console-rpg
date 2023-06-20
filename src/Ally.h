#pragma once

#include "Entity.h"

/*enum RoleClass
{
	Warrior,
	Healer,
	Magician,
	Assassin
};*/

class Ally : public Entity
{
	public:
		Ally(Team* playerTeam, RoleClass role, std::wstring name, int level);
		~Ally();

		fightAction chooseAction() override;
		Ability* chooseAbility() override;
		Entity* chooseTarget(Team* targetTeam) override;
		std::wstring getRoleString() override;
		RoleClass getRole() override;

	protected:
		RoleClass role;
};

