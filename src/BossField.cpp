#include "BossField.h"

BossField::BossField(std::wstring& parameters)
{
	bossNr = std::stoi(parameters);
}

BossField::~BossField() = default;

void BossField::onEnter(Game* game)
{
	//Starting a Bossfight
	if(bossNr > game->player->getBossProgression())
	{
		auto dialogueIterator = game->bossDialogues.find(bossNr);
		if (dialogueIterator == game->bossDialogues.end())
		{
			throw std::invalid_argument("Unknown boss nr key.");
		}
		game->getUIManager()->showDialog(dialogueIterator->second, true);
		FightMode* fightMode = new FightMode();
		fightMode->currentEnemyType = (enemyType)bossNr;
		game->nextGameMode = fightMode;
	}
}

void BossField::onInteract(Game* game)
{
	//nothing
}

bool BossField::isEnterable()
{
	return true;
}

bool BossField::isInteractable()
{
	return false;
}
