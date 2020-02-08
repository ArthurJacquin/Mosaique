#pragma once
#include <string>
#include <vector>
#include <FreeImage.h>
#include "Color.h"

using namespace std;

enum ImageType {
	RGB,
	HSV
};

class Image {
	
	bool successfullLoad = false;
	FREE_IMAGE_FORMAT baseFormat; //Base image format
	vector<vector<Color>> m_pixels; //Array of RGB pixels
	int m_width; //Width
	int m_height; //Height
	ImageType m_colorType; // Image color type (RGB, HSV, ...)

public:
	Image();
	Image(int nbPixels);
	Image(const char* filename);
	Image(const Image& im); //Constructor by copy

	//Destructor
	~Image();

	//Operators
	Color operator()(const int x, const int y) const; //Acces the pixel (x, y)
	Color& operator()(const int x, const int y);
	Image& operator=(Image b); 
	
	//Load/save functions (using FreeImage)
	void save(const char* fileName, FREE_IMAGE_FORMAT format) const;
	int loadFromFile(const char* filename);
	
	//Transformation functions
	void convert(ImageType type);

	//Getters
	bool getStateLoad() const { return successfullLoad; }
	int getHeight() const { return m_height; }
	int getWidth() const { return m_width; }
	vector<vector<Color>> getPixels() const { return m_pixels; }
	FREE_IMAGE_FORMAT getBaseFormat() const { return baseFormat; }

	//Setters
	void setHeight(int height) { m_height = height; }
	void setWidth(int width) { m_width = width; }
	void setPixels(vector<vector<Color>> pixels);
};