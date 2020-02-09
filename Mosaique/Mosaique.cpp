#pragma once
#include <iostream>
#include <Windows.h>
#include "Image.h"
#include "Crop.h"
#include "ImageTreatment.h"

using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	Image baseImage;

	string imagePath;
	while (baseImage.getStateLoad() != true)
	{
		cout << u8"Chemin de l'image à modifier ?" << "\n";
		cin >> imagePath;
		cout << u8"Chargement de l'image" << "\r";
		baseImage.loadFromFile(imagePath.c_str());
	}
	cout << u8"Image " << imagePath << u8" chargée avec succès !" << "\n\n";

	int nbRow = 0;
	int nbCol = 0;

	while (nbRow == 0 || nbRow > baseImage.getHeight()) 
	{
		cout << u8"Choissisez un nombre de lignes" << "\n";
		cin >> nbRow;
		if (nbRow == 0 || nbRow > baseImage.getHeight())
			std::cout << u8"Ceci n'est pas un nombre valide de lignes" << "\n";
	}

	while (nbCol == 0 || nbCol > baseImage.getWidth())
	{
		cout << u8"Choissisez un nombre de colonnes" << "\n";
		cin >> nbCol;
		if (nbCol == 0 || nbCol > baseImage.getWidth())
			std::cout << u8"Ceci n'est pas un nombre valide de lignes" << "\n";
	}

	cropCentered(baseImage, 200, 200);
	baseImage.save("test.jpg", baseImage.getBaseFormat());

	vector<vector<Color>> vignettes;
	vignettes = cut(baseImage, nbRow, nbCol);

	int widthVignettes = baseImage.getWidth() / nbCol;
	int heightVignettes = baseImage.getHeight() / nbRow;
	
	string databasePath;
	int nbOfFiles = 0;
	vector<Image> database;
	while (nbOfFiles == 0) 
	{
		cout << "\n" << u8"Chemin du dossier contenant la base de données d'images ?" << "\n";
		cin >> databasePath;
		nbOfFiles = checkRegistre(databasePath);
		if (nbOfFiles == 0)
			std::cout << u8"Ceci n'est pas une base de données valide" << "\n";
	}

	loadRegistre(database, databasePath.c_str(), nbOfFiles);
	resizeSet(database, widthVignettes, heightVignettes);
	vector<vector<vector<int>>> histogramSet;
	histogramSet = histoSet(database);

	vector<Image> vignettesBase;
	vignettesBase = findSim(vignettes, widthVignettes, heightVignettes, database, histogramSet, nbCol, nbRow);
	reassembleFinaleIm(baseImage, vignettesBase, nbRow, nbCol);

	baseImage.save("save.jpg", baseImage.getBaseFormat());
	return 0;
}

