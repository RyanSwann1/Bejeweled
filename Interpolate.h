#pragma once

#include <SFML\Graphics.hpp>

class Interpolate
{
public:
	Interpolate();

	bool isActive() const { return m_isActive; }

	void activate();
	void deactivate();
	sf::Vector2f interpolate(const sf::Vector2f& pointA, const sf::Vector2f& pointB, const float factor);
	bool isExpired() const { return m_timeElasped >= m_expirationTime; }
	sf::Vector2f update(const sf::Vector2f& pointA, const sf::Vector2f& pointB, const float deltaTime);

private:
	float m_timeElasped;
	float m_expirationTime;
	bool m_isActive;
};

