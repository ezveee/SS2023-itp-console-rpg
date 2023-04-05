#include "GameManager.h"

bool GameManager::isSafeScreen(Screen curScreen)
{

}

void GameManager::randomEnemyEncounter()
{

}

std::vector<Entity*> GameManager::setFightOrder(Team* teamA, Team* teamB)
{
	/*
	std::vector<Entity*> fightOrder;

	Entity* currEntity = nullptr;
	Entity* highestSpeed = nullptr;

	int index = 0;

	while (index < (teamA->members.size() + teamB->members.size()))
	{
		
		//Team A
		for (int i = 0; i < teamA->members.size(); i++)
		{
			currEntity = teamA->members[i];

			//set highestSpeed to the first Entity
			if (highestSpeed == nullptr)
				highestSpeed = currEntity;

			//set highestSpeed, when curEntity has higher Speed
			if (highestSpeed->getSpeed() < currEntity->getSpeed())
			{
				if (!(std::find(fightOrder.begin(), fightOrder.end(), currEntity) != fightOrder.end()))
					highestSpeed = currEntity;
			}
		}
		//Team B
		for (int i = 0; i < teamB->members.size(); i++)
		{
			currEntity = teamB->members[i];

			//set highestSpeed, when curEntity has higher Speed
			if (highestSpeed->getSpeed() < currEntity->getSpeed())
				highestSpeed = currEntity;
		}
		//add highestSpeed to fightOrder
		fightOrder.push_back(highestSpeed);

		//increment index
		index++;
	}

	return fightOrder;
	*/
}

void GameManager::fight(std::vector<Entity*> entities /*, Team* teamA, Team* teamB*/)
{ 
	/*
	bool fighting = true;

	//Fight is lasting until one Team is dead
	while (fighting != false)
	{
		for (int i = 0; i < entities.size(); i++)
		{
			//do something when alive
			if(entities[i]->isAlive())
			{

			}

			//check if Other-Team is alive
			fighting = ;
		}
	}
	*/
}

void GameManager::transition()
{

}
