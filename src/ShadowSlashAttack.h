#pragma once
#include "Ability.h"

class ShadowSlashAttack : public Ability
{
	public:
		ShadowSlashAttack(Entity* entity);
		void action(Entity* user, Entity* target) override;

		~ShadowSlashAttack();
};
