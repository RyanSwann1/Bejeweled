#pragma once
#include "JewelBase.h"
class JewelNormal :
	public JewelBase
{
public:
	JewelNormal(EntityManager* entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType);
	JewelNormal(EntityManager* entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType, const sf::Vector2f& startPos);
	~JewelNormal();

private:
	void init();
};

