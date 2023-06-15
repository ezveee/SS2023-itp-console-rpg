#include "FireballAttack.h"
#include "Entity.h"

FireballAttack::FireballAttack(Entity* entity)
{
	this->name = L"Fireball";
	this->cost = MAGICIAN_COST + entity->getStats().level;
	this->isAOE = false;
}

void FireballAttack::action(Entity* user, Entity* target)
{
	int damage = user->getStats().spAttack + MAGICIAN_COST;
	attack(damage, this->cost, true, user, target);
}

FireballAttack::~FireballAttack() {}