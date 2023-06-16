// SS2023-itp-console-rpg.cpp

#include <fcntl.h>
#include <io.h>
#include <locale>
#include <codecvt>
#include "Game.h"

/*
	main
*/
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	std::locale::global(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	Game* game = Game::getInstance();

	game->playerTeam = new Team();
	game->player = game->loadSaveFile(game->getSaveFile());
	//game->player = new Player(game->playerTeam, Warrior);

	game->run();
}
