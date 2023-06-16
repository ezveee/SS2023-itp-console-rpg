#include "FightMode.h"
#include "Enemy.h"
#include "Game.h"
#include "AllyAbility.h"

#include "conio.h"
#include <iostream>

FightMode::FightMode()
{
    //this->fightUI = new FightUI();
}

FightMode::~FightMode()
{
    //delete this->fightUI;
}

void FightMode::randomEnemyEncounter()
{

}

Team* FightMode::createEnemyTeam(int pTeamSize, int playerLevel)
{
    //1 Player-Team-Size, 1-2 enemies
    //2 Player-Team-Size, 2-3 enemies 
    //3 Player-Team-Size, 3-4 enemies 
    int enemyTeamSize = rand() % 2 + pTeamSize;

    if (enemyTeamSize > (pTeamSize + 1) || enemyTeamSize < pTeamSize)
        throw std::runtime_error("Error: Enemy-Team-Size is wrong. (FightMode)");


    Team* enemyTeam = new Team();

    EnemyType type;
	bool isPhysicalType;

	//Randomize Enemy Level (= playerLevel || playerLevel - 1)
	int level = 1;
	if(playerLevel > 1)
		level = rand() % 2 + playerLevel - 1;

    for (int i = 0; i < enemyTeamSize; i++)
    {
		int randomNum = rand() % 2;
		if (randomNum == 0) 
		{
			type = Goblin;
			isPhysicalType = true;
		}
		else 
		{
			type = Slime;
			isPhysicalType = false;
		}

        Enemy* enemy = new Enemy(enemyTeam, type);
		enemy->setLevel(level, isPhysicalType);
    }

    return enemyTeam;
}

std::vector<Entity*> FightMode::setFightOrder(Team* playerTeam, Team* enemyTeam)
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

