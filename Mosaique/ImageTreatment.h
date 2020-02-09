#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include <math.h>
#include "Image.h"
#include "Crop.h"
#include "Similirate.h"

namespace fs = std::experimental::filesystem;

int checkRegistre(string path) 
{
	int nbOfFiles = 0;

	auto directory = std::experimental::filesystem::directory_iterator(path.c_str());

	for (const auto& entry : directory)
		nbOfFiles++;

	return nbOfFiles;
}

void loadRegistre(vector<Image>& images, string folderPath, int nbOfFiles)
{
	auto directory = std::experimental::filesystem::directory_iterator(folderPath.c_str());
	float imageTreated = 0;

	directory = std::experimental::filesystem::directory_iterator(folderPath.c_str());

	for (const auto& entry : directory)
	{
		int pourcentage = 100 * (imageTreated / nbOfFiles);
		std::cout << "Chargement des images : " << pourcentage << "%" << '\r';
		Image im(entry.path().u8string().c_str());
		images.push_back(im);
		imageTreated++;
	}

	std::cout << u8"Base de données chargée avec succès !" << "\n\n";
}

vector<vector<Color>> cut(Image im, int nbrOfRows, int nbrOfCols)
{
	int vignetteRows = int(im.getHeight() / nbrOfRows);
	int vignetteCols = int(im.getWidth() / nbrOfCols);

	vector<vector<Color>> imageCut;
	imageCut.resize(nbrOfRows * nbrOfCols);
	
	int i = 0;
	int j = 0;

	for (int x = 0; x < im.getHeight(); x++)
	{
		i = j * nbrOfRows;
	
		for (int y = 0; y < im.getWidth(); y++)
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

//Reassemble the vignettes to form an image
void reassembleFinaleIm(Image& image, vector<Image> vignettesIm, int nbRow, int nbCol)
{
	if (vignettesIm.size() == 0)
		std::cout << u8"Tableau de vignettes (images) vide !" << "\n";
	
	int heightVignettes = image.getHeight() / nbRow;
	int widthVignettes = image.getWidth() / nbCol;

	int currVignette = 0;

	for (int currRow = 0; currRow < nbRow; currRow++)
	{
		for (int currCol = 0; currCol < nbCol; currCol++) 
		{
			for (int x = 0; x < heightVignettes; x++)
			{
				for (int y = 0; y < widthVignettes; y++)
				{
					image(x + currRow * heightVignettes, y + currCol * widthVignettes) = vignettesIm[currVignette](x, y);
				}
			}
			currVignette += 1;
		}
		
	}

	std::cout << u8"Image réassemblée !" << "\n";
}

void resizeSet(vector<Image>& images, int w, int h)
{
	for (int i = 0; i < images.size(); ++i)
	{
		cropCentered(images[i], w, h);
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

vector<Image> findSim(vector<vector<Color>>& vignettes, int width, int height, vector<Image>& database, vector<vector<vector<int>>> histogramSet, int nbrOfCols, int nbrOfRows)
{
	vector<Image> result;
	result.resize(vignettes.size());

	vector<Image> vignetteIm;
	vector<vector<vector<int>>> histoVignette;
	for (int i = 0; i < vignettes.size(); i++) 
	{
		vignetteIm.push_back(Image(width, height));
		vignetteIm[i].setPixels(vignettes[i]);
		histoVignette.push_back(calculateHistogram(vignetteIm[i]));
	}
	std::cout << u8"Tableau de vignettes (images) réassemblées et histogrammes calculés!" << "\n";

	int nbOfComparison = 0;

	for (int i = 0; i < nbrOfCols * nbrOfRows; i++)
	{
		int min = 15000000;
		int diff = 0;
		int indexImageData = 0;
		for (int j = 0; j < database.size(); j++)
		{
			diff = diffHisto(histoVignette[i], histogramSet[j]);
			nbOfComparison++;
			if (diff < min)
			{
				min = diff;
				indexImageData = j;
			}
		}
		result[i].setPixels(database[indexImageData].getPixels());
	}
	std::cout << u8"Images similaires trouvées !" << "\n";
	std::cout << u8"Nombre d'appel à diffHisto : " << nbOfComparison << "\n";

	return result;
}

Image sobel(Image im) 
{
	im.toGrayScale();
	Image res = im;
	int radius = 1;

	int tabGx[] = { -1, 0, 1, -2, 0, 2, -1, 0, 1};
	int tabGy[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1};

	for (int i = 0; i < im.getHeight(); ++i)
	{
		for (int j = 0; j < im.getWidth(); ++j)
		{
			int Gx = 0;
			int Gy = 0;
			int id = 0;

			for (int k = i - radius; k < i + radius + 1; ++k)
			{
				for (int l = j - radius; l < j + radius + 1; ++l)
				{
					if (0 <= k && k < im.getHeight() && 0 <= l && l < im.getWidth())
					{
						Gx += im(k, l).x * tabGx[id];
						Gy += im(k, l).x * tabGy[id];
						id++;
					}
				}
			}

			int G = sqrt(pow(Gx, 2) + pow(Gy, 2));
			Color newColor((int)G, (int)G, (int)G);
			res(i, j) = newColor;
		}
	}

	return res;
}