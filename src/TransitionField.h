#pragma once
#include "WorldField.h"

class TransitionField : public WorldField
{
public:
	TransitionField(std::wstring& parameters);
	virtual ~TransitionField();

	void onEnter(Game* game) override;
	bool isEnterable() override;

private:
	int getCoordinate(std::wstring text);
	int getCoordinate(char axis, std::wstring text);

	std::wstring mapName;
	int xPos;
	int yPos;
};
