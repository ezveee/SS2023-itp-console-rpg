#pragma once
#include "Ability.h"

class CriticalStrikeAttack : public Ability
{
	public:
		CriticalStrikeAttack(Entity* entity);
		void action(Entity* user, Entity* target) override;

		~CriticalStrikeAttack();
};
