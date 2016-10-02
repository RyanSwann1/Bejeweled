#include "EntityManager.h"
#include "SharedContext.h"
#include <algorithm>

EntityManager::EntityManager(SharedContext* sharedContext)
	: m_sharedContext(sharedContext),
	m_entityID(0)
{
}

EntityManager::~EntityManager()
{
	purgeEntities();
}

//if const causes error
void EntityManager::add(Entity* entity)
{
	entity->setID(m_entityID);
	m_entities.emplace_back(std::make_pair(m_entityID, entity));
	
	m_entityID++;
}

void EntityManager::removeEntity(unsigned int entityID)
{
	//New way
	if (m_entitiesToRemove.find(entityID) == m_entitiesToRemove.cend())
	{
		m_entitiesToRemove.emplace(entityID);
		m_sharedContext->m_board->entityToBeRemoved();
	}
	////Old way
	//bool addEntity = true;
	//for (auto &i : m_entitiesToBeRemoved)
	//{
	//	if (i == entityID) {
	//		addEntity = false;
	//	}
	//}
	//if (addEntity) {
	//	m_entitiesToBeRemoved.push_back(entityID);
	//}
	//else {
	//	return;
	//}
}

void EntityManager::update(const float deltaTime)
{
	auto entitiesCopy = m_entities;
	for (auto &i : entitiesCopy)
	{
		i.second->update(deltaTime);
	}

	processRemovals();
}

void EntityManager::draw(sf::RenderWindow & window)
{
	for (auto &i : m_entities)
	{
		i.second->draw(window);
	}
}

//std::list<std::pair<unsigned int, Entity*>> m_entities;
sf::Vector2f EntityManager::getEntityPosition(unsigned int entityID)
{
	//auto iter = std::find_if(m_entities.begin(), m_entities.end(), [entityID](std::pair<unsigned int, Entity*>& pair) {return pair.second->getID() == entityID; });
	//if (iter != m_entities.cend())
	//{
	//	return iter->second->getPos();
	//}

	//for (auto cIter = m_entities.cbegin(); cIter != m_entities.cend(); cIter++)
	//{
	//	if (cIter->second->getID() == entityID)
	//	{
	//		return cIter->second->getPos();
	//	}
	//}
	return sf::Vector2f();
}


Entity * EntityManager::getEntityAtPosition(const std::initializer_list<EntityType>& list, const sf::Vector2f & pos)
{
	for (auto iter = m_entities.begin(); iter != m_entities.end(); iter++)
	{
		for (auto &type : list)
		{
			if (iter->second->getType() == type && iter->second->getPos() == pos)
			{
				return iter->second;
			}
		}
	}
	return nullptr;
}

bool EntityManager::isEntityAtPosition(const std::initializer_list<EntityType>& list, const sf::Vector2f & pos)
{
	//Have the ability to scan for multiple entities at the same position at the same time - >:D
	for (auto iter = m_entities.cbegin(); iter != m_entities.cend(); ++iter)
	{
		for (auto &type : list)
		{
			if (iter->second->getType() == type && iter->second->getPos() == pos)
			{
				return true;
			}
		}
	}
	return false;
}


void EntityManager::purgeEntities()
{
	for (auto &i : m_entities)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_entities.clear();
}

void EntityManager::processRemovals()
{
	for (auto &i : m_entitiesToRemove)
	{
		removeActiveEntity(i);
	}
	m_entitiesToRemove.clear();
	
}

void EntityManager::removeActiveEntity(const unsigned int ID)
{
	for (auto iter = m_entities.begin(); iter != m_entities.end(); iter++)
	{
		if (iter->second->getID() == ID)
		{
			delete iter->second;
			iter->second = nullptr;	
			m_entities.erase(iter);
			return;
		}
	}
}