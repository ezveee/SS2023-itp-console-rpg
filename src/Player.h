#pragma once

#include "Position.h"
#include "UserInput.h"

class Player
{
	public:
		Player();
		virtual ~Player();

		bool getIsExitRequested() const;
		Position processMovement(UserInput input);
		//void processMovement(UserInput input);
		void setPosition(int x, int y);
		void setPosition(Position newPosition);
		Position getPosition() const;

	private:
		Position position;
		bool isExitRequested = false;
};

