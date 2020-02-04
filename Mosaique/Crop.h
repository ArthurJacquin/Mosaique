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

//crop image by 2 from top left
void cropTopLeft(Image &image) 
{
	int width = image.getWidth() / 2;
	int height = image.getHeight() / 2;

	std::cerr << "orig width : " << image.getWidth() << "; orig height : " << image.getHeight() << std::endl;
	std::cerr << "center : (" << width << ", " << height << ")" << std::endl;
	//std::cerr << "copy start at : " << widthHalf - size / 2 << " and at : " << heightHalf - size / 2 << std::endl;
	//std::cerr << "copy end at : " << widthHalf + size / 2 << " and at : " << heightHalf + size / 2 << std::endl;

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

//Crop the image to a square which center is actual center of image and size of square's edge is 'size'
void cropCentered(Image& image, int size) 
{
	if (size > image.getHeight() || size > image.getWidth()) 
	{
		size = image.getWidth() < image.getHeight() ? image.getWidth() : image.getHeight();
	}

	int width = size;
	int height = size;
	int widthHalf = image.getWidth() / 2;
	int heightHalf = image.getHeight() / 2;

	/*std::cerr << "size : " << size << "; orig width : " << image.getWidth() << "; orig height : " << image.getHeight() << std::endl;
	std::cerr << "center : (" << widthHalf << ", " << heightHalf << ")" << std::endl;
	std::cerr << "copy start at : " << widthHalf - size / 2 << " and at : " << heightHalf - size / 2 << std::endl;
	std::cerr << "copy end at : " << widthHalf + size / 2 << " and at : " << heightHalf + size / 2 << std::endl;*/

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			image(i, j) = image(i + (widthHalf - size / 2), j + (heightHalf - size / 2));
		}
	}

	image.setWidth(width);
	image.setHeight(height);
}