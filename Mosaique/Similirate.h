#pragma once
#include "Image.h"
#include <iostream>

int diffVal(Image im, Image imCompare)
{
	int somme = 0;
	int diff[] = { 0, 0, 0 };
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
			diff[0] = im(x, y).x - imCompare(x, y).x;
			diff[1] = im(x, y).y - imCompare(x, y).y;
			diff[2] = im(x, y).z - imCompare(x, y).z;
			somme = diff[0] + diff[1] + diff[2];
		}
	}

	std::cerr << "diffVal() : " << diff[0] << ", " << diff[1] << ", " << diff[2] << std::endl;
	std::cerr << "diffVal() : " << somme;
	return somme;

}

int diffHisto(Image im1, Image im2) 
{
	int dist = 0;
	

	return dist;
}

vector<vector<int>> calculateHistogram(Image im) 
{
	vector<vector<int>> hist;
	hist.resize(3);

	for (int i = 0; i < 3; i++) 
	{
		hist[i].resize(255);
		for (int x = 0; x < im.getWidth(); x++) 
		{
			for (int y = 0; y < im.getHeight(); y++)
			{
				switch(i) 
				{
				case 0:
					hist[i][im(x, y).x] += 1;
					break;
				case 1:
					hist[i][im(x, y).y] += 1;
					break;
				case 2:
					hist[i][im(x, y).z] += 1;
					break;
				}

			}
		}
	}

	return hist;
}