#include "Board.h"
#include "Utilities.h"
#include "EntityManager.h"
#include "SharedContext.h"
#include "JewelBase.h"
#include "PowerUpClearRow.h"
#include "PowerUpScore.h"
#include "GameRules.h"
#include "JewelNormal.h"
#include <iostream>


Board::Board(SharedContext* sharedContext) 
	: m_minCombinationCount(3),
	m_intervalYSize(40),
	m_intervalXSize(40),
	m_sharedContext(sharedContext),
	m_entitiesToBeRemoved(0),
	m_entitiesMoving(0),
	m_combinationSearchReady(false),
	m_updateBoardReady(false),
	m_pendingJewelsToErase(false),
	m_spawnTimer(0.025f, 0)
{
	m_sharedContext->m_board = this;
}

Board::~Board()
{

}

bool Board::hasBoardPos(const sf::Vector2f & pos) const
{
	//Keep within bounds of board
	//if (pos.x <= -5.0f || pos.x >(m_startXPos * m_xSize)) {
	//	return false;
	//}
	for (unsigned int y = 0; y < m_ySize; y++)
	{
		for (unsigned int x = 0; x < m_xSize; x++)
		{
			if (m_positionOnBoard[y][x] == pos)
			{
				return true;
			}
		}
	}
	//If not found, return current pos
	return false;
}

void Board::checkForCombination(const Color::Value color)
{
	EntityManager* entityManager = m_sharedContext->m_entityManager;
	for (unsigned int y = 0; y < m_ySize; ++y)
	{
		for (unsigned int x = 0; x < m_xSize; ++x)
		{
			JewelBase* jewelBase = nullptr;
			//If entity at position is jewel or power up

			if (entityManager->isEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[y][x]))
			{
				//if (entityManager->getEntityAtPosition({ EntityType::Jewel }, m_positionOnBoard[y][x])) {
				//	entity = static_cast<Jewel*>(entityManager->getEntityAtPosition({ EntityType::Jewel }, m_positionOnBoard[y][x]));
				//}
				//else if (entityManager->getEntityAtPosition({ EntityType::Jewel }, m_positionOnBoard[y][x])) {
				//	entity = static_cast<PowerUp*>(entityManager->getEntityAtPosition({ EntityType::PowerUp }, m_positionOnBoard[y][x]));
				//}
				jewelBase = static_cast<JewelBase*>(entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[y][x]));
			
				if (jewelBase->getColorValue() == color)
				{
					//Reset the combination count upon direction change
					int combination = 0;
					//This makes my eyes water
					//Check right
					combination = searchForCombination(x, y, Direction::Right, color);
					if (combination >= m_minCombinationCount)
					{
						clearPartOfBoard(x, y, combination, Direction::Right);
					}

					combination = 0;
					//Check left
					combination = searchForCombination(x, y, Direction::Left, color);
					if (combination >= m_minCombinationCount)
					{
						clearPartOfBoard(x, y, combination, Direction::Left);
					}

					combination = 0;
					//Check up
					combination = searchForCombination(x, y, Direction::Up, color);
					if (combination >= m_minCombinationCount)
					{
						clearPartOfBoard(x, y, combination, Direction::Up);
					}

					combination = 0;
					//Check Down
					combination = searchForCombination(x, y, Direction::Down, color);
					if (combination >= m_minCombinationCount)
					{
						clearPartOfBoard(x, y, combination, Direction::Down);
					}
				}
			}
			//if (entityManager->getEntityAtPosition({ EntityType::Jewel }, sf::Vector2f(m_positionOnBoard[y][x])))
			//{
			//	Jewel* jewel = nullptr;
			//	jewel = static_cast<Jewel*>(entityManager->getEntityAtPosition({ EntityType::Jewel }, sf::Vector2f(m_positionOnBoard[y][x])));

			//	if (jewel && jewel->getColor() == color)
			//	{


			//		//After the painful checks
			//		//?

			//	}
			//}

		}
	}
}

void Board::clearAtGrid(const int x, const int y)
{
	EntityManager* entityManager = m_sharedContext->m_entityManager;
	entityManager->removeEntity(entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[y][x])->getID());
	//m_entitiesToBeRemoved++;
	m_filledPosition[y][x] = false;

	//Re arrange board
	//Cycle through each gap and attempt to fill all
}

