#include "Player.h"

Player::Player()
	: DynamicObject{ Cfg::Textures::PlayerAtlas, sf::Vector2f{ 130.f, 160.f }, sf::Vector2f{ 325.f, 225.f } }
{
	animator.addAnim("Idle", 3, { 130.f,160.f }, 0.43f, { 0.f,160.f }, "Right", false, true, true, 3.f);
}

Player::~Player()
{
}

void Player::update(float gameTime_)
{
	animator.update(gameTime_);

}
