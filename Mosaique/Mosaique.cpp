#include <iostream>
#include "Image.h"

using namespace std;

int main()
{
	string filename = "test.jpg";
	Image im (filename.c_str());

	//TODO: Faire des trucs sur l'image

	im.save("save.jpg");
	return 0;
}

