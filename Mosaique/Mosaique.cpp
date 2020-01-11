#include <iostream>
#include "Image.h"

using namespace std;

int main()
{
	string filename = "lenna.jpeg";
	Image im (filename.c_str());
	//TODO: Faire des trucs sur l'image

	im.save("save.jpg", im.getBaseFormat());
	return 0;
}

