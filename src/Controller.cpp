#include "Controller.h"
#include <iostream>

Controller::Controller()
	:	m_startMusic(SoundManager::instance().getStartMusic()),
		m_siren1(SoundManager::instance().getSiren1()),
		m_intermission(SoundManager::instance().getIntermission()),
		m_win(SoundManager::instance().getWin()),
		m_lose(SoundManager::instance().getLose()),
		m_mainMenu(MainMenu()),
		m_display(Display()), m_time(sf::Clock()),
		m_state(GameState::MENU) {}

void Controller::run()
{
	srand(static_cast<unsigned>(time(nullptr)));

	int levels = levelCount();
	
	// Loop of the program (Game States)
	while (true)
	{
		if (m_state == GameState::MENU)
			runMainMenu();
		else if (m_state == GameState::PLAY)
			runGame(levels);
		else if (m_state == GameState::LOST)
			lostGame();
		else if (m_state == GameState::WIN)
			winGame();
		else if(m_state == GameState::EXIT)
			return;
	}
}

// Run MainMenu window loop
void Controller::runMainMenu()
{
	auto menuWindow = m_display.openMenuDisplay();

	// Play intro music one time
	m_startMusic.play();

	setMouseCursor(menuWindow);

	while (menuWindow.isOpen())
	{
		// Clear window
		menuWindow.clear();

		// Get mouse position
		auto mPosition = menuWindow.mapPixelToCoords(sf::Mouse::getPosition(menuWindow));

		// MainMenu Event loop
		for (auto event = sf::Event{}; menuWindow.pollEvent(event); )
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					menuWindow.close();
					m_state = GameState::EXIT;
					return;
				case sf::Event::MouseButtonReleased:
					// click on apropirate object and change game state
					m_mainMenu.handleMouseInput(mPosition, m_state);
					// Check game state to enter requested option
					switch (m_state)
					{
						case GameState::PLAY:
							return;
						case GameState::HELP:
							runHelp();
							break;
						case GameState::EXIT:
							menuWindow.close();
						default:
							break;
					}
					break;
				case sf::Event::MouseMoved:
					// Handle hover above buttons
					m_mainMenu.handleMouseLocation(mPosition);
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
					{
						m_state = GameState::EXIT;
						return;
					}
				default:
					break;
			}
		}

		// Draw main menu on window
		m_mainMenu.drawMenu(menuWindow);

		// Display drawn objects
		menuWindow.display();
	}
}

// Run help window loop
void Controller::runHelp()
{
	auto helpWindow = m_display.openHelpDisplay();

	setMouseCursor(helpWindow);

	while (helpWindow.isOpen())
	{
		// Clear window
		helpWindow.clear();

		// Get mouse position
		auto mPosition = helpWindow.mapPixelToCoords(sf::Mouse::getPosition(helpWindow));

		for (auto event = sf::Event{}; helpWindow.pollEvent(event); )
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				helpWindow.close();
				break;
			case sf::Event::MouseButtonReleased:
				m_mainMenu.handleMouseInput(mPosition, m_state);
				// Check game state to enter requested option
				if (m_state == GameState::EXIT)
				{
					// Set state back to menu
					m_state = GameState::MENU;
					return;
				}
			case sf::Event::MouseMoved:
				// Handle hover above buttons
				m_mainMenu.handleMouseLocation(mPosition);
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_state = GameState::MENU;
					return;
				}
			}
		}

		// Draw Help window objects
		m_mainMenu.drawHelp(helpWindow);

		// Display drawn objects
		helpWindow.display();
	}
}

// Run Game loop
void Controller::runGame(const int levels)
{
	while (m_level <= levels)
	{
		auto m_board = GameBoard(m_level, m_points);

		auto runWindow = m_display.openGameDisplay(m_board.getWidth(), m_board.getHeight());

		setMouseCursor(runWindow);

		getReady(runWindow, m_board);

		// Set background sound of the game
		m_siren1.setLoop(true);
		m_siren1.play();

		// Reset time before starting the game
		m_time.restart();

		while (runWindow.isOpen() &&
			   m_board.getCookieAmount() > 0 &&
			   !m_board.isPlayerLost() && m_board.getTimeLeft() > 0.f)
		{
			runWindow.clear();

			// Draw board
			m_board.draw(runWindow);

			// Display drawn board
			runWindow.display();

			// Event loop
			for (auto event = sf::Event{}; runWindow.pollEvent(event); )
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					runWindow.close();
					m_state = GameState::MENU;
					m_level = 1;
					m_points = 0;
					m_siren1.stop();
					return;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
					{
						runWindow.close();
						m_state = GameState::MENU;
						m_level = 1;
						m_points = 0;
						m_siren1.stop();
						return;
					}
					// Set Direction
					m_board.setCharacterDirection(event.key.code);
					break;
				}
			}

			// Get the time that past since restart of time
			auto delta = m_time.restart();
			// Give all ghosts pacmans pos
			m_board.giveGhostPacmanPos();
			// Move characters
			m_board.moveCharacters(delta);
			// Handle Collisions if any
			m_board.handleCollisions();
			// If pacman is dead, reset positions and time
			if (m_board.isPacmanDead())
				m_time.restart();
			m_board.setBonuses();
			// Update Ui information
			m_board.updateUi();
		}

		// Check if game is lost
		if (isGameLost(m_board))
			return;

		// Continue to next level
		nextLevel(m_board);
	}
	// Finish game (WIN)
	m_state = GameState::WIN;
}

