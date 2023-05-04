// SS2023-itp-console-rpg.cpp

#include <iostream>
#include "conio.h"

#include "World.h"
#include "Player.h"
#include "ScreenDefinitions.h"

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

	world.fillWorld(city1Screen2.landmarks); // just temporary; should be currentScreen.landmarks

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


