#include "HouseField.h"

HouseField::HouseField(std::wstring& parameters)
{
	houseName = parameters;
}

HouseField::~HouseField() = default;

void HouseField::onEnter(Game* game)
{
	auto dialogueIterator = game->dialogues.find(houseName);
	if (dialogueIterator == game->dialogues.end())
	{
		throw std::invalid_argument("Unknown house name key.");
	}
	std::wstring currentDialogue = dialogueIterator->second;

	game->getUIManager()->showDialog(currentDialogue, true);
}

bool HouseField::isEnterable()
{
	return true;
}

void HouseField::onInteract(Game* game)
{

}

bool HouseField::isInteractable()
{
	return false;
}