void Controller::getReady(sf::RenderWindow& runWindow, GameBoard& m_board)
{
	// Play the starting music
	if (m_level == 1)
		m_startMusic.play();
	else // Play intermission music between level changes
		m_intermission.play();

	// Get ready texture>sprite
	auto ready = sf::Sprite(TextureManager::instance().getReady());

	// Set position of the ready
	ready.setPosition(runWindow.getSize().x / 2.f - 77.f,
					  runWindow.getSize().y / 2.f);

	// Clear window
	runWindow.clear();
	// Draw all objects
	m_board.draw(runWindow);
	// Draw ready
	runWindow.draw(ready);
	// Display all
	runWindow.display();

	// While music plays..wait..
	while (m_startMusic.getStatus() == sf::Sound::Playing ||
		   m_intermission.getStatus() == sf::Sound::Playing)
	{
		// Wait...
	}

	// Restart timer so move func will work properly
	m_time.restart();
	// Add lost time while waiting
	m_board.addLostTime(5.f);
}

void Controller::setMouseCursor(sf::RenderWindow& window)
{
	sf::Sprite cursorSprite(TextureManager::instance().getCursor());

	// Set the Texture for the cursor exactly at the middle
	cursorSprite.setOrigin(
		sf::Vector2f(cursorSprite.getTexture()->getSize() / 2u));

	// Create a custom cursor using the sprite
	m_cursor.loadFromPixels(cursorSprite.getTexture()->copyToImage().getPixelsPtr(),
			   sf::Vector2u(cursorSprite.getTexture()->getSize()),
			   sf::Vector2u(cursorSprite.getOrigin()));

	window.setMouseCursor(m_cursor);
}

void Controller::nextLevel(const GameBoard& board)
{
	// Next level
	m_level++;
	// Save points to set to the next level
	m_points = board.getPoints();
	// Stop siren sound
	m_siren1.stop();
}

bool Controller::isGameLost(const GameBoard& board)
{
	// Lost game
	if (board.isPlayerLost() ||
		board.getTimeLeft() <= 0.f && board.getCookieAmount() > 0)
	{
		// Set State to lose, reset level and turn off siren
		m_state = GameState::LOST;
		m_level = 1;
		m_points = 0;
		m_siren1.stop();
		return true;
	}
	return false;
}

void Controller::lostGame()
{
	auto lostWindow = m_display.openLostDisplay();

	setMouseCursor(lostWindow);

	m_lose.play();

	while (lostWindow.isOpen())
	{
		lostWindow.clear();

		// Get mouse position
		auto mPosition = lostWindow.mapPixelToCoords(sf::Mouse::getPosition(lostWindow));

		for (auto event = sf::Event{}; lostWindow.pollEvent(event); )
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				lostWindow.close();
				m_state = GameState::MENU;
				// Maybe play music?
				return;
			case sf::Event::MouseButtonReleased:
				m_mainMenu.handleMouseInput(mPosition, m_state);
				if (m_state == GameState::EXIT)
				{
					m_state = GameState::MENU;
					return;
				}
			case sf::Event::MouseMoved:
				// Handle hover above buttons
				m_mainMenu.handleMouseLocation(mPosition);
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_state = GameState::MENU;
					return;
				}
			}
		}

		// Draw board
		m_mainMenu.drawLost(lostWindow);

		// Display drawn board
		lostWindow.display();
	}
}

void Controller::winGame()
{
	auto winWindow = m_display.openWinDisplay();

	setMouseCursor(winWindow);

	m_win.play();

	while (winWindow.isOpen())
	{
		winWindow.clear();

		// Get mouse position
		auto mPosition = winWindow.mapPixelToCoords(sf::Mouse::getPosition(winWindow));

		for (auto event = sf::Event{}; winWindow.pollEvent(event); )
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				winWindow.close();
				m_state = GameState::MENU;
				// Maybe play music?
				return;
			case sf::Event::MouseButtonReleased:
				m_mainMenu.handleMouseInput(mPosition, m_state);
				if (m_state == GameState::EXIT)
				{
					// Set first level and points for new game
					m_level = 1;
					m_points = 0;
					m_state = GameState::MENU;
					return;
				}
			case sf::Event::MouseMoved:
				// Handle hover above buttons
				m_mainMenu.handleMouseLocation(mPosition);
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_state = GameState::MENU;
					return;
				}
			}
		}

		// Draw board
		m_mainMenu.drawWin(winWindow, m_points);

		// Display drawn board
		winWindow.display();
	}
}

int Controller::levelCount()
{
	std::ifstream playList;
	std::string levelName;
	int levels = 0;

	playList.open("playlist.txt");
	if (!playList)
	{
		std::cerr << "Can't open playlist file\n";
		exit(EXIT_FAILURE);
	}

	// Count levels
	while (std::getline(playList, levelName))
		levels++;

	playList.close();

	return levels;
}