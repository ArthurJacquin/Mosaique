#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include "Image.h"

namespace fs = std::experimental::filesystem;

void loadRegistre(vector<Image>& images, string folderPath)
{
	auto directory = std::experimental::filesystem::directory_iterator(folderPath.c_str());
	float imageTreated = 0;
	float nbOfFiles = 0;

	for (const auto& entry : directory)
		nbOfFiles++;

	directory = std::experimental::filesystem::directory_iterator(folderPath.c_str());

	for (const auto& entry : directory)
	{
		int pourcentage = 100 * (imageTreated / nbOfFiles);
		std::cout << "Chargement des images : " << pourcentage << "%" << '\r';
		Image im(entry.path().u8string().c_str());
		images.push_back(im);
		imageTreated++;
	}
}
