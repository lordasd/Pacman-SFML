#pragma once

#include <SFML/Graphics.hpp>
		
class TextureManager {
public:
	static TextureManager& instance();
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	void operator=(const TextureManager&) = delete;

	const std::vector<sf::Texture>& getPacman() const;
	const std::vector < sf::Texture>& getBlinky() const;
	const std::vector < sf::Texture>& getPinky() const;
	const std::vector < sf::Texture>& getInky() const;
	const std::vector < sf::Texture>& getClyde() const;
	const std::vector < sf::Texture>& getScaredGhost() const;
	const sf::Texture& getSuperBonus() const;
	const sf::Texture& getTimeFreezeBonus() const;
	const sf::Texture& getTimeBonus() const;
	const sf::Texture& getLifeBonus() const;
	const sf::Texture& getKey() const;
	const sf::Texture& getWall() const;
	const sf::Texture& getDoor() const;
	const sf::Texture& getCookie() const;
	const sf::Texture& getBlank() const;
	const sf::Texture& getMainMenu() const;
	const sf::Texture& getPlay() const;
	const sf::Texture& getPlayH() const;
	const sf::Texture& getHelp() const;
	const sf::Texture& getHelpH() const;
	const sf::Texture& getExit() const;
	const sf::Texture& getExitH() const;
	const sf::Texture& getHelpWindow() const;
	const sf::Texture& getReady() const;
	const sf::Texture& getLost() const;
	const sf::Texture& getWin() const;
	const sf::Texture& getCursor() const;
	const sf::Texture& getClock() const;
	const sf::Texture& getLevel() const;
	const sf::Texture& getScore() const;
	const sf::Font& getFont() const;

private:
	TextureManager();
	sf::Texture m_spriteSheet;
	std::vector<sf::Texture> m_pacman;
	std::vector < sf::Texture> m_blinky;
	std::vector < sf::Texture> m_pinky;
	std::vector < sf::Texture> m_inky;
	std::vector < sf::Texture> m_clyde;
	std::vector < sf::Texture> m_scaredGhost;
	sf::Texture m_superBonus;
	sf::Texture m_timeFreezeBonus;
	sf::Texture m_timeBonus;
	sf::Texture m_lifeBonus;
	sf::Texture m_key;
	sf::Texture m_wall;
	sf::Texture m_door;
	sf::Texture m_cookie;
	sf::Texture m_blank;
	sf::Texture m_mainMenu;
	sf::Texture m_play;
	sf::Texture m_playH;
	sf::Texture m_help;
	sf::Texture m_helpH;
	sf::Texture m_exit;
	sf::Texture m_exitH;
	sf::Texture m_helpWindow;
	sf::Texture m_ready;
	sf::Texture m_lost;
	sf::Texture m_win;
	sf::Texture m_cursor;
	sf::Texture m_clock;
	sf::Texture m_level;
	sf::Texture m_score;
	sf::Font m_font;

	void createTexturePacman();
	void createTextureBlinky();
	void createTexturePinky();
	void createTextureInky();
	void createTextureClyde();
	void createScaredGhost();
	void createStaticObjects();
	void createBonusObjects();
	void createUiObjects();
	void createBackgrounds();
	void createButtons();
};