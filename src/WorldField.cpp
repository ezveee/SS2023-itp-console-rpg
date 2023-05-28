#include "WorldField.h"

WorldField::WorldField() = default;
WorldField::~WorldField() = default;

wchar_t WorldField::getSign() const
{
	return this->sign;
}

void WorldField::setSign(wchar_t sign)
{
	this->sign = sign;
}

std::wstring WorldField::getInfo() const
{
	return this->info;
}

void WorldField::setInfo(std::wstring info)
{

}
