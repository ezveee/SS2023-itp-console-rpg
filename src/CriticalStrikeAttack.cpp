#include "CriticalStrikeAttack.h"
#include "Entity.h"

CriticalStrikeAttack::CriticalStrikeAttack(Entity* entity)
{
	this->name = L"Critical Strike";
	this->cost = ASSASSIN_COST + entity->getStats().level;
	this->isAOE = false;
}

void CriticalStrikeAttack::action(Entity* user, Entity* target)
{
	int damage = user->getStats().attack + user->getStats().level;

	int temp = user->getStats().critical;
	user->setCritical(temp + user->getStats().level);

	attack(damage, this->cost, false, user, target);

	user->setCritical(temp);
}

CriticalStrikeAttack::~CriticalStrikeAttack() {}
