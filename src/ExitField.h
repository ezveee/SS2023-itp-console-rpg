#pragma once
#include "WorldField.h"

class ExitField : public WorldField
{
	public:
		ExitField(std::string& parameters);
		virtual ~ExitField();

		void onEnter(Game* game) override;
		void onInteract(Game* game) override;
		bool isEnterable() override;
		bool isInteractable() override;
};
