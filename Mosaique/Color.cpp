#include "Color.h"

Color& Color::operator=(Color b)
{
	this->x = b.x;
	this->y = b.y;
	this->z = b.z;
	return *this;
}

Color& Color::operator-(Color b)
{
	this->x = this->x - b.x;
	this->y = this->y - b.y;
	this->z = this->z - b.z;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Color& obj)
{
	os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")" << std::endl;
	return os;
}
