#include "JewelNormal.h"
#include "SharedContext.h"



JewelNormal::JewelNormal(EntityManager * entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType)
	:JewelBase(entityManager, color, jewelType)
{
	init();
}

JewelNormal::JewelNormal(EntityManager * entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType, const sf::Vector2f & startPos)
	: JewelBase(entityManager, color, jewelType, startPos)
{
	init();
}

JewelNormal::~JewelNormal()
{
	GameLogic* gameLogic = m_entityManager->getSharedContext()->m_gameLogic;
	GUI_Manager* guiManager = m_entityManager->getSharedContext()->m_guiManager;

	gameLogic->addScore(m_score);
	//guiManager->updateInterface(StateType::Game, "Score Text", std::string("Score: " + std::to_string(gameLogic->getScore())));
	std::cout << "Jewel Normal: Exited" << "\n";
}

void JewelNormal::init()
{
	m_type = EntityType::Jewel;
	m_score = 1;
}
