#pragma once
#include "StateBase.h"
struct EventDetails;
class StateDifficultySelector :
	public StateBase
{
public:
	StateDifficultySelector(StateManager* stateManager);
	~StateDifficultySelector();

	void onEnter() override;
	void onExit() override;

	void onCreate() override;
	void onDestroy() override;

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

private:
	void reactToInput(EventDetails* eventDetails);
	
};

