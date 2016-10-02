#pragma once

#include "ResourceManager.h"
#include "Utilities.h"
#include <SFML\Graphics.hpp>
#include <sstream>
#include <fstream>
#include <iostream>

class TextureManager
	: public ResourceManager<sf::Texture>
{
public:
	TextureManager(const std::string& fileName)
	{
		loadInResources(fileName);
	}

	~TextureManager()
	{
		purgeResources();
	}

	sf::Texture* loadFromFile(const std::string& id) override
	{
		sf::Texture* texture = new sf::Texture;
		auto iter = m_filePaths.find(id);
		if (iter != m_filePaths.cend())
		{
			if (!texture->loadFromFile(Utilities::getResourceLocation() + iter->second))
			{
				delete texture;
				texture = nullptr;
				return nullptr;
			}
			return texture;
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
		while(std::getline(file, line))
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