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

	//TODO : laisser le choix à l'utilisateur des dimensions pour croper l'image
	cropCentered(baseImage, 200, 200);
	baseImage.save("test.jpg", baseImage.getBaseFormat());

	int nbRow = 0;
	int nbCol = 0;

	cout << u8"Choissisez un nombre de lignes" << "\n";
	cin >> nbRow;
	cout << u8"Choissisez un nombre de colonnes" << "\n";
	cin >> nbCol;

	vector<vector<Color>> vignettes;
	vignettes = cut(baseImage, nbRow, nbCol);
	
	string databasePath;
	cout << "\n" << u8"Chemin du dossier contenant la base de données d'images ?" << "\n";
	cin >> databasePath;

	int widthVignettes = baseImage.getWidth() / nbCol;
	int heightVignettes = baseImage.getHeight() / nbRow;

	vector<Image> database;
	loadRegistre(database, databasePath.c_str());
	resizeSet(database, widthVignettes, heightVignettes);
	vector<vector<vector<int>>> histogramSet;
	histogramSet = histoSet(database);

	vector<Image> vignettesBase;
	vignettesBase = findSim(vignettes, widthVignettes, heightVignettes, database, histogramSet, nbCol, nbRow);
	reassembleFinaleIm(baseImage, vignettesBase, nbRow, nbCol);

	baseImage.save("save.jpg", baseImage.getBaseFormat());
	return 0;
}

