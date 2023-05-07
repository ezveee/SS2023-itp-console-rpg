#include "ExitField.h"



ExitField::ExitField(std::string& parameters)
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

bool ExitField::isEnterable()
{
	return true;
}

