#pragma once

#include <vector>
#include <array>
#include <map>
#include <string>
#include "defines.h"

class Player;
class WorldField;

class Screen
{
public:
	explicit Screen(const std::string& filename);
	virtual ~Screen();
	void display(const Player& player) const;
	WorldField* getWorldField(int x, int y) const;

private:
	std::array <std::array <WorldField*, MAP_SIZE_Y + 2>, MAP_SIZE_X + 2> world;
	
	void insertFromFile(const std::string& filename, std::vector<std::string>& vector);
	void load(const std::string& filename);
	WorldField* createWorldField(std::map<char, std::string>& legend, char fieldTypeKey);
	std::map<char, std::string> getLegend(std::vector<std::string> lines);
};

