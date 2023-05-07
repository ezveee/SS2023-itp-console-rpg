#pragma once
#include "WorldField.h"

class EmptyField : public WorldField
{
public:
	EmptyField();
	virtual ~EmptyField();

	void onEnter() override;
	bool isEnterable() override;
};

