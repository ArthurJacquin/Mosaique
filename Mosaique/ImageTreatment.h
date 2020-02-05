#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include "Image.h"

namespace fs = std::experimental::filesystem;

void loadRegistre(vector<Image>& images, string folderPath)
{
	auto directory = std::experimental::filesystem::directory_iterator(folderPath.c_str());
	float imageTreated = 0;
	float nbOfFiles = 0;

	for (const auto& entry : directory)
		nbOfFiles++;

	directory = std::experimental::filesystem::directory_iterator(folderPath.c_str());

	for (const auto& entry : directory)
	{
		int pourcentage = 100 * (imageTreated / nbOfFiles);
		std::cout << "Chargement des images : " << pourcentage << "%" << '\r';
		Image im(entry.path().u8string().c_str());
		images.push_back(im);
		imageTreated++;
	}
}

vector<vector<Color>> cut(Image im, int nbrOfRows, int nbrOfCols)
{
	int imageRows = int(im.getHeight() / nbrOfRows);
	int imageCols = int(im.getWidth() / nbrOfCols);

	vector<vector<Color>> imageCut;
	imageCut.resize(nbrOfRows * nbrOfCols);

	int i = 0;
	int j = 0;

	for (int x = 0; x < im.getWidth() -1; x++)
	{
		imageCut[i].resize(imageRows * imageCols);

		for (int y = 0; y < im.getHeight()-1; y++)
		{
			if (y % imageCols == 0 && y!= 0)
			{
				i++;
			}

			imageCut[x + i][j] = im(x, y);
		}

		i = 0;
		if (x % imageRows == 0 && x != 0)
		{
			j++;
		}
	}

	return imageCut;
}
