#include "StateManager.h"
#include "StateGame.h"
#include "StateDifficultySelector.h"

StateManager::StateManager(SharedContext* sharedContext)
	: m_sharedContext(sharedContext)
{
	registerState<StateGame>(StateType::Game);
	registerState<StateDifficultySelector>(StateType::DifficultySelector);
}


StateManager::~StateManager()
{

}

void StateManager::switchTo(const StateType type)
{
	if (!m_states.empty()) {
		m_states.back().second->onExit();
	}

	createState(type);
}

void StateManager::update(const float deltaTime)
{
	auto statesCopy = m_states;
	for (auto &i : statesCopy)
	{
		i.second->update(deltaTime);
	}

	processRemovals();
}

void StateManager::draw(sf::RenderWindow & window)
{
	//m_currentState->draw(window);
	for (auto &i : m_states)
	{
		i.second->draw(window);
	}
}

void StateManager::createState(const StateType type)
{
	auto iter = m_stateFactory.find(type);
	if (iter != m_stateFactory.cend())
	{
		m_states.emplace_back(iter->first, iter->second());
		m_states.back().second->onCreate();
		m_states.back().second->onEnter();
		m_stateCurrent = m_states.back().first;
		m_currentState = m_states.back().second;
	}
}

void StateManager::processRemovals()
{
	for (auto iter = m_removals.begin(); iter != m_removals.end();)
	{
		if (removedActiveState(*iter))
		{
			iter = m_removals.erase(iter);
		}
		else {
			++iter;
		}

	}
}

bool StateManager::removedActiveState(const StateType stateType)
{
	for (auto iter = m_states.begin(); iter != m_states.end();)
	{
		if (iter->first == stateType)
		{
			//iter->second->onExit();
			iter->second->onDestroy();
			m_states.erase(iter);
			return true;
		}
		else {
			++iter;
		}
	}
	return false;
}
