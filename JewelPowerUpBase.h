#pragma once
#include "JewelBase.h"
class JewelPowerUpBase :
	public JewelBase
{
public:
	JewelPowerUpBase(EntityManager* entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType, const sf::Vector2f& startPos);
	JewelPowerUpBase(EntityManager* entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType);
	virtual ~JewelPowerUpBase();
	

	virtual void activate() {} //Optionally activate the power up

private:
	void init();

};

