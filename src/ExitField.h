#pragma once
#include "WorldField.h"

class ExitField : public WorldField
{
	public:
		ExitField(std::string& parameters);
		virtual ~ExitField();

		void onEnter(Game* game) override;
		bool isEnterable() override;
};
