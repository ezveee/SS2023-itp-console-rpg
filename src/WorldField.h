#pragma once

#include <string>
#include "Position.h"

class WorldField
{
public:
	WorldField();
	virtual ~WorldField();

	virtual void onEnter() = 0;
	virtual bool isEnterable() = 0;

	char getSign() const;
	void setSign(char sign);

	std::string getInfo() const;
	void setInfo(std::string info);

private:
	char sign;
	std::string info;

	/*
	Wir wollen ein playfield = std::array <std::array <WorldField*, MAP_SIZE_Y>, MAP_SIZE_X> in das wir bei jedem Feld die jeweilig richtige
	abgeleitete Instanz gespeichert haben wollen und beim Betreten einfach nur onEnter() aufrufen brauchen.
	*/
};

