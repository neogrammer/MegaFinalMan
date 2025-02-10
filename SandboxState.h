#ifndef SANDBOX_STATE_H__
#define SANDBOX_STATE_H__

#include <SFML/Graphics.hpp>
#include "source/gameStates/GameState.h"
#include "source/resources/Cfg.h"
#include "source/tilemap/Tilemap.h"
class Player;
class SandboxState : public GameState
{
	std::unique_ptr<Player> player;

	Cfg::Textures aTex;
	sf::Sprite aSpr;

	Cfg::Textures bgTex;
	sf::Sprite bgSpr;

	Tilemap tilemap;
public:
	SandboxState();
	~SandboxState() override final;

	virtual void Update(float gameTime_);
	virtual void Render(sf::RenderWindow& wnd);
	virtual void ProcessInputStates();
	virtual void UpdateFixed(float gameTime_);
};

#endif