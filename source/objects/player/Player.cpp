#include "Player.h"

Player::Player()
	: DynamicObject{ Cfg::Textures::PlayerAtlas, sf::Vector2f{ 130.f, 160.f }, sf::Vector2f{ 325.f, 225.f } }
{
	animator.addAnim( "Idle", 3, { 130.f,160.f }, 0.43f, { 0.f,1 * 160.f }, "Right", false, true, true, 3.f, { 51.f, 42.f }, { 42.f,85.f });
	animator.addAnim("Idle", 3, { 130.f,160.f }, 0.43f, { 0.f,14*160.f }, "Left", false, true, true, 3.f, { 51.f, 42.f }, { 42.f,85.f });
	
	animator.addAnim( "Run", 10, { 130.f,160.f }, 0.13f, { 3 * 130.f, 15 * 160.f }, "Left", false, true, false, 0.f, { 51.f, 42.f }, { 42.f,85.f });
	animator.addAnim( "Run", 10, { 130.f,160.f }, 0.13f, { 3 * 130.f, 2 * 160.f }, "Right", false, true, false, 0.f, { 51.f, 42.f }, { 42.f,85.f });

	//rigidBody.setRigidBody(); 
}

Player::~Player()
{
}

void Player::update(float gameTime_)
{
	if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
	{
		if (getCurrAnimID() != "Idle")
		{
			queueAnim("Idle");
		}
		setVelocity({ 0.f,getVelocity().y});
	}
	else
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (getCurrAnimID() != "Run")
			{
				queueAnim("Run");
			}
			setVelocity({ 300.f, getVelocity().y });
			//setPosition({ getPosition().x + 300.f * gameTime_, getPosition().y });
			setDir("Right");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (getCurrAnimID() != "Run")
			{
				queueAnim("Run");
			}
			setVelocity({ -300.f, getVelocity().y});
			//setPosition({ getPosition().x - 300.f * gameTime_, getPosition().y });
			setDir("Left");
		}
	}

	animator.update(gameTime_);

}

void Player::setDir(std::string dir_)
{
	this->animator.setDir(dir_);
}
