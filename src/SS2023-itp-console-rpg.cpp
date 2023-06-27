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
		system("CLS");
		game->getUIManager()->showDialog(L"You wake up to sun rays shining through the window, directly in your face. Downstairs, you hear your mother clattering in the kitchen, preparing food. You get up and head downstairs.\n\nMother: Good morning " + game->player->getName() + L", have you slept well? I hope I didn't wake you up. A letter came for you earlier today. It seems very important. The man delivering it said it was urgent and that it was to be read by no one but yourself.\n\nYou take the letter and break the seal at the back. The stamp was that of the king's royal emblem. You take out the paper, unfold it and start reading it:\n\n'To " + game->player->getName() + L",\nEsteemed " + game->player->getName() + L",\nI hope this letter finds you in good health. I request your presence at my castle in the grand city with great urgency as I have an important matter to discuss with you regarding your extraordinary lineage and most remarkable potential as the child of the great warrior who once fought by my side.\n\nShow this letter to the guards stationed in front of my castle. They will let you through.\n\nI implore you to heed my call and follow my invitation to my castle. I eagerly await your presence, " + game->player->getName() + L", for the entire kingdom is dependent on your skill, as well as your bravery and valor.\n\nYours faithfully,\nthe King.'\n\nYou stare at the letter in disbelief. Your mother walks up next to you.\n\nMother: What is the letter about? You look pale as a sheet " + game->player->getName() + L".\n\nYou show your mother the letter, who gasps in disbelief.\n\nMother: Good heavens, the king wants you to fight alongside him, just like your father once did! You should get ready as soon as possible! You wouldn't want to make the king wait! Be on your way now, "+ game->player->getName() + L". I wish you safe travels!", true);
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
	std::wcout << "						      >New Game\n\n						      Load Game\n";
	do {
		selection = _getch();
		system("CLS");
		std::wcout << title << std::endl;
		switch (selection)
		{
		case 'w':
		case 'W':
		case ARROWKEY_UP: std::wcout << "						      >New Game\n\n						      Load Game\n";
			createNewGame = true;
			break;
		case 's':
		case 'S':
		case ARROWKEY_DOWN: std::wcout << "						      New Game\n\n						      >Load Game\n";
			createNewGame = false;
			break;
		}

	} while (selection != '\r' && selection != ' ');
	return createNewGame;
}
