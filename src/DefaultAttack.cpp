#include "DefaultAttack.h"
#include "Entity.h"
#include "Game.h"

DefaultAttack::DefaultAttack(Entity* entity) 
{
	this->name = L"Default Attack";
	this->cost = 0;
	this->isAOE = false;
}

void DefaultAttack::action(Entity* user, Entity* target)
{
	int damage = user->getStats().attack;

	Ally* ally = dynamic_cast<Ally*>(user);
	if (ally != nullptr)
	{
		Game* game = Game::getInstance();
		int weaponLevel = game->player->getWeaponLevel();

		damage = damage * weaponLevel;
	}

	attack(damage, this->cost, false, user, target);
}

DefaultAttack::~DefaultAttack() {}
