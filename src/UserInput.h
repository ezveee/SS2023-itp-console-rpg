#pragma once

#include <map>
#include "Command.h"

class UserInput
{
public:
	Command getUserInput() const;

protected:
	virtual std::map<char, Command> getKeyMapping() const = 0;
};