int Board::searchForCombination(const int x, const int y, const Direction dir, const Color::Value color)
{
	EntityManager* entityManager = m_sharedContext->m_entityManager;
	int combinationCount = 0;
	
	switch (dir)
	{
	case(Direction::Left):
	{
		int tempX = x;
		while (entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[y][x]))
		{
			if (static_cast<JewelBase*>(entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[y][tempX]))->getColorValue() == color)
			{
				++combinationCount;
				if (tempX > 0) {
					--tempX;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		
		return combinationCount;
	}
	case(Direction::Right):
	{
		int tempX = x;

		while (entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[y][x]))
		{
			if (static_cast<JewelBase*>(entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[y][tempX]))->getColorValue() == color)
			{
				++combinationCount;
				if (tempX < m_xSize - 1) {
					++tempX;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		
		return combinationCount;
	}
	case(Direction::Up):
	{
		int tempY = y;
		while (entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[y][x]))
		{
			if (static_cast<JewelBase*>(entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[tempY][x]))->getColorValue() == color)
			{
				++combinationCount;
				if (tempY > 0) {
					--tempY;

				}
				else
				{
					break;
				}
			}
			else {
				break;
			}
		}
		
		return combinationCount;
	}
	case(Direction::Down):
	{
		int tempY = y;
		while (entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[y][x]))
		{
			if (static_cast<JewelBase*>(entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[tempY][x]))->getColorValue() == color)
			{
				++combinationCount;
				if (tempY < m_ySize - 1) {
					++tempY;

				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		return combinationCount;
	}
	}
	
	return combinationCount;
}

void Board::clearPartOfBoard(const int x, const int y, const int amount, const Direction dir)
{

	switch (dir)
	{
	case(Direction::Left):
	{
		unsigned int tempX = x;
		for (unsigned int i = 0; i < amount; ++i)
		{
			clearAtGrid(tempX, y);
			--tempX;
		}
		break;
	}
	case(Direction::Right):
	{
		unsigned int tempX = x;
		for (unsigned int i = 0; i < amount; ++i)
		{
			clearAtGrid(tempX, y);
			++tempX;
		}
		break;
	}
	case(Direction::Up):
	{
		unsigned int tempY = y;
		for (unsigned int i = 0; i < amount; ++i)
		{
			clearAtGrid(x, tempY);
			--tempY;
		}
		break;
	}
	case(Direction::Down):
	{
		unsigned int tempY = y;
		for (unsigned int i = 0; i < amount; ++i)
		{
			clearAtGrid(x, tempY);
			++tempY;
		}
		break;
	}
	}
}

void Board::clearRow()
{
	sf::Vector2f position;
	int yPos = 0;
	for (unsigned int y = 0; y < m_ySize; ++y)
	{
		for (unsigned int x = 0; x < m_xSize; ++x)
		{
			if (m_positionOnBoard[y][x] == m_rowToClear)
			{
				yPos = y;
				position = m_positionOnBoard[y][x];
			}
		}
	}

	EntityManager* entityManager = m_sharedContext->m_entityManager;
	for (unsigned int x = 0; x < m_xSize; ++x)
	{
		if (entityManager->isEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[yPos][x]))
		{
			sf::Vector2f entityPos = m_positionOnBoard[yPos][x];
			clearAtGrid(x, yPos);
		}
		//clear
	}
}

void Board::replenishBoard(const float deltaTime)
{

	//std::cout << m_entitiesToBeRemoved << "\n";
	if (m_updateBoardReady)
	{
		m_spawnTimer.update(deltaTime);
		//std::cout << m_spawnTimer.getElaspedTime() << "\n";

		if (m_spawnTimer.isExpired())
		{
			m_spawnTimer.restart();
			updateAllPos();
			if (isBoardFull())
			{
				m_updateBoardReady = false;
				m_combinationSearchReady = true;
			}

			//Once the board is filled, 
			//Allow The board to scan for potential combinations 


		}
	}
}

void Board::update(const float deltaTime)
{
	if (m_pendingJewelsToErase)
	{
		clearRow();
		m_pendingJewelsToErase = false;
		replenishBoard(deltaTime);
	}

	//Only check for combinations once all the entities have stopped their movement phase
	if (m_combinationSearchReady && !m_entitiesMoving)
	{
		for (unsigned int i = 0; i < static_cast<int>(Color::Value::Total); ++i)
		{
			checkForCombination(static_cast<Color::Value>(i));
		}
		m_combinationSearchReady = false;
	}

	replenishBoard(deltaTime);
	//Perfrom update all of board whilst there are empty grids
	//Hold vector of temporary open grid positions
	//if(!m_tempGrid.empty())
}

bool Board::entitiesMoving() const
{
	if (m_entitiesMoving > 0) {
		std::cout << "Entities moving." << m_entitiesMoving << "\n";
		return true;
	}
	else
	{
		std::cout << "Entities not Moving: " << m_entitiesMoving << "\n";
		return false;
		
	}
}

void Board::updateAllPos()
{
	EntityManager* entityManager = m_sharedContext->m_entityManager;

	for (int y = m_ySize - 1; y >= 0; --y)
	{
		for (int x = m_xSize - 1; x >= 0; --x)
		{
			//Deal with entites below the top row
			int topRow = 0;
			if (y > topRow)
			{
				int tempY = y;
				while (tempY > topRow)
				{
					if (!m_filledPosition[tempY][x])
					{
						sf::Vector2f currentPos = m_positionOnBoard[tempY][x]; //Current position in loop
						//sf::Vector2f newPos = sf::Vector2f(currentPos.x, currentPos.y - m_intervalYSize); //Position one grid higher than current

						//If entity is at position one higher than current
						if (m_filledPosition[((tempY) - 1)][x])
						{
							//Get and move down onto the current position
							Entity* entity = entityManager->getEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[((tempY)-1)][x]);
							if (!m_filledPosition[tempY][x] && entity)
							{
								m_filledPosition[((tempY)-1)][x] = false; //Old position of entity is empty

								entity->move(currentPos); //Move entity to new position
								m_filledPosition[tempY][x] = true; //new position is full
								//return;
							}
						}
						
					}
					--tempY;
				}
			}

			//std::cout << y << "\n";
			//Deal with entities on the top row
			if (y == topRow)
			{
				sf::Vector2f pos = m_positionOnBoard[y][x];
				if (!entityManager->isEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, pos))
				{
					
					m_filledPosition[y][x] = true;
					addToPosition(pos.x, pos.y);
					//return;
				}
				
			}
		}
	}
}


