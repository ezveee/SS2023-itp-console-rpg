#include "SpinAttack.h"
#include "Entity.h"

SpinAttack::SpinAttack(Entity* entity)
{
	this->name = L"Spin";
	this->cost = WARRIOR_COST + entity->getStats().level;
	this->isAOE = true;
	this->info = L"An attack that deals physical damage to all enemies";
}

void SpinAttack::action(Entity* user, Entity* target)
{
	int damage = user->getStats().attack;
	attack(damage, this->cost, false, user, target);
}

SpinAttack::~SpinAttack() {}
