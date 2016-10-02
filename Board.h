#pragma once

#include "Color.h"
#include "Direction.h"
#include "Selector.h"
#include "Timer.h"
#include "GameDifficulty.h" 
#include <SFML\Graphics.hpp>
#include <vector>
#include <list>
#include <set>

struct SharedContext;
class Board
{
	friend class StateGame;
public:
	Board(SharedContext* sharedContext);
	~Board();

	bool hasBoardPos(const sf::Vector2f& pos) const;
	
	void rowToClear(const sf::Vector2f& pos)
	{
		m_pendingJewelsToErase = true;
		m_rowToClear = pos;
	}
	void update(const float deltaTime);

	bool entitiesMoving() const;
	int getStartXPos() const { return m_startXPos; }
	int getStartYPos() const { return m_startYPos; }
	int getIntervalXSize() const { return m_intervalXSize; }
	int getIntervalYSize() const { return m_intervalYSize; }

	void entityToBeRemoved() { m_entitiesToBeRemoved++; }
	void entityRemoved() { m_entitiesToBeRemoved--; if (!m_entitiesToBeRemoved) { m_updateBoardReady = true; } }
	void entityMoving() { m_entitiesMoving++; }
	inline void entityFinishedMoving()
	{
		if (m_entitiesMoving > 0) {
			--m_entitiesMoving;
		}
		if (!m_entitiesMoving) {
			m_updateBoardReady = true;
		}
	}
	//void entityFinishedMoving() { m_entitiesMoving--; if (!m_entitiesMoving) { m_combinationSearchReady = true; } }

private:
	std::vector<std::vector<sf::Vector2f>> m_positionOnBoard;
	std::vector<std::vector<bool>> m_filledPosition;

	int m_xSize; //X Axis size of board
	int m_ySize; //Y Axis size of board
	
	int m_minCombinationCount;

	int m_startXPos;
	int m_startYPos;

	int m_intervalXSize;
	int m_intervalYSize; 
	SharedContext* m_sharedContext;
	Timer m_spawnTimer;
	void init();
	void updateAllPos();
	void addToPosition(const unsigned int x, const unsigned int y);
	bool isBoardFull();

	bool m_combinationSearchReady;
	bool m_updateBoardReady;
	bool m_pendingJewelsToErase;
	sf::Vector2f m_rowToClear;
	unsigned int m_entitiesToBeRemoved;
	unsigned int m_entitiesMoving;

	void checkForCombination(const Color::Value color);
	inline void clearAtGrid(const int x, const int y);
	int searchForCombination(const int x, const int y, const Direction dir, const Color::Value color);
	void clearPartOfBoard(const int x, const int y, const int amount, const Direction dir);
	void clearRow();
	void replenishBoard(const float deltaTime);
	void initBoardPos(const GameDifficulty gameDifficulty);
};