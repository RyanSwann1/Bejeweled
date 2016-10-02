
#include "Game.h"
#include "Test.h"
#include "Utilities.h"
#include <SFML\Graphics.hpp>
#include <array>
#include <iostream>

//enum class Direction
//{
//	Right,
//	Left,
//	Up,
//	Down
//};
//
//enum class EntityType
//{
//	Red,
//	Green,
//	Yellow,
//	Blue,
//	Total,
//	None
//};
//
//EntityType chooseEntityType(const EntityType entityType)
//{
//	switch (entityType)
//	{
//	case (EntityType::Red) :
//	{
//		return EntityType::Red;
//		break;
//	}
//	case (EntityType::Green) :
//	{
//		return EntityType::Green;
//		break;
//	}
//	case (EntityType::Yellow) :
//	{
//		return EntityType::Yellow;
//		break;
//	}
//	case (EntityType::Blue) :
//	{
//		return EntityType::Blue;
//		break;
//	}
//	}
//}
//
//std::vector<std::vector<int>> m_board;
//std::vector<std::vector<EntityType>> m_entityBoard;
//const unsigned int x_Size = 10;
//const unsigned int y_Size = 5;
//const unsigned int m_minimalCombinationCount = 3;
//bool m_winnerFound = false;
//
//int searchForCombination(const unsigned int x, const unsigned int y, const Direction dir, const EntityType type)
//{
//	int combinationCount = 0; //Keep track of how many of the same entities have been detected
//	switch (dir)
//	{
//	case(Direction::Left) :
//	{
//		unsigned int tempX = x;
//		while (m_entityBoard[y][tempX] == type)
//		{
//			++combinationCount;
//			--tempX; 
//		}
//		return combinationCount;
//	}
//	case(Direction::Right) :
//	{
//		unsigned int tempX = x;
//		while (m_entityBoard[y][tempX] == type)
//		{
//			++combinationCount;
//			tempX++;
//		}
//		return combinationCount;
//	}
//	case(Direction::Up) :
//	{
//		unsigned int tempY = y;
//		while (m_entityBoard[tempY][x] == type)
//		{
//			++combinationCount;
//			--tempY;
//		}
//		return combinationCount;
//	}
//	case(Direction::Down) :
//	{
//		unsigned int tempY = y;
//		while (m_entityBoard[tempY][x] == type)
//		{
//			++combinationCount;
//			tempY++;
//		}
//		return combinationCount;
//	}
//	}
//}
//
//void clearPartOfBoard(const unsigned int x, const unsigned int y, const unsigned int amount, const Direction clearDir)
//{
//	switch (clearDir)
//	{
//	case(Direction::Left) :
//	{
//		unsigned int tempX = x;
//		for (unsigned int i = 0; i < amount; ++i)
//		{
//			m_entityBoard[y][tempX] = EntityType::None;
//			m_board[y][tempX] = 0;
//			tempX--;
//		}
//		break;
//	}
//	case(Direction::Right) :
//	{
//		unsigned int tempX = x;
//		for (unsigned int i = 0; i < amount; ++i)
//		{
//			m_entityBoard[y][tempX] = EntityType::None;
//			m_board[y][tempX] = 0;
//			++tempX;
//		}
//		break;
//	}
//	case(Direction::Up) :
//	{
//		unsigned int tempY = y;
//		for (unsigned int i = 0; i < amount; ++i)
//		{
//
//			//Update Entity board at same time of updating the normal board 
//			//Cast to entity - put in the sme function
//			m_entityBoard[tempY][x] = EntityType::None;
//			m_board[tempY][x] = 0;
//			--tempY;
//		}
//		break;
//	}
//	case(Direction::Down) :
//	{
//		unsigned int tempY = y;
//		for (unsigned int i = 0; i < amount; ++i)
//		{
//			m_entityBoard[tempY][x] = EntityType::None;
//			m_board[tempY][x] = 0;
//			++tempY;
//		}
//		break;
//	}
//	}
//}
//
////void manuallyCheckForCombination(const unsigned int x, const unsigned int y)
////{
////	EntityType type = m_entityBoard[y][x];
////	int combination = 0;
////	//This makes my eyes water
////	//Check right
////	combination = searchForCombination(x, y, Direction::Right, EntityType::Red);
////	if (combination >= m_minimalCombinationCount)
////	{
////		clearPartOfBoard(x, y, combination, Direction::Right);
////		combination = 0;
////	}
////	//Check left
////	combination = searchForCombination(x, y, Direction::Left, EntityType::Red);
////	if (combination >= m_minimalCombinationCount)
////	{
////		clearPartOfBoard(x, y, combination, Direction::Left);
////		combination = 0;
////	}
////	//Check up
////	combination = searchForCombination(x, y, Direction::Up, EntityType::Red);
////	if (combination >= m_minimalCombinationCount)
////	{
////		clearPartOfBoard(x, y, combination, Direction::Up);
////		combination = 0;
////	}
////	//Check Down
////	combination = searchForCombination(x, y, Direction::Down, EntityType::Red);
////	if (combination >= m_minimalCombinationCount)
////	{
////		clearPartOfBoard(x, y, combination, Direction::Down);
////		combination = 0;
////	}
////}
//
////This happens after the players go
//void checkForCombination()
//{
//	//Send in an arguement of the entity type the user is currently checking
//	
//	//Alternative to this is selecting a specific entity colour
//	//Then sending that in as an arguement 
//	//Instead of specifying each entity type specifically
//
//	for (unsigned int y = 0; y < y_Size; y++)
//	{
//		for (unsigned int x = 0; x < x_Size; x++)
//		{
//			if (m_entityBoard[y][x] == EntityType::Red)
//			{
//				int combination = 0;
//				//This makes my eyes water
//				//Check right
//				combination = searchForCombination(x, y, Direction::Right, EntityType::Red);
//				if(combination >= m_minimalCombinationCount)
//				{ 
//					clearPartOfBoard(x, y, combination, Direction::Right);
//					combination = 0;
//				}
//				//Check left
//				combination = searchForCombination(x, y, Direction::Left, EntityType::Red);
//				if (combination >= m_minimalCombinationCount)
//				{
//					clearPartOfBoard(x, y, combination, Direction::Left);
//					combination = 0;
//				}
//				//Check up
//				combination = searchForCombination(x, y, Direction::Up, EntityType::Red);
//				if (combination >= m_minimalCombinationCount)
//				{
//					clearPartOfBoard(x, y, combination, Direction::Up);
//					combination = 0;
//				}
//				//Check Down
//				combination = searchForCombination(x, y, Direction::Down, EntityType::Red);
//				if (combination >= m_minimalCombinationCount)
//				{
//					clearPartOfBoard(x, y, combination, Direction::Down);
//					combination = 0;
//				}
//
//				//After the painful checks
//				//?
//	
//			}
//		}
//	}
//}
//
//void chooseBoardPos()
//{
//	std::cout << "Choose y pos" << "\n";
//	unsigned yPos = 0;
//	std::cin >> yPos;
//
//	std::cout << "Choose x pos" << "\n";
//	unsigned int xPos = 0;
//	std::cin >> xPos;
//
//	std::cout << "Choose direction" << "\n";
//	unsigned int direction = 0;
//	std::cin >> direction;
//	Direction dir = static_cast<Direction>(direction);
//
//	EntityType type = m_entityBoard[yPos][xPos];
//
//	int combinationAmount = searchForCombination(xPos, yPos, dir, type);
//	if (combinationAmount >= m_minimalCombinationCount)
//	{
//		clearPartOfBoard(xPos, yPos, combinationAmount, dir);
//	}
//	else
//	{
//		std::cout << "Combination Amount: " << combinationAmount << "\n";
//	}
//}
//
////
////void chooseBoardPos()
////{
////
////	std::cout << "Choose x pos" << "\n";
////	unsigned int xPos = 0;
////	std::cin >> xPos;
////
////	std::cout << "Choose y pos" << "\n";
////	unsigned yPos = 0;
////	std::cin >> yPos;
////
////	std::cout << "Choose entity Type" << "\n";
////	unsigned int type = 0;
////	std::cin >> type;
////
////	m_entityBoard[yPos][xPos] = chooseEntityType(static_cast<EntityType>(type));
////	m_board[yPos][xPos] = type;
////}
//
//void displayBoard()
//{
//	for (unsigned int y = 0; y < y_Size; y++)
//	{
//		for (unsigned int x = 0; x < x_Size; x++)
//		{
//			std::cout << m_board[y][x];
//		}
//		std::cout << "\n";
//	}
//}
//
//void fillBoard()
//{
//	//Fill normal board
//	for (unsigned int y = 0; y < y_Size; ++y)
//	{
//		std::vector<int> row;
//		std::vector<EntityType> entityRow;
//		for (unsigned int x = 0; x < x_Size; ++x)
//		{
//			int randNumb = Utilities::randomNumberGenerator(0, static_cast<int>(EntityType::Total) - 1);
//
//			row.push_back(randNumb);
//			EntityType type = static_cast<EntityType>(randNumb);
//			entityRow.push_back(type);
//		}
//
//		m_board.push_back(row);
//		m_entityBoard.push_back(entityRow);
//	}
//}

