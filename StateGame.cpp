#include "StateGame.h"
#include "StateManager.h"
#include "SharedContext.h"
#include "EntityManager.h"
#include "GUI_Manager.h"
#include <assert.h>
#include <iostream>

StateGame::StateGame(StateManager* stateManager)
	: StateBase(stateManager),
	m_board(stateManager->getSharedContext())
{
	m_thisState = StateType::Game;
}

StateGame::~StateGame()
{
}

void StateGame::onEnter()
{
	SharedContext* sharedContext = m_stateManager->getSharedContext();
	m_board.init(); //Initialize the board
	sharedContext->m_entityManager->add(new Selector(sharedContext->m_entityManager));
	sharedContext->m_gameLogic->resetScore();

	if (!sharedContext->m_guiManager->setCurrentInterface(StateType::Game))
	{
		std::cerr << "Unable to switch to interface: StateType::Game" << "\n";
	}
	sharedContext->m_guiManager->updateInterface(StateType::Game, "Score Text", std::string("Score: " + sharedContext->m_gameLogic->getScore()));
}

void StateGame::onExit()
{
	
}

void StateGame::onCreate()
{

}

void StateGame::onDestroy()
{
	m_stateManager->getSharedContext()->m_entityManager->purgeEntities();
}

void StateGame::update(const float deltaTime)
{
	SharedContext* sharedContext = m_stateManager->getSharedContext();
	sharedContext->m_entityManager->update(deltaTime);
	sharedContext->m_board->update(deltaTime);
	sharedContext->m_gameTimer->update(-deltaTime);
	sharedContext->m_gameLogic->update(deltaTime);

	sharedContext->m_guiManager->updateInterface(StateType::Game, "Time Text", std::to_string(static_cast<int>(sharedContext->m_gameTimer->getElaspedTime())));

	if (sharedContext->m_gameTimer->isExpired())
	{
		m_stateManager->switchTo(StateType::DifficultySelector);
		sharedContext->m_stateManager->removeState(StateType::Game);
		sharedContext->m_gameTimer->restart();
	}
}

void StateGame::draw(sf::RenderWindow & window)
{
	SharedContext* sharedContext = m_stateManager->getSharedContext();
	sharedContext->m_entityManager->draw(window);
	sharedContext->m_guiManager->draw(window);
}