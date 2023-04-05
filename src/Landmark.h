#pragma once

#include "defines.h" // temporary header file for defines
#include "Position.h"

enum class LandmarkType
{
	//CornerBorder = CORNER_BORDER,
	//HorizontalBorder = HORIZONTAL_BORDER,
	//VerticalBorder = VERTICAL_BORDER,
	
	EmptyField = EMPTY_FIELD,
	House = LANDMARK_HOUSE,
	Dungeon = LANDMARK_DUNGEON
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