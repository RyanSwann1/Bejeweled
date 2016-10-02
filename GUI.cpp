#include "GUI.h"
#include "GUI_Manager.h"
#include "Utilities.h"
#include "SharedContext.h"

GUI::GUI(const sf::Vector2f & pos, const unsigned int charSize, FontManager* fontManager, const std::string & text)
	: m_characterSize(charSize),
	m_position(pos)
{
	m_text.setString(text);
	m_text.setCharacterSize(m_characterSize);
	m_text.setPosition(m_position);
	if (fontManager->requireResource(Utilities::getFontName()))
	{
		//             Dereferencing the pointer
		//Get what the pointer is pointing to
		m_text.setFont(*fontManager->getResource(Utilities::getFontName()));
	}
}