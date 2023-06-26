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
