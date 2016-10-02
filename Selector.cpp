#include "Selector.h"
#include "SharedContext.h"
#include "Board.h"
#include "EntityManager.h"
#include "EventSystem.h"



Selector::Selector(EntityManager* entityManager)
	: Entity(entityManager),
	m_holdingJewel(false)
{
	m_textureName = "Selector";
	m_placedSelectorName = "PlacedSelector";
	
	Board* board = m_entityManager->getSharedContext()->m_board;
	m_position = sf::Vector2f(static_cast<float>(board->getStartXPos()), static_cast<float>(board->getStartYPos()));
	m_xMovement = board->getIntervalXSize();
	m_yMovement = board->getIntervalYSize();
	applyTexture();
	m_speed = 0.25f;
	m_type = EntityType::Selector;
	EventSystem* eventSystem = m_entityManager->getSharedContext()->m_eventSystem;
	eventSystem->addCallback<Selector>(StateType::Game, "Move_Left", &Selector::reactToInput, this);
	eventSystem->addCallback<Selector>(StateType::Game, "Move_Right", &Selector::reactToInput, this);
	eventSystem->addCallback<Selector>(StateType::Game, "Move_Up", &Selector::reactToInput, this);
	eventSystem->addCallback<Selector>(StateType::Game, "Move_Down", &Selector::reactToInput, this);
	eventSystem->addCallback<Selector>(StateType::Game, "Action_Button", &Selector::reactToInput, this);
}

Selector::~Selector()
{
	//Remove call backs
	EventSystem* eventSystem = m_entityManager->getSharedContext()->m_eventSystem;
	eventSystem->removeCallback(StateType::Game, "Move_Left");
	eventSystem->removeCallback(StateType::Game, "Move_Right");
	eventSystem->removeCallback(StateType::Game, "Move_Up");
	eventSystem->removeCallback(StateType::Game, "Move_Down");
	eventSystem->removeCallback(StateType::Game, "Action_Button");
}

void Selector::move(const Direction dir)
{
	if (!m_holdingJewel) {
		m_oldPosition = m_position;
	}
	
	Board* board = m_entityManager->getSharedContext()->m_board;

	switch (dir)
	{
	case (Direction::Left) :
	{
		if (board->hasBoardPos(sf::Vector2f(m_position.x - m_xMovement, m_position.y)))
		{
			m_position = sf::Vector2f((m_position.x -= m_xMovement), m_position.y);
			//m_interpolate.activate();
		}
		break;
	}
	case (Direction::Right) :
	{
		if (board->hasBoardPos(sf::Vector2f(m_position.x + m_xMovement, m_position.y)))
		{
			m_position = sf::Vector2f((m_position.x + m_xMovement), m_position.y);
			//m_interpolate.activate();
		}
		
		break;
	}
	case (Direction::Up) :
	{
		if (board->hasBoardPos(sf::Vector2f(m_position.x, m_position.y - m_yMovement)))
		{
			m_position = sf::Vector2f(m_position.x, (m_position.y - m_yMovement));
			//m_interpolate.activate();
		}
		break;
	}
	case (Direction::Down) :
	{
		if (board->hasBoardPos(sf::Vector2f(m_position.x, m_position.y + m_yMovement)))
		{
			m_position = sf::Vector2f(m_position.x, (m_position.y + m_yMovement));
			//m_interpolate.activate();
		}
		break;
	}
	}
	
}

void Selector::draw(sf::RenderWindow & window)
{
	m_sprite.setPosition(m_position);
	window.draw(m_sprite);
	if (m_holdingJewel)
	{
		m_placedSelector.setPosition(m_oldPosition);
		window.draw(m_placedSelector);
	}
}

void Selector::update(const float deltaTime)
{
	Entity::update(deltaTime);
	//if (m_interpolate.isActive())
	//{
	//	m_position = m_interpolate.update(m_position, m_newPos, m_timeElasped * 1.5f);
	//	if (m_interpolate.isExpired())
	//	{
	//		m_interpolate.deactivate();
	//	}
	//}
}

void Selector::applyTexture()
{
	TextureManager* textureManager = m_entityManager->getSharedContext()->m_textureManager;
	if (textureManager->requireResource(m_textureName))
	{
		m_texture = textureManager->getResource(m_textureName);
		m_sprite.setTexture(*m_texture);
		m_sprite.setOrigin(m_texture->getSize().x / 2.0f, m_texture->getSize().y / 2.0f);
	}

	if (textureManager->requireResource(m_placedSelectorName))
	{
		m_placedSelectorTexture = textureManager->getResource(m_placedSelectorName);
		m_placedSelector.setTexture(*m_placedSelectorTexture);
		m_placedSelector.setOrigin(m_placedSelectorTexture->getSize().x / 2.0f, m_placedSelectorTexture->getSize().y / 2.0f);
	}
}

void Selector::reactToInput(EventDetails * eventDetails)
{
	if (eventDetails->m_name == "Move_Left") {
		move(Direction::Left);
	}
	else if (eventDetails->m_name == "Move_Right") {
		move(Direction::Right);
	}
	else if (eventDetails->m_name == "Move_Up") {
		move(Direction::Up);
	}
	else if (eventDetails->m_name == "Move_Down") {
		move(Direction::Down);
	}
	else if (eventDetails->m_name == "Action_Button")
	{
		if (!m_holdingJewel) {
			selectJewel();
		}
		else {
			placeJewel();
		}
	}
}

void Selector::selectJewel()
{
	//Only allow to select jewel, not power up
	if (m_entityManager->isEntityAtPosition({ EntityType::Jewel }, m_position))
	{
		m_holdingJewel = true;
		m_oldPosition = m_position;
	}
}

void Selector::placeJewel()
{

	//Do not place at the same position as when picked up
	if (m_oldPosition == m_position) 
	{
		m_holdingJewel = false;
		return;
	}
	Board* board = m_entityManager->getSharedContext()->m_board;
	if(!board->entitiesMoving())
	{ 

		//Keep new jewel placement within a 1 movement radius from the original placement
		if (m_position.x <= (m_oldPosition.x + m_xMovement) && m_position.x >= (m_oldPosition.x - m_xMovement) &&
			m_position.y >= (m_oldPosition.y - m_yMovement) && m_position.y <= (m_oldPosition.y + m_yMovement))
		{
			Entity* entity1 = m_entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_oldPosition);
			Entity* entity2 = m_entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_position);

			//(currentTime - lastTime) / 1000.0f
			//Little Coding Fox : currentTime = 1000
			//	Little Coding Fox : lastTime = 500
			//	Little Coding Fox : (currentTime - lastTime) = 500
			//	Little Coding Fox : 500 / 1000.0f = 0.5
			//	Little Coding Fox : 0.5 seconds between last time and current time
			//Time between frames

			/*if (entity1->getType() == EntityType::PowerUp) {
			PowerUp* powerUp = static_cast<PowerUp*>(entity1);
			powerUp->activate();
			}*/

			//Move only if valid entities
			if (entity1 && entity2)
			{
				entity1->move(m_position);
				entity2->move(m_oldPosition);
			}

			m_holdingJewel = false;
		}
	}

	else
	{
		m_holdingJewel = false;
	}
}