#include "UserInput.h"

#include "conio.h"

Command UserInput::getUserInput() const
{
	auto keyMapping = getKeyMapping();

	std::map<char, Command>::iterator iterator;
	do
	{
		char input = _getch();
		iterator = keyMapping.find(input);

	} while (iterator == keyMapping.end());
	return iterator->second;
}
