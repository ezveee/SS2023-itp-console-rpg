#include "Ally.h"
#include <iostream>
#include "conio.h"
#include "defines.h"
#include "Game.h"

#include "SlashAttack.h"
#include "SpinAttack.h"

#include "FireballAttack.h"
#include "MeteorAttack.h"

#include "HammerSmashAttack.h"
#include "HealAllAbility.h"

Ally::Ally(Team* playerTeam, RoleClass role)
{
	this->defaultAttack = new DefaultAttack(this);

    struct Stats allyStats = {};
    switch (role)
    {
		case Warrior:
			this->name = L"Warrior";

			allyStats.maxHealth		= 12;
			allyStats.maxMana		= 9;
			allyStats.accuracy		= 2;
			allyStats.attack		= 3;
			allyStats.defense		= 12;
			allyStats.spAttack		= 1;
			allyStats.spDefense		= 8;
			allyStats.speed			= 2;
			allyStats.critical		= 2;

			this->abilities.push_back(new SlashAttack(this));
			this->abilities.push_back(new SpinAttack(this));

			break;
		case Magician:
			this->name = L"Magician";

			allyStats.maxHealth		= 10;
			allyStats.maxMana		= 14;
			allyStats.accuracy		= 2;
			allyStats.attack		= 2;
			allyStats.defense		= 8;
			allyStats.spAttack		= 2;
			allyStats.spDefense		= 12;
			allyStats.speed			= 1;
			allyStats.critical		= 1;

			this->abilities.push_back(new FireballAttack(this));
			this->abilities.push_back(new MeteorAttack(this));

			break;
		case Assassin:
			this->name = L"Assassin";

			allyStats.maxHealth = 10;
			allyStats.maxMana = 9;
			allyStats.accuracy = 1;
			allyStats.attack = 3;
			allyStats.defense = 10;
			allyStats.spAttack = 2;
			allyStats.spDefense = 10;
			allyStats.speed = 3;
			allyStats.critical = 3;

			break;
		case Healer:
			this->name = L"Healer";

			allyStats.maxHealth = 12;
			allyStats.maxMana = 12;
			allyStats.accuracy = 2;
			allyStats.attack = 2;
			allyStats.defense = 10;
			allyStats.spAttack = 4;
			allyStats.spDefense = 10;
			allyStats.speed = 1;
			allyStats.critical = 1;

			this->abilities.push_back(new HammerSmashAttack(this));
			this->abilities.push_back(new HealAllAbility(this));
			break;
		default:
			this->name = L"Default ally";
	}

	this->stat = allyStats;

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
