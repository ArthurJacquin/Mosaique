#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include "Image.h"
#include "Crop.h"
#include "Similirate.h"

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
	int vignetteRows = int(im.getHeight() / nbrOfRows);
	int vignetteCols = int(im.getWidth() / nbrOfCols);

	vector<vector<Color>> imageCut;
	imageCut.resize(nbrOfRows * nbrOfCols);
	
	int i = 0;
	int j = 0;

	for (int x = 0; x < im.getWidth(); x++)
	{
		i = j * nbrOfRows;

		for (int y = 0; y < im.getHeight(); y++)
		{
			imageCut[i].push_back(im(x, y));
			if ((y + 1) % vignetteCols == 0 && y!= 0)
			{
				i++;
			}
		}

		if ( (x + 1) % vignetteRows == 0 && x != 0)
		{
			j++;
		}
	}

	return imageCut;
}

void resizeSet(vector<Image>& images, int w, int h)
{
	int width = 100;
	int height = 100;

	for (int i = 0; i < images.size(); ++i)
	{
		cropCentered(images[i], width, height);
	}	 
}

void findSim(vector<vector<Color>>& vignettes, vector<Image>& images)
{
	vector<Image> result;

	for (int i = 0; i < images.size() ; i++)
	{

	}
}