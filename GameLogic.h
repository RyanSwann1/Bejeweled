#pragma once

//namespace SpawnTiming
//{
//	int 
//}
#include "StateType.h"
#include "GameDifficulty.h"
#include "Timer.h"
#include <string>

struct SharedContext;
class GameLogic
{
public:
	GameLogic(SharedContext* sharedContext);

	void addScore(unsigned int score);
	void resetScore();
	unsigned int getScore() const { return m_score; }
	GameDifficulty getGameDifficulty() const { return m_gameDifficulty; }
	void setGameDifficulty(const GameDifficulty gameDifficulty) { m_gameDifficulty = gameDifficulty; }

	void updateUI(const StateType stateType, const std::string& name, const std::string& text);
	void update(const float deltaTime);

private:
	unsigned int m_score;
	unsigned int m_tempScore;
	unsigned int m_incrementScoreValue;
	SharedContext* m_sharedContext;
	GameDifficulty m_gameDifficulty;
	Timer m_timer;
};

