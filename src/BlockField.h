#pragma once
#include "WorldField.h"

class BlockField : public WorldField
{
public:
	BlockField();
	virtual ~BlockField();

	void onEnter() override;
	bool isEnterable() override;
};

