#include "SandboxState.h"
#include <string>
#include "source/objects/player/Player.h"
SandboxState::SandboxState()
	: GameState{"SandBox"}
	, aTex{Cfg::Textures::Invariant}
	, aSpr{Cfg::textures.get((int)aTex)}
	, bgTex{ Cfg::Textures::Background_Start }
	, bgSpr{Cfg::textures.get((int)bgTex)}
	, player{}
	, tilemap{}
{
	aSpr.setPosition({ 295.f,215.f }); // invariant is 50x50
	bgSpr.setPosition({ 0.f, 0.f });

	player = std::make_unique<Player>();

	tilemap.setTileset(Cfg::Textures::Tileset1, 25, 5, sf::Vector2f{ 50.f,50.f });

	int arr[16*12] = { 
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		06,06,06,06,06,06,06,06,06,06,06,06,06,06,06,06
	};

	tilemap.setMap(arr, 16 * 12, 16);
}

SandboxState::~SandboxState()
{
}

void SandboxState::Update(float gameTime_)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player->setPosition({ player->getPosition().x + 300.f * gameTime_, player->getPosition().y });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player->setPosition({ player->getPosition().x - 300.f * gameTime_, player->getPosition().y });
	}

	player->update(gameTime_);
}

void SandboxState::Render(sf::RenderWindow& wnd)
{
	wnd.draw(bgSpr);

	tilemap.render(wnd);

	wnd.draw(*player->sprite());

	//wnd.draw(aSpr);

}

void SandboxState::ProcessInputStates()
{
}


