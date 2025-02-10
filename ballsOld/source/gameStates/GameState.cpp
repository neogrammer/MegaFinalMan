#include "GameState.h"

GameState::GameState(std::string typeName_)
	: typeName{typeName_}
{
}

GameState::~GameState()
{
}

void GameState::Update(float gameTime_)
{
}

void GameState::Render(sf::RenderWindow& wnd)
{
}

void GameState::ProcessInputStates()
{
}

void GameState::Pause()
{
	paused = true;
}

void GameState::UnPause()
{
	paused = false;
}

bool GameState::IsPaused()
{
	return paused;
}


inline bool operator==(const GameState& left, const GameState& right)
{
	if (left.getTypeName() == right.getTypeName())
		return true;

	return false;
}