#pragma once
#include "WorldField.h"

class BlockField : public WorldField
{
public:
	BlockField();
	virtual ~BlockField();

	void onEnter(Game* game) override;
	bool isEnterable() override;
};

