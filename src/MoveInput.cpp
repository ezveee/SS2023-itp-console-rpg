#include "MoveInput.h"
#include "defines.h"

std::map<char, Command> MoveInput::getKeyMapping() const
{
	return
	{
		{'w', Command::MoveUp},
		{'W', Command::MoveUp},
		{ARROWKEY_UP, Command::MoveUp},
		{'a', Command::MoveLeft},
		{'A', Command::MoveLeft},
		{ARROWKEY_LEFT, Command::MoveLeft},
		{'s', Command::MoveDown},
		{'S', Command::MoveDown},
		{ARROWKEY_DOWN, Command::MoveDown},
		{'d', Command::MoveRight},
		{'D', Command::MoveRight},
		{ARROWKEY_RIGHT, Command::MoveRight},
		{'e', Command::Interact},
		{'E', Command::Interact},
		{'m', Command::OpenMenu},
		{'M', Command::OpenMenu},
		{'q', Command::EndGame},
		{'Q', Command::EndGame},
		{ESCAPEKEY, Command::EndGame},
	};
}