void Board::addToPosition(const unsigned int x, const unsigned int y)
{
	//sf::Vector2f pos = m_positionOnBoard[y][x];
	EntityManager* entityManager = m_sharedContext->m_entityManager;
	int randValue = Utilities::randomNumberGenerator(0, static_cast<int>(Color::Value::Total) - 1);
	
	int jewelTypeDecider = Utilities::randomNumberGenerator(0, GameRules::m_jewelTypeDecidingAmount); //Determines whehter to spawn power up or normal jewel

	//Spawn Power Up
	if (jewelTypeDecider > GameRules::m_chanceOfPowerUpSpawn)
	{
		int powerUpDecider = Utilities::randomNumberGenerator(0, GameRules::m_chanceOfSpecialPowerUpSpawn);
		if (powerUpDecider > GameRules::m_specialPowerUpDecidingAmount)
		{	
			entityManager->add(new PowerUpClearRow(entityManager, std::make_pair(std::string("BlueBall"), Color::Value::Blue), JewelType::PowerUp, sf::Vector2f(x, y)));
		}
		else 
		{
			entityManager->add(new PowerUpScore(entityManager, std::make_pair(Color::Name::m_colorNames[randValue],
				static_cast<Color::Value>(randValue)), JewelType::PowerUp, sf::Vector2f(x, y)));
		}
	}
	//Spawn jewel
	else
	{
		entityManager->add(new JewelNormal(entityManager, std::make_pair(Color::Name::m_colorNames[randValue], 
			static_cast<Color::Value>(randValue)), JewelType::Normal, sf::Vector2f(x, y)));
	}
	
}

bool Board::isBoardFull()
{
	//bool isBoardFull = true;
	//Search for any open positions and add them to the open position container to be dealt with later
	EntityManager* entityManager = m_sharedContext->m_entityManager;
	for (unsigned int y = 0; y < m_ySize; ++y)
	{
		for (unsigned int x = 0; x < m_xSize; ++x)
		{
			if (!m_filledPosition[y][x])
			{
				return false;
			}
			//Needs to scan by position to see if all entities have mopved to their correct positions
		/*	if(!entityManager->isEntityAtPosition({ EntityType::Jewel, EntityType::PowerUp }, m_positionOnBoard[y][x]))
			{
				return false;
			}*/
			//sf::Vector2f pos = m_positionOnBoard[y][x];
			//if (m_bo)
			//{
			//	//m_isBoardFull = ;
			//	//m_filledPosition[y][x] = true;
			//	return false;
			//}
			////else 
			////{
			////	m_filledPosition[y][x] = false;
			////}
		}
	}
	return true;
}

void Board::init()
{
	EntityManager* entityManager = m_sharedContext->m_entityManager;

	initBoardPos(m_sharedContext->m_gameLogic->getGameDifficulty());
	
	//Initialize the board
	int tempXPosition = m_startXPos;
	int tempYPosition = m_startYPos;
	for (unsigned int y = 0; y < m_ySize; ++y)
	{
		std::vector<sf::Vector2f> rowPos;
		std::vector<bool> fullRow;
		for (unsigned int x = 0; x < m_xSize; ++x)
		{
			addToPosition(tempXPosition, tempYPosition);
			rowPos.push_back(sf::Vector2f(tempXPosition, tempYPosition));
			fullRow.push_back(true);
			tempXPosition += m_intervalXSize;
		}
		tempXPosition = m_startXPos;
		tempYPosition += m_intervalYSize;
		m_positionOnBoard.push_back(rowPos);
		m_filledPosition.push_back(fullRow);
	}
}

void Board::initBoardPos(const GameDifficulty gameDifficulty)
{
	//Normal
	//: m_xSize(10),
	//	m_ySize(5),
	//	m_minCombinationCount(3),
	//	m_startXPos(160),
	//	m_startYPos(250),

	switch (gameDifficulty)
	{
	case (GameDifficulty::Easy) :
	{
		m_startXPos = 250;
		m_startYPos = 220;
		m_xSize = 5;
		m_ySize = 5;
		break;
	}
	case (GameDifficulty::Hard) :
	{
		m_startXPos = 150;
		m_startYPos = 220;
		m_xSize = 10;
		m_ySize = 5;
		break;
	}
	}
}
