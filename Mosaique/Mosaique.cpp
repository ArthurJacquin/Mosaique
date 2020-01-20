#include <iostream>
#include "Image.h"

using namespace std;

int main()
{
	string filename = "lenna.jpeg";
	Image im (filename.c_str());
	
	im.convert(HSV);
	//TODO: Faire des trucs sur l'image

	im.convert(RGB);

	im.save("save.jpg", im.getBaseFormat());
	return 0;
}

