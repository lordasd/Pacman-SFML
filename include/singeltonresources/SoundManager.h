#pragma once

#include <SFML/Audio.hpp>

class SoundManager {
public:
	static SoundManager& instance();
	~SoundManager() = default;
	SoundManager(const SoundManager&) = delete;
	void operator=(const SoundManager&) = delete;
	const sf::SoundBuffer& getStartMusic() const;
	const sf::SoundBuffer& getChomp() const;
	const sf::SoundBuffer& getSiren1() const;
	const sf::SoundBuffer& getPacmanDeath() const;
	const sf::SoundBuffer& getGhostDeath() const;
	const sf::SoundBuffer& getPowerPellet() const;
	const sf::SoundBuffer& getDoorOpen() const;
	const sf::SoundBuffer& getDoorBreak() const;
	const sf::SoundBuffer& getSelect() const;
	const sf::SoundBuffer& getIntermission() const;
	const sf::SoundBuffer& getExtendTime() const;
	const sf::SoundBuffer& getWin() const;
	const sf::SoundBuffer& getLose() const;
	const sf::SoundBuffer& getFreeze() const;
	const sf::SoundBuffer& getHp() const;

private:
	SoundManager();
	sf::SoundBuffer m_startMusic;
	sf::SoundBuffer m_chomp;
	sf::SoundBuffer m_siren1;
	sf::SoundBuffer m_pacmanDeath;
	sf::SoundBuffer m_ghostDeath;
	sf::SoundBuffer m_powerPellet;
	sf::SoundBuffer m_doorOpen;
	sf::SoundBuffer m_doorBreak;
	sf::SoundBuffer m_select;
	sf::SoundBuffer m_intermission;
	sf::SoundBuffer m_extendTime;
	sf::SoundBuffer m_win;
	sf::SoundBuffer m_lose;
	sf::SoundBuffer m_freeze;
	sf::SoundBuffer m_hp;
};