#include "UIManager.h"
#include <iostream>
#include <sstream>
#include "conio.h"

void UIManager::showStats()
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

    std::wcout << "= = = = = Stats = = = = =\n" << std::endl;

    //Show Player-Team-Stats
    std::wstring pTeamOutput = L"----- Player Team -----\n\n";
    for (int index = 0; index < playerTeam->members.size(); index++)
    {
        std::wstring name = playerTeam->members[index]->getName();
        std::wstring health = std::to_wstring(playerTeam->members[index]->getHealth());
        std::wstring maxHealth = std::to_wstring(playerTeam->members[index]->getStats().maxHealth);
		std::wstring mana = std::to_wstring(playerTeam->members[index]->getMana());
		std::wstring maxMana = std::to_wstring(playerTeam->members[index]->getStats().maxMana);

        pTeamOutput += L"\t" + name + L" [" + health + L"/" + maxHealth + L"]" + L" [" + mana + L"/" + maxMana + L"]\n";
    }
    std::wcout << pTeamOutput << std::endl;

    //Show Enemy-Team-Stats
    std::wstring eTeamOutput = L"----- Enemy Team -----\n\n";
    for (int index = 0; index < enemyTeam->members.size(); index++)
    {
        std::wstring name = enemyTeam->members[index]->getName();
        std::wstring health = std::to_wstring(enemyTeam->members[index]->getHealth());
        std::wstring maxHealth = std::to_wstring(enemyTeam->members[index]->getStats().maxHealth);

        eTeamOutput += L"\t" + name + L" [" + health + L"/" + maxHealth + L"]\n";
    }
    std::wcout << eTeamOutput << std::endl;
}

void UIManager::showChooseAction(Ally* user, int selection)
{
    system("cls");

    //Dialog Box
    std::wstring dialog = user->getName() + L", please select an Action...";
    this->showDialog(dialog, false);

    if (selection == Default)
        std::wcout << "> ";
    std::wcout << "Base Attack" << std::endl;

    if (selection == UseAbility)
        std::wcout << "> ";
    std::wcout << "Use Ability" << std::endl;

    if (selection == UseItem)
        std::wcout << "> ";
    std::wcout << "Use Item" << std::endl;

    if (selection == Block)
        std::wcout << "> ";
    std::wcout << "Block" << std::endl;
    std::wcout << std::endl;

    this->showStats();
}

void UIManager::showChooseAbility(Ally* user, int selection)
{
    system("cls");

    //Dialog Box
    std::wstring dialog = user->getName() + L", please select an Ability...";
    this->showDialog(dialog, false);

    std::vector<Ability*> abilities = user->getAbilities();
    for (int i = 0; i < abilities.size(); i++)
    {
        if (i == selection)
            std::wcout << "> ";

        std::wcout << abilities[i]->getName() << " [" << abilities[i]->cost << "]" << std::endl;
    }

	this->showStats();
}

void UIManager::showChooseTarget(Ally* user, int selection, Team* targetTeam)
{
    system("cls");

    //Dialog Box
    std::wstring dialog = user->getName() + L", please select a Target...";
    this->showDialog(dialog, false);

    for (int i = 0; i < targetTeam->members.size(); i++)
    {
        if (i == selection)
            std::wcout << "> ";

        Entity* enemy = targetTeam->members[i];
        std::wcout << enemy->getName();
        std::wcout << L" [" << enemy->getHealth() << L"/" << enemy->getStats().maxHealth << L"]" << std::endl;
    }
    std::wcout << std::endl;

    this->showStats();
}

void UIManager::showDialog(std::wstring dialog, bool requireInput)
{
    int dialogWidth = 50;
    std::wstring border = L"+------------------------------------------------+";

	std::wcout << border << L"\n";

	std::wistringstream iss(dialog);
    std::wstring line;
    while (std::getline(iss, line))
    {
        while (!line.empty())
        {
            std::wstring output = L"| ";

            if (line.length() <= (dialogWidth - 4))
            {
                output += line + std::wstring(dialogWidth - 4 - line.length(), ' ');
                output += L" |";
                line.clear();
            }
            else
            {
                size_t lastSpace = line.substr(0, dialogWidth - 4).find_last_of(L' ');
                if (lastSpace == std::wstring::npos)
                {
                    output += line.substr(0, dialogWidth - 4) + L" |";
                    line = line.substr(dialogWidth - 4);
                }
                else
                {
                    output += line.substr(0, lastSpace) + std::wstring(dialogWidth - 4 - lastSpace, ' ') + L" |";
                    line = line.substr(lastSpace + 1);
                }
            }

            std::wcout << output << std::endl;
        }
    }

    std::wcout << border << L"\n" << std::endl;

    if (requireInput)
        _getch();
}

void UIManager::setTeams(Team* playerTeam, Team* enemyTeam)
{
    this->playerTeam = playerTeam;
    this->enemyTeam = enemyTeam;
}
