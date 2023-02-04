#pragma once

enum class GameState {
	PLAY,
	HELP, 
	EXIT, 
	MENU,
	LOST,
	WIN,
};

int toInt(const GameState& state);