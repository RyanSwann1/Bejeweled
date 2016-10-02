#include "GUI_Manager.h"
#include "SharedContext.h"


GUI_Manager::GUI_Manager(SharedContext* sharedContext)
	: m_sharedContext(sharedContext)
{
}

GUI_Manager::~GUI_Manager()
{
}

bool GUI_Manager::setCurrentInterface(const StateType stateType)
{
	auto iter = m_interfaces.find(stateType);
	if (iter != m_interfaces.cend())
	{
		m_currentInterface = &iter->second;
		return true;
	}
	return false;
}

void GUI_Manager::addInterface(const StateType stateType, const GUI_Interface & gui)
{
	if (m_interfaces.find(stateType) == m_interfaces.cend())
	{
		m_interfaces.insert(std::make_pair(stateType, gui));
	}
}

void GUI_Manager::draw(sf::RenderWindow & window)
{
	m_currentInterface->draw(window);
}

void GUI_Manager::updateInterface(const StateType stateType, const std::string & guiName, const std::string & text)
{
	for (auto &i : m_interfaces)
	{
		if (i.first == stateType)
		{
			i.second.update(guiName, text);
		}
	}
}

void GUI_Manager::loadInInterfaces()
{
	//Difficulty GUI
	std::vector<std::pair<std::string, GUI>> difficultySelectorUI;
	difficultySelectorUI.push_back(std::make_pair(std::string("Easy Text"), GUI(sf::Vector2f(100, 300), 24, m_sharedContext->m_fontManager, std::string("1. Easy"))));
	//difficultySelectorUI.push_back(std::make_pair(std::string("Medium Text"), GUI(sf::Vector2f(250, 300), 24, m_sharedContext->m_fontManager, std::string("2. Medium"))));
	difficultySelectorUI.push_back(std::make_pair(std::string("Hard Text"), GUI(sf::Vector2f(400, 300), 24, m_sharedContext->m_fontManager, std::string("2. Hard"))));


	//The game GUI
	std::vector<std::pair<std::string, GUI>> gameGUI;
	gameGUI.push_back(std::make_pair(std::string("Score Text"), GUI(sf::Vector2f(300, 100), 24, m_sharedContext->m_fontManager, std::string("Score: " + std::to_string(m_sharedContext->m_gameLogic->getScore())))));
	gameGUI.push_back(std::make_pair(std::string("Time Text"), GUI(sf::Vector2f(320, 480), 32, m_sharedContext->m_fontManager)));
	

	//Created a local scope 'GUI_Interface'
	//GUI_Interface gameInterface(this, gameGUI); 
	
	//Copy into the m_interfaces variable
	//All font variables are still pointing to the original one
	//When it goes out of scope, 

	//Create the game interface
	addInterface(StateType::DifficultySelector, GUI_Interface(this, difficultySelectorUI));
	addInterface(StateType::Game, GUI_Interface(this, gameGUI));

}