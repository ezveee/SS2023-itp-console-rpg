#pragma once
#include "WorldField.h"
#include "defines.h"

class BossField : public WorldField
{
public:
	BossField(std::wstring& parameters);
	virtual ~BossField();

	void onEnter(Game* game) override;
	void onInteract(Game* game) override;
	bool isEnterable() override;
	bool isInteractable() override;
private:
	int bossNr;
};
