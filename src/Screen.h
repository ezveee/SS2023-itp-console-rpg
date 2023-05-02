#pragma once

#include "defines.h"
#include "Landmark.h"
#include <vector>

struct Screen // screen number, landmarks vector, safe screen bool
{
	int screenNumber; // for screen transitions; not sure if needed
	const std::vector<Landmark> landmarks;
	//const std::vector<Path> paths;
	bool isSafeScreen;
};
