#pragma once

class Ability
{
	public:
		virtual void action() = 0;

		int level;
		int cost;
		bool isAOE;
};
