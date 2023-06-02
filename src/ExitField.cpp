#include "ExitField.h"



ExitField::ExitField(std::wstring& parameters)
{
	// evtl. Initialisierung mit Daten aus dem File.
}

ExitField::~ExitField() = default;

void ExitField::onEnter(Game* game)
{
	// Mapname & Koordinaten aus info auslesen
	// Map laden
	// Koordinaten setzen
}

void ExitField::onInteract(Game* game)
{

}

bool ExitField::isEnterable()
{
	return true;
}

bool ExitField::isInteractable()
{
	return false;
}

