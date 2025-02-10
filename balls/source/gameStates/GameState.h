#ifndef GAME_STATE_H__
#define GAME_STATE_H__
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
class GameState
{
	bool paused{ false };
	std::string typeName{ "Default" };
public:
	GameState(std::string typeName_);
	virtual ~GameState();

	GameState(const GameState&) = default;
	GameState(GameState&&) = default;
	GameState& operator=(const GameState&) = default;
	GameState& operator=(GameState&&) = default;






	virtual void Update(float gameTime_);
	virtual void Render(sf::RenderWindow& wnd);
	virtual void ProcessInputStates();

	void Pause();
	void UnPause();
	bool IsPaused();

	const std::string getTypeName() const { return typeName; }
	
};


static bool operator==(const GameState& left, const GameState& right);

#endif