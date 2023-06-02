#include "FightUI.h"
#include <iostream>
#include <sstream>

void FightUI::showStats()
{
    //If any Team-Pointer is a nullptr, Error
    if (this->playerTeam == nullptr)
        throw std::runtime_error("Error: The Player-Team is a nullptr. (Fight-UI)");
    if (this->enemyTeam == nullptr)
        throw std::runtime_error("Error: The Enemy-Team is a nullptr. (Fight-UI)");

    Team* playerTeam = this->playerTeam;
    Team* enemyTeam = this->enemyTeam;

    //If any Team is empty, Error
    if (playerTeam->members.size() == 0)
        throw std::runtime_error("Error: The Player-Team is empty. (Fight-UI)");
    if (enemyTeam->members.size() == 0)
        throw std::runtime_error("Error: The Enemy-Team is empty. (Fight-UI)");

    std::cout << "= = = = = Stats = = = = =\n" << std::endl;

    //Show Player-Team-Stats
    std::string pTeamOutput = "----- Player Team -----\n\n";
    for (int index = 0; index < playerTeam->members.size(); index++)
    {
        std::string name = playerTeam->members[index]->getName();
        std::string health = std::to_string(playerTeam->members[index]->getHealth());
        std::string maxHealth = std::to_string(playerTeam->members[index]->getStats().maxHealth);

        pTeamOutput += "\t" + name + " [" + health + "/" + maxHealth + "]\n";
    }
    std::cout << pTeamOutput << std::endl;

    //Show Enemy-Team-Stats
    std::string eTeamOutput = "----- Enemy Team -----\n\n";
    for (int index = 0; index < enemyTeam->members.size(); index++)
    {
        std::string name = enemyTeam->members[index]->getName();
        std::string health = std::to_string(enemyTeam->members[index]->getHealth());
        std::string maxHealth = std::to_string(enemyTeam->members[index]->getStats().maxHealth);

        eTeamOutput += "\t" + name + " [" + health + "/" + maxHealth + "]\n";
    }
    std::cout << eTeamOutput << std::endl;
}

void FightUI::showChooseAction(Ally* user, int selection)
{
    system("cls");

    //Dialog Box
    std::string dialog = user->getName() + ", please select an Action...";
    this->showDialog(dialog, false);

    if (selection == Default)
        std::cout << "> ";
    std::cout << "Base Attack" << std::endl;

    if (selection == UseAbility)
        std::cout << "> ";
    std::cout << "Use Ability" << std::endl;

    if (selection == UseItem)
        std::cout << "> ";
    std::cout << "Use Item" << std::endl;

    if (selection == Block)
        std::cout << "> ";
    std::cout << "Block" << std::endl;
    std::cout << std::endl;

    this->showStats();
}

void FightUI::showChooseAbility(Ally* user, int selection)
{
    system("cls");

    //Dialog Box
    std::string dialog = user->getName() + ", please select an Ability...";
    this->showDialog(dialog, false);

    std::vector<Ability*> abilities = user->getAbilities();
    for (int i = 0; i < abilities.size(); i++)
    {
        if (i == selection)
            std::cout << "> ";

        std::cout << abilities[i]->getName() << " [" << abilities[i]->cost << "]" << std::endl;
    }

	this->showStats();
}

void FightUI::showChooseTarget(Ally* user, int selection, Team* targetTeam)
{
    system("cls");

    //Dialog Box
    std::string dialog = user->getName() + ", please select a Target...";
    this->showDialog(dialog, false);

    for (int i = 0; i < targetTeam->members.size(); i++)
    {
        if (i == selection)
            std::cout << "> ";

        Entity* enemy = targetTeam->members[i];
        std::cout << enemy->getName();
        std::cout << " [" << enemy->getHealth() << "/" << enemy->getStats().maxHealth << "]" << std::endl;
    }
    std::cout << std::endl;

    this->showStats();
}

