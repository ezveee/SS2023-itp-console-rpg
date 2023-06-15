#include "Entity.h"

bool Entity::isAlive()
{
	if (this->stat.health <= 0)
		return false;

	return true;
}

void Entity::modifyHealth(int addValue)
{
	this->stat.health += addValue;

	if (this->stat.health < 0)
		this->stat.health = 0;

	if (this->stat.health > this->stat.maxHealth)
		this->stat.health = this->stat.maxHealth;
}

void Entity::modifyMana(int addValue)
{
	this->stat.mana += addValue;

	if (this->stat.mana < 0)
		this->stat.mana = 0;

	if (this->stat.mana > this->stat.maxMana)
		this->stat.mana = this->stat.maxMana;
}

Ability* Entity::chooseAbility()
{
	return nullptr;
}

Entity* Entity::chooseTarget(Team* targetTeam)
{
	return nullptr;
}

void Entity::useAbilityOnTarget(Ability* ability, Entity* user, Entity* target)
{
	ability->action(user, target);
}

void Entity::useAbilityOnTeam(Ability* ability, Entity* user, Team* targetTeam)
{
	for (int i = 0; i < targetTeam->members.size(); i++)
	{
		//Only attack alive Entities
		if (targetTeam->members[i]->isAlive())
		{
			ability->action(user, targetTeam->members[i]);
			user->modifyMana(ability->cost);
		}
	}

	user->modifyMana(-ability->cost);
}

int Entity::getSpeed() const { return this->stat.speed; }
int Entity::getHealth() const { return this->stat.health; };
int Entity::getMana() const { return this->stat.mana; };
std::wstring Entity::getName() const { return this->name; };
Stats Entity::getStats() const { return this->stat; };

Ability* Entity::getDefaultAttack() const { return this->defaultAttack; }

std::vector<Ability*> Entity::getAbilities() const { return this->abilities; };
