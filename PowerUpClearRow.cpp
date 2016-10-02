#include "PowerUpClearRow.h"
#include "SharedContext.h"

PowerUpClearRow::PowerUpClearRow(EntityManager * entityManager, std::pair<std::string, Color::Value>& color, const JewelType jewelType)
	: JewelPowerUpBase(entityManager, color, jewelType)
{
}

PowerUpClearRow::PowerUpClearRow(EntityManager * entityManager, std::pair<std::string, Color::Value>& color, const JewelType jewelType, const sf::Vector2f & newPos)
	: JewelPowerUpBase(entityManager, color, jewelType, newPos)
{
}

PowerUpClearRow::~PowerUpClearRow()
{
	clearRowOnBoard();
	std::cout << "Jewel Clear Row: Exited" << "\n";
}

void PowerUpClearRow::activate()
{
	clearRowOnBoard();
}

void PowerUpClearRow::clearRowOnBoard()
{
	m_entityManager->getSharedContext()->m_board->rowToClear(m_position);
}
