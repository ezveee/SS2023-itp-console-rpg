#pragma once

#include "defines.h" // temporary header file for defines
#include "Landmark.h"
#include <array>

using playfield = std::array <std::array <LandmarkType, MAP_SIZE_Y>, MAP_SIZE_X>;

class World
{
	public:
		void fillWorld();
		void printWorld() const;


	private:
		playfield world;

};

