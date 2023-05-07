// SS2023-itp-console-rpg.cpp

#include <iostream>
#include "conio.h"

#include "World.h"
#include "Player.h"

#include "Screen.h"

/*
	forward declarations
*/
UserInput getUserInput();
UserInput getValidUserInput();

/*
	main
*/
int main()
{
	Player player;

	Screen* currentScreen = new Screen("City_1_4");
	Screen* nextScreen = nullptr;

	while (!player.getIsExitRequested())
	{
		system("CLS");
		currentScreen->display(player);
		UserInput input = getValidUserInput();

		Position newPosition = player.processMovement(input);
		if (currentScreen->getWorldField(newPosition.x, newPosition.y)->isEnterable())
		{
			currentScreen->getWorldField(newPosition.x, newPosition.y)->onEnter();
			player.setPosition(newPosition.x, newPosition.y);
		}
	}

	delete currentScreen;
	delete nextScreen;
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

UserInput getValidUserInput()
{
	UserInput input;
	do
	{
		input = getUserInput();

	} while (input == UserInput::Invalid);
	return input;
}


