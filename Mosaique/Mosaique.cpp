#pragma once
#include <iostream>
#include <Windows.h>
#include "Image.h"
#include "Crop.h"
//#include "Similirate.h"
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
		/*
		string imageBisPath;
		cout << u8"Chemin de l'image à comparer ?" << "\n";
		cin >> imageBisPath;
		*/
		cout << u8"Chargement de l'image" << "\r";
		baseImage.loadFromFile(imagePath.c_str());
	}
	cout << u8"Image " << imagePath << u8" chargée avec succès !" << "\n";

	//Image compareImage(imageBisPath.c_str());
	baseImage.convert(HSV);
	//compareImage.convert(HSV);
	cropCentered(baseImage, 100, 100);

	vector<vector<Color>> vignettes;
	vignettes = cut(baseImage, 4, 4);

	string databasePath;
	cout << u8"Chemin du dossier contenant la base de données d'images ?" << "\n";
	cin >> databasePath;

	vector<Image> database;
	loadRegistre(database, databasePath.c_str());
	resizeSet(database, 100, 100);
	vector<vector<vector<int>>> histogramSet;
	histogramSet = histoSet(database);

	vector<Image> vignettesBase;
	vignettesBase = findSim(vignettes, database, histogramSet, 4, 4);
	baseImage = reassembleFinaleIm(vignettesBase, baseImage.getWidth(), baseImage.getHeight());
	baseImage.convert(RGB);
	//compareImage.convert(RGB);
	
	/*imCompare.convert(HSV);
	diffVal(im, imCompare);
	cropTopLeft(imCompare);
	imCompare.convert(RGB);*/

	baseImage.save("save.jpg", baseImage.getBaseFormat());
	//compareImage.save("saveBis.jpg", compareImage.getBaseFormat());
	return 0;
}

