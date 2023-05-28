#pragma once

#include <string>

class Game;

class WorldField
{
public:
	WorldField();
	virtual ~WorldField();

	virtual void onEnter(Game* game) = 0;
	virtual bool isEnterable() = 0;

	wchar_t getSign() const;
	void setSign(wchar_t sign);

	std::wstring getInfo() const;
	void setInfo(std::wstring info);

private:
	wchar_t sign;
	std::wstring info;
};

