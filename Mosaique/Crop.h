#pragma once
#include "Image.h"

void resizeCrop(Image& image, int factor)
{
	int dimensionX = int(image.getWidth() / factor);
	int dimensionY = int(image.getHeight() / factor);

	for (int x = 0; x < dimensionY; x++)
	{
		for (int y = 0; y < dimensionX; y++)
		{
			image(x, y) = image(int(x * factor), int(y * factor));
		}
	}

	image.setHeight(dimensionY);
	image.setWidth(dimensionX);
}

//get the top left corner of image
void cropTopLeft(Image &image) 
{
	int width = image.getWidth() / 2;
	int height = image.getHeight() / 2;

	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width; j++)
		{
			image(i, j) = image(i, j + height);
		}
	}

	image.setHeight(height);
	image.setWidth(width);
}

//Crop the image to a square which center is actual center of image and size of square's edge is 'size'
void cropCentered(Image& image, int sizeWidth, int sizeHeight) 
{
	int widthHalf = image.getWidth() / 2;
	int heightHalf = image.getHeight() / 2;

	for (int i = 0; i < sizeHeight; i++)
	{
		for (int j = 0; j < sizeWidth; j++)
		{
			image(i, j) = image(i + (heightHalf - sizeHeight / 2), j + (widthHalf - sizeWidth / 2));
		}
	}

	image.setHeight(sizeHeight);
	image.setWidth(sizeWidth);
}