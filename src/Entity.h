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

enum RoleClass
{
	Warrior,
	Healer,
	Magician,
	Assassin
};

enum fightAction {
	Default = 0,
	UseAbility,
	UseItem,
	Block,
	Run
};

struct Stats
{
	int level = 1;
	int maxHealth = 0;
	int health = 0;
	int maxMana = 0;
	int mana = 0;
	int accuracy = 0;
	int attack = 0;
	int spAttack = 0;
	int defense = 0;
	int spDefense = 0;
	int speed = 0;
	int critical = 0;
};

class Entity
{
	public:
		virtual ~Entity() = default; // Virtual destructor

		bool isAlive();

		void modifyHealth(int addValue);
		void modifyMana(int addValue);

		virtual fightAction chooseAction() = 0;
		virtual Ability* chooseAbility();
		virtual Entity* chooseTarget(Team* targetTeam);

		void useAbilityOnTarget(Ability* ability, Entity* user, Entity* target);
		void useAbilityOnTeam(Ability* ability, Entity* user, Team* targetTeam);

		void setLevel(int level, bool isPhysicalClass);
		virtual std::wstring getRoleString();
		virtual RoleClass getRole();

		int getSpeed() const;
		int getHealth() const;
		int getMana() const;
		std::wstring getName() const;
		Stats getStats() const;

		Ability* getDefaultAttack() const;
		std::vector<Ability*> getAbilities() const;

	protected:
		std::wstring name;
		Stats stat;

		Ability* defaultAttack;
		std::vector<Ability*> abilities;
};