void FightUI::showDialog(std::string dialog, bool requireInput)
{
    int dialogWidth = 50;
    std::string border = "+------------------------------------------------+";

    std::cout << border << std::endl;

    std::istringstream iss(dialog);
    std::string line;
    while (std::getline(iss, line))
    {
        while (!line.empty())
        {
            std::string output = "| ";

            if (line.length() <= (dialogWidth - 4))
            {
                output += line + std::string(dialogWidth - 4 - line.length(), ' ');
                output += " |";
                line.clear();
            }
            else
            {
                size_t lastSpace = line.substr(0, dialogWidth - 4).find_last_of(' ');
                if (lastSpace == std::string::npos)
                {
                    output += line.substr(0, dialogWidth - 4) + " |";
                    line = line.substr(dialogWidth - 4);
                }
                else
                {
                    output += line.substr(0, lastSpace) + std::string(dialogWidth - 4 - lastSpace, ' ') + " |";
                    line = line.substr(lastSpace + 1);
                }
            }

            std::cout << output << std::endl;
        }
    }

    std::cout << border << "\n" << std::endl;

    if (requireInput)
        std::cin.get();
}

void FightUI::setTeams(Team* playerTeam, Team* enemyTeam)
{
    this->playerTeam = playerTeam;
    this->enemyTeam = enemyTeam;
}

//std::string output =
//"+----------------------------------------------------------------------+\n"
//"|                                                                      |\n"
//"|  +--------------------+                      +--------------------+  |\n"
//"|  |Ally 1              |                      |Enemy 1             |  |\n"
//"|  |xxx/xxx HP          |                      |xxx/xxx MANA        |  |\n"
//"|  |xxx/xxx MANA        |      \        /      |xxx/xxx MANA        |  |\n"
//"|  +--------------------+       \      /       +--------------------+  |\n"
//"|  |Ally 2              |        \    /        |Enemy 1             |  |\n"
//"|  |xxx/xxx HP          |         \  /         |xxx/xxx MANA        |  |\n"
//"|  |xxx/xxx MANA        |          \/          |xxx/xxx MANA        |  |\n"
//"|  +--------------------+                      +--------------------+  |\n"
//"|  |Ally 3              |      +---------      |Enemy 1             |  |\n"
//"|  |xxx/xxx HP          |      |               |xxx/xxx MANA        |  |\n"
//"|  |xxx/xxx MANA        |      +--------+      |xxx/xxx MANA        |  |\n"
//"|  +--------------------+               |      +--------------------+  |\n"
//"|                              ---------+      |Enemy 1             |  |\n"
//"|                                              |xxx/xxx MANA        |  |\n"
//"|                                              |xxx/xxx MANA        |  |\n"
//"|                                              +--------------------+  |\n"
//"|                                                                      |\n"
//"|  +-------------------------------++-------------------------------+  |\n"
//"|  |                               ||                               |  |\n"
//"|  |><><><><| A T T A C K |><><><><||><><><|  A B I L I T Y  |><><><|  |\n"
//"|  |                               ||                               |  |\n"
//"|  +-------------------------------++-------------------------------+  |\n"
//"|  |                               ||                               |  |\n"
//"|  |><><><><><| I T E M |><><><><><||><><><><><|  R U N  |><><><><><|  |\n"
//"|  |                               ||                               |  |\n"
//"|  +--+----------------------------++----------------------------+--+  |\n"
//"|  |><|  Lorem ipsum dolor sit amet, consetetur sadipscing elit  |><|  |\n"
//"|  |><|  r, sed diam nonumy eirmod tempor invidunt ut labore et  |><|  |\n"
//"|  |><|   dolore magna aliquyam erat, sed diam voluptua. At ver  |><|  |\n"
//"|  |><|  o eos et accusam et justo duo dolores et ea rebum. ...  |><|  |\n"
//"|  |><|    Zeilen: Max 54 Zeichen -> Textbox: Max 270 Zeichen    |><|  |\n"
//"|  +--+----------------------------------------------------------+--+  |\n"
//"|                                                                      |\n"
//"+----------------------------------------------------------------------+\n";
