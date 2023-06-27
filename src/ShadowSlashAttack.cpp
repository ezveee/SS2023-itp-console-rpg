#include "ShadowSlashAttack.h"
#include "Entity.h"

ShadowSlashAttack::ShadowSlashAttack(Entity* entity)
{
	this->name = L"Shadow Slash";
	this->cost = ASSASSIN_COST + entity->getStats().level;
	this->isAOE = false;
	this->info = L"A sneaky slash, hits one enemy";
}

void ShadowSlashAttack::action(Entity* user, Entity* target)
{
	int damage = user->getStats().spAttack + user->getStats().level;

	attack(damage, this->cost, true, user, target);
}

ShadowSlashAttack::~ShadowSlashAttack() {}
