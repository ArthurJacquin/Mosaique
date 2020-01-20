#pragma once

class Color {
public:
	float x, y, z;

	Color() :x(0), y(0), z(0) {};
	Color(float r, float g, float b) :x(r), y(g), z(b) {};

	Color& operator=(Color b);
};
