#include "JewelBase.h"
#include "EntityManager.h"
#include "SharedContext.h"



JewelBase::JewelBase(EntityManager * entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType)
	:Entity(entityManager)
{
	init(color, jewelType);
}

JewelBase::JewelBase(EntityManager * entityManager, const std::pair<std::string, Color::Value>& color, const JewelType jewelType, const sf::Vector2f & startPos)
	:Entity(entityManager)
{
	m_position = startPos;
	init(color, jewelType);
}

JewelBase::~JewelBase()
{
	Board* board = m_entityManager->getSharedContext()->m_board;
	board->entityFinishedMoving();
	board->entityRemoved();
	if (m_moving)
	{
		std::cout << "HAVENT STOPPED MOVING" << "\n";
	}

	std::cout << "Jewel Base: Exited" << "\n";
}

void JewelBase::move(const sf::Vector2f & newPos)
{
	m_newPos = newPos;
	m_interpolate.activate();
	if (!m_moving)
	{
		m_entityManager->getSharedContext()->m_board->entityMoving();
		m_moving = true;
	}	
}

void JewelBase::update(const float deltaTime)
{
	if (m_interpolate.isActive())
	{
		m_position = m_interpolate.update(m_position, m_newPos, deltaTime);
	}
	if (m_interpolate.isExpired())
	{
		m_entityManager->getSharedContext()->m_board->entityFinishedMoving();
		m_interpolate.deactivate();
		m_moving = false;
		std::cout << "Stopped Moving." << "\n";
	}
}

void JewelBase::applyTexture()
{
	TextureManager* textureManager = m_entityManager->getSharedContext()->m_textureManager;
	if (m_jewelType == JewelType::Normal)
	{
		if (textureManager->requireResource(m_textureName))
		{
			m_texture = textureManager->getResource(m_textureName);
			m_sprite.setTexture(*m_texture);
			m_sprite.setOrigin(m_texture->getSize().x / 2.0f, m_texture->getSize().y / 2.0f);
			m_sprite.setScale(0.7f, 0.7f);
		}
	}
	else if (m_jewelType == JewelType::PowerUp)
	{
		if (textureManager->requireResource(m_textureName + "_PowerUp"))
		{
			m_texture = textureManager->getResource(m_textureName + "_PowerUp");
			m_sprite.setTexture(*m_texture);
			m_sprite.setOrigin(m_texture->getSize().x / 2.0f, m_texture->getSize().y / 2.0f);
			m_sprite.setScale(0.7f, 0.7f);
		}
	}

}

void JewelBase::init(const std::pair<std::string, Color::Value>& color, const JewelType jewelType)
{
	m_jewelType = jewelType;
	m_textureName = color.first;
	m_colorValue = color.second;
	//m_sprite.setPosition(startPos);
	applyTexture();
	m_speed = .5f;
	m_moving = false;
	m_score = 0;
}
