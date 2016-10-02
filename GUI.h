#pragma once

#include "FontManager.h"
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <string>

struct GUI
{
	GUI(const sf::Vector2f& pos, const unsigned int charSize, FontManager* fontManager, const std::string& text = "");
	unsigned int m_characterSize;
	sf::Vector2f m_position;
	sf::Text m_text;
};

