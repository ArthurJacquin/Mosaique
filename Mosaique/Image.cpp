#include "Image.h"
#include <stdio.h>
#include <setjmp.h>
#include <iostream>

//Create an image from a file
Image::Image(const char* filename)
{
	this->loadFromFile((char*)filename);
}

//Constructor by copy
Image::Image(const Image& im)
{
	m_pixels = im.getPixels();
	m_height = im.getHeight();
	m_width = im.getWidth();
}

Image::~Image()
{
}

Color& Image::operator()(int x, int y)
{
	return m_pixels[x][y];
}

Image& Image::operator=(Image im)
{
	m_height = im.m_height;
	m_width = im.m_width;

	for (int i = 0; i < m_height; ++i)
		for (int j = 0; j < m_width; ++j)
			m_pixels[i][j] = im(i, j);

	return *this;
}

//Save the given image on the disk with a certain quality of detail
void Image::save(const string fileName, int quality) const
{
	//TODO: save image
}

//Load the image given by the filename
//Fill the pixel array with RGB values in each cell
int Image::loadFromFile(char* filename)
{
	//Get image format
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	if (format == FIF_UNKNOWN) {
		cerr << "Format de fichier invalide !" << endl;
		return 0;
	}
		

	//Load image
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	if (!bitmap) {
		cerr << "Impossible de charger l'image" << endl;
		return 0;
	}
	//Convert to 32 bits to get pixels
	bitmap = FreeImage_ConvertTo32Bits(bitmap);
	if (!bitmap) {
		cerr << "convertion impossible" << endl;
		return 0;
	}

	//Set iamge dimensions
	m_height = FreeImage_GetHeight(bitmap);
	m_width = FreeImage_GetWidth(bitmap);
	m_pixels.resize(m_height);

	//Init pixel array
	for (int i = 0; i < FreeImage_GetHeight(bitmap); i++)
	{
		m_pixels[i].resize(m_width);
		for (int j = 0; j < FreeImage_GetWidth(bitmap); j++) {
			RGBQUAD pixColor;
			FreeImage_GetPixelColor(bitmap, i, j, &pixColor);
			Color color(pixColor.rgbRed, pixColor.rgbGreen, pixColor.rgbBlue);
			m_pixels[i][j] = color;
		}
	}

	return 0;
}
