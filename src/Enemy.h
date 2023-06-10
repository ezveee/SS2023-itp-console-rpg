#pragma once

#include "Entity.h"

enum EnemyType
{
	Slime,
	Goblin
};


class Enemy : public Entity
{
	public:
		Enemy(Team* enemyTeam, EnemyType type);
		~Enemy();

		fightAction chooseAction() override;
		Ability* chooseAbility() override;
		Entity* chooseTarget(Team* targetTeam) override;
};

