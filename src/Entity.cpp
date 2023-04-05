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

void Entity::setStats(Stats addStats)
{
	this->stat.level += addStats.level;
	this->stat.maxHealth += addStats.maxHealth;
	this->stat.health += addStats.health;
	this->stat.maxMana += addStats.maxMana;
	this->stat.mana += addStats.mana;
	this->stat.accuracy += addStats.accuracy;
	this->stat.attack += addStats.attack;
	this->stat.spAttack += addStats.spAttack;
	this->stat.defense += addStats.defense;
	this->stat.spDefense += addStats.spDefense;
	this->stat.speed += addStats.speed;
	this->stat.critical += addStats.critical;
}

void Entity::useAbilityOnTarget(Ability* ability, Entity* target)
{
	
}

void Entity::useAbilityOnTeam(Ability* ability, Team* targets)
{

}

int Entity::getSpeed() const { return this->stat.speed; }