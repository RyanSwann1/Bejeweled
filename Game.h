#pragma once

#include "SharedContext.h"
#include "Window.h"
#include "Board.h"
#include "TextureManager.h"
#include "StateManager.h"
#include "EntityManager.h"
#include "GameLogic.h"
#include "FontManager.h"
#include "GUI_Manager.h"
#include "Timer.h"

#include <SFML\System.hpp>

class Game
{
public:
	Game();
	~Game();
	
	void update();
	void render();
	void lateUpdate();

	bool isRunning() const { return m_window.m_window.isOpen(); }

private:
	SharedContext m_sharedContext;
	Window m_window;
	TextureManager m_textureManager;
	StateManager m_stateManager;
	EntityManager m_entityManager;
	GameLogic m_gameLogic;
	FontManager m_fontManager;
	GUI_Manager m_guiManager;

	Timer m_gameTimer;
	sf::Time m_timeElasped;
	sf::Clock m_clock;
};

