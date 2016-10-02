#pragma once

#include "ResourceManager.h"
#include "Utilities.h"
#include <SFML\Graphics.hpp>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

class FontManager
	: public ResourceManager<sf::Font>
{
public:
	FontManager(const std::string& filePath)
	{
		loadInResources(filePath);
	}

	sf::Font* loadFromFile(const std::string& id)
	{
		sf::Font* font = new sf::Font;
		auto iter = m_filePaths.find(id);
		if (iter != m_filePaths.cend())
		{
			if (!font->loadFromFile(Utilities::getResourceLocation() + iter->second))
			{
				delete font;
				font = nullptr;
				return nullptr;
			}
			return font;
		}
		return nullptr;
	}

private:
	void loadInResources(const std::string& fileName)
	{
		std::ifstream file;
		file.open(Utilities::getResourceLocation() + fileName);
		if (!file.is_open())
		{
			std::cerr << "Failed to open file: " << fileName << "\n";
			return;
		}
		std::string line;
		while (std::getline(file, line))
		{
			std::stringstream keyStream(line);
			std::string name;
			std::string location;
			keyStream >> name >> location;
			m_filePaths.emplace(name, location);
		}
		file.close();
	}
};