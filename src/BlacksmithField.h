#pragma once
#include "WorldField.h"

class BlacksmithField : public WorldField
{
	public:
		BlacksmithField(std::wstring& parameters);
		virtual ~BlacksmithField();

		void onEnter(Game* game) override;
		void onInteract(Game* game) override;
		bool isEnterable() override;
		bool isInteractable() override;
};
