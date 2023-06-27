#include "MeteorAttack.h"
#include "Entity.h"

MeteorAttack::MeteorAttack(Entity* entity)
{
	this->name = L"Meteor";
	this->cost = MAGICIAN_COST + entity->getStats().level;
	this->isAOE = true;
	this->info = L"Hits all enemies with a meteor shower";
}

void MeteorAttack::action(Entity* user, Entity* target)
{
	int damage = user->getStats().spAttack;
	attack(damage, this->cost, true, user, target);
}

MeteorAttack::~MeteorAttack() {}
