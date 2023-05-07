#pragma once
#include "WorldField.h"

class BlacksmithField : public WorldField
{
	public:
		BlacksmithField(std::string& parameters);
		virtual ~BlacksmithField();

		void onEnter(Game* game) override;
		bool isEnterable() override;
};
