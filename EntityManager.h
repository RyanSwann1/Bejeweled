#pragma once

#include "Entity.h"
#include <list>
#include <vector>
#include <set>
#include <initializer_list>

struct SharedContext;
class EntityManager
{
public:
	EntityManager(SharedContext* sharedContext);
	~EntityManager();

	void add(Entity* entity);
	void removeEntity(unsigned int entityID); 
	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getEntityPosition(unsigned int entityID);
	Entity* getEntityAtPosition(const std::initializer_list<EntityType>& list, const sf::Vector2f& pos);
	bool isEntityAtPosition(const std::initializer_list<EntityType>& list, const sf::Vector2f& pos);

	void purgeEntities();
	SharedContext* getSharedContext() { return m_sharedContext; }

private:
	std::list<std::pair<unsigned int, Entity*>> m_entities;
	std::set<unsigned int> m_entitiesToRemove;
	unsigned int m_entityID;

	SharedContext* m_sharedContext;

	
	void processRemovals();
	void removeActiveEntity(const unsigned int ID);

};