#include "Player.h"
#include "Game.h"
#include <iostream>
#include <conio.h>
#include <stdexcept>
#include "defines.h"
#include <cmath>

Player::Player(Team* playerTeam, std::wstring name, RoleClass role, int level, int gold, int exp, int nextExpRequirement, int weaponLevel, bool canProgress, int bossProgression) :
	Ally(playerTeam, role, name, level),
	gold(gold),
	exp(exp),
	nextExpRequirement(nextExpRequirement),
	weaponLevel(weaponLevel),
	progress(canProgress),
	bossProgression(bossProgression)
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

void Player::setExitRequested()
{
	this->isExitRequested = true;
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

int Player::getGold()
{
	return this->gold;
}

void Player::modifyGold(int goldAmount)
{
	this->gold += goldAmount;
	std::wcout << goldAmount << " gold earned\n\n";
}

int Player::getExp()
{
	return this->exp;
}

void Player::modifyExp(int expAmount)
{
	this->exp += expAmount;
	std::wcout << expAmount << " exp points gained\n\n";
	if (this->exp >= this->nextExpRequirement)
	{
		Game* game = Game::getInstance();

		for (auto& member : game->playerTeam->members)
		{
			bool isPhysical = (member->getRole() == Warrior || member->getRole() == Assassin);
			member->setLevel((member->getStats().level) + 1, isPhysical);
			std::wcout << member->getName() << L" is level " << member->getStats().level << L" now\n";
			_getch();
		}
		this->exp = this->exp - this->nextExpRequirement;
		this->nextExpRequirement = pow(((game->playerTeam->members[0]->getStats().level) / 0.2), 2);
		std::wcout << "you need " << this->nextExpRequirement << " more exp to level up again\n";
	}
}

int Player::getWeaponLevel()
{
	return this->weaponLevel;
}

void Player::weaponLevelUp()
{
	this->weaponLevel += 1;
}

int Player::getNextExpRequirement()
{
	return this->nextExpRequirement;
}

int Player::getBossProgression()
{
	return this->bossProgression;
}

void Player::setBossProgression()
{
	this->bossProgression += 1;
}
