#pragma once

#include "TextureManager.h"
#include "Board.h"
#include "EntityManager.h"
#include "StateManager.h"
#include "EventSystem.h" 
#include "Window.h"
#include "GameLogic.h"
#include "FontManager.h"
#include "GUI_Manager.h"
#include "Timer.h"

struct SharedContext
{
	SharedContext()
		: m_textureManager(nullptr),
		m_board(nullptr),
		m_entityManager(nullptr),
		m_stateManager(nullptr),
		m_eventSystem(nullptr),
		m_window(nullptr),
		m_gameLogic(nullptr),
		m_fontManager(nullptr),
		m_guiManager(nullptr),
		m_gameTimer(nullptr) {}

	TextureManager* m_textureManager;
	Board* m_board;
	EntityManager*  m_entityManager;
	StateManager* m_stateManager;
	EventSystem* m_eventSystem;
	Window* m_window;
	GameLogic* m_gameLogic;
	FontManager* m_fontManager;
	GUI_Manager* m_guiManager;
	Timer* m_gameTimer;
};