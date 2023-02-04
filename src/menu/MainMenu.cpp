#include "MainMenu.h"

MainMenu::MainMenu()
	:	m_menuSprite(TextureManager::instance().getMainMenu()),
		m_helpSprite(TextureManager::instance().getHelpWindow()),
		m_winSprite(TextureManager::instance().getWin()),
		m_lostSprite(TextureManager::instance().getLost()),
		m_playh(false), m_helph(false), m_exith(false),
		m_select(SoundManager::instance().getSelect())
{
	// Insert item objects into a vector of menu items
	m_menuItems.emplace_back(MenuItem(sf::Sprite(TextureManager::instance().getPlay())));
	m_menuItems.emplace_back(MenuItem(sf::Sprite(TextureManager::instance().getHelp())));
	m_menuItems.emplace_back(MenuItem(sf::Sprite(TextureManager::instance().getExit())));
	m_menuItemsHighlighted.emplace_back(MenuItem(sf::Sprite(TextureManager::instance().getPlayH())));
	m_menuItemsHighlighted.emplace_back(MenuItem(sf::Sprite(TextureManager::instance().getHelpH())));
	m_menuItemsHighlighted.emplace_back(MenuItem(sf::Sprite(TextureManager::instance().getExitH())));
}

// Handle input for 3 buttons
void MainMenu::handleMouseInput(sf::Vector2f mPosition, GameState& state)
{
	// Check where the mouse clicked
	if (m_menuItems[toInt(GameState::PLAY)].getGlobalBounds().contains(mPosition))
	{
		state = GameState::PLAY;
		m_select.play();
	}
	else if (m_menuItems[toInt(GameState::HELP)].getGlobalBounds().contains(mPosition))
	{
		state = GameState::HELP;
		m_select.play();
	}
	else if (m_menuItems[toInt(GameState::EXIT)].getGlobalBounds().contains(mPosition))
	{
		state = GameState::EXIT;
		m_select.play();
	}
}

void MainMenu::handleMouseLocation(sf::Vector2f mPosition)
{
	// Check where the mouse hovered
	// If mouse on a button higlight it, and if not, unhighlight it
	if (m_menuItems[toInt(GameState::PLAY)].getGlobalBounds().contains(mPosition))
		m_playh = true;
	else
		m_playh = false;
	if (m_menuItems[toInt(GameState::HELP)].getGlobalBounds().contains(mPosition))
		m_helph = true;
	else
		m_helph = false;
	if (m_menuItems[toInt(GameState::EXIT)].getGlobalBounds().contains(mPosition))
		m_exith = true;
	else
		m_exith = false;
}

void MainMenu::drawMenu(sf::RenderWindow& window)
{
	// Draw the main menu background
	window.draw(m_menuSprite);
	// place and draw menu items in window
	float row = 225.f, col = 25.f;

	for (int i = 0; i < ITEMS; ++i, col += 175.f)
	{
		// Check if any of the buttons are highlighted
		// Set buttons position and draw them in the window
		if (m_playh && i == toInt(GameState::PLAY))
		{
			m_menuItemsHighlighted[i].setPos(col, row);
			window.draw(m_menuItemsHighlighted[i].getSprite());
		}
		else if (m_helph && i == toInt(GameState::HELP))
		{
			m_menuItemsHighlighted[i].setPos(col, row);
			window.draw(m_menuItemsHighlighted[i].getSprite());
		}
		else if (m_exith && i == toInt(GameState::EXIT))
		{
			m_menuItemsHighlighted[i].setPos(col, row);
			window.draw(m_menuItemsHighlighted[i].getSprite());
		}
		else // Non highlighted button
		{
			m_menuItems[i].setPos(col, row);
			window.draw(m_menuItems[i].getSprite());
		}
	}
}

void MainMenu::drawHelp(sf::RenderWindow& window)
{
	// Draw the help window background
	window.draw(m_helpSprite);
	
	// Set positions of buttons
	m_menuItemsHighlighted[toInt(GameState::EXIT)].setPos(250.f, 700.f);
	m_menuItems[toInt(GameState::EXIT)].setPos(250.f, 700.f);

	// Draw EXIT button
	if (m_exith)
		window.draw(m_menuItemsHighlighted[toInt(GameState::EXIT)].getSprite());
	else
		window.draw(m_menuItems[toInt(GameState::EXIT)].getSprite());
}

void MainMenu::drawLost(sf::RenderWindow& window)
{
	// Draw background
	window.draw(m_lostSprite);

	// Set positions of buttons
	m_menuItems[toInt(GameState::EXIT)].setPos(195.f, 200.f);
	m_menuItemsHighlighted[toInt(GameState::EXIT)].setPos(195.f, 200.f);
	setOutsidePos();

	// Draw EXIT button
	if (m_exith)
		window.draw(m_menuItemsHighlighted[toInt(GameState::EXIT)].getSprite());
	else
		window.draw(m_menuItems[toInt(GameState::EXIT)].getSprite());
}

void MainMenu::drawWin(sf::RenderWindow& window, const int points)
{
	// Draw background
	window.draw(m_winSprite);
	
	auto& font = TextureManager::instance().getFont();
	auto pointsText = sf::Text(std::to_string(points), font, 50u);
	pointsText.setPosition(280.f, 500.f);
	window.draw(pointsText);

	// Set positions of buttons
	m_menuItems[toInt(GameState::EXIT)].setPos(195.f, 600.f);
	m_menuItemsHighlighted[toInt(GameState::EXIT)].setPos(195.f, 600.f);
	setOutsidePos();

	// Draw EXIT button
	if (m_exith)
		window.draw(m_menuItemsHighlighted[toInt(GameState::EXIT)].getSprite());
	else
		window.draw(m_menuItems[toInt(GameState::EXIT)].getSprite());
}

void MainMenu::setOutsidePos()
{
	// Set Help and Play buttons outside the window so it's impossible to click on
	m_menuItems[toInt(GameState::HELP)].setPos(-100.f, -100.f);
	m_menuItems[toInt(GameState::PLAY)].setPos(-100.f, -100.f);
	m_menuItemsHighlighted[toInt(GameState::HELP)].setPos(-100.f, -100.f);
	m_menuItemsHighlighted[toInt(GameState::PLAY)].setPos(-100.f, -100.f);
}
