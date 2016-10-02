#pragma once

#include "StateType.h"
#include "GUI.h"
#include "GUI_Interface.h"
#include <unordered_map>

struct SharedContext;
class GUI_Manager
{
	friend class Game;
	friend class GUI_Interface;
public:
	GUI_Manager(SharedContext* sharedContext);
	~GUI_Manager();

	bool setCurrentInterface(const StateType stateType);
	void addInterface(const StateType stateType, const GUI_Interface& gui);

	void draw(sf::RenderWindow& window);
	void updateInterface(const StateType stateType, const std::string& guiName, const std::string& text);
	
	GUI_Interface* getCurrentInterface() { return m_currentInterface; }
	SharedContext* getSharedContext() const { return m_sharedContext; }

private:
	std::unordered_map<StateType, GUI_Interface> m_interfaces;
	GUI_Interface* m_currentInterface;
	SharedContext* m_sharedContext;

	void loadInInterfaces();
};

