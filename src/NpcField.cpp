#include "NpcField.h"
#include <iostream>
#include <conio.h>

NpcField::NpcField(std::wstring& parameters)
{
	size_t pos = parameters.find(';');
	npcName = parameters.substr(0, pos);
	storyNpc = parameters[pos + 1];
}

NpcField::~NpcField() = default;

void NpcField::onEnter(Game* game)
{
	// nothing to do
}

void NpcField::onInteract(Game* game)
{
	auto iterator = game->dialogues.find(npcName);
	if (iterator == game->dialogues.end())
	{
		throw std::invalid_argument("Unknown npc name key.");
	}
	std::wstring currentDialogue = iterator->second;

	game->getUIManager()->showDialog(currentDialogue, true);

	game->player->setProgress();//temp, normally this would be set after a boss battle or something
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
			auto iterator = game->dialogues.find(npcName);
			iterator->second = L"thanks for helping me out\n";
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
