#pragma once
#include "Image.h"

void resizeCrop(Image& image, int factor)
{
	int dimensionX = int(image.getWidth() / factor);
	int dimensionY = int(image.getHeight() / factor);

	for (int x = 0; x < dimensionX; x++)
	{
		for (int y = 0; y < dimensionY; y++)
		{
			image(x, y) = image(int(x * factor), int(y * factor));
		}
	}

	image.setHeight(dimensionY);
	image.setWidth(dimensionX);
}

void crop(Image& image)
{
	int xDepart = image.getWidth() / 4;
	int yDepart = image.getHeight() / 4;

	for (int x = xDepart; x < int(image.getWidth() - xDepart); x++)
	{
		for (int y = yDepart; y < int(image.getHeight() - yDepart); y++)
		{
			image(x, y) = image(x, y);
		}
	}

	image.setWidth(image.getWidth() - xDepart);
	image.setHeight(image.getHeight() - yDepart);
}

void cropTopLeft(Image &image) 
{
	int width = image.getWidth() / 2;
	int height = image.getHeight() / 2;

	for (int i = 0; i < width; i++) 
	{
		for (int j = height; j < height; j++) 
		{
			image(i, j) = image(i, j);
		}
	}

	image.setWidth(width);
	image.setHeight(height);
}

void cropCentered(Image& image, int size) 
{
	int width = size * 2;
	int height = size * 2;

	for (int i = 0; i < width; i++)
	{
		for (int j = height; j < height; j++)
		{
			image(i, j) = image(i + size, j + size);
		}
	}

	image.setWidth(width);
	image.setHeight(height);
}