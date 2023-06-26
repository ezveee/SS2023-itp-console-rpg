#include "Game.h"
#include "Player.h"
#include "defines.h"

#include <iostream>
#include <time.h>
#include <conio.h>
#include <vector>


Game* Game::instance = nullptr;

Game* Game::getInstance()
{
	if (instance == nullptr) {
		instance = new Game();
	}
	return instance;
}

Game::Game()
{
	instance = this;
	uiManager = new UIManager();

	currentGameMode = new MoveMode(this);
	nextGameMode = nullptr;
}

Game::~Game()
{
	delete uiManager;
	delete currentGameMode;
}

void Game::run()
{
	srand(time(NULL));

	while (!this->player->getIsExitRequested())
	{
		currentGameMode->handle(this);

		if (nextGameMode != nullptr)
		{
			delete currentGameMode;
			currentGameMode = nextGameMode;
			nextGameMode = nullptr;
		}
	}

	delete currentGameMode;
}

void Game::generateMaps()
{
	this->dialogues =
	{
		{L"Castle_npc", L"hello i am the castle npc, talk to me again to unlock the barrier to the next area!"},
	};

	this->storyNpcs =
	{
		{L"Castle_npc", this->boundaries.find(L"City_1_Gate")},
	};

	this->miniMaps =
	{
		{L"City_1", THUMBNAIL_MAP_CITY_1},
		{L"City_2", THUMBNAIL_MAP_CITY_2},
		{L"City_3", THUMBNAIL_MAP_CITY_3},
		{L"Area_1", THUMBNAIL_MAP_AREA_1},
		{L"Area_2", THUMBNAIL_MAP_AREA_2},
		{L"Area_3", THUMBNAIL_MAP_AREA_3},
		{L"Area_4", THUMBNAIL_MAP_AREA_4},

	};

	this->respawn =
	{
		{L"Area_1", L"Village_2"},
		{L"Area_2", L"City_1_2"},
		{L"Area_3", L"City_2_2"},
		{L"Area_4", L"City_3_2"}
	};
}


Player* Game::loadSaveFile(std::vector<std::wstring> lines)
{
	std::vector<std::wstring> names;
	std::vector<int> roles;

	
	do
	{
		size_t pos = lines[0].find(';');
		names.push_back(lines[0].substr(0, pos));
		lines[0] = lines[0].substr(pos + 1);
	} while (lines[0] != L"" && lines[0] != L";");
	
	do
	{
		size_t pos = lines[1].find(';');
		roles.push_back(std::stoi(lines[1].substr(0, pos)));
		lines[1] = lines[1].substr(pos + 1);
	} while (lines[1] != L"" && lines[1] != L";");

	Player* newPlayer = new Player(this->playerTeam, names[0], (RoleClass)roles[0], std::stoi(lines[2]), std::stoi(lines[3]), std::stoi(lines[4]), std::stoi(lines[5]), std::stoi(lines[6]), std::stoi(lines[7]), std::stoi(lines[9]));

	for (int i = 1; i < names.size(); i++)
	{
		Ally* newAlly = new Ally(this->playerTeam, (RoleClass)roles[i], names[i], std::stoi(lines[2]));
		newAlly->setLevel(std::stoi(lines[2]), (RoleClass)roles[i] == Warrior || (RoleClass)roles[i] == Assassin ? true : false);
	}

	this->currentScreenName = lines[8];
	//add loading for playerstats

	for (int lineNr = 10; lineNr < lines.size(); ++lineNr)
	{
		size_t pos = lines[lineNr].find(';');
		this->boundaries.insert(std::pair<std::wstring, bool>(lines[lineNr].substr(0, pos), stoi(lines[lineNr].substr(pos + 1))));
	}

	return newPlayer;
}

Player* Game::createNewGame()
{
	int classSelection = 0;
	bool confirmed = false;
	std::wstring playerName;
	char input = 'w';
	do
	{
		do
		{
			system("CLS");
			std::wcout << "=============~*+-+*~=============\n Pick a class for your hero\n=================================\n\n\n";

			if (classSelection == 0) std::wcout << ">";
			std::wcout << "Warrior\n";

			if (classSelection == 1) std::wcout << ">";
			std::wcout << "Healer\n";

			if (classSelection == 2) std::wcout << ">";
			std::wcout << "Magician\n";

			if (classSelection == 3) std::wcout << ">";
			std::wcout << "Assassin\n";

			input = _getch();
		
			switch (input)
			{
				case 'w':
				case 'W':
				case ARROWKEY_UP: if (classSelection != 0)classSelection--;
					break;
				case 's':
				case 'S':
				case ARROWKEY_DOWN: if (classSelection != 3)classSelection++;
					break;
				default:break;
			}
		} while (input != '\r' && input != ' ');
		std::wcout << "=============~*+-+*~=============\n Pick a name for your hero\n=================================\n";
		std::wcout << "Your name: ";
		std::wcin >> playerName;

		std::wcout << L"Are you happy with your choices?(y/n)\n";
		char choice = _getch();
		switch (choice)
		{
			case 'y':
			case 'Y':
			case '\r': confirmed = true;
				break;
			case 'n':
			case 'N':
			case ESCAPEKEY: break;
			default: continue;
		}
	} while (!confirmed);
	this->boundaries =
	{
		{L"Village_Gate",0},
		{L"City_1_Gate", 0},
		{L"City_2_Gate", 0},
		{L"City_3_Gate", 0},

	};
	return new Player(this->playerTeam, playerName, (RoleClass)classSelection, 1, 0, 0, 40, 1, 0, 0);
}

void Game::makeSaveFile()
{
	std::wofstream file(L"./Savefiles/save.txt", std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file ");
	}
	file.trunc;

	for (auto member : this->playerTeam->members)
	{
		file << member->getName() << ";";
	}
	file << " \n";
	for (auto member : this->playerTeam->members)
	{
		file << member->getRole() << ";";
	}
	file << " \n";
	file << this->player->getStats().level << " \n";
	file << this->player->getGold() << " \n";
	file << this->player->getExp() << " \n";
	file << this->player->getNextExpRequirement() << " \n";
	file << this->player->getWeaponLevel() << " \n";
	file << this->player->canProgress() << " \n";
	file << this->currentScreenName << " \n";
	file << this->player->getBossProgression() << " \n";

	for (auto pair : this->boundaries) {
		file << pair.first << ";" << pair.second << " \n";
	}
	file.close();
	this->getUIManager()->showDialog(L"Game successfully saved!", true);
}
