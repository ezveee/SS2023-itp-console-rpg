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
#include "HouseField.h"
#include "ExitField.h"
#include "Player.h"
#include "BoundaryField.h"
#include "BossField.h"

Screen::Screen(const std::wstring& filename)
{
	size_t pos = filename.find('_');
	std::wstring screenType = filename.substr(0, pos);

	if (screenType == L"City" || screenType == L"Village" || screenType == L"Castle")
		this->isSafe = true;
	else
		this->isSafe = false;

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


void Screen::insertFromFile(const std::wstring& filename, std::vector<std::wstring>& lines)
{
	std::wifstream file(L"./Maps/" + filename + L".txt", std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file "/* + filename*/);
	}

	std::wstring line;
	while (std::getline(file, line))
	{
		lines.push_back(line.substr(0, line.length() - 1));
	}

	file.close();
}

void Screen::load(const std::wstring& filename)
{
	std::vector<std::wstring> lines;
	insertFromFile(filename, lines);

	std::map<wchar_t, std::wstring> legend = getLegend(lines);

	for (int y = 0; y < MAP_SIZE_Y + 2; ++y)
	{
		for (int x = 0; x < MAP_SIZE_X + 2; ++x)
		{
			wchar_t currentField = lines[MAP_FIRST_CONFIG_LINE + y][x];
			world[x][y] = createWorldField(legend, currentField);
			world[x][y]->setSign(lines[MAP_FIRST_GRAPHICS_LINE + y][x + ((y == 0) ? 1 : 0)]);
			// ternärer operator weil am anfang des files ein leerzeichen eingefügt wird
		}
	}
}

std::map<wchar_t, std::wstring> Screen::getLegend(std::vector<std::wstring> lines)
{
	std::map<wchar_t, std::wstring> legend;

	legend.insert(std::pair<wchar_t, std::wstring>('#', L"Block"));
	legend.insert(std::pair<wchar_t, std::wstring>(' ', L"Empty"));

	for (int lineNr = MAP_FIRST_LEGEND_LINE; lineNr < lines.size(); ++lineNr)
	{
		legend.insert(std::pair<wchar_t, std::wstring>(lines[lineNr][0], lines[lineNr].substr(3)));
	}
	return legend;
}

/// <summary>
/// Sucht den fieldTypeKey als Key in der Map und verwendet den ersten Teil des Values der Map zum Instanzieren des jeweiligen WorldFields.
/// </summary>
/// <param name="legend"></param>
/// <param name="fieldType"></param>
/// <returns></returns>
WorldField* Screen::createWorldField(std::map<wchar_t, std::wstring>& legend, wchar_t fieldTypeKey)
{
	// Finde die zum fieldTypeKey passende Legend-Zeile.
	auto iterator = legend.find(fieldTypeKey);
	if (iterator == legend.end())
	{
		throw std::invalid_argument("Unknown WorldField type key.");
	}

	// Ermittle die Art des WorldFields (Empty, Block, Transition, ...) und deren Parameter.
	std::wstring fieldType;
	std::wstring parameters;
	size_t pos = iterator->second.find(';');
	if (pos != std::wstring::npos)
	{
		fieldType = iterator->second.substr(0, pos);
		parameters = iterator->second.substr(pos + 1);
	}
	else
	{
		fieldType = iterator->second;
		parameters = L"";
	}

	// Erstelle das entsprechende WorldField.
	if (fieldType == L"Empty")
	{
		return new EmptyField();
	}

	if (fieldType == L"Block")
	{
		return new BlockField();
	}

	if (fieldType == L"Transition")
	{
		return new TransitionField(parameters);
	}

	if (fieldType == L"Blacksmith")
	{
		return new BlacksmithField(parameters);
	}

	if (fieldType == L"Inn")
	{
		return new InnField(parameters);
	}

	if (fieldType == L"Shop")
	{
		return new ShopField(parameters);
	}

	if (fieldType == L"House")
	{
		return new HouseField(parameters);
	}

	if (fieldType == L"Npc")
	{
		return new NpcField(parameters);
	}

	if (fieldType == L"Boundary")
	{
		return new BoundaryField(parameters);
	}

	if (fieldType == L"BossField")
	{
		return new BossField(parameters);
	}

	if (fieldType == L"Exit")
	{
		return new ExitField(parameters);
	}

	throw std::invalid_argument("Unknown WorldField type.");
}

void Screen::display(Player* player) const
{
	for (int y = 0; y < MAP_SIZE_Y + 2; ++y)
	{
		for (int x = 0; x < MAP_SIZE_X + 2; ++x)
		{
			Position playerPosition = player->getPosition();

			if ((playerPosition.x) == x && (playerPosition.y) == y)
			{
				std::wcout << PLAYER_CHAR;
				continue;
			}

			std::wcout << this->world[x][y]->getSign();
		}
		std::wcout << "\n";
	}
}

bool Screen::getIsSafe()
{
	return this->isSafe;
}
