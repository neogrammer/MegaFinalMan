#include "Player.h"

Player::Player()
	: DynamicObject{ Cfg::Textures::PlayerAtlas, sf::Vector2f{ 130.f, 160.f }, sf::Vector2f{ 325.f, 225.f } }
{
	animator.addAnim("Idle", 4, { 130.f,160.f }, 0.13f, { 0.f,320.f }, "Right", false);
	
}

Player::~Player()
{
}
