#include "WorldField.h"

WorldField::WorldField() = default;
WorldField::~WorldField() = default;

char WorldField::getSign() const
{
	return this->sign;
}

void WorldField::setSign(char sign)
{
	this->sign = sign;
}

std::string WorldField::getInfo() const
{
	return this->info;
}

void WorldField::setInfo(std::string info)
{

}
