#pragma once
#include "Entity.h"
#include "Color.h"
#include "Interpolate.h"
#include "JewelType.h"

class JewelBase :
	public Entity
{
public:
	JewelBase(EntityManager* entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType);
	JewelBase(EntityManager* entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType, const sf::Vector2f& startPos);
	virtual ~JewelBase();

	Color::Value getColorValue() const { return m_colorValue; }
	JewelType getJewelType() const { return m_jewelType; }

	void move(const sf::Vector2f& newPos) override;
	void update(const float deltaTime) override;

protected:
	unsigned int m_score;

private:
	Color::Value m_colorValue;
	std::string m_colorName;

	bool m_moving;
	void applyTexture();
	bool m_finishedMovement;
	sf::Vector2f m_newPos;
	Interpolate m_interpolate;
	//COLOR - temp taken out
	JewelType m_jewelType;

	void init(const std::pair<std::string, Color::Value>& color, const JewelType jewelType);
};

