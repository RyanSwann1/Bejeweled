#pragma once

#include "GUI.h"
#include <vector>

class GUI_Manager;
class GUI_Interface
{
public:
	GUI_Interface() {}
	GUI_Interface(GUI_Manager* guiManager, const std::vector<std::pair<std::string, GUI>>& interface);
	~GUI_Interface();

	void loadInInterface(const std::vector<GUI>& interface);

	void draw(sf::RenderWindow& window);
	void update(const std::string& guiName, const std::string& text);

private:
	//The static variable is initialized before main is
	//Goes out of scope when the program ends
	//sf::Font m_font;
	std::vector<std::pair<std::string, GUI>> m_interface;
	GUI_Manager* m_guiManager;

	void init();
};

