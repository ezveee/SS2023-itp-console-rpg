#pragma once

#include "Position.h"
#include "Command.h"
#include "Ally.h"

class Player : public Ally
{
	public:
		Player(Team* playerTeam, RoleClass role, int gold, int expUntilLevelUp, int weaponLevel);
		virtual ~Player();

		bool getIsExitRequested() const;
		bool getInteractionRequested() const;
		void setInteractionRequested();
		Position calculateNewPosition(Command command);
		void setPosition(int x, int y);
		void setPosition(Position newPosition);
		Position getPosition() const;
		bool canProgress() const;
		void setProgress();
		int getGold();
		void modifyGold(int goldAmount);
		int getExpUntilLevelUp();
		void setExpUntilLevelUp(int expAmount);
		int getWeaponLevel();
		void setWeaponLevel(int weaponLevel);

	private:
		Position position;
		bool isExitRequested = false;
		bool interactionRequested = false;
		bool progress;
		int gold;
		int expUntilLevelUp;
		int weaponLevel;
};

