#include "Screen.h"

#include <memory>
#include <fstream>
#include <stdexcept>
#include <typeinfo>
#include <iostream>
#include "BlockField.h"
#include "EmptyField.h"
#include "TransitionField.h"
#include "BlacksmithField.h"
#include "InnField.h"
#include "ShopField.h"
#include "NpcField.h"
#include "ExitField.h"
#include "Player.h"

Screen::Screen(const std::string& filename)
{
	load(filename);
}

Screen::~Screen()
{
	for (int y = 0; y < MAP_SIZE_Y + 2; ++y)
	{
		for (int x = 0; x < MAP_SIZE_X + 2; ++x)
		{
			if (world[x][y] != nullptr)
				delete world[x][y];
		}
	}
}

WorldField* Screen::getWorldField(int x, int y) const
{
	return world[x][y];
}


void Screen::insertFromFile(const std::string& filename, std::vector<std::string>& lines)
{
	std::ifstream file("./Maps/" + filename + ".txt");

	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file " + filename);
	}

	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	file.close();
}

void Screen::load(const std::string& filename)
{
	std::vector<std::string> lines;
	insertFromFile(filename, lines);

	std::map<char, std::string> legend = getLegend(lines);

	for (int y = 0; y < MAP_SIZE_Y + 2; ++y)
	{
		for (int x = 0; x < MAP_SIZE_X + 2; ++x)
		{
			char currentField = lines[MAP_FIRST_CONFIG_LINE + y][x];
			world[x][y] = createWorldField(legend, currentField);
			world[x][y]->setSign(lines[MAP_FIRST_GRAPHICS_LINE + y][x]);
		}
	}
}

std::map<char, std::string> Screen::getLegend(std::vector<std::string> lines)
{
	std::map<char, std::string> legend;

	legend.insert(std::pair<char, std::string>('#', "Block"));
	legend.insert(std::pair<char, std::string>(' ', "Empty"));

	for (int lineNr = MAP_FIRST_LEGEND_LINE; lineNr < lines.size(); ++lineNr)
	{
		legend.insert(std::pair<char, std::string>(lines[lineNr][0], lines[lineNr].substr(3)));
	}
	return legend;
}

/// <summary>
/// Sucht den fieldTypeKey als Key in der Map und verwendet den ersten Teil des Values der Map zum Instanzieren des jeweiligen WorldFields.
/// </summary>
/// <param name="legend"></param>
/// <param name="fieldType"></param>
/// <returns></returns>
WorldField* Screen::createWorldField(std::map<char, std::string>& legend, char fieldTypeKey)
{
	// Finde die zum fieldTypeKey passende Legend-Zeile.
	auto iterator = legend.find(fieldTypeKey);
	if (iterator == legend.end())
	{
		throw std::invalid_argument("Unknown WorldField type key.");
	}

	// Ermittle die Art des WorldFields (Empty, Block, Transition, ...) und deren Parameter.
	std::string fieldType;
	std::string parameters;
	size_t pos = iterator->second.find(';');
	if (pos != std::string::npos)
	{
		fieldType = iterator->second.substr(0, pos);
		parameters = iterator->second.substr(pos + 1);
	}
	else
	{
		fieldType = iterator->second;
		parameters = "";
	}

	// Erstelle das entsprechende WorldField.
	if (fieldType == "Empty")
	{
		return new EmptyField();
	}

	if (fieldType == "Block")
	{
		return new BlockField();
	}

	if (fieldType == "Transition")
	{
		return new TransitionField(parameters);
	}

	if (fieldType == "Blacksmith")
	{
		return new BlacksmithField(parameters);
	}

	if (fieldType == "Inn")
	{
		return new InnField(parameters);
	}

	if (fieldType == "Shop")
	{
		return new ShopField(parameters);
	}

	if (fieldType == "Npc")
	{
		return new NpcField(parameters);
	}

	if (fieldType == "Exit")
	{
		return new ExitField(parameters);
	}

	throw std::invalid_argument("Unknown WorldField type.");
}

void Screen::display(const Player& player) const
{
	for (int y = 0; y < MAP_SIZE_Y + 2; ++y)
	{
		for (int x = 0; x < MAP_SIZE_X + 2; ++x)
		{
			Position playerPosition = player.getPosition();

			if ((playerPosition.x) == x && (playerPosition.y) == y)
			{
				std::cout << PLAYER_CHAR;
				continue;
			}

			std::cout << this->world[x][y]->getSign();
		}
		std::cout << "\n";
	}
}
