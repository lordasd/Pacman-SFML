#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager()
{
	createTexturePacman();
	createTextureBlinky();
	createTexturePinky();
	createTextureInky();
	createTextureClyde();
	createScaredGhost();
	createStaticObjects();
	createBonusObjects();
	createUiObjects();
	createBackgrounds();
	createButtons();

	if (!m_ready.loadFromFile("ready.png"))
	{
		std::cerr << "Can't load ready.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_cursor.loadFromFile("cursor.png"))
	{
		std::cerr << "Can't load cursor.png\n";
		exit(EXIT_FAILURE);
	}
	
	if (!m_font.loadFromFile("pixelfont.otf"))
	{
		std::cerr << "Can't load Arial font\n";
		exit(EXIT_FAILURE);
	}
}

// Return textures of all pictures

TextureManager& TextureManager::instance()
{
	static auto texturemanager = TextureManager();
	return texturemanager;
}

const std::vector<sf::Texture>& TextureManager::getPacman() const
{
	return m_pacman;
}

const std::vector < sf::Texture>& TextureManager::getBlinky() const
{
	return m_blinky;
}

const std::vector < sf::Texture>& TextureManager::getPinky() const
{
	return m_pinky;
}

const std::vector < sf::Texture>& TextureManager::getInky() const
{
	return m_inky;
}

const std::vector < sf::Texture>& TextureManager::getClyde() const
{
	return m_clyde;
}

const std::vector<sf::Texture>& TextureManager::getScaredGhost() const
{
	return m_scaredGhost;
}

const sf::Texture& TextureManager::getSuperBonus() const
{
	return m_superBonus;
}

const sf::Texture& TextureManager::getTimeFreezeBonus() const
{
	return m_timeFreezeBonus;
}

const sf::Texture& TextureManager::getTimeBonus() const
{
	return m_timeBonus;
}

const sf::Texture& TextureManager::getLifeBonus() const
{
	return m_lifeBonus;
}

const sf::Texture& TextureManager::getKey() const
{
	return m_key;
}

const sf::Texture& TextureManager::getWall() const
{
	return m_wall;
}

const sf::Texture& TextureManager::getDoor() const
{
	return m_door;
}

const sf::Texture& TextureManager::getCookie() const
{
	return m_cookie;
}

const sf::Texture& TextureManager::getBlank() const
{
	return m_blank;
}

const sf::Texture& TextureManager::getMainMenu() const
{
	return m_mainMenu;
}

const sf::Texture& TextureManager::getPlay() const
{
	return m_play;
}

const sf::Texture& TextureManager::getPlayH() const
{
	return m_playH;
}

const sf::Texture& TextureManager::getHelp() const
{
	return m_help;
}

const sf::Texture& TextureManager::getHelpH() const
{
	return m_helpH;
}

const sf::Texture& TextureManager::getExit() const
{
	return m_exit;
}

const sf::Texture& TextureManager::getExitH() const
{
	return m_exitH;
}

const sf::Texture& TextureManager::getHelpWindow() const
{
	return m_helpWindow;
}

const sf::Texture& TextureManager::getReady() const
{
	return m_ready;
}

const sf::Texture& TextureManager::getLost() const
{
	return m_lost;
}

const sf::Texture& TextureManager::getWin() const
{
	return m_win;
}

const sf::Texture& TextureManager::getCursor() const
{
	return m_cursor;
}

const sf::Texture& TextureManager::getClock() const
{
	return m_clock;
}

const sf::Texture& TextureManager::getLevel() const
{
	return m_level;
}

const sf::Texture& TextureManager::getScore() const
{
	return m_score;
}

const sf::Font& TextureManager::getFont() const
{
	return m_font;
}

void TextureManager::createTexturePacman()
{
	auto pacmanup = sf::Texture();
	if (!pacmanup.loadFromFile("pacmanup.png"))
	{
		std::cerr << "Can't load pacmanup.png\n";
		exit(EXIT_FAILURE);
	}
	m_pacman.push_back(pacmanup);

	auto pacmandown = sf::Texture();
	if (!pacmandown.loadFromFile("pacmandown.png"))
	{
		std::cerr << "Can't load pacmandown.png\n";
		exit(EXIT_FAILURE);
	}
	m_pacman.push_back(pacmandown);

	auto pacmanright = sf::Texture();
	if (!pacmanright.loadFromFile("pacmanright.png"))
	{
		std::cerr << "Can't load pacmanright.png\n";
		exit(EXIT_FAILURE);
	}
	m_pacman.push_back(pacmanright);

	auto pacmanleft = sf::Texture();
	if (!pacmanleft.loadFromFile("pacmanleft.png"))
	{
		std::cerr << "Can't load pacmanleft.png\n";
		exit(EXIT_FAILURE);
	}
	m_pacman.push_back(pacmanleft);
}

void TextureManager::createTextureBlinky()
{
	auto blinkyup = sf::Texture();
	if (!blinkyup.loadFromFile("blinkyup.png"))
	{
		std::cerr << "Can't load blinkyup.png\n";
		exit(EXIT_FAILURE);
	}
	m_blinky.push_back(blinkyup);

	auto blinkydown = sf::Texture();
	if (!blinkydown.loadFromFile("blinkydown.png"))
	{
		std::cerr << "Can't load blinkydown.png\n";
		exit(EXIT_FAILURE);
	}
	m_blinky.push_back(blinkydown);

	auto blinkyright = sf::Texture();
	if (!blinkyright.loadFromFile("blinkyright.png"))
	{
		std::cerr << "Can't load blinkyright.png\n";
		exit(EXIT_FAILURE);
	}
	m_blinky.push_back(blinkyright);

	auto blinkyleft = sf::Texture();
	if (!blinkyleft.loadFromFile("blinkyleft.png"))
	{
		std::cerr << "Can't load blinkyleft.png\n";
		exit(EXIT_FAILURE);
	}
	m_blinky.push_back(blinkyleft);
}

void TextureManager::createTexturePinky()
{
	auto pinkyup = sf::Texture();
	if (!pinkyup.loadFromFile("pinkyup.png"))
	{
		std::cerr << "Can't load pinkyup.png\n";
		exit(EXIT_FAILURE);
	}
	m_pinky.push_back(pinkyup);

	auto pinkydown = sf::Texture();
	if (!pinkydown.loadFromFile("pinkydown.png"))
	{
		std::cerr << "Can't load pinkydown.png\n";
		exit(EXIT_FAILURE);
	}
	m_pinky.push_back(pinkydown);

	auto pinkyright = sf::Texture();
	if (!pinkyright.loadFromFile("pinkyright.png"))
	{
		std::cerr << "Can't load pinkyright.png\n";
		exit(EXIT_FAILURE);
	}
	m_pinky.push_back(pinkyright);

	auto pinkyleft = sf::Texture();
	if (!pinkyleft.loadFromFile("pinkyleft.png"))
	{
		std::cerr << "Can't load pinkyleft.png\n";
		exit(EXIT_FAILURE);
	}
	m_pinky.push_back(pinkyleft);
}

void TextureManager::createTextureInky()
{
	auto inkyup = sf::Texture();
	if (!inkyup.loadFromFile("inkyup.png"))
	{
		std::cerr << "Can't load inkyup.png\n";
		exit(EXIT_FAILURE);
	}
	m_inky.push_back(inkyup);

	auto inkydown = sf::Texture();
	if (!inkydown.loadFromFile("inkydown.png"))
	{
		std::cerr << "Can't load inkydown.png\n";
		exit(EXIT_FAILURE);
	}
	m_inky.push_back(inkydown);

	auto inkyright = sf::Texture();
	if (!inkyright.loadFromFile("inkyright.png"))
	{
		std::cerr << "Can't load inkyright.png\n";
		exit(EXIT_FAILURE);
	}
	m_inky.push_back(inkyright);

	auto inkyleft = sf::Texture();
	if (!inkyleft.loadFromFile("inkyleft.png"))
	{
		std::cerr << "Can't load inkyleft.png\n";
		exit(EXIT_FAILURE);
	}
	m_inky.push_back(inkyleft);
}

void TextureManager::createTextureClyde()
{
	auto clydeup = sf::Texture();
	if (!clydeup.loadFromFile("clydeup.png"))
	{
		std::cerr << "Can't load clydeup.png\n";
		exit(EXIT_FAILURE);
	}
	m_clyde.push_back(clydeup);

	auto clydedown = sf::Texture();
	if (!clydedown.loadFromFile("clydedown.png"))
	{
		std::cerr << "Can't load clydedown.png\n";
		exit(EXIT_FAILURE);
	}
	m_clyde.push_back(clydedown);

	auto clyderight = sf::Texture();
	if (!clyderight.loadFromFile("clyderight.png"))
	{
		std::cerr << "Can't load clyderight.png\n";
		exit(EXIT_FAILURE);
	}
	m_clyde.push_back(clyderight);

	auto clydeleft = sf::Texture();
	if (!clydeleft.loadFromFile("clydeleft.png"))
	{
		std::cerr << "Can't load clydeleft.png\n";
		exit(EXIT_FAILURE);
	}
	m_clyde.push_back(clydeleft);
}

void TextureManager::createScaredGhost()
{
	auto scaredup = sf::Texture();
	if (!scaredup.loadFromFile("scaredghostup.png"))
	{
		std::cerr << "Can't load scaredghostup.png\n";
		exit(EXIT_FAILURE);
	}
	m_scaredGhost.push_back(scaredup);

	auto scareddown = sf::Texture();
	if (!scareddown.loadFromFile("scaredghostdown.png"))
	{
		std::cerr << "Can't load scaredghostdown.png\n";
		exit(EXIT_FAILURE);
	}
	m_scaredGhost.push_back(scareddown);

	auto scaredright = sf::Texture();
	if (!scaredright.loadFromFile("scaredghostright.png"))
	{
		std::cerr << "Can't load scaredghostright.png\n";
		exit(EXIT_FAILURE);
	}
	m_scaredGhost.push_back(scaredright);

	auto scaredleft = sf::Texture();
	if (!scaredleft.loadFromFile("scaredghostleft.png"))
	{
		std::cerr << "Can't load scaredghostleft.png\n";
		exit(EXIT_FAILURE);
	}
	m_scaredGhost.push_back(scaredleft);
}

void TextureManager::createStaticObjects()
{
	if (!m_key.loadFromFile("key.png"))
	{
		std::cerr << "Can't load key.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_wall.loadFromFile("wall.png"))
	{
		std::cerr << "Can't load wall.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_door.loadFromFile("door.png"))
	{
		std::cerr << "Can't load door.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_cookie.loadFromFile("cookie.png"))
	{
		std::cerr << "Can't load cookie.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_blank.loadFromFile("blank.png"))
	{
		std::cerr << "Can't load blank.png\n";
		exit(EXIT_FAILURE);
	}
}

void TextureManager::createBonusObjects()
{
	if (!m_superBonus.loadFromFile("superbonus.png"))
	{
		std::cerr << "Can't load superbonus.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_timeFreezeBonus.loadFromFile("timefreezebonus.png"))
	{
		std::cerr << "Can't load timefreezebonus.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_timeBonus.loadFromFile("timebonus.png"))
	{
		std::cerr << "Can't load timebonus.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_lifeBonus.loadFromFile("lifebonus.png"))
	{
		std::cerr << "Can't load lifebonus.png\n";
		exit(EXIT_FAILURE);
	}
}

void TextureManager::createUiObjects()
{
	if (!m_clock.loadFromFile("clock.png"))
	{
		std::cerr << "Can't load clock.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_level.loadFromFile("level.png"))
	{
		std::cerr << "Can't load level.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_score.loadFromFile("score.png"))
	{
		std::cerr << "Can't load score.png\n";
		exit(EXIT_FAILURE);
	}
}

void TextureManager::createButtons()
{
	if (!m_play.loadFromFile("play.png"))
	{
		std::cerr << "Can't load play.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_playH.loadFromFile("playh.png"))
	{
		std::cerr << "Can't load playh.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_help.loadFromFile("help.png"))
	{
		std::cerr << "Can't load help.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_helpH.loadFromFile("helph.png"))
	{
		std::cerr << "Can't load helph.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_exit.loadFromFile("exit.png"))
	{
		std::cerr << "Can't load exit.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_exitH.loadFromFile("exith.png"))
	{
		std::cerr << "Can't load exith.png\n";
		exit(EXIT_FAILURE);
	}
}

void TextureManager::createBackgrounds()
{
	if (!m_mainMenu.loadFromFile("mainmenu.png"))
	{
		std::cerr << "Can't load mainmenu.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_helpWindow.loadFromFile("helpwindow.png"))
	{
		std::cerr << "Can't load helpwindow.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_lost.loadFromFile("lost.png"))
	{
		std::cerr << "Can't load ready.png\n";
		exit(EXIT_FAILURE);
	}

	if (!m_win.loadFromFile("win.png"))
	{
		std::cerr << "Can't load ready.png\n";
		exit(EXIT_FAILURE);
	}
}