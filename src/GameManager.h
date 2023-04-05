#pragma once

#include <vector>

#include "Entity.h"

class GameManager
{
	public:
		bool isSafeScreen(Screen curScreen);

		void randomEnemyEncounter();

		std::vector<Entity*> setFightOrder(Team* teamA, Team* teamB);

		void fight(std::vector<Entity*> entities /*, Team* teamA, Team* teamB*/);

		void transition();
};

