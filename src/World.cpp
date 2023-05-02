#include "World.h"

#include <iostream>
#include "Player.h"

using namespace mapConstants;

void World::fillWorld(const std::vector<Landmark>& landmarks/*, const std::vector<Path>& paths*/)
// implement once screens are implemented
// each screen needs to have a vector with all landmarks
{
	for (int y = 0; y < MAP_SIZE_Y; ++y)
	{
		for (int x = 0; x < MAP_SIZE_X; ++x)
		{
			world[x][y] = LandmarkType::EmptyField;
		}
	}

	for (auto landmark : landmarks)
	{
		world[landmark.position.x][landmark.position.y] = landmark.type;
	}

	/*
	// TEMP to display paths
	for (auto path : paths)
	{
		world[path.position.x][path.position.y] = path.type;
	}
	*/

}

void World::printWorld(const Player& player) const
{
	int realSizeX = MAP_SIZE_X + 1;
	int realSizeY = MAP_SIZE_Y + 1;

	for (int guiY = 0; guiY <= realSizeY; ++guiY)
	{
		for (int guiX = 0; guiX <= realSizeX; ++guiX)
		{
			bool isOnGridX = guiY == 0 || guiY == realSizeY ? true : false;
			bool isOnGridY = guiX == 0 || guiX == realSizeX ? true : false;

			if (isOnGridX && isOnGridY)
			{
				std::cout << mapElement::corner;
				continue;
			}

			if (isOnGridX && !isOnGridY)
			{
				std::cout << mapElement::horizontalBorder;
				continue;
			}

			if (!isOnGridX && isOnGridY)
			{
				std::cout << mapElement::verticalBorder;
				continue;
			}

			int xPos = guiX - 1;
			int yPos = guiY - 1;

			Position playerPosition = player.getPosition();

			if (playerPosition.x == xPos && playerPosition.y == yPos)
			{
				std::wcout << PLAYER_CHAR;
				continue;
			}

			std::cout << (char)this->world[xPos][yPos];
		}
		std::cout << "\n";
	}
}

/*
void World::printWorld(const Player& player) const
{
	int realSizeX = MAP_SIZE_X * (SCALE_FACTOR_X + 1) + 1;
	int realSizeY = MAP_SIZE_Y * (SCALE_FACTOR_Y + 1) + 1;

	for (int guiY = 0; guiY < realSizeY; ++guiY)
	{
		for (int guiX = 0; guiX < realSizeX; ++guiX)
		{
			bool isOnGridY = (guiX % (SCALE_FACTOR_X + 1)) == 0;
			bool isOnGridX = (guiY % (SCALE_FACTOR_Y + 1)) == 0;

			if (isOnGridX && isOnGridY)
			{
				std::cout << mapElement::corner;
				continue;
			}

			if (isOnGridX && !isOnGridY)
			{
				std::cout << mapElement::horizontalBorder;
				continue;
			}

			if (!isOnGridX && isOnGridY)
			{
				std::cout << mapElement::verticalBorder;
				continue;
			}

			// calculate if current position is field to represent world content
			bool isWorldContentX = (guiX - (SCALE_FACTOR_X + 1) / 2) % (SCALE_FACTOR_X + 1) == 0;
			bool isWorldContentY = (guiY - (SCALE_FACTOR_Y + 1) / 2) % (SCALE_FACTOR_Y + 1) == 0;

			// otherwise
			if (!isWorldContentX || !isWorldContentY)
			{
				// it's an empty space
				std::cout << mapElement::emptyField;
				continue;
			}

			int xPos = guiX / (SCALE_FACTOR_X + 1);
			int yPos = guiY / (SCALE_FACTOR_Y + 1);

			Position playerPosition = player.getPosition();

			if (playerPosition.x == xPos && playerPosition.y == yPos)
			{
				std::wcout << PLAYER_CHAR;
				continue;
			}

			std::cout << (char)this->world[xPos][yPos];
		}
		std::cout << std::endl;
	}
}
*/

