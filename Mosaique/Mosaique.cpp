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

	/*Image testImage;
	string imagePathTest;
	while (testImage.getStateLoad() != true)
	{
		cout << u8"Chemin de l'image à tester ?" << "\n";
		cin >> imagePathTest;
		cout << u8"Chargement de l'image test" << "\r";
		testImage.loadFromFile(imagePathTest.c_str());
	}
	cout << u8"Pixel à l'origine : " << testImage(0, 0) << "\n\n";
	*/

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

	//baseImage.convert(HSV);
	cropCentered(baseImage, 100, 100);
	baseImage.save("test.jpg", baseImage.getBaseFormat());

	int nbRow = 4;
	int nbCol = 4;
	//TODO : récupérer ces caleurs depuis la console (set par l'utilisateur)

	vector<vector<Color>> vignettes;
	vignettes = cut(baseImage, nbRow, nbCol);
	
	string databasePath;
	cout << u8"Chemin du dossier contenant la base de données d'images ?" << "\n";
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
	//baseImage.convert(RGB);

	baseImage.save("save.jpg", baseImage.getBaseFormat());
	return 0;
}

