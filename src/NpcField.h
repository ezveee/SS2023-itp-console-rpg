#pragma once
#include "WorldField.h"
#include "defines.h"

class NpcField : public WorldField
{
public:
	NpcField(std::wstring& parameters);
	virtual ~NpcField();

	void onEnter(Game* game) override;
	void onInteract(Game* game) override;
	bool isEnterable() override;
	bool isInteractable() override;
	bool isStoryNpc();

private:
	std::wstring npcName;
	bool storyNpc;
};
