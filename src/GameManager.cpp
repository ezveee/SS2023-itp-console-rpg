#include "GameManager.h"
#include "Enemy.h"
#include <iostream>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
    this->fightUI = new FightUI();
}

GameManager::~GameManager()
{
    delete this->fightUI;
}

GameManager* GameManager::getInstance()
{
    if (instance == nullptr) {
        instance = new GameManager();
    }
    return instance;
}

void GameManager::randomEnemyEncounter()
{

}

Team* GameManager::createEnemyTeam(int pTeamSize)
{
    //1 Player-Team-Size, 1-2 enemies
    //2 Player-Team-Size, 2-3 enemies 
    //3 Player-Team-Size, 3-4 enemies 
    int enemyTeamSize = rand() % 2 + pTeamSize;

    if (enemyTeamSize > (pTeamSize + 1) || enemyTeamSize < pTeamSize)
        throw std::runtime_error("Error: Enemy-Team-Size is wrong. (GameManager)");


    Team* enemyTeam = new Team();

    int randomNum = rand() % 2;
    EnemyType type;
    if (randomNum == 0) {
        type = Goblin;
    }
    else {
        type = Slime;
    }

    for (int i = 0; i < enemyTeamSize; i++)
    {
        Enemy* enemy = new Enemy(enemyTeam, type);
    }

    return enemyTeam;
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

    int sizeOfAll = allEntities.size();

	//As long as the fightOrder.size != allEntities.size...
	while (fightOrder.size() < sizeOfAll)
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

void GameManager::fight(Team* playerTeam)
{
    Team* enemyTeam = this->createEnemyTeam(playerTeam->members.size());

    std::vector<Entity*> entitiesOrder = this->setFightOrder(playerTeam, enemyTeam);

    //If any Team is empty, throw an exception
    if (entitiesOrder.size() == 0)
        throw std::runtime_error("Error: The Entities-Order is empty.");
    if (playerTeam->members.size() == 0)
        throw std::runtime_error("Error: The Player-Team is empty.");
    if (enemyTeam->members.size() == 0)
        throw std::runtime_error("Error: The Enemy-Team is empty.");

    bool fighting = true;
    this->fightUI->setTeams(playerTeam, enemyTeam);

    //Fight is lasting until one Team is dead
    while (fighting)
    {
        //Attack
        for (int i = 0; i < entitiesOrder.size(); i++)
        {
            bool choosingAnAction = true;

            while (choosingAnAction)
            {
                system("cls");
                //'#' means there is a line break
                this->fightUI->showDialog(
                    entitiesOrder[i]->getName() + " is next!\n" + 
                    "Press any Key to continue... "
                    , false);
                this->fightUI->showStats();
                std::cin.get();

                //Check if current Entity is in the Players Team
                Team* oponentTeam = nullptr;
                if (std::find(playerTeam->members.begin(), playerTeam->members.end(), entitiesOrder[i]) != playerTeam->members.end())
                    oponentTeam = enemyTeam;
                else
                    oponentTeam = playerTeam;

                fightAction chosenAction = entitiesOrder[i]->chooseAction();

                if (chosenAction == Default)
                {
                    Entity* target = nullptr;
                    while (target == nullptr)
                    {
                        target = entitiesOrder[i]->chooseTarget(oponentTeam);
                    }

                    entitiesOrder[i]->useAbilityOnTarget(entitiesOrder[i]->getDefaultAttack(), entitiesOrder[i], target);
                }
                else if (chosenAction == UseAbility)
                {
                    //chooseAbility
                    Ability* chosenAbility = nullptr;
                    chosenAbility = entitiesOrder[i]->chooseAbility();

                    //Go back to "choseAction"
                    if (chosenAbility == nullptr)
                    {
                        this->fightUI->showDialog("Choosing Ability canceled.", true);
                        continue;
                    }

                    //Use Ability on Oponent-Team
                    if (chosenAbility->isAOE)
                    {
                        entitiesOrder[i]->useAbilityOnTeam(chosenAbility, entitiesOrder[i], oponentTeam);
                    }
                    else
                    {
                        Entity* target = entitiesOrder[i]->chooseTarget(oponentTeam);
                        entitiesOrder[i]->useAbilityOnTarget(chosenAbility, entitiesOrder[i], target);
                    }
                }
                else if (chosenAction == UseItem)
                {

                }
                else if (chosenAction == Block)
                {

                }
                else if (chosenAction == Run)
                {
                    fightUI->showDialog("You've run from the fight.", true);
                    fighting = false;
                    entitiesOrder.clear();
                }
                choosingAnAction = false;

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

            if (!enemyTeam->isTeamAlive() || !playerTeam->isTeamAlive())
            {
                system("cls");

                //Check if Enemy-Team is Alive
                if (!enemyTeam->isTeamAlive())
                {
                    //Message: You've won!
                    fightUI->showDialog("You have won.", false);
                }
                //Check if Player-Team is Alive
                if (!playerTeam->isTeamAlive())
                {
                    //Message: You've lost!
                    fightUI->showDialog("You have died.", false);
                }
                fightUI->showStats();
                std::cin.get();

                fighting = false;
                entitiesOrder.clear();
            }
        }
    }

    //delete Enemies
    delete enemyTeam;
}
