#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::instance()
{
	static auto soundmanager = SoundManager();
	return soundmanager;
}

SoundManager::SoundManager()
{
	if (!m_startMusic.loadFromFile("pacman_beginning.wav"))
	{
		std::cerr << "Can't open pacman_beginning.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_siren1.loadFromFile("siren_1.wav"))
	{
		std::cerr << "Can't open siren_1.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_chomp.loadFromFile("pacman_chomp.wav"))
	{
		std::cerr << "Can't open pacman_chomp.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_pacmanDeath.loadFromFile("pacman_death.wav"))
	{
		std::cerr << "Can't open pacman_death.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_powerPellet.loadFromFile("power_pellet.wav"))
	{
		std::cerr << "Can't open power_pellet.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_doorOpen.loadFromFile("door_open.wav"))
	{
		std::cerr << "Can't open door_open.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_doorBreak.loadFromFile("door_break.wav"))
	{
		std::cerr << "Can't open door_break.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_ghostDeath.loadFromFile("eat_ghost.wav"))
	{
		std::cerr << "Can't open eat_ghost.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_select.loadFromFile("select-sound.wav"))
	{
		std::cerr << "Can't open select-sound.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_intermission.loadFromFile("intermission.wav"))
	{
		std::cerr << "Can't open intermission.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_extendTime.loadFromFile("extend.wav"))
	{
		std::cerr << "Can't open extend.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_win.loadFromFile("win.wav"))
	{
		std::cerr << "Can't open extend.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_lose.loadFromFile("lose.wav"))
	{
		std::cerr << "Can't open extend.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_freeze.loadFromFile("freeze.wav"))
	{
		std::cerr << "Can't open freeze.wav\n";
		exit(EXIT_FAILURE);
	}

	if (!m_hp.loadFromFile("hp.wav"))
	{
		std::cerr << "Can't open hp.wav\n";
		exit(EXIT_FAILURE);
	}
}

const sf::SoundBuffer& SoundManager::getStartMusic() const
{
	return m_startMusic;
}

const sf::SoundBuffer& SoundManager::getChomp() const
{
	return m_chomp;
}

const sf::SoundBuffer& SoundManager::getSiren1() const
{
	return m_siren1;
}

const sf::SoundBuffer& SoundManager::getPacmanDeath() const
{
	return m_pacmanDeath;
}

const sf::SoundBuffer& SoundManager::getGhostDeath() const
{
	return m_ghostDeath;
}

const sf::SoundBuffer& SoundManager::getPowerPellet() const
{
	return m_powerPellet;
}

const sf::SoundBuffer& SoundManager::getDoorOpen() const
{
	return m_doorOpen;
}

const sf::SoundBuffer& SoundManager::getDoorBreak() const
{
	return m_doorBreak;
}

const sf::SoundBuffer& SoundManager::getSelect() const
{
	return m_select;
}

const sf::SoundBuffer& SoundManager::getIntermission() const
{
	return m_intermission;
}

const sf::SoundBuffer& SoundManager::getExtendTime() const
{
	return m_extendTime;
}

const sf::SoundBuffer& SoundManager::getWin() const
{
	return m_win;
}

const sf::SoundBuffer& SoundManager::getLose() const
{
	return m_lose;
}

const sf::SoundBuffer& SoundManager::getFreeze() const
{
	return m_freeze;
}

const sf::SoundBuffer& SoundManager::getHp() const
{
	return m_hp;
}
