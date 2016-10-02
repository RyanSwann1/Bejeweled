#include "Entity.h"



Entity::Entity(EntityManager* entityManager)
	: m_entityManager(entityManager),
	m_textureName(""),
	m_direction(Direction::None),
	m_ID(0)
{
	
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderWindow & window)
{
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
}
