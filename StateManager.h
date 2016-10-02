#pragma once

#include "StateBase.h"
#include "StateType.h"
#include <functional>
#include <unordered_map>
#include <string>
#include <vector>

struct SharedContext;
class StateManager
{
public:
	StateManager(SharedContext* sharedContext);
	~StateManager();

	void switchTo(const StateType type);
	SharedContext* getSharedContext() { return m_sharedContext; }
	void removeState(const StateType state) { m_removals.push_back(state); }

	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

	StateType getCurrentState() const { return m_stateCurrent; }

private:
	std::unordered_map<StateType, std::function<StateBase*()>> m_stateFactory;
	std::vector<std::pair<StateType, StateBase*>> m_states;
	std::vector<StateType> m_removals;
	SharedContext* m_sharedContext;
	StateType m_stateCurrent;
	StateBase* m_currentState;
	template <class T>
	void registerState(const StateType state)
	{
		m_stateFactory[state] = [this]() -> StateBase*
		{
			return new T(this);
		};
	}

	void createState(const StateType type);
	void processRemovals();
	bool removedActiveState(const StateType stateType);
};

