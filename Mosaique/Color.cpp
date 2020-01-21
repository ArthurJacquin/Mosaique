#include "Color.h"

Color& Color::operator=(Color b)
{
	this->x = b.x;
	this->y = b.y;
	this->z = b.z;
	return *this;
}
