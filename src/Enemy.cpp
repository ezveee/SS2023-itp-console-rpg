#include "Enemy.h"
#include <iostream>

#define SMARTER_BEHAVIOR_LV 5

Enemy::Enemy(Team* enemyTeam, EnemyType type) 
{
	this->stat = {
		1, //level
		0, //maxHealth
		0, //health
		0, //maxMana
		0, //mana
		0, //accuracy
		0, //attack
		0, //spAttack
		0, //defense
		0, //spDefense
		0, //speed
		0  //critical
	};

	this->defaultAttack = new DefaultAttack(this);

	struct Stats enemyStats = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	if (type == Slime)
	{
		this->name = "Slime";

		enemyStats.maxHealth = 8;
		enemyStats.maxMana = 12;
		enemyStats.accuracy = 2;
		enemyStats.attack = 1;
		enemyStats.defense = 8;
		enemyStats.spAttack = 3;
		enemyStats.spDefense = 10;
		enemyStats.speed = 1;
		enemyStats.critical = 1;
	}
	if (type == Goblin)
	{
		this->name = "Goblin";

		enemyStats.maxHealth = 10;
		enemyStats.maxMana = 10;
		enemyStats.accuracy = 2;
		enemyStats.attack = 2;
		enemyStats.defense = 10;
		enemyStats.spAttack = 2;
		enemyStats.spDefense = 8;
		enemyStats.speed = 1;
		enemyStats.critical = 1;
	}

	this->setStats(enemyStats);

	this->stat.health = this->stat.maxHealth;
	this->stat.mana = this->stat.maxMana;

	enemyTeam->addMember(this);
}

Enemy::~Enemy()
{
	std::cout << "\t- - - - - " << this->getName() << " - - - - -" << std::endl;
	
	std::cout <<"\t> " << this->defaultAttack->getName() << ", was deleted" << std::endl;
	delete this->defaultAttack;

	for (int i = 0; i < this->abilities.size(); i++)
	{
		std::cout << "\t> " << abilities[i]->getName() << ", was deleted" << std::endl;
		delete this->abilities[i];
	}
	this->abilities.clear();
	std::cout << "\t- - - - - " << this->getName() << " deleted - - - - -" << std::endl;
}

fightAction Enemy::chooseAction()
{
	if (this->defaultAttack == nullptr)
		throw std::runtime_error("Error: Default Attack does not exist. (Enemy)");

	if (getMana() == 0)
		return Default;
	else
		return UseAbility;
}

Ability* Enemy::chooseAbility()
{
	std::vector<Ability*> abilities = getAbilities();

	if (abilities.size() == 0)
		return this->defaultAttack;


	//If this->stat.level is lower than "SMARTER_BEHAVIOR_LV" ...
	if (this->stat.level < SMARTER_BEHAVIOR_LV)
	{
		//Return a random Ability, unless its too expensive
		for (int i = 0; i < abilities.size(); i++)
		{
			int randomInt = rand() % (abilities.size());

			if(abilities[randomInt]->cost <= this->getMana())
				return abilities[randomInt];
		}
		return this->defaultAttack;
	}
	else
	{
		//Return the Ability with the highest manaCost, if possible
		Ability* highestCost = this->defaultAttack;

		for (int i = 0; i < abilities.size(); i++)
		{
			if (abilities[i]->cost <= this->getMana())
			{
				if (highestCost->cost < abilities[i]->cost)
					highestCost = abilities[i];
			}
		}
		return highestCost;
	}
}

Entity* Enemy::chooseTarget(Team* targetTeam)
{
	if (targetTeam->members.size() == 0)
		throw std::runtime_error("Error: The Target-Team is empty. (called from Enemy)");

	// If this->stat.level is lower than "SMARTER_BEHAVIOR_LV" ...
	// Return a random Entity
	if (this->stat.level < SMARTER_BEHAVIOR_LV)
	{
		Entity* target = nullptr;
		while (target == nullptr)
		{
			int randomInt = rand() % targetTeam->members.size();

			if (targetTeam->members[randomInt]->isAlive())
				target = targetTeam->members[randomInt];
		}
		return target;
	}
	// Return the Entity with the lowest health
	else
	{
		Entity* lowestHealth = nullptr;

		for (int i = 0; i < targetTeam->members.size(); i++)
		{
			if (targetTeam->members[i]->isAlive())
			{
				if (lowestHealth == nullptr || lowestHealth->getHealth() > targetTeam->members[i]->getHealth())
					lowestHealth = targetTeam->members[i];
			}
		}
		return lowestHealth;
	}
}
