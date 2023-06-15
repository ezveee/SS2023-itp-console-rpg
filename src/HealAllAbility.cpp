#include "HealAllAbility.h"
#include "Entity.h"
#include "Game.h"

HealAllAbility::HealAllAbility(Entity* entity)
{
	this->name = L"Heal Team";
	this->cost = HEALER_COST + entity->getStats().level;
	this->isAOE = true;
}

void HealAllAbility::allyAction(Entity* user, Entity* target)
{
	//If any Entity is empty, throw an exception
	if (user == nullptr)
		throw std::runtime_error("Error: The User is empty.");
	if (target == nullptr)
		throw std::runtime_error("Error: The Target is empty.");

	int healAmount = user->getStats().spAttack;

	//Remove Mana
	user->modifyMana(-this->cost);

	target->modifyHealth(healAmount);


	Game* gameManager = Game::getInstance();
	UIManager* uiManager = gameManager->getUIManager();

	std::wstring dialog =
		user->getName() + L" healed " + target->getName() +
		L" for " + std::to_wstring(healAmount) + L" Health!";

	uiManager->showDialog(dialog, true);
}

HealAllAbility::~HealAllAbility() {}
