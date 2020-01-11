#pragma once
#include <string>
#include <vector>
#include <FreeImage.h>
#include "Color.h"

using namespace std;

class Image {

	FREE_IMAGE_FORMAT baseFormat; //format de l'image de base
	vector<vector<Color>> m_pixels; //Array of RGB pixels
	int m_width; //Width
	int m_height; //Height

public:
	Image(const char* filename);
	Image(const Image& im); //Constructor by copy

	//Destructor
	~Image();

	//Operators
	Color& operator()(const int x, const int y); //Acces the pixel (x, y)
	Image& operator=(Image b); 
	
	//Load/save functions (using FreeImage)
	void save(const char* fileName, FREE_IMAGE_FORMAT format) const;
	int loadFromFile(char* filename);

	//Getters
	int getHeight() const { return m_height; }
	int getWidth() const { return m_width; }
	vector<vector<Color>> getPixels() const { return m_pixels; }
	FREE_IMAGE_FORMAT getBaseFormat() { return baseFormat; }
};