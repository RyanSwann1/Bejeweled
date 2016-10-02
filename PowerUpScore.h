#pragma once
#include "JewelBase.h"
#include "JewelPowerUpBase.h"
class PowerUpScore :
	public JewelPowerUpBase
{

public:
	PowerUpScore(EntityManager* entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType, const sf::Vector2f& startPos);
	PowerUpScore(EntityManager* entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType);
	~PowerUpScore();

	

private:
	unsigned int m_minScoreAmount;
	unsigned int m_maxScoreAmount;

	void init();
};

