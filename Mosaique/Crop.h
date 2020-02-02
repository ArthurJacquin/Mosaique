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