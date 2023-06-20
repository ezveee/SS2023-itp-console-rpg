#pragma once

#include "Position.h"
#include "Command.h"
#include "Ally.h"

class Player : public Ally
{
	public:
		Player(Team* playerTeam, std::wstring name,RoleClass role, int level, int gold, int exp, int nextExpRequirement, int weaponLevel, bool canProgress);
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
		int getExp();
		void modifyExp(int expAmount);
		int getNextExpRequirement();
		int getWeaponLevel();
		void weaponLevelUp();

	private:
		Position position;
		bool isExitRequested = false;
		bool interactionRequested = false;
		bool progress;
		int gold;
		int exp;
		int weaponLevel;
		int nextExpRequirement;
};

