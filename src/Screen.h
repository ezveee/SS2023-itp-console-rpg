#pragma once

#include <vector>
#include <array>
#include <map>
#include <string>
#include "defines.h"

class Game;
class Player;
class WorldField;

class Screen
{
public:
	explicit Screen(const std::wstring& filename);
	virtual ~Screen();
	void display(Player* player) const;
	WorldField* getWorldField(int x, int y) const;
	bool getIsSafe();

private:
	std::array <std::array <WorldField*, MAP_SIZE_Y + 2>, MAP_SIZE_X + 2> world;
	bool isSafe;

	void insertFromFile(const std::wstring& filename, std::vector<std::wstring>& vector);
	void load(const std::wstring& filename);
	WorldField* createWorldField(std::map<wchar_t, std::wstring>& legend, wchar_t fieldTypeKey);
	std::map<wchar_t, std::wstring> getLegend(std::vector<std::wstring> lines);
};

