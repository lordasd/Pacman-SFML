#include "GameBoard.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Cookie.h"
#include "StaticObjects.h"
#include <iostream>
#include "Key.h"
#include "Door.h"

GameBoard::GameBoard(const int level, const int points)
	:	m_level(level), m_points(points),
		m_gameObjFactory(GameObjectFactory(points))
{
	// Open levels file
	openLevelFile();

	// If file empty quit
	if (!loadLevel())
	{
		std::cerr << "Level file is empty\n";
		exit(EXIT_FAILURE);
	}

	m_ui = Ui(m_rows * 50.f, level, points, m_levelTime);

	// Load all objects into a vector of objects
	loadObjects();
}

void GameBoard::checkCookieCollision(std::unique_ptr<GameObject>& obj,
								     std::unique_ptr<GameObject>& otherObj)
{
	if (auto pacman = dynamic_cast<Pacman*>(obj.get()))
		if (auto cookie = dynamic_cast<Cookie*>(otherObj.get()))
			if (cookie->isAvail())
				m_cookies--;
}

void GameBoard::openLevelFile()
{
	std::string levelname;

	// Open playlist of levels
	m_fin.open("playlist.txt");
	if (!m_fin)
	{
		std::cerr << "Can't open playlist file\n";
		exit(EXIT_FAILURE);
	}

	// Set level string apropriate to the m_level we got
	for (int i = 1; i <= m_level; ++i)
	{
		std::getline(m_fin, levelname);
		if (m_level == i) // Current level
			break;
	}
	// Close playlist
	m_fin.close();

	// Open the level file
	m_fin.open(levelname);
	if (!m_fin)
	{
		std::cerr << "Can't open level file\n";
		exit(EXIT_FAILURE);
	}
}

bool GameBoard::loadLevel()
{
	// If file is not empty / finished
	if (m_fin.peek() != std::ifstream::traits_type::eof())
	{
		// Clear board for next level
		m_board.clear();

		// Get the size of the board
		m_fin >> m_rows >> m_cols >> m_levelTime;
		std::string line;
		// Get all rows from the file
		std::getline(m_fin, line);
		while (std::getline(m_fin, line))
			m_board.push_back(line);
		// Close file
		m_fin.close();

		return true;
	}
	return false;
}

void GameBoard::loadObjects()
{
	for (int row = 0; row < m_rows; ++row)
	{
		for (int col = 0; col < m_cols; ++col)
		{
			// Get cookies count
			if (m_board[row][col] == '*')
				m_cookies++;

			// Get an object of the character on the board
			auto obj = m_gameObjFactory.createGameObject(
				m_board[row][col], sf::Vector2f((float)col * 50.f, (float)row * 50.f));
			
			// If not null
			if (obj)
			{
				// Check who is what and add to the apropriate vector
				if (dynamic_cast<MovingObjects*>(obj.get()) != nullptr)
					m_movingObjects.push_back(std::move(obj));
				else if(dynamic_cast<StaticObjects*>(obj.get()) != nullptr)
					m_staticObjects.push_back(std::move(obj));
			}
		}
	}
}

void GameBoard::draw(sf::RenderWindow& window)
{
	// Draw all objects in the window
	for (const auto& obj : m_staticObjects)
		obj->draw(window);
	for (const auto& obj : m_movingObjects)
		obj->draw(window);
	m_ui.draw(window);
}

float GameBoard::getWidth() const
{
	return m_cols;
}

float GameBoard::getHeight() const
{
	return m_rows;
}

void GameBoard::setCharacterDirection(sf::Keyboard::Key key)
{
	// Check if the key is an arrow key or space before setting
	if (key == sf::Keyboard::Up || key == sf::Keyboard::Down ||
		key == sf::Keyboard::Right || key == sf::Keyboard::Left ||
		key == sf::Keyboard::Space)
	{
		// Find pacman and set requested direction
		for (const auto& object : m_movingObjects)
		{
			if (auto pacman = dynamic_cast<Pacman*>(object.get()))
			{
				pacman->setDirection(key);
				return;
			}
		}
	}
}

void GameBoard::moveCharacters(sf::Time delta)
{
	// Find pacman and all ghosts and move them
	for (const auto& object : m_movingObjects)
	{
		if (auto movingobj = dynamic_cast<MovingObjects*>(object.get()))
		{
			movingobj->move(delta);
			movingobj->updateStayTexture(movingobj->getDirection());
		}
	}
}

