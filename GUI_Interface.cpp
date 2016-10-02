#include "GUI_Interface.h"
#include "GUI_Manager.h"
#include "SharedContext.h"

//sf::Font GUI_Interface::m_font;

GUI_Interface::GUI_Interface(GUI_Manager* guiManager, const std::vector<std::pair<std::string, GUI>>& interface)
	: m_interface(interface),
	m_guiManager(guiManager)
{
	init();
}

GUI_Interface::~GUI_Interface()
{
	init();
}

void GUI_Interface::draw(sf::RenderWindow & window)
{
	for (auto &i : m_interface)
	{
		window.draw(i.second.m_text);
	}
}

void GUI_Interface::update(const std::string & guiName, const std::string & text)
{
	//Find matching GUI to update
	for (auto iter = m_interface.begin(); iter != m_interface.end(); iter++)
	{
		if (iter->first == guiName)
		{
			iter->second.m_text.setString(text);
		}
	}
}

void GUI_Interface::init()
{
	//FontManager* fontManager = m_guiManager->getSharedContext()->m_fontManager;
	//if (fontManager->requireResource(Utilities::getFontName()))
	//{
	//	m_font = *fontManager->getResource(Utilities::getFontName());
	//	std::cout << "h" << "\n";
	//}

	//for (auto &i : m_interface)
	//{
	//	i.second.m_text.setFont(m_font);
	//}
}