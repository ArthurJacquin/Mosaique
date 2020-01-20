#include "Image.h"
#include <stdio.h>
#include <setjmp.h>
#include <iostream>
#include <algorithm>

//Create an image from a file
Image::Image(const char* filename)
{
	this->loadFromFile((char*)filename);
	this->m_colorType = RGB;
}

//Constructor by copy
Image::Image(const Image& im)
{
	m_pixels = im.m_pixels;
	m_height = im.m_height;
	m_width = im.m_width;
	m_colorType = im.m_colorType;
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
void Image::save(const char* filename, FREE_IMAGE_FORMAT format) const
{
	FIBITMAP* bitmap = FreeImage_Allocate(m_width, m_height, 32);

	//Set pixel array
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++) 
		{	
			RGBQUAD color;
			color.rgbRed = m_pixels[i][j].x;
			color.rgbGreen = m_pixels[i][j].y;
			color.rgbBlue = m_pixels[i][j].z;
			
			FreeImage_SetPixelColor(bitmap, i, j, &color);
		}
	}

	FreeImage_Save(format, bitmap, filename);
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

	//Set image dimensions
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

void Image::convert(ImageType type)
{
	switch (type)
	{
	//RGB to HSV
	case HSV:
		//Don't convert if already in HSV
		if (this->m_colorType == HSV)
			return;

		for (int i = 0; i < m_height; ++i) 
		{
			for (int j = 0; j < m_width; ++j)
			{
				float R = m_pixels[i][j].x / 255;
				float G = m_pixels[i][j].y / 255;
				float B = m_pixels[i][j].z / 255;

				float mini = min(min(R, G), B);
				float maxi = max(max(R, G), B);
				
				// Hue color in deggrees [0, 360]
				float H;
				if (maxi == mini)
					H = 0;
				else if (maxi == R)
					H = (int)(60 * ((G - B) / (maxi - mini)) + 360) % 360;
				else if (maxi == G)
					H = 60 * ((B - R) / (maxi - mini)) + 120; // A vérifier
				else
					H = 60 * ((R - G) / (maxi - mini)) + 240;

				if (H < 0)
					H += 360;

				// Value [0, 1]
				float V = maxi; 

				// Saturation [0, 1]
				float S; 
				if (V == 0)
					S = 0;
				else
					S = (maxi - mini) / maxi;

				Color hsvColor(H, S, V);

				m_pixels[i][j] = hsvColor;
			}
		}

		this->m_colorType = HSV;

		break;

	//HSV to RGB
	case RGB:
		if (this->m_colorType == RGB)
			return;
		
		for (int i = 0; i < m_height; ++i)
		{
			for (int j = 0; j < m_width; ++j)
			{
				float H = m_pixels[i][j].x;
				float S = m_pixels[i][j].y;
				float V = m_pixels[i][j].z * 255;

				int t = (int)(H / 60) % 6;
				float f = H / 60 - t;

				//+ 0.5 to round to the closest int 
				int l = V * (1 - S) + 0.5; 
				int m = V * (1 - f * S) + 0.5;
				int n = V * (1 - (1 - f) * S) + 0.5;

				Color* rgbColor;

				switch (t)
				{
				case 0:
					rgbColor = new Color(V, n, l);
					break;

				case 1:
					rgbColor = new Color(m, V, l);
					break;

				case 2:
					rgbColor = new Color(l, V, n);
					break;

				case 3:
					rgbColor = new Color(l, m, V);
					break;

				case 4:
					rgbColor = new Color(n, l, V);
					break;

				case 5:
					rgbColor = new Color(V, l, m);
					break;

				default:
					rgbColor = new Color(0, 0, 0);
					break;
				}

				m_pixels[i][j] = *rgbColor;
			}
		}

		this->m_colorType = RGB;

		break;

	default:
		break;
	}
}
