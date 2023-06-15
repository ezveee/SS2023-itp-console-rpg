#include "Player.h"
#include <iostream>

#include <stdexcept>
#include "defines.h"

Player::Player(Team* playerTeam, RoleClass role) : Ally(playerTeam, role)
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

Position Player::calculateNewPosition(Command command)
{
	int deltaX = 0;
	int deltaY = 0;

	switch (command)
	{
	case Command::MoveUp:
		deltaY = -1;
		break;

	case Command::MoveLeft:
		deltaX = -1;
		break;

	case Command::MoveDown:
		deltaY = 1;
		break;

	case Command::MoveRight:
		deltaX = 1;
		break;

	case Command::Interact:
		deltaX = 0;
		this->interactionRequested = true;
		break;

	case Command::OpenMenu:
		deltaX = 0;
		break;

	case Command::EndGame:
		this->isExitRequested = true;
		break;

	default:
		throw std::invalid_argument("Incorrect command.");
	}

	Position newPosition;

	newPosition.x = this->getPosition().x + deltaX;
	newPosition.y = this->getPosition().y + deltaY;

	return newPosition;
}

bool Player::getInteractionRequested() const
{
	return this->interactionRequested;
}
void Player::setInteractionRequested()
{
	this->interactionRequested = false;
}

bool Player::canProgress() const
{
	return this->progress;
}

void Player::setProgress()
{
	this->progress = !progress;
}
