#pragma once
#include "Image.h"

void resizeCrop(Image& im, int height, int width) 
{
	Image res = im;
	res.setHeight(height);
	res.setWidth(width);

	int facteurX = int(im.getHeight() / height);
	int facteurY = int(im.getWidth() / width);

	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
		{
			res(x, y) = im(int(x * facteurX), int(y * facteurY));
		}
	}

	im.setHeight(height);
	im.setWidth(width);
}

//get the top left corner of image
void cropTopLeft(Image& image)
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
void cropCentered(Image& image, int sizeHeight, int sizeWidth) 
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