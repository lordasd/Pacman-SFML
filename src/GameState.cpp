#include "GameState.h"

int toInt(const GameState& state)
{
	switch (state)
	{
	case GameState::PLAY:
		return 0;
	case GameState::HELP:
		return 1;
	case GameState::EXIT:
		return 2;
	case GameState::MENU:
		return 3;
	case GameState::LOST:
		return 4;
	case GameState::WIN:
		return 5;
	default:
		return 0; // EXIT
	}
}