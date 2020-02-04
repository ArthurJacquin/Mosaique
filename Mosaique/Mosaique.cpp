#include <iostream>
#include "Image.h"
#include "Crop.h"
#include "Similirate.h"
#include "ImageTreatment.h"

using namespace std;

int main()
{
	string filename = "lenna.jpeg";
	Image im (filename.c_str());

	string filenameL = "licorne.jpg";
	Image imCompare(filenameL.c_str());

	vector<Image> baseImages;
	loadRegistre(baseImages);

	
	imCompare.convert(HSV);
	//TODO: Faire des trucs sur l'image
	diffVal(im, imCompare);
	//cropTopLeft(imCompare);
	imCompare.convert(RGB);

	imCompare.save("save.jpg", imCompare.getBaseFormat());
	return 0;
}

