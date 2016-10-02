#include "Game.h"

Game::Game()
//Initialization segment
	:m_window(&m_sharedContext, sf::Vector2u(700, 700), "Bejeweled"),
	m_textureManager("Textures.txt"),
	m_stateManager(&m_sharedContext),
	m_entityManager(&m_sharedContext),
	m_fontManager("Fonts.txt"),
	m_guiManager(&m_sharedContext),
	m_gameLogic(&m_sharedContext),
	m_gameTimer(0, 10)
{
	//Assignment segment
	m_sharedContext.m_textureManager = &m_textureManager;
	m_sharedContext.m_entityManager = &m_entityManager;
	m_sharedContext.m_stateManager = &m_stateManager;
	m_sharedContext.m_window = &m_window;
	m_sharedContext.m_gameLogic = &m_gameLogic;
	m_sharedContext.m_fontManager = &m_fontManager;
	m_sharedContext.m_guiManager = &m_guiManager;
	m_sharedContext.m_gameTimer = &m_gameTimer;
	
	m_guiManager.loadInInterfaces();
	m_stateManager.switchTo(StateType::DifficultySelector);
}

Game::~Game()
{	
}

void Game::update()
{
	m_stateManager.update(m_timeElasped.asSeconds());
	
	m_window.update();
}

void Game::render()
{
	m_window.beginDraw();
	
	m_stateManager.draw(m_window.getWindow());
	
	m_window.endDraw();
}

void Game::lateUpdate()
{
	m_timeElasped = m_clock.restart();
}