//http://www.jobsite.co.uk/job/956698990?&utm_medium=aggregator&utm_source=indeedSponsored&utm_campaign=PSD&cid=msearche_indeedSponsored___PSD_ 
//http://www.jobsite.co.uk/job/956695784?src=apply-confirm&jobTile=listing-3&v96=ssr&noret=1
//http://stackoverflow.com/questions/16508018/running-multiple-functions-at-the-same-time

#define number = 4234;
//https://github.com/vurtun/nuklear/blob/master/example/canvas.c

//afronym: emplace_back:
//afronym: 1) allocate memory for the new element
//afronym: 2) call the appropriate constructor, with the new instance being located in the memory we just allocated
//afronym: push_back:
//afronym: 1) allocate memory for the new element
//afronym: 2) copy the element into the memory we just allocated
//afronym: (using the copy constructor)
//

int iAMANINT;
int main()
{
	//Game game;
	//while (game.isRunning())
	//{
	//	game.update();
	//	game.render();
	//	game.lateUpdate();
	//}
	//const std::size_t size = 5;
	//std::array<std::array<int, size>, size> board = { {
	//	{ 1, 1, 1, 1, 1 },
	//	{ 2, 2, 2, 2, 2 },
	//	{ 3, 3, 3, 3, 3 },
	//	{ 4, 4, 4, 4, 4 },
	//	{ 5, 5, 5, 5, 5 }
	//} };
	//for (unsigned int x = 0; x < size; x++)
	//{
	//	for (unsigned int y = 0; y < size; y++)
	//	{
	//		std::cout << board[x][y];
	//	}
	//	std::cout << "\n";
	//}

	Game game;
	while (game.isRunning())
	{
		game.update();
		game.render();
		game.lateUpdate();
	}

	//int numb = 0;
	//std::cout << numb;
	//TestClass test;
	//std::cout << test.getNumb() << "\n";
	char c;
	std::cin >> c;
	return 0;
}


//Must make all 

//newPos rejected movement
//if(!move(oldPos, newPos)
//{
	//MoveBack
//}

//make the entities slide down 
//if(currentPosType == 0) 
//{
	//if(m_entityPOs > 0) 
		//m_entity.move(Down);
	//else
		//Spawn new entity at 0
//}