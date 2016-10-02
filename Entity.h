#pragma once

#include "Direction.h"
#include <SFML\Graphics.hpp>
#include <iostream>

enum class EntityType { Jewel, PowerUp, Selector };

class EntityManager;
class Entity
{
public:
	Entity(EntityManager* entityManager);
	virtual ~Entity();

	void setPosition(const sf::Vector2f& pos) { m_position = pos; }
	void setID(unsigned int id) { m_ID = id; std::cout << m_ID << "\n"; }

	sf::Vector2f getPos() const { return m_position; }
	EntityType getType() const { return m_type; }
	unsigned int getID() const { return m_ID; }

	virtual void move(const Direction dir) {}
	virtual void move(const sf::Vector2f& newPos) {}

	virtual void update(const float deltaTime) { m_timeElasped = deltaTime; }
	virtual void draw(sf::RenderWindow& window);

protected:
	sf::Vector2f m_oldPosition;
	sf::Vector2f m_position;
	sf::Texture* m_texture;
	sf::Sprite m_sprite;
	std::string m_textureName;
	EntityManager* m_entityManager;
	Direction m_direction;
	unsigned int m_ID;
	EntityType m_type;
	float m_timeElasped;
	float m_speed;
	virtual void applyTexture() {}
};

