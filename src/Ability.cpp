#include "Ability.h"
#include "Entity.h"
#include "GameManager.h"

void Ability::setLevel(Entity* entity)
{
	this->level = entity->getStats().level;
}

std::string Ability::getName() const { return this->name; };

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

	std::string defOrSpDef = " Defense: ";
	int targetDef = 0;
	if (isSpecial)
	{
		targetDef = target->getStats().spDefense;
		defOrSpDef = " Sp. Defense: ";
	}
	else
		targetDef = target->getStats().defense;


	GameManager* gameManager = GameManager::getInstance();
	FightUI* fightUI = gameManager->getFightUI();

	std::string dialog = user->getName() + "'s modified Accuracy: " + std::to_string(modifiedAcc) + "\n";
	//Check if Attack Hits
	if (doesAttackHit(modifiedAcc, targetDef))
	{
		std::string hitOrCrit = " hits ";
		//Double the Damage if the modified Accuracy + the Crit-Stat > targetDef * 2
		if ((modifiedAcc + user->getStats().critical) >= (targetDef * 2))
		{
			damage = damage * 2;
			hitOrCrit = " crits ";
		}

		//Attack
		target->modifyHealth(-damage);

		dialog += 
			"(+ " + std::to_string(user->getStats().critical) + " critical Chance)\n" +
			target->getName() + "'s" + defOrSpDef + std::to_string(targetDef) + "\n" +
			user->getName() + hitOrCrit + target->getName() + ", for " + std::to_string(damage) + " Damage!";
	}
	else
	{
		dialog += user->getName() + " misses " + target->getName() + "!";
	}

	fightUI->showDialog(dialog, true);
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
