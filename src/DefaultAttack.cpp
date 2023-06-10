#include "DefaultAttack.h"
#include "Entity.h"

DefaultAttack::DefaultAttack(Entity* entity) 
{
	setLevel(entity);
	this->name = L"Default Attack";
	this->cost = 0;
	this->isAOE = false;
}

void DefaultAttack::action(Entity* user, Entity* target)
{
	int damage = user->getStats().attack;
	attack(damage, this->cost, false, user, target);
}

DefaultAttack::~DefaultAttack() {}
