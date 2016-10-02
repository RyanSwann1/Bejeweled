#include "JewelPowerUpBase.h"

JewelPowerUpBase::JewelPowerUpBase(EntityManager * entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType, const sf::Vector2f & startPos)
	: JewelBase(entityManager, color, jewelType, startPos)
{
	init();
}

JewelPowerUpBase::JewelPowerUpBase(EntityManager * entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType)
	: JewelBase(entityManager, color, jewelType)
{
	init();
}

JewelPowerUpBase::~JewelPowerUpBase()
{
	std::cout << "Jewel Power Up Base: Exited" << "\n";
}

void JewelPowerUpBase::init()
{
	m_type = EntityType::PowerUp;
}
