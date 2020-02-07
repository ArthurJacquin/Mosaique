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

	std::cout << u8"Base de données chargée avec succès !" << "\n";
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

vector<vector<vector<int>>> histoSet(vector<Image> database)
{
	vector<vector<vector<int>>> histo;
	histo.resize(database.size());

	for (int i = 0; i < database.size(); i++)
	{
		histo[i] = calculateHistogram(database[i]);
	}
	return histo;
}

vector<Image> findSim(vector<vector<Color>>& vignettes, vector<Image>& database, vector<vector<vector<int>>> histogramSet, int nbrOfCols, int nbrOfRows)
{
	vector<Image> result;
	result.resize(vignettes.size());

	vector<Image> vignetteIm;
	vignetteIm.resize(vignettes.size());

	vector<vector<vector<int>>> histoVignette;
	histoVignette.resize(vignettes.size());

	int width = 100;
	int height = 100;

	for (int i = 0; i < vignettes.size(); i++)
	{
		vignetteIm[i].setHeight(height);
		vignetteIm[i].setWidth(width);

		vignetteIm[i].setPixels(vignettes[i]);
		histoVignette.push_back(calculateHistogram(vignetteIm[i]));
	}

	int min = 15000000;
	int diff = 0;
	int indexImageData = 0;

	for (int i = 0; i < nbrOfCols * nbrOfRows; i++)
	{
		for (int j = 0; j < database.size(); j++)
		{
			diff = diffHisto(histoVignette[i], histogramSet[j]);
			if (diff < min)
			{
				min = diff;
				indexImageData = j;
			}
		}

		result[i].setPixels(database[indexImageData].getPixels());
	}

	return result;
}