void FightMode::handle(Game* game)
{
	UIManager* uiManager = game->getUIManager();
	
	Team* enemyTeam = this->createEnemyTeam(game->playerTeam->members.size(), game->playerTeam->members[0]->getStats().level);

    std::vector<Entity*> entitiesOrder = this->setFightOrder(game->playerTeam, enemyTeam);

    //If any Team is empty, throw an exception
    if (entitiesOrder.size() == 0)
        throw std::runtime_error("Error: The Entities-Order is empty.");
    if (game->playerTeam->members.size() == 0)
        throw std::runtime_error("Error: The Player-Team is empty.");
    if (enemyTeam->members.size() == 0)
        throw std::runtime_error("Error: The Enemy-Team is empty.");

    bool fighting = true;
    uiManager->setTeams(game->playerTeam, enemyTeam);

	//For Blocking
	bool isBlocking = false;
	Entity* blockUser = nullptr;

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

				if (isBlocking == true && entitiesOrder[i] == blockUser)
				{
					uiManager->showDialog(blockUser->getName() + L" has stopped blocking.", false);

					isBlocking = false;
					blockUser = nullptr;
				}

                //'#' means there is a line break
                uiManager->showDialog(
                    entitiesOrder[i]->getName() + L" is next!\n" + 
                    L"Press any Key to continue... "
                    , false);
                uiManager->showStats();
                _getch();

                //Check if current Entity is in the Players Team
                Team* oponentTeam = nullptr;
                if (std::find(game->playerTeam->members.begin(), game->playerTeam->members.end(), entitiesOrder[i]) != game->playerTeam->members.end())
                    oponentTeam = enemyTeam;
                else
                    oponentTeam = game->playerTeam;

                fightAction chosenAction = entitiesOrder[i]->chooseAction();

                if (chosenAction == Default)
                {
                    Entity* target = nullptr;
                    while (target == nullptr)
                    {
                        target = entitiesOrder[i]->chooseTarget(oponentTeam);

						if (target == blockUser)
							target = nullptr;
                    }

                    entitiesOrder[i]->useAbilityOnTarget(entitiesOrder[i]->getDefaultAttack(), entitiesOrder[i], target);
                }
                else if (chosenAction == UseAbility)
                {
                    //chooseAbility
                    Ability* chosenAbility = nullptr;
                    chosenAbility = entitiesOrder[i]->chooseAbility();

					//If user has not enough Mana, go back to "chooseAction"
					if (chosenAbility->cost > entitiesOrder[i]->getMana())
					{
						uiManager->showDialog(L"You do not have enough Mana.", true);
						continue;
					}

					//Go back to "chooseAction"
					if (chosenAbility == nullptr)
                    {
                        uiManager->showDialog(L"Choosing Ability canceled.", true);
                        continue;
                    }

					AllyAbility* aAbility = dynamic_cast<AllyAbility*>(chosenAbility);
					if (aAbility != nullptr)
					{
						if (oponentTeam == game->playerTeam)
							oponentTeam = enemyTeam;
						else
							oponentTeam = game->playerTeam;
					}

                    //Use Ability on Oponent-Team
                    if (chosenAbility->isAOE)
                    {
                        entitiesOrder[i]->useAbilityOnTeam(chosenAbility, entitiesOrder[i], oponentTeam);
                    }
                    else
                    {
						Entity* target = nullptr;
						while (target == nullptr)
						{
							target = entitiesOrder[i]->chooseTarget(oponentTeam);

							if (target == blockUser)
								target = nullptr;
						}

                        entitiesOrder[i]->useAbilityOnTarget(chosenAbility, entitiesOrder[i], target);
                    }
                }
                else if (chosenAction == UseItem)
                {
					uiManager->showDialog(L"You do not have any Items.", true);
					continue;
				}
                else if (chosenAction == Block)
                {
					if (game->playerTeam->members.size() <= 1)
					{
						uiManager->showDialog(L"You cannot block right now because you are fighting alone.", true);
						continue;
					}
					else if (isBlocking == true && blockUser != nullptr)
					{
						uiManager->showDialog(L"You cannot block right now. " + blockUser->getName() + L"is already blocking.", true);
						continue;
					}
					else
					{
						blockUser = entitiesOrder[i];
						isBlocking = true;
					}
                }
                else if (chosenAction == Run)
                {
                    uiManager->showDialog(L"You've run from the fight.", true);
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

            if (!enemyTeam->isTeamAlive() || !game->playerTeam->isTeamAlive())
            {
                system("cls");

                //Check if Enemy-Team is Alive
                if (!enemyTeam->isTeamAlive())
                {
                    //Message: You've won!
                    uiManager->showDialog(L"You have won.", false);
					giveOutRewards(game->playerTeam->members[0], enemyTeam);
                }
                //Check if Player-Team is Alive
                if (!game->playerTeam->isTeamAlive())
                {
                    //Message: You've lost!
					uiManager->showDialog(L"You have died.", false);
					auto iterator = game->respawn.find(game->currentScreenName.substr(0, 6));
					if (iterator == game->respawn.end())
					{
						throw std::invalid_argument("Unknown map name key.");
					}
					game->currentScreenName = iterator->second;
					game->player->setPosition(5, 5);
                }
				uiManager->showStats();
                _getch();

				if(!enemyTeam->isTeamAlive() || !game->playerTeam->isTeamAlive())
					game->player->modifyHealth(1);

                fighting = false;
                entitiesOrder.clear();
            }
        }
    }

    //delete Enemies
    delete enemyTeam;

	game->nextGameMode = new MoveMode(game);
}

void FightMode::giveOutRewards(Entity* player, Team* enemyTeam)
{
	Player* playerInstance = dynamic_cast<Player*>(player);
	if(playerInstance == nullptr)
		throw std::runtime_error("Error: Entity is not a Player (FightMode)");

	for (int i = 0; i < enemyTeam->members.size(); i++)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(enemyTeam->members[i]);

		if(enemy == nullptr)
			throw std::runtime_error("Error: Entity is not a Enemy (FightMode)");

		playerInstance->modifyGold(enemy->getGoldReward());
		playerInstance->setExpUntilLevelUp(enemy->getExperienceReward());
	}
}
