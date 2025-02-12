#include "SandboxState.h"
#include <string>
#include "source/objects/player/Player.h"
#include "source/physics/Physics.h"
#include "source/tilemap/Tilemap.h"
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
	player->setPosition({200.f, 100.f});
	tilemap.setTileset(Cfg::Textures::Tileset1, 25, 5, sf::Vector2f{ 50.f,50.f });

	int arr[16*12] = { 
		06,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		06,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		06,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		06,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		06,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		06,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		06,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		06,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		06,-1,-1,-1,-1,-1,-1,-1,-1,06,06,06,06,-1,-1,-1,
		06,-1,-1,-1,-1,-1,-1,-1,06,06,-1,-1,-1,-1,06,-1,
		06,-1,-1,-1,-1,-1,-1,-1,06,06-1,-1,-1,-1,06,-1,
		06,06,06,06,06,06,06,06,06,06,06,06,06,06,06,06
	};

	tilemap.setMap(arr, 16 * 12, 16);
}

SandboxState::~SandboxState()
{
}

void SandboxState::Update(float gameTime_, sf::RenderWindow& wnd)
{
	Physics::updateMouse(wnd);
	player->update(gameTime_);
}

void SandboxState::Render(sf::RenderWindow& wnd)
{
	wnd.draw(bgSpr);
	tilemap.render(wnd);
	wnd.draw(*player->sprite());
}

void SandboxState::ProcessInputStates()
{
}

void SandboxState::UpdateFixed(float gameTime_)
{
	static bool movedx{ false };
	static bool movedy{ false };
	Physics::applyGravity(*player, gameTime_);

	
	sf::Vector2f cn, cp;
	float ct;
	auto vec = tilemap.getVisibleTiles();
	movedx = false;
	movedy = false;
	Physics::DynoVsTiles(*player, vec , cp, cn, ct, gameTime_, movedx, movedy);

	if (!movedx || !movedy)
		Physics::applyMovement(*player, gameTime_, tilemap);


	player->updateAnimState();
}


