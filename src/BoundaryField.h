#pragma once
#include "WorldField.h"
#include <iostream>

class BoundaryField : public WorldField
{
public:
	BoundaryField(std::wstring& parameters, Game* game);
	virtual ~BoundaryField();

	void onEnter(Game* game) override;
	void onInteract(Game* game) override;
	bool isEnterable() override;
	bool isInteractable() override;

private:
	std::wstring boundaryName;
	bool enterable;
};

