#include "GameManager.h"

bool GameManager::isSafeScreen(Screen curScreen)
{

}

void GameManager::randomEnemyEncounter()
{

}

std::vector<Entity*> GameManager::setFightOrder(Team* teamA, Team* teamB)
{
	std::vector<Entity*> fightOrder;

	Entity* curEntity = nullptr;
	Entity* highestSpeed = nullptr;

	int index = 0;

	while (index < (teamA->members.size() + teamB->members.size()))
	{
		//Team A
		for (int i = 0; i < teamA->members.size(); i++)
		{
			curEntity = teamA->members[i];

			//set highestSpeed to the first Entity
			if (highestSpeed == nullptr)
				highestSpeed = curEntity;

			//set highestSpeed, when curEntity has higher Speed
			if(highestSpeed->getSpeed() < curEntity->getSpeed())
				highestSpeed = curEntity;
		}
		//Team B
		for (int i = 0; i < teamB->members.size(); i++)
		{
			curEntity = teamB->members[i];

			//set highestSpeed, when curEntity has higher Speed
			if (highestSpeed->getSpeed() < curEntity->getSpeed())
				highestSpeed = curEntity;
		}
		//add highestSpeed to fightOrder
		fightOrder.push_back(highestSpeed);

		//increment index
		index++;
	}

	return fightOrder;
}

void GameManager::fight(std::vector<Entity*> entities /*, Team* teamA, Team* teamB*/)
{
	bool fighting = true;
	while (fighting != false)
	{
		for (int i = 0; i < entities.size(); i++)
		{
			//choose an ability if alive
			if(entities[i]->isAlive())
				entities[i]->chooseAbility();

			//check if Other-Team is alive
			fighting = isTeamAlive();
		}
	}
}

void GameManager::transition()
{

}
