#include <iostream>
#include <Windows.h>
#include "Image.h"
#include "Crop.h"
#include "Similirate.h"
#include "ImageTreatment.h"


using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	string imagePath;
	cout << u8"Chemin de l'image à modifer ?" << "\n";
	cin >> imagePath;

	cout << u8"Chargement de l'image" << "\r";
	Image baseImage(imagePath.c_str());
	cout << u8"Image chargé avec succès !" << "\n";

	string databasePath;
	cout << u8"Chemin du dossier contenant la base de données d'image ?" << "\n";
	cin >> databasePath;


	vector<Image> database;
	loadRegistre(database, databasePath.c_str());
	cout << u8"Base de données chargé avec succès !" << "\n";



	
	/*imCompare.convert(HSV);
	diffVal(im, imCompare);
	cropTopLeft(imCompare);
	imCompare.convert(RGB);*/

	baseImage.save("save.jpg", baseImage.getBaseFormat());
	return 0;
}

