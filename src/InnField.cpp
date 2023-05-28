#include "InnField.h"



InnField::InnField(std::wstring& parameters)
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

bool InnField::isEnterable()
{
	return true;
}

