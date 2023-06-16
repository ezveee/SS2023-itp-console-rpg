#include "Ability.h"
#include "Entity.h"
#include "Game.h"

std::wstring Ability::getName() const { return this->name; };

void Ability::attack(int damage, int manaCost, bool isSpecial, Entity* user, Entity* target)
{
	//If any Entity is empty, throw an exception
	if (user == nullptr)
		throw std::runtime_error("Error: The User is empty.");
	if (target == nullptr)
		throw std::runtime_error("Error: The Target is empty.");

	//Remove Mana
	user->modifyMana(-manaCost);

	//Adds a D20 to the Accuracy-Stat
	int modifiedAcc = modifyAccuracy(user->getStats().accuracy);

	std::wstring defOrSpDef = L" Defense: ";
	int targetDef = 0;
	if (isSpecial)
	{
		targetDef = target->getStats().spDefense;
		defOrSpDef = L" Sp. Defense: ";
	}
	else
		targetDef = target->getStats().defense;


	Game* game = Game::getInstance();
	UIManager* uiManager = game->getUIManager();

	std::wstring dialog = user->getName() + L"'s modified Accuracy: " + std::to_wstring(modifiedAcc) + L"\n";
	//Check if Attack Hits
	if (doesAttackHit(modifiedAcc, targetDef))
	{
		std::wstring hitOrCrit = L" hits ";
		//Double the Damage if the modified Accuracy + the Crit-Stat > targetDef * 2
		if ((modifiedAcc + user->getStats().critical) >= (targetDef * 2))
		{
			damage = damage * 2;
			hitOrCrit = L" crits ";
		}

		//Attack
		target->modifyHealth(-damage);

		dialog += 
			L"(+ " + std::to_wstring(user->getStats().critical) + L" critical Chance)\n" +
			target->getName() + L"'s" + defOrSpDef + std::to_wstring(targetDef) + L"\n" +
			user->getName() + hitOrCrit + target->getName() + L", for " + std::to_wstring(damage) + L" Damage!";
	}
	else
	{
		dialog +=
			user->getName() + L" misses " + target->getName() + L"!\n" +
			target->getName() + L"'s" + defOrSpDef + std::to_wstring(targetDef);
	}

	uiManager->showDialog(dialog, true);
}

int Ability::modifyAccuracy(int userAccuracy)
{
	int d20Roll = rand() % 20 + 1;
	return userAccuracy + d20Roll;
}

bool Ability::doesAttackHit(int modifiedAccuracy, int targetDefense)
{
	if (modifiedAccuracy >= targetDefense)
		return true;

	return false;
}
