#include "PowerUpScore.h"
#include "Utilities.h"
#include "SharedContext.h"

PowerUpScore::PowerUpScore(EntityManager * entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType, const sf::Vector2f & startPos)
	: JewelPowerUpBase(entityManager, color, jewelType, startPos)
{
	init();
}

PowerUpScore::PowerUpScore(EntityManager * entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType)
	: JewelPowerUpBase(entityManager, color, jewelType)
{
	init();
}

PowerUpScore::~PowerUpScore()
{
	//m_entityManager->getSharedContext()->m_gameLogic->addScore(m_score);

	GameLogic* gameLogic = m_entityManager->getSharedContext()->m_gameLogic;
	GUI_Manager* guiManager = m_entityManager->getSharedContext()->m_guiManager;

	gameLogic->addScore(m_score);
	//guiManager->updateInterface(StateType::Game, "Score Text", std::string("Score: " + std::to_string(gameLogic->getScore())));
	std::cout << "Jewel Power Up Score: Exited" << "\n";
}

void PowerUpScore::init()
{
	m_minScoreAmount = 5;
	m_maxScoreAmount = 20;
	m_score = Utilities::randomNumberGenerator(m_minScoreAmount, m_maxScoreAmount);
}
