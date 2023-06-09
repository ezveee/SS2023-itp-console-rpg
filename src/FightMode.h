#pragma once

#include <vector>
#include <stdexcept>

#include "Entity.h"
#include "Team.h"
#include "GameMode.h"

class FightMode : public GameMode
{
	public:
		FightMode();
		~FightMode();

		//static FightMode* getInstance();

		//bool isSafeScreen(Screen curScreen);

		void randomEnemyEncounter();

		Team* createEnemyTeam(int pTeamSize);

		std::vector<Entity*> setFightOrder(Team* playerTeam, Team* enemyTeam);

		//void fight(Team* playerTeam);
		void handle(Game* game) override;

		//void transition();

		//FightUI* getFightUI() const { return this->fightUI; };

	private:
		//vector<Ally*> playerTeam;
		/*FightUI* fightUI;
		static FightMode* instance;*/
};

