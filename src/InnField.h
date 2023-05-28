#pragma once
#include "WorldField.h"

class InnField : public WorldField
{
	public:
		InnField(std::wstring& parameters);
		virtual ~InnField();

		void onEnter(Game* game) override;
		bool isEnterable() override;
};
