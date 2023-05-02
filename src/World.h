#pragma once

#include "defines.h" // temporary header file for defines
#include "Landmark.h"
#include <vector>
#include <array>

using playfield = std::array <std::array <LandmarkType, MAP_SIZE_Y>, MAP_SIZE_X>;

class Player;

class World
{
	public:
		void fillWorld(const std::vector<Landmark>& landmarks/*, const std::vector<Path>& paths*/);
		void printWorld(const Player& player) const;

	private:
		playfield world;

};

