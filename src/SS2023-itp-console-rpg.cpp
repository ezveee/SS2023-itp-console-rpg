// SS2023-itp-console-rpg.cpp

#include <fcntl.h>
#include <io.h>
#include <locale>
#include <codecvt>
#include "Game.h"
#include <iostream>
#include <conio.h>
#include "defines.h"

std::vector<std::wstring> getSaveFile();
bool startingScreen();

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	std::locale::global(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	
	Game* game = Game::getInstance();
	game->playerTeam = new Team();

	if (startingScreen())
	{
		game->player = game->createNewGame();
		game->generateMaps();
	}
	else 
	{
		game->player = game->loadSaveFile(getSaveFile());
		game->generateMaps();
		game->currentGameMode = new MoveMode(game);
	}

	game->run();
}

std::vector<std::wstring> getSaveFile()
{
	std::wifstream file(L"./Savefiles/save.txt", std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file ");
	}

	std::vector<std::wstring> lines;
	std::wstring line;

	while (std::getline(file, line))
	{
		lines.push_back(line.substr(0, line.length() - 1));
	}
	file.close();

	return lines;
}

bool startingScreen()
{
	std::wstring title = LR"(
=======================================================~*+--+*~========================================================= 
------------------------------------------------------------------------------------------------------------------------ 
   _______   ___      __       __       _______ .__   __.  __  ___ __ .__   __.  _______  _______   ______  .___  ___.   
  |   ____| /   \    |  |     |  |     |   ____||  \ |  | |  |/  /|  ||  \ |  | /  _____||       \ /  __  \ |   \/   |   
  |  |__   /  ^  \   |  |     |  |     |  |__   |   \|  | |  '  / |  ||   \|  ||  |  __  |  .--.  |  |  |  ||  \  /  |   
  |   __| /  /_\  \  |  |     |  |     |   __|  |  . `  | |    <  |  ||  . `  ||  | |_ | |  |  |  |  |  |  ||  |\/|  |   
  |  |   /  _____  \ |  `----.|  `----.|  |____ |  |\   | |  .  \ |  ||  |\   ||  |__| | |  '--'  |  `--'  ||  |  |  |   
  |__|  /__/     \__\|_______||_______||_______||__| \__| |__|\__\|__||__| \__| \______| |_______/ \______/ |__|  |__|   
                                                                                                                         
------------------------------------------------------------------------------------------------------------------------ 
=======================================================~*+--+*~========================================================= 
)";

	std::wcout << title << std::endl;
	char selection = 'w';
	bool createNewGame = true;
	std::wcout << "	>New Game\n	Load Game\n";
	do {
		selection = _getch();
		system("CLS");
		std::wcout << title << std::endl;
		switch (selection)
		{
		case 'w':
		case 'W':
		case ARROWKEY_UP: std::wcout << "	>New Game\n	Load Game\n";
			createNewGame = true;
			break;
		case 's':
		case 'S':
		case ARROWKEY_DOWN: std::wcout << "	New Game\n	>Load Game\n";
			createNewGame = false;
			break;
		}

	} while (selection != '\r' && selection != ' ');
	return createNewGame;
}
