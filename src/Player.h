#pragma once

#include "Position.h"
#include "Command.h"

class Player
{
	public:
		Player();
		virtual ~Player();

		bool getIsExitRequested() const;
		bool getInteractionRequested() const;
		void setInteractionRequested();
		Position calculateNewPosition(Command command);
		void setPosition(int x, int y);
		void setPosition(Position newPosition);
		Position getPosition() const;

	private:
		Position position;
		bool isExitRequested = false;
		bool interactionRequested = false;
};

