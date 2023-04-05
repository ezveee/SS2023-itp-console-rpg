#include "Player.h"

#include "defines.h"

Player::Player()
{
	setPosition(PLAYER_START_X, PLAYER_START_Y);
}

Player::~Player() = default;

void Player::setPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}

void Player::setPosition(Position newPosition)
{
	this->position.x = newPosition.x;
	this->position.y = newPosition.y;
}

Position Player::getPosition() const
{
	return this->position;
}

bool Player::getIsExitRequested() const
{
	return this->isExitRequested;
}

void Player::processMovement(UserInput input)
{
	int deltaX = 0;
	int deltaY = 0;

	switch (input)
	{
	case UserInput::MoveUp:
		deltaY = -1;
		break;

	case UserInput::MoveLeft:
		deltaX = -1;
		break;

	case UserInput::MoveDown:
		deltaY = 1;
		break;

	case UserInput::MoveRight:
		deltaX = 1;
		break;

	case UserInput::EndGame:
		this->isExitRequested = true;
		return;

	default:
		return;
	}

	int newX = this->getPosition().x + deltaX;
	int newY = this->getPosition().y + deltaY;

	if (newX >= 0 && newX < MAP_SIZE_X && newY >= 0 && newY < MAP_SIZE_Y)
	{
		this->setPosition(newX, newY);
	}
}

