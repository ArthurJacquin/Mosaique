#pragma once
#include <string>
#include <vector>
#include <FreeImage.h>
#include "Color.h"

using namespace std;

class Image {

	vector<vector<Color>> m_pixels;
	size_t m_width;
	size_t m_height;


public:
	Image(const char* filename);
	Image(const Image& rhs); //Constructor by copy

	//Destructor
	~Image();

	//Operators
	Image& operator=(const Image& b); 
	Image& operator()(const size_t x, const size_t y)const; //Acces the pixel (x, y)

	void save(const string fileName, int quality = 95) const;
	int loadFromFile(char* filename);

	//Getters
	size_t getHeight()    const { return m_height; }
	size_t getWidth()     const { return m_width; }

};