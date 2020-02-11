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

	//Choix de l'image � mosaiquer
	while (baseImage.getStateLoad() != true)
	{
		cout << u8"Chemin de l'image � modifier ?" << "\n";
		cin >> imagePath;
		cout << u8"Chargement de l'image" << "\r";
		baseImage.loadFromFile(imagePath.c_str());
	}
	cout << u8"Image " << imagePath << u8" charg�e avec succ�s !" << "\n\n";

	//Choix du nombre de vignettes
	int nbRow = 0;
	int nbCol = 0;

	//V�rification de la validit� des valeurs d'entr�e
	while (nbRow <= 0) 
	{
		cout << u8"Choissisez un nombre de lignes" << "\n";
		cin >> nbRow;
		if (nbRow == 0)
			std::cout << u8"Ceci n'est pas un nombre valide de lignes" << "\n";
	}

	if (nbRow > baseImage.getHeight()) 
	{
		nbRow = baseImage.getHeight();
		std::cout << u8"Le nombre de lignes ne peut �tre sup�rieur � la hauteur de l'image" << "\n";
		std::cout << u8"Valeur resteinte � : " << nbRow << "\n";
	}

	while (nbCol <= 0)
	{
		cout << u8"Choissisez un nombre de colonnes" << "\n";
		cin >> nbCol;
		if (nbCol == 0)
			std::cout << u8"Ceci n'est pas un nombre valide de lignes" << "\n";
	}

	if (nbCol > baseImage.getWidth())
	{
		nbCol = baseImage.getWidth();
		std::cout << u8"Le nombre de colonnes ne peut �tre sup�rieur � la largeur de l'image" << "\n";
		std::cout << u8"Valeur resteinte � : " << nbCol << "\n";
	}

	//Redimensionnement en fonction du nombre de vignettes
	int size = min(baseImage.getWidth(), baseImage.getHeight());
	int widthVignettes = size / nbCol;
	int heightVignettes = size / nbRow;

	//Dimension finale de l'image de base
	int width = size - (size % (nbCol * widthVignettes));
	int height = size - (size % (nbRow * heightVignettes));

	//Crop
	resizeCrop(baseImage, width, height);
	baseImage.save("test.jpg", baseImage.getBaseFormat());

	//D�coupage de l'image en vignettes
	vector<vector<Color>> vignettes;
	vignettes = cut(baseImage, nbRow, nbCol);
	
	//Choix de la base de donn�es
	string databasePath;
	int nbOfFiles = 0;
	vector<Image> database;
	while (nbOfFiles == 0) 
	{
		cout << "\n" << u8"Chemin du dossier contenant la base de donn�es d'images ?" << "\n";
		cin >> databasePath;
		nbOfFiles = checkRegistre(databasePath);
		if (nbOfFiles == 0)
			std::cout << u8"Ceci n'est pas une base de donn�es valide" << "\n";
	}

	//Chargement de la base de donn�es
	loadRegistre(database, databasePath.c_str(), nbOfFiles);

	//Redimensionnement de la DB � la taille des vignettes
	resizeSet(database, widthVignettes, heightVignettes);

	//Calcul des histos pour chaque vignette
	vector<vector<vector<int>>> histogramSet;
	histogramSet = histoSet(database);

	//Recherche de similarit� pour chaque vignette de l'image
	vector<Image> vignettesBase;
	vignettesBase = findSim(vignettes, widthVignettes, heightVignettes, database, histogramSet, nbCol, nbRow);

	//Reconstitution de l'image finale a partir des vignettes
	reassembleFinaleIm(baseImage, vignettesBase, nbRow, nbCol);

	//Enregistrement de l'image
	baseImage.save("save.jpg", baseImage.getBaseFormat());
	return 0;
}

