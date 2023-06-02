#pragma once

#include <vector>
#include <stdexcept>

#include "Entity.h"
#include "Team.h"
#include "FightUI.h"

class GameManager
{
	public:
		GameManager();
		~GameManager();

		static GameManager* getInstance();

		//bool isSafeScreen(Screen curScreen);

		void randomEnemyEncounter();

		Team* createEnemyTeam(int pTeamSize);

		std::vector<Entity*> setFightOrder(Team* playerTeam, Team* enemyTeam);

		void fight(Team* playerTeam);

		//void transition();

		FightUI* getFightUI() const { return this->fightUI; };

	private:
		//vector<Ally*> playerTeam;
		FightUI* fightUI;
		static GameManager* instance;
};

