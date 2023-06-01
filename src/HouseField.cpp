#include "HouseField.h"

HouseField::HouseField(std::wstring& parameters)
{
	// evtl. Initialisierung mit Daten aus dem File.
}

HouseField::~HouseField() = default;

void HouseField::onEnter(Game* game)
{
	// Mapname & Koordinaten aus info auslesen
	// Map laden
	// Koordinaten setzen
}

bool HouseField::isEnterable()
{
	return true;
}
