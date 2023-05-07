#pragma once

#include "UserInput.h"

class MoveInput : public UserInput
{
protected:
	std::map<char, Command> getKeyMapping() const override;
};

