#include "BlacksmithField.h"
#include <iostream>
#include <conio.h>
#include "defines.h"


BlacksmithField::BlacksmithField(std::wstring& parameters)
{
	// evtl. Initialisierung mit Daten aus dem File.
}

BlacksmithField::~BlacksmithField() = default;

void BlacksmithField::onEnter(Game* game)
{
	char input;
	int currCost = 1000 * game->player->getWeaponLevel();
	while(true)
	{
		game->getUIManager()->showDialog(L"You enter the Blacksmith, do you want to upgrade your weapon for " + std::to_wstring(currCost) + L" Gold?\n(y / n)", false);
		input = _getch();
		if ((input == 'y' || input == 'Y' || input == '\r') && game->player->getGold() >= currCost)
		{
			game->player->weaponLevelUp();
			game->player->modifyGold(currCost * (-1));
			game->getUIManager()->showDialog(L"You have successfully upgraded your weapon",true);
			return;
		}
		if ((input == 'n' || input == 'N' || input == ESCAPEKEY))
			return;

		game->getUIManager()->showDialog(L"You don't have enough Gold to upgrade your weapon", true);
		break;
	}
}

void BlacksmithField::onInteract(Game* game)
{

}

bool BlacksmithField::isEnterable()
{
	return true;
}

bool BlacksmithField::isInteractable()
{
	return false;
}

