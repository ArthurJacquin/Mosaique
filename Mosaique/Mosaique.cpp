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

	string imageBisPath;
	cout << u8"Chemin de l'image à comparer ?" << "\n";
	cin >> imageBisPath;

	cout << u8"Chargement des images" << "\r";
	Image baseImage(imagePath.c_str());
	Image compareImage(imageBisPath.c_str());
	cout << u8"Images chargées avec succès !" << "\n";

	baseImage.convert(HSV);
	compareImage.convert(HSV);


	string databasePath;
	cout << u8"Chemin du dossier contenant la base de données d'image ?" << "\n";
	cin >> databasePath;

	vector<Image> database;
	loadRegistre(database, databasePath.c_str());
	cout << u8"Base de données chargée avec succès !" << "\n";

	baseImage.convert(RGB);
	compareImage.convert(RGB);
	
	/*imCompare.convert(HSV);
	diffVal(im, imCompare);
	cropTopLeft(imCompare);
	imCompare.convert(RGB);*/

	baseImage.save("save.jpg", baseImage.getBaseFormat());
	compareImage.save("saveBis.jpg", compareImage.getBaseFormat());
	return 0;
}

