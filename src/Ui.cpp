#include "Ui.h"

Ui::Ui(float height, int level, int points, float levelTime)
	:	m_level(TextureManager::instance().getLevel()), 
		m_levelTime(levelTime), m_points(TextureManager::instance().getScore()),
		m_timer(TextureManager::instance().getClock())
{
	// Exact height to place UI
	height += 10.f;

	// Set 4 lives into array of sprites
	float widthf = 40.f;
	for (int i = 0; i < m_hpNm+1; ++i, widthf += 30.f)
	{
		m_hpSprites.emplace_back(TextureManager::instance().getLifeBonus());
		m_hpSprites.back().setPosition(widthf, height);
	}

	m_level.setPosition(190.f, height - 5.f);

	m_levelNm.setFont(TextureManager::instance().getFont());
	m_levelNm.setPosition(290.f, height - 5.f);
	m_levelNm.setString(std::to_string(level));

	m_points.setPosition(350.f, height - 5.f);

	m_pointsNm.setFont(*m_levelNm.getFont());
	m_pointsNm.setPosition(450.f, height - 5.f);
	m_pointsNm.setString(std::to_string(points));

	m_timer.setPosition(705.f, height - 5.f);

	m_timerNm.setFont(*m_levelNm.getFont());
	m_timerNm.setPosition(630.f, height - 5.f);

	// Set time for the first time
	updateTime();
}

void Ui::draw(sf::RenderWindow& window) const
{
	for (int i = 0; i < m_hpNm; ++i)
		window.draw(m_hpSprites[i]);
	window.draw(m_level);
	window.draw(m_levelNm);
	window.draw(m_points);
	window.draw(m_pointsNm);
	window.draw(m_timer);
	window.draw(m_timerNm);
}

void Ui::setHp(const int hp)
{
	//m_hpNm.setString(std::to_string(hp));
	// Set current hp
	m_hpNm = hp;
}

void Ui::setLevel(const int level)
{
	m_levelNm.setString(std::to_string(level));
}

void Ui::setPoints(const int points)
{
	std::string strPoints = std::to_string(points);
	// Set Points
	m_pointsNm.setString(strPoints);
}

void Ui::updateTime()
{
	// Get left time
	auto elapsedTime = m_clock.getElapsedTime().asSeconds();
	auto left = m_levelTime - elapsedTime + m_saveTime;
	auto leftStr = std::to_string((int)left);

	// Set left time
	m_timerNm.setString(leftStr);
}

void Ui::saveTime(float time)
{
	m_saveTime += time;
}

float Ui::getTimeLeft() const
{
	return m_levelTime - m_clock.getElapsedTime().asSeconds() + m_saveTime;
}

void Ui::addTime()
{
	m_saveTime += 15;
}