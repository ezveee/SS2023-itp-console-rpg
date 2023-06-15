#include "InnField.h"
#include "defines.h"
#include <iostream>
#include <conio.h>



InnField::InnField(std::wstring& parameters)
{
	// evtl. Initialisierung mit Daten aus dem File.
}

InnField::~InnField() = default;

void InnField::onEnter(Game* game)
{
	for (auto members : game->playerTeam->members)
	{
		members->modifyHealth(members->getStats().maxHealth);
		members->modifyMana(members->getStats().maxMana);
	}
	game->getUIManager()->showDialog(L"you spent time in the inn and fully replenished their HP and MP", true);
}

void InnField::onInteract(Game* game)
{

}

bool InnField::isEnterable()
{
	return true;
}

bool InnField::isInteractable()
{
	return false;
}

