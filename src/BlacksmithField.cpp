#include "BlacksmithField.h"


BlacksmithField::BlacksmithField(std::string& parameters)
{
	// evtl. Initialisierung mit Daten aus dem File.
}

BlacksmithField::~BlacksmithField() = default;

void BlacksmithField::onEnter(Game* game)
{
	// Mapname & Koordinaten aus info auslesen
	// Map laden
	// Koordinaten setzen
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

