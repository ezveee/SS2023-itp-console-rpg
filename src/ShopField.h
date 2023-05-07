#pragma once
#include "WorldField.h"

class ShopField : public WorldField
{
	public:
		ShopField(std::string& parameters);
		virtual ~ShopField();

		void onEnter() override;
		bool isEnterable() override;
};
