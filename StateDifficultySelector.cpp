#include "StateDifficultySelector.h"
#include "EventSystem.h"
#include "SharedContext.h"

StateDifficultySelector::StateDifficultySelector(StateManager* stateManager)
	: StateBase(stateManager)
{
	m_thisState = StateType::DifficultySelector;
}

StateDifficultySelector::~StateDifficultySelector()
{
}

void StateDifficultySelector::onEnter()
{
	SharedContext* sharedContext = m_stateManager->getSharedContext();

	sharedContext->m_eventSystem->addCallback<StateDifficultySelector>(StateType::DifficultySelector, "Easy", &StateDifficultySelector::reactToInput, this);
	sharedContext->m_eventSystem->addCallback<StateDifficultySelector>(StateType::DifficultySelector, "Hard", &StateDifficultySelector::reactToInput, this);
	
	if (!sharedContext->m_guiManager->setCurrentInterface(m_thisState))
	{
		std::cerr << "Unable to set current interface: StateDifficultySelector." << "\n";
	}
}

void StateDifficultySelector::onExit()
{
	EventSystem* eventSystem = m_stateManager->getSharedContext()->m_eventSystem;
	eventSystem->removeCallback(m_thisState, "Easy");
	eventSystem->removeCallback(m_thisState, "Hard");
}

void StateDifficultySelector::onCreate()
{

}

void StateDifficultySelector::onDestroy()
{
}

void StateDifficultySelector::update(const float deltaTime)
{
}

void StateDifficultySelector::draw(sf::RenderWindow & window)
{
	m_stateManager->getSharedContext()->m_guiManager->draw(window);
}

void StateDifficultySelector::reactToInput(EventDetails * eventDetails)
{
	GameLogic* gameLogic = m_stateManager->getSharedContext()->m_gameLogic;

	if (eventDetails->m_name == "Easy") {
		gameLogic->setGameDifficulty(GameDifficulty::Easy);
		m_stateManager->switchTo(StateType::Game);
	}
	else if (eventDetails->m_name == "Hard") {
		gameLogic->setGameDifficulty(GameDifficulty::Hard);
		m_stateManager->switchTo(StateType::Game);
	}
}
