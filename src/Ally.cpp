#include "Ally.h"
#include <iostream>
#include "conio.h"
#include "defines.h"
#include "Game.h"

#include "SlashAttack.h"
#include "SpinAttack.h"

#include "FireballAttack.h"
#include "MeteorAttack.h"

Ally::Ally(Team* playerTeam, RoleClass role)
{
    this->stat = { 
        1, //level
        0, //maxHealth
        0, //health
        0, //maxMana
        0, //mana
        0, //accuracy
        0, //attack
        0, //spAttack
        0, //defense
        0, //spDefense
        0, //speed
        0  //critical
    };

	this->defaultAttack = new DefaultAttack(this);

    struct Stats allyStats = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    if (role == Warrior)
    {
        this->name = L"Warrior";

        allyStats.maxHealth = 12;
        allyStats.maxMana = 8;
        allyStats.accuracy = 2;
        allyStats.attack = 2;
        allyStats.defense = 12;
        allyStats.spAttack = 1;
        allyStats.spDefense = 8;
        allyStats.speed = 1;
        allyStats.critical = 1;

		Ability* ability01 = new SlashAttack(this);
		Ability* ability02 = new SpinAttack(this);

		this->abilities.push_back(ability01);
		this->abilities.push_back(ability02);
    }
    if (role == Magician)
    {
        this->name = L"Magician";

        allyStats.maxHealth = 10;
        allyStats.maxMana = 14;
        allyStats.accuracy = 4;
        allyStats.attack = 1;
        allyStats.defense = 8;
        allyStats.spAttack = 2;
        allyStats.spDefense = 12;
        allyStats.speed = 1;
        allyStats.critical = 1;


		Ability* ability01 = new FireballAttack(this);
		Ability* ability02 = new MeteorAttack(this);

		this->abilities.push_back(ability01);
		this->abilities.push_back(ability02);
    }

    this->setStats(allyStats);

	this->stat.health = this->stat.maxHealth;
	this->stat.mana = this->stat.maxMana;

    playerTeam->addMember(this);
}

Ally::~Ally()
{
    std::wcout << L"- - - - - " << this->getName() << L" - - - - -" << std::endl;
    this->defaultAttack;
    for (int i = 0; i < this->abilities.size(); i++)
    {
        std::wcout << abilities[i]->getName() << L", was deleted" << std::endl;
        delete this->abilities[i];
    }
    this->abilities.clear();
    std::wcout << L"- - - - - " << this->getName() << L" deleted - - - - -" << std::endl;
}

fightAction Ally::chooseAction()
{
	Game* game = Game::getInstance();
	UIManager* uiManager = game->getUIManager();

    int selection = 0;
    bool choosingAction = true;
    char input = '\0';
    while (choosingAction)
    {
        uiManager->showChooseAction(this, selection);
        input = _getch();

        //Enter or Space
        if (input == '\r' || input == ' ')
        {
            choosingAction = false;
        }
        //'w', 'W', UpArrow
        else if (input == 'w' || input == 'W' || input == ARROWKEY_UP)
        {
            selection--;
            if (selection < Default)
                selection = Default;
        }
        //'s', 'S', DownArrow
        else if (input == 's' || input == 'S' || input == ARROWKEY_DOWN)
        {
            selection++;
            if (selection > Block)
                selection = Block;
        }

    }

    switch (selection)
    {
        case Default:
            return Default;
        case UseAbility:
            return UseAbility;
        case UseItem:
            return UseItem;
        case Block:
            return Block;
    }
}

Ability* Ally::chooseAbility()
{
    //No Abilities
    if (this->abilities.size() == 0)
    {
        std::wcout << this->getName() << " doesn't have any Abilities!" << std::endl;
        return nullptr;
    }

	Game* game = Game::getInstance();
	UIManager* uiManager = game->getUIManager();

    int selection = 0;
    bool choosingAbility = true;
    char input = '\0';
    while (choosingAbility)
    {
        uiManager->showChooseAbility(this, selection);
        input = _getch();

        //Enter or Space
        if (input == '\r' || input == ' ')
        {
            return this->abilities[selection];
        }
        //'w', 'W', UpArrow
        else if (input == 'w' || input == 'W' || input == ARROWKEY_UP)
        {
            selection--;
            if (selection < 0)
                selection = 0;
        }
        //'s', 'S', DownArrow
        else if (input == 's' || input == 'S' || input == ARROWKEY_DOWN)
        {
            selection++;
            if (selection > (abilities.size() - 1))
                selection = (abilities.size() - 1);
        }
        //Escape
        else if (input == ESCAPEKEY)
            choosingAbility = false;
    }
    return nullptr;
}

Entity* Ally::chooseTarget(Team* targetTeam)
{
    if(targetTeam->members.size() == 0)
        throw std::runtime_error("Error: The Target-Team is empty.");

	Game* game = Game::getInstance();
	UIManager* uiManager = game->getUIManager();

    int selection = 0;
    bool choosingTarget = true;
    char input = '\0';
    while (choosingTarget)
    {
        uiManager->showChooseTarget(this, selection, targetTeam);
        input = _getch();

        //Enter or Space
        if (input == '\r' || input == ' ')
        {
            if (!targetTeam->members[selection]->isAlive())
                return nullptr;

            return targetTeam->members[selection];
        }
        //'w', 'W', UpArrow
        else if (input == 'w' || input == 'W' || input == ARROWKEY_UP)
        {
            selection--;
            if (selection < 0)
                selection = 0;
        }
        //'s', 'S', DownArrow
        else if (input == 's' || input == 'S' || input == ARROWKEY_DOWN)
        {
            selection++;
            if (selection > (targetTeam->members.size() - 1))
                selection = (targetTeam->members.size() - 1);
        }
    }
}
