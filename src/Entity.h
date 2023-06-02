#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib> // for rand() and srand()

#include "Team.h"
#include "Ability.h"
#include "DefaultAttack.h"

class Team;
class Ability;

enum fightAction {
	Default = 0,
	UseAbility,
	UseItem,
	Block,
	Run
};

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
		virtual ~Entity() = default; // Virtual destructor

		bool isAlive();

		void modifyHealth(int addValue);
		void modifyMana(int addValue);

		void setStats(Stats addStats);

		virtual fightAction chooseAction() = 0;
		virtual Ability* chooseAbility();
		virtual Entity* chooseTarget(Team* targetTeam);

		void useAbilityOnTarget(Ability* ability, Entity* user, Entity* target);
		void useAbilityOnTeam(Ability* ability, Entity* user, Team* targetTeam);

		int getSpeed() const;
		int getHealth() const;
		int getMana() const;
		std::string getName() const;
		Stats getStats() const;

		Ability* getDefaultAttack() const;
		std::vector<Ability*> getAbilities() const;

	protected:
		std::string name;
		Stats stat;

		Ability* defaultAttack;
		std::vector<Ability*> abilities;
};

