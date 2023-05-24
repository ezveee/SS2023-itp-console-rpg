#include "Enemy.h"

#define SMARTER_BEHAVIOR_LV 5

Ability* Enemy::chooseAbility()
{
	if (getMana() == 0)
		return this->defaultAttack;

	vector<Ability*> abilities = getAbilities();

	if (abilities.size() == 0)
		throw std::runtime_error("Error: The Ability-Vector is empty. (called from Enemy)");


	//If this->stat.level is lower than "SMARTER_BEHAVIOR_LV" ...
	//Return a random Ability 
	if (this->stat.level < SMARTER_BEHAVIOR_LV)
	{
		int randomInt = rand() % (abilities.size());
		return abilities[randomInt];
	}
	//Return the Ability with the highest manaCost, if possible
	else
	{
		Ability* highestCost = this->defaultAttack;

		for (int i = 0; i < abilities.size(); i++)
		{
			if (highestCost->cost() < abilities[i]->cost)
				highestCost = abilities[i];
		}
		return highestCost;
	}
}

Entity* Enemy::chooseTarget(Team* targetTeam)
{
	if (targetTeam->members.size() == 0)
		throw std::runtime_error("Error: The Target-Team is empty. (called from Enemy)");


	//If this->stat.level is lower than "SMARTER_BEHAVIOR_LV" ...
	//Return a random Entity
	if (this->stat.level < SMARTER_BEHAVIOR_LV)
	{
		int randomInt = rand() % (targetTeam->members.size());
		return targetTeam->members[randomInt];
	}
	//Return the Entity with the lowest health
	else
	{
		Entity* lowestHealth = nullptr;

		for (int i = 0; i < targetTeam->members.size(); i++)
		{
			if (lowestHealth == nullptr || lowestHealth->getHealth() < targetTeam->members[i]->getHealth())
				lowestHealth = targetTeam->members[i];
		}
		return lowestHealth;
	}
}