#pragma once
#include "JewelPowerUpBase.h"
class PowerUpClearRow :
	public JewelPowerUpBase
{
public:
	PowerUpClearRow(EntityManager* entityManager, std::pair<std::string, Color::Value>& color, const JewelType jewelType);
	PowerUpClearRow(EntityManager* entityManager, std::pair<std::string, Color::Value>& color, const JewelType jewelType, const sf::Vector2f& newPos);
	~PowerUpClearRow();

	void activate() override;

private:

	void clearRowOnBoard();
};

