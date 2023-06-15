#include "HammerSmashAttack.h"
#include "Entity.h"

HammerSmashAttack::HammerSmashAttack(Entity* entity)
{
	this->name = L"Hammer Smash";
	this->cost = HEALER_COST + entity->getStats().level;
	this->isAOE = false;
}

void HammerSmashAttack::action(Entity* user, Entity* target)
{
	int damage = user->getStats().attack + user->getStats().level;
	attack(damage, this->cost, false, user, target);
}

HammerSmashAttack::~HammerSmashAttack() {}
