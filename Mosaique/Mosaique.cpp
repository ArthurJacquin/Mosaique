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
	cout << u8"Chemin de l'image � modifer ?" << "\n";
	cin >> imagePath;

	cout << u8"Chargement de l'image" << "\r";
	Image baseImage(imagePath.c_str());
	cout << u8"Image charg� avec succ�s !" << "\n";

	string databasePath;
	cout << u8"Chemin du dossier contenant la base de donn�es d'image ?" << "\n";
	cin >> databasePath;


	vector<Image> database;
	loadRegistre(database, databasePath.c_str());
	cout << u8"Base de donn�es charg� avec succ�s !" << "\n";



	
	/*imCompare.convert(HSV);
	diffVal(im, imCompare);
	cropTopLeft(imCompare);
	imCompare.convert(RGB);*/

	baseImage.save("save.jpg", baseImage.getBaseFormat());
	return 0;
}

