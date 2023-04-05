// SS2023-itp-console-rpg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "World.h"
#include "Player.h"
#include "conio.h"

/*
	forward declarations
*/
UserInput getUserInput();

/*
	main
*/
int main()
{
    World world;
    Player player;

    world.fillWorld();

	bool isExitRequested = false;
	while (!player.getIsExitRequested())
	{
		system("CLS");
		world.printWorld(player);

		UserInput input;
		do
		{
			input = getUserInput();

		} while (input == UserInput::Invalid);

		player.processMovement(input);
	}


}


/*
	Functions
*/
UserInput getUserInput()
{
	char input = _getch();

	switch (input)
	{
	case 'w':
	case 'W':
	case ARROWKEY_UP:
		return UserInput::MoveUp;

	case 'a':
	case 'A':
	case ARROWKEY_LEFT:
		return UserInput::MoveLeft;

	case 's':
	case 'S':
	case ARROWKEY_DOWN:
		return UserInput::MoveDown;

	case 'd':
	case 'D':
	case ARROWKEY_RIGHT:
		return UserInput::MoveRight;

	case 'q':
	case 'Q':
	case ESCAPEKEY:
		return UserInput::EndGame;

	default:
		return UserInput::Invalid;
	}
}


