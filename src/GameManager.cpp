#include "GameManager.h"

bool GameManager::isSafeScreen(Screen curScreen)
{

}

void GameManager::randomEnemyEncounter()
{

}

std::vector<Entity*> GameManager::setFightOrder(Team* playerTeam, Team* enemyTeam)
{
	//If any Team is empty, Error
	if (playerTeam->members.size() == 0)
		throw std::runtime_error("Error: The Player-Team is empty.");
	if (enemyTeam->members.size() == 0)
		throw std::runtime_error("Error: The Enemy-Team is empty.");


	//Create a new Vector with all Entities (unordered)
	std::vector<Entity*> allEntities;

	//Add Player-Team
	for (int i = 0; i < playerTeam->members.size(); i++)
	{
		allEntities.push_back(playerTeam->members[i]);
	}
	//Add Enemy-Team
	for (int i = 0; i < enemyTeam->members.size(); i++)
	{
		allEntities.push_back(enemyTeam->members[i]);
	}


	//Create a new Vector with all Entities (ordered), to return
	std::vector<Entity*> fightOrder;

	//As long as the fightOrder.size != allEntities.size...
	while (fightOrder.size() < allEntities.size())
	{
		Entity* highestSpeed = nullptr;

		//Search for the Entity with the highest Speed-Stat
		for (int i = 0; i < allEntities.size(); i++)
		{
			if (highestSpeed == nullptr || highestSpeed->getSpeed() < allEntities[i]->getSpeed())
				highestSpeed = allEntities[i];
		}

		//Add the Entity with the highest Speed-Stat to the ordered Vector and remove it from the unordered Vector
		fightOrder.push_back(highestSpeed);
		allEntities.erase(std::remove(allEntities.begin(), allEntities.end(), highestSpeed), allEntities.end());
	}

	return fightOrder;
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
