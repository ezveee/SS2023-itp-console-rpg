#pragma once
#include <string>
#include "Team.h"
#include "Ally.h"

class FightUI
{
	public:
		void showStats();
		void showDialog(std::string dialog, bool requireInput);

		void showChooseAction(Ally* user, int selection);
		void showChooseAbility(Ally* user, int selection);
		void showChooseTarget(Ally* user, int selection, Team* targetTeam);

		void setTeams(Team* playerTeam, Team* enemyTeam);

	private:
		Team* playerTeam;
		Team* enemyTeam;
};

