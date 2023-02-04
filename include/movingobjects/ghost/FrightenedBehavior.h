#pragma once

#include "Behavior.h"

class FrightenedBehavior : public Behavior {
public:
	FrightenedBehavior(const Direction& direction);
	void update() override;
	virtual Direction getDireciton() override;
	virtual void setDirection(const Direction& direction);
private:
	Direction m_currDirection;
};