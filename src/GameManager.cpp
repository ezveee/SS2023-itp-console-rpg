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

void GameManager::fight(std::vector<Entity*> entitiesOrder, Team* playerTeam, Team* enemyTeam)
{
    //If any Team is empty, throw an exception
    if (entitiesOrder.size() == 0)
        throw std::runtime_error("Error: The Entities-Order is empty.");
    if (playerTeam->members.size() == 0)
        throw std::runtime_error("Error: The Player-Team is empty.");
    if (enemyTeam->members.size() == 0)
        throw std::runtime_error("Error: The Enemy-Team is empty.");

    bool fighting = true;

    //Fight is lasting until one Team is dead
    while (fighting)
    {
        //Attack
        for (int i = 0; i < entitiesOrder.size(); i++)
        {
            /*
            chosenAction = chooseAction();

            switch (chosenAction)
            {
                case UseDefaultAttack:
                    break;
                case UseAbility:
                    break;
                case UseItem:
                    break;
                case Block:
                    break;
                case Run:
                    break;
            }
            */

            //Check if current Entity is in the Players Team
            Team* oponentTeam = nullptr;
            if (std::find(playerTeam->members.begin(), playerTeam->members.end(), entitiesOrder[i]) != playerTeam->members.end())
                oponentTeam = playerTeam;
            else
                oponentTeam = enemyTeam;


            //Use Ability on Oponent-Team
            Ability* chosenAbility = entitiesOrder[i]->chooseAbility();

            if (chosenAbility->isAOE)
            {
                entitiesOrder[i]->useAbilityOnTeam(chosenAbility, oponentTeam);
            }
            else
            {
                Entity* target = entitiesOrder[i]->chooseTarget(oponentTeam);
                entitiesOrder[i]->useAbilityOnTarget(chosenAbility, target);
            }


            //If any Entity died, remove it from Vector
            for (int j = 0; j < oponentTeam->members.size(); j++)
            {
                if (!oponentTeam->members[j]->isAlive())
                {
                    //Message: Entity.name died!
                    entitiesOrder.erase(std::remove(entitiesOrder.begin(), entitiesOrder.end(), oponentTeam->members[j]), entitiesOrder.end());
                }
            }
        }


        //Check if Player-Team is Alive
        if (!playerTeam->isTeamAlive())
        {
            //Message: You've won!
            fighting = false;
        }
        //Check if Enemy-Team is Alive
        if (!enemyTeam->isTeamAlive())
        {
            //Message: You've lost!
            fighting = false;
        }
    }
}

void GameManager::transition()
{

}
