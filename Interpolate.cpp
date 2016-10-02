#include "Interpolate.h"

Interpolate::Interpolate() :
	m_isActive(false),
	m_expirationTime(1.0f),
	m_timeElasped(0)
{
}

void Interpolate::activate()
{
	m_isActive = true;
	m_timeElasped = 0.0f;
}

void Interpolate::deactivate()
{
	//m_expirationTime = 1.0f;
	m_timeElasped = 0.0f;
	m_isActive = false;
}

sf::Vector2f Interpolate::interpolate(const sf::Vector2f & pointA, const sf::Vector2f & pointB, const float factor)
{
	return pointA + (pointB - pointA) * factor;
}

sf::Vector2f Interpolate::update(const sf::Vector2f& pointA, const sf::Vector2f& pointB, const float deltaTime)
{
	m_timeElasped += deltaTime;
	sf::Vector2f pos = interpolate(pointA, pointB, m_timeElasped);
	return pos;
}
