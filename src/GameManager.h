#pragma once

#include <vector>
#include <stdexcept>

#include "Entity.h"
#include "Team.h"

class GameManager
{
	public:
		bool isSafeScreen(Screen curScreen);

		void randomEnemyEncounter();

		std::vector<Entity*> setFightOrder(Team* playerTeam, Team* enemyTeam);

		void fight(std::vector<Entity*> entitiesOrder, Team* playerTeam, Team* enemyTeam);

		void transition();
};

