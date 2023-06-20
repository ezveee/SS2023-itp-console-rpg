#include "ShopField.h"



ShopField::ShopField(std::wstring& parameters)
{
	// evtl. Initialisierung mit Daten aus dem File.
}

ShopField::~ShopField() = default;

void ShopField::onEnter(Game* game)
{
	game->makeSaveFile();
}

void ShopField::onInteract(Game* game)
{

}

bool ShopField::isEnterable()
{
	return true;
}

bool ShopField::isInteractable()
{
	return false;
}

