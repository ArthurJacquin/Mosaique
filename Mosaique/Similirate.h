#pragma once
#include "Image.h"
#include <iostream>

int diffVal(Image im, Image imCompare)
{
	int somme = 0;
	Color diff(0.f, 0.f, 0.f);
	int heightMax = 0;
	int widthMax = 0;


	if (im.getHeight() > imCompare.getHeight())
	{
		heightMax = im.getHeight();
	}
	else
	{
		heightMax = imCompare.getHeight();
	}

	if (im.getWidth() > imCompare.getWidth())
	{
		widthMax = im.getWidth();
	}
	else
	{
		widthMax = imCompare.getWidth();
	}


	for (int x = 0; x < widthMax; x++)
	{
		for (int y = 0; y < heightMax; y++)
		{
			diff = im(x, y) - imCompare(x, y);
		}
	}

	std::cerr << diff << std::endl;
	return somme;

}