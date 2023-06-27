#include "HammerSmashAttack.h"
#include "Entity.h"

HammerSmashAttack::HammerSmashAttack(Entity* entity)
{
	this->name = L"Hammer Smash";
	this->cost = (HEALER_COST-1) + entity->getStats().level;
	this->isAOE = false;
	this->info = L"Bashes one enemy over the head with a hammer";
}

void HammerSmashAttack::action(Entity* user, Entity* target)
{
	int damage = user->getStats().attack + user->getStats().level;
	attack(damage, this->cost, false, user, target);
}

HammerSmashAttack::~HammerSmashAttack() {}
