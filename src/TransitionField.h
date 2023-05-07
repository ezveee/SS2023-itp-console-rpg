#pragma once
#include "WorldField.h"

class TransitionField : public WorldField
{
	public:
		TransitionField(std::string& parameters);
		virtual ~TransitionField();

		void onEnter() override;
		bool isEnterable() override;
};
