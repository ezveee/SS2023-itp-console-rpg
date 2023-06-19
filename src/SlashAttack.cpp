#include "SlashAttack.h"
#include "Entity.h"

SlashAttack::SlashAttack(Entity* entity)
{
	this->name = L"Slash";
	this->cost = (WARRIOR_COST-2) + entity->getStats().level;
	this->isAOE = false;
}

void SlashAttack::action(Entity* user, Entity* target)
{
	int damage = user->getStats().attack + user->getStats().level;
	attack(damage, this->cost, false, user, target);
}

SlashAttack::~SlashAttack() {}
