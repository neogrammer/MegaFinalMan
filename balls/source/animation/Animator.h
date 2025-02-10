#ifndef ANIMATOR_H__
#define ANIMATOR_H__
#include "AnimSet.h"

class Animator
{
	AnimSet animSet;
public:
	Animator();
	~Animator();
	sf::IntRect getFrame();
	sf::Vector2f getFrameSize();
	void addAnim(std::string id_, int numFrames_ = 1, sf::Vector2f frameSize_ = sf::Vector2f{ 50.f,50.f }, float frameDelay_ = { 0.13f }, sf::Vector2f startPixel_ = sf::Vector2f{ 0.f,0.f }, std::string dirType_ = "Uni", bool genOtherDirection_ = false, bool loops_ = true, bool loopWaits_ = false, float loopDelay_ = 0.f);
	
	void update(float gameTime_);

};

#endif