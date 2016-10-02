#include "GameLogic.h"
#include "SharedContext.h"
#include <iostream>


GameLogic::GameLogic(SharedContext* sharedContext) :
	m_score(0),
	m_sharedContext(sharedContext),
	m_tempScore(0),
	m_timer(0.15f, 0),
	m_incrementScoreValue(1)
{ 
}

void GameLogic::addScore(unsigned int score)
{
	m_tempScore += score;
	m_timer.restart();
}

void GameLogic::resetScore()
{
	m_score = 0;
	m_tempScore = 0;
	std::cout << m_score << "\n";
}

void GameLogic::updateUI(const StateType stateType, const std::string& name, const std::string & text)
{
	GUI_Manager* guiManager = m_sharedContext->m_guiManager;

	guiManager->updateInterface(stateType, name, text);
}

void GameLogic::update(const float deltaTime)
{
	m_timer.update(deltaTime);

	if (m_tempScore > 0)
	{
		if (m_timer.isExpired())
		{
			m_tempScore -= m_incrementScoreValue;
			m_score += m_incrementScoreValue;
			m_sharedContext->m_guiManager->updateInterface(StateType::Game, "Score Text", "Score: " + std::to_string(m_score));
			m_timer.restart();
			std::cout << m_score << "\n";
		}
	}
}
