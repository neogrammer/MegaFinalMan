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

void SandboxState::Update(float gameTime_, sf::RenderWindow& wnd)
{
	Physics::updateMouse(wnd);
	//std::cout << "x : " << pos.x << ", y : " << pos.y << "\n";
	//std::cout << "bbox->w : " << tilemap.getVisibleTiles().at(150)->getBBox().w << ", bbox->h : " << tilemap.getVisibleTiles().at(150)->getBBox().h << "::  tilex : " << tilemap.getVisibleTiles().at(150)->getPosX() << ", tiley : " << tilemap.getVisibleTiles().at(150)->getPosY() << std::endl;
	
	

		/*if (Physics::RayVsBBox({ 100.f,100.f }, (sf::Vector2f)sf::Mouse::getPosition(wnd), player->getVelocity().x, tilemap.getVisibleTiles().at(150)->getBBox(), tilemap.getVisibleTiles().at(150)->getPosition(), cp, cn, ct, gameTime_))
		{
			if (ct < 1.f && ct >= 0.f)
				std::cout << "Collided" << std::endl;
		}*/
	player->update(gameTime_);
}

void SandboxState::Render(sf::RenderWindow& wnd)
{
	/*if (Physics::BBoxVsBBox(BoundingBox{ 10.f,10.f }, (sf::Vector2f)sf::Mouse::getPosition(wnd), dynamic_cast<StaticObject*>(tilemap.getVisibleTiles().at(0))->getBBox(), dynamic_cast<StaticObject*>(tilemap.getVisibleTiles().at(0))->getPosition()))
	{
		std::cout << "Collided" << std::endl;
	}*/
	wnd.draw(bgSpr);
	tilemap.render(wnd);
	wnd.draw(*player->sprite());

}

void SandboxState::ProcessInputStates()
{

}

void SandboxState::UpdateFixed(float gameTime_)
{
	Physics::applyGravity(*player, gameTime_);
	Physics::applyMovement(*player, gameTime_, tilemap);

	for (auto* t : tilemap.getVisibleTiles())
	{
		sf::Vector2f cp, cn;
		float ct;
		if (Physics::DynoVsStatic(*player, *t, cp, cn, ct, gameTime_))
		{
			std::cout << "Collided" << std::endl;
		}
	}
	//Physics::resolveCollision(*player, tilemap);
	player->updateAnimState();
}


