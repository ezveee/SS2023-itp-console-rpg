#pragma once
#include "WorldField.h"

class BlockField : public WorldField
{
public:
	BlockField();
	virtual ~BlockField();

	void onEnter(Game* game) override;
	void onInteract(Game* game) override;
	bool isEnterable() override;
	bool isInteractable() override;
};

