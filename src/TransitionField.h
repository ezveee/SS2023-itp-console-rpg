#pragma once
#include "WorldField.h"

class TransitionField : public WorldField
{
public:
	TransitionField(std::string& parameters);
	virtual ~TransitionField();

	void onEnter(Game* game) override;
	void onInteract(Game* game) override;
	bool isEnterable() override;
	bool isInteractable() override;

private:
	int getCoordinate(std::string text);
	int getCoordinate(char axis, std::string text);

	std::string mapName;
	int xPos;
	int yPos;
};
