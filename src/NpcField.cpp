#include "NpcField.h"
#include <iostream>
#include <conio.h>

void addAlly(Game* game);

NpcField::NpcField(std::wstring& parameters)
{
	size_t pos = parameters.find(';');
	npcName = parameters.substr(0, pos);
	if (parameters[pos + 1] == L'0')
		storyNpc = false;
	else
		storyNpc = true;
}

NpcField::~NpcField() = default;

void NpcField::onEnter(Game* game)
{
	// nothing to do
}

void NpcField::onInteract(Game* game)
{
	auto dialogueIterator = game->dialogues.find(npcName);
	if (dialogueIterator == game->dialogues.end())
	{
		throw std::invalid_argument("Unknown npc name key.");
	}
	std::wstring currentDialogue = dialogueIterator->second;

	game->getUIManager()->showDialog(currentDialogue, true);

	if (npcName == L"King")
	{
		if (game->playerTeam->members.size() <= 1)
		{
			addAlly(game);
			game->player->setProgress();
			dialogueIterator->second = L"Be off now.\n";
		}
	}

	if (this->isStoryNpc() && game->player->canProgress())
	{
		auto iterator = game->storyNpcs.find(npcName);
		if (iterator == game->storyNpcs.end())
		{
			throw std::invalid_argument("Unknown npc name key.");
		}
		if (!iterator->second->second)
		{
			iterator->second->second = true;
			game->player->setProgress();
			dialogueIterator = game->dialogues.find(npcName);
			if (npcName != L"King")
				dialogueIterator->second = L"Off you go now!\n";
		}
	}
}

bool NpcField::isEnterable()
{
	return false;
}

bool NpcField::isInteractable()
{
	return true;
}

bool NpcField::isStoryNpc()
{
	return this->storyNpc;
}

void addAlly(Game* game)
{
	int classSelection = 0;
	bool confirmed = false;
	std::wstring allyName;
	char input = 'w';
	do
	{
		do
		{
			system("CLS");
			std::wcout << "=============~*+-+*~=============\n Pick a class for your new Ally\n=================================\n\n\n";

			if (classSelection == 0) std::wcout << ">";
			std::wcout << "Warrior\n";

			if (classSelection == 1) std::wcout << ">";
			std::wcout << "Healer\n";

			if (classSelection == 2) std::wcout << ">";
			std::wcout << "Magician\n";

			if (classSelection == 3) std::wcout << ">";
			std::wcout << "Assassin\n";

			input = _getch();

			switch (input)
			{
			case 'w':
			case 'W':
			case ARROWKEY_UP: if (classSelection != 0)classSelection--;
				break;
			case 's':
			case 'S':
			case ARROWKEY_DOWN: if (classSelection != 3)classSelection++;
				break;
			default:break;
			}
		} while (input != '\r' && input != ' ');
		std::wcout << "=============~*+-+*~=============\n Pick a name for your hero\n=================================\n";
		std::wcout << "Your ally's name: ";
		std::wcin >> allyName;

		std::wcout << L"Are you happy with your choices?(y/n)\n";
		char choice = _getch();
		switch (choice)
		{
		case 'y':
		case 'Y':
		case '\r': confirmed = true;
			break;
		case 'n':
		case 'N':
		case ESCAPEKEY: break;
		default: continue;
		}
	} while (!confirmed);

	new Ally(game->playerTeam, (RoleClass)classSelection, allyName, game->player->getStats().level);
}
