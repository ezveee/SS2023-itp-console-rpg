#pragma once

#include "Entity.h"

enum EnemyType
{
	Slime,
	Goblin,
	GoblinKing,
	RebellionGeneral,
	RebellionLeader
};


class Enemy : public Entity
{
	public:
		Enemy(Team* enemyTeam, EnemyType type);
		~Enemy();

		fightAction chooseAction() override;
		Ability* chooseAbility() override;
		Entity* chooseTarget(Team* targetTeam) override;

		int getGoldReward();
		int getExperienceReward();

		bool isBoss = false;

	private:
		int goldReward;
		int experienceReward;
};

