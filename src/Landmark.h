#pragma once

#include "defines.h" // temporary header file for defines
#include "Position.h"

enum class LandmarkType
{	
	EmptyField = EMPTY_FIELD,
	Dungeon = LANDMARK_DUNGEON,
	House = LANDMARK_HOUSE,
	Shop = LANDMARK_SHOP,
	Blacksmith = LANDMARK_BLACKSMITH,
	Inn = LANDMARK_INN,

	PathCorner = '+',
	PathHorizontal = '-',
	PathVertical = '|'
};

struct Landmark
{
	LandmarkType type;
	Position position;
};

namespace mapConstants
{
	namespace mapElement
	{
		constexpr char corner = '+';
		constexpr char horizontalBorder = '-';
		constexpr char verticalBorder = '|';
		constexpr char emptyField = ' ';
	}
}

// temp
enum class PathType
{
	Corner = '+',
	Horizontal = '-',
	Vertical = '|'
};

struct Path
{
	PathType type;
	Position position;
};

