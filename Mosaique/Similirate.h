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
		heightMax = imCompare.getHeight();
	}
	else
	{
		heightMax = im.getHeight();
	}

	if (im.getWidth() > imCompare.getWidth())
	{
		widthMax = imCompare.getWidth();
	}
	else
	{
		widthMax = im.getWidth();
	}

	for (int x = 0; x < widthMax; x++)
	{
		for (int y = 0; y < heightMax; y++)
		{
			diff[0] = abs(im(x, y).x - imCompare(x, y).x);
			diff[1] = abs(im(x, y).y - imCompare(x, y).y);
			diff[2] = abs(im(x, y).z - imCompare(x, y).z);
			somme += diff[0] + diff[1] + diff[2];
		}
	}

	//std::cerr << "diffVal() : " << somme;
	return somme;

}

int diffValWithMoy(Image im, Image imCompare)
{
	int moy = 0;
	int diff[] = { 0, 0, 0 };
	int heightMax = 0;
	int widthMax = 0;

	if (im.getHeight() > imCompare.getHeight())
	{
		heightMax = imCompare.getHeight();
	}
	else
	{
		heightMax = im.getHeight();
	}

	if (im.getWidth() > imCompare.getWidth())
	{
		widthMax = imCompare.getWidth();
	}
	else
	{
		widthMax = im.getWidth();
	}

	for (int x = 0; x < widthMax; x++)
	{
		for (int y = 0; y < heightMax; y++)
		{
			diff[0] = abs(im(x, y).x - imCompare(x, y).x);
			diff[1] = abs(im(x, y).y - imCompare(x, y).y);
			diff[2] = abs(im(x, y).z - imCompare(x, y).z);
			moy += ((diff[0] + diff[1] + diff[2]) / 3);
		}
	}

	//std::cerr << "diffValMoyenne() : " << moy;
	return moy;

}

vector<vector<int>> calculateHistogram(Image im)
{
	vector<vector<int>> hist;
	hist.resize(3);

	for (int i = 0; i < 3; i++)
	{
		hist[i].resize(256);
		for (int x = 0; x < im.getWidth(); x++)
		{
			for (int y = 0; y < im.getHeight(); y++)
			{
				switch (i)
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

int binHisto(vector<vector<int>> hist, int start, int end) 
{
	int value = 0;

	for (int x = 0; x < 3; x++)
	{
		for (int y = start; y < end; y++)
		{
			value += hist[x][y];
		}
	}

	return value;
}

int diffHisto(Image im1, Image im2) 
{
	int dist = 0;
	vector<vector<int>> histo1 = calculateHistogram(im1);
	vector<vector<int>> histo2 = calculateHistogram(im2);

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 256; y++)
		{
			dist += abs(histo1[x][y] - histo2[x][y]);
		}
	}

	std::cerr << "diffHisto() : " << dist;
	return dist;
}

int diffHistoBin(Image im1, Image im2, int nbBin) 
{
	int dist = 0;
	vector<vector<int>> histo1 = calculateHistogram(im1);
	vector<vector<int>> histo2 = calculateHistogram(im2);

	int decal = 256 / nbBin;
	vector<vector<int>> histoBin1;
	vector<vector<int>> histoBin2;
	histoBin1.resize(3);
	histoBin2.resize(3);
	for (int i = 0; i < 3; i++)
	{
		histoBin1[i].resize(nbBin);
		histoBin2[i].resize(nbBin);
		for (int j = 0; j < nbBin; j++) 
		{
			histoBin1[i][j] = binHisto(histo1, 0 + (decal * j), decal + (decal * j));
			histoBin2[i][j] = binHisto(histo2, 0 + (decal * j), decal + (decal * j));
		}
	}

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < nbBin; y++)
		{
			dist += abs(histoBin1[x][y] - histoBin2[x][y]);
		}
	}

	std::cerr << "diffHistoBin() : " << dist << " with bin = " << nbBin;
	return dist;
}