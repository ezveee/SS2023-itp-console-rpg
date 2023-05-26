#include "InnField.h"



InnField::InnField(std::string& parameters)
{
	// evtl. Initialisierung mit Daten aus dem File.
}

InnField::~InnField() = default;

void InnField::onEnter(Game* game)
{
	// Mapname & Koordinaten aus info auslesen
	// Map laden
	// Koordinaten setzen
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

