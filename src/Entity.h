#pragma once

#include "Team.h"
#include "Ability.h"

struct Stats
{
	int level;
	int maxHealth;
	int health;
	int maxMana;
	int mana;
	int accuracy;
	int attack;
	int spAttack;
	int defense;
	int spDefense;
	int speed;
	int critical;
};

class Entity
{
	public:
		bool isAlive();

		void modifyHealth(int addValue);
		void modifyMana(int addValue);

		void setStats(Stats addStats);

		virtual Ability* chooseAbility();
		virtual Entity* chooseTarget(Team* targets);

		void useAbilityOnTarget(Ability* ability, Entity* target);
		void useAbilityOnTeam(Ability* ability, Team* targets);

		int getSpeed() const;

	protected:
		Ability* defaultAttack;


	private:
		Stats stat;
};

