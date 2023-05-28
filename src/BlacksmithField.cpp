#include "BlacksmithField.h"


BlacksmithField::BlacksmithField(std::wstring& parameters)
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

bool BlacksmithField::isEnterable()
{
	return true;
}