void GameBoard::handleCollisions()
{
	// Iterate over all moving objects on the board
	for (auto& obj : m_movingObjects)
	{
		for (auto& otherObj : m_staticObjects) // Iterate over all static objects on the board
		{
			if (obj->getSprite().getGlobalBounds().intersects(otherObj->getSprite().getGlobalBounds()))
			{
				checkCookieCollision(obj, otherObj);
				obj->handleCollision(*otherObj);
			}
		}

		for(auto& otherObj : m_movingObjects)
			if (obj->getSprite().getGlobalBounds().intersects(otherObj->getSprite().getGlobalBounds()))
				obj->handleCollision(*otherObj);
	}

	// If key is collected, open door
	// If door broken, remove key
	isKeyDoorStatus();
}

int GameBoard::getCookieAmount() const
{
	return m_cookies;
}

bool GameBoard::isPacmanDead()
{
	for (const auto& obj : m_movingObjects)
	{
		if (auto pacman = dynamic_cast<Pacman*>(obj.get()))
		{
			if (pacman->getState() == PacmanState::Dead)
			{
				resetGamePositions();
				pacman->unDie();
				// Add lost 2 seconds while dying
				m_ui.saveTime(2.f);
				return true;
			}
			return false;
		}
	}
	return false;
}

void GameBoard::isKeyDoorStatus()
{  
	// Find door
	for (const auto& obj : m_staticObjects)
	{
		if (auto door = dynamic_cast<Door*>(obj.get()))
		{
			// find key
			for (const auto& otherObj : m_staticObjects)
			{
				if (auto key = dynamic_cast<Key*>(otherObj.get()))
				{
					// Key and door have same id
					if (door->getId() == key->getId())
					{	
						// Door close & Key picked up
						if (!key->isAvail() && door->isAvail())
						{	// Unshow door(Open door)
							door->unshow();
							return;
						} // Door destroyed & Key isn't picked up
						else if (!door->isAvail() && key->isAvail())
						{	// Unshow key
							key->unshow();
							return;
						}
						else
							break;
					}
					else
						continue;
				}
			}
		}
	}
}

bool GameBoard::isPlayerLost() const
{
	for (const auto& obj : m_movingObjects)
	{
		// Find pacman
		if (auto pacman = dynamic_cast<Pacman*>(obj.get()))
		{
			if (pacman->getLivesAmount() > 0)
				return false;
			break;
		}
	}
	return true;
}

void GameBoard::resetGamePositions()
{
	// Reset all moving objects positions to the starting positions
	for (const auto& obj : m_movingObjects)
		obj->setSpritesPositions(obj->getStartPosition());
}

void GameBoard::updateUi()
{
	// Find pacman
	for (const auto& obj : m_movingObjects)
	{
		// Set lives and points into ui
		if (auto pacman = dynamic_cast<Pacman*>(obj.get()))
		{
			m_ui.setHp(pacman->getLivesAmount());
			m_points = pacman->getPoints();
			m_ui.setPoints(m_points);
		}
	}
	// Set level number for ui
	m_ui.setLevel(m_level);
	m_ui.updateTime();
}

void GameBoard::giveGhostPacmanPos()
{
	// Find pacman
	for (const auto& obj : m_movingObjects)
	{
		if (auto pacman = dynamic_cast<Pacman*>(obj.get()))
		{
			// Find ghosts
			for (const auto& otherObj : m_movingObjects)
			{
				if (auto ghost = dynamic_cast<Ghost*>(otherObj.get()))
				{
					// Update ghost state if needed
					ghost->updateGhostState(*pacman);

					// Give the ghost pacman pos
					ghost->updatePositions(pacman->getPosition());
				}
			}
			return;
		}
	}
}

void GameBoard::setBonuses()
{
	// Find pacman
	for (const auto& movObj : m_movingObjects)
	{	
		// Check what bonus to enable
		if (auto pacman = dynamic_cast<Pacman*>(movObj.get()))
		{
			if (pacman->getBonusState() == BonusState::Super)
				pacman->setSuper();
			else if (pacman->getBonusState() == BonusState::Life)
				pacman->addLife();
			else if (pacman->getBonusState() == BonusState::Time)
				m_ui.addTime();
			else if (pacman->getBonusState() == BonusState::TimeFreeze)
				for (const auto& otherMovObj : m_movingObjects)
					if (auto ghost = dynamic_cast<Ghost*>(otherMovObj.get()))
						ghost->freeze();

			// Check Super bonus timer
			pacman->checkBonusTime();
			// Remove bonus state from pacman
			pacman->unsetBonus();
			return;
		}
	}
}

void GameBoard::addLostTime(float time)
{
	m_ui.saveTime(time);
}

float GameBoard::getTimeLeft() const
{
	return m_ui.getTimeLeft();
}

int GameBoard::getPoints() const
{
	return m_points;
}