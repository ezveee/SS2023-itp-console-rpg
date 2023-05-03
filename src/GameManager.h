#pragma once

#include <vector>

#include "Entity.h"
#include "Team.h"

class GameManager
{
	public:
		bool isSafeScreen(Screen curScreen);

		void randomEnemyEncounter();

		std::vector<Entity*> setFightOrder(Team* playerTeam, Team* enemyTeam);

		void fight(std::vector<Entity*> entities /*, Team* teamA, Team* teamB*/);

		void transition();
};

