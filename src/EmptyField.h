#pragma once
#include "WorldField.h"

class EmptyField : public WorldField
{
public:
	EmptyField();
	virtual ~EmptyField();

	void onEnter(Game* game) override;
	bool isEnterable() override;
};

