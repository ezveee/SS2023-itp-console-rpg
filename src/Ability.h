#pragma once

class Ability
{
	int level;
	bool isAOE;

	virtual void action() = 0;
};
