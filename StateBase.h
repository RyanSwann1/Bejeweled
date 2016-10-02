#pragma once

#include <SFML\Graphics.hpp>
#include "StateType.h"

class StateManager;
class StateBase
{
public:
	StateBase(StateManager* stateManager)
		: m_stateManager(stateManager) {}
	virtual ~StateBase() {}


	virtual void onEnter() {}
	virtual void onExit() {}
	
	virtual void onCreate() {}
	virtual void onDestroy() {}

	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	StateManager* m_stateManager;
	StateType m_thisState;
};

