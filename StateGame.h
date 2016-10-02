#pragma once
#include "StateBase.h"
#include "Board.h"

class StateGame :
	public StateBase
{
public:
	StateGame(StateManager* stateManager);
	~StateGame();

	void onEnter() override;
	void onExit() override;

	void onCreate() override;
	void onDestroy() override;

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

private:
	Board m_board;
	
};

