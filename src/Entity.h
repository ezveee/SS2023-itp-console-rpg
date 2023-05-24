#pragma once

#include <vector>
#include <string>
#include <stdexcept>

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
		virtual Entity* chooseTarget(Team* targetTeam);

		void useAbilityOnTarget(Ability* ability, Entity* target);
		void useAbilityOnTeam(Ability* ability, Team* targetTeam);

		int getSpeed() const;
		int getMana() const;
		std::string getName() const;

		std::vector<Ability*> getAbilities() const;

	protected:
		std::string name;
		Stats stat;

		Ability* defaultAttack;
		std::vector<Ability*> abilities;
};

