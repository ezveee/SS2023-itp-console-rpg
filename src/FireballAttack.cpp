#include "FireballAttack.h"
#include "Entity.h"

FireballAttack::FireballAttack(Entity* entity)
{
	this->name = L"Fireball";
	this->cost = (MAGICIAN_COST-2) + entity->getStats().level;
	this->isAOE = false;
	this->info = L"Hits a single enemy with a fireball";
}

void FireballAttack::action(Entity* user, Entity* target)
{
	int damage = user->getStats().spAttack + user->getStats().level;
	attack(damage, this->cost, true, user, target);
}

FireballAttack::~FireballAttack() {}
