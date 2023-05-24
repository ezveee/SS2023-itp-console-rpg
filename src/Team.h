#pragma once

#include <vector>

#include "Entity.h"
#include "Item.h"

class Entity;

class Team
{
	public:
		std::vector<Entity*> members;
		void addMember(Entity* member);

		/// <summary>
		/// Checks all Team-Members Function: isAlive()
		/// </summary>
		/// <returns>True if at least one Team-Member is alive.</returns>
		bool isTeamAlive();

	private:
		std::vector<Item*> inventory;
};

