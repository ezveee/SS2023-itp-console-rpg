#include "ShopField.h"



ShopField::ShopField(std::string& parameters)
{
	// evtl. Initialisierung mit Daten aus dem File.
}

ShopField::~ShopField() = default;

void ShopField::onEnter(Game* game)
{
	// Mapname & Koordinaten aus info auslesen
	// Map laden
	// Koordinaten setzen
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

