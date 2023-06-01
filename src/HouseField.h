#pragma once
#include "WorldField.h"

class HouseField : public WorldField
{
public:
	HouseField(std::wstring& parameters);
	virtual ~HouseField();

	void onEnter(Game* game) override;
	bool isEnterable() override;
};
