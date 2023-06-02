#pragma once
#include "WorldField.h"

class ShopField : public WorldField
{
	public:
		ShopField(std::wstring& parameters);
		virtual ~ShopField();

		void onEnter(Game* game) override;
		void onInteract(Game* game) override;
		bool isEnterable() override;
		bool isInteractable() override;
};
