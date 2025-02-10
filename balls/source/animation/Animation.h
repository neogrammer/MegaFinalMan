#ifndef ANIMATION_H__
#define ANIMATION_H__
#include <string>
#include "../resources/Cfg.h"
class Animation
{
	std::string id{ "Default" };
	std::string dirType{ "Uni" };  // Uni, Left, or Right.  Is this animation facing left, right or forward,  for a platformer,   N, S, E, W, for top-down
	sf::Vector2f frameSize{0.f,0.f};
	float frameDelay{};
	float firstDelay{};
	float loopDelay{};
	bool loops{ true };
	bool loopWaits{ false };
	unsigned int numFrames{};



	

	std::vector<sf::IntRect> rects;
	sf::Vector2f texStartPos;

public:
	Animation(std::string id_ = "Default", std::string dir_ = "Uni", float frameDelay_ = { 0.13f }, unsigned numFrames_ = 1, sf::Vector2f frameSize_ = {50.f,50.f}, sf::Vector2f texStartPos_ = { 0.f,0.f }, bool loops_ = true, bool loopWaits_ = false, float loopDelay_ = 0.f);
	~Animation();

	std::string getDirType();
	std::string getID();
	sf::Vector2f getFrameSize();
	sf::IntRect getFrame(int index);
	float getFrameDelay();
	float getLoopDelay();
	bool isLooping();
	bool doesLoopWait();
	void setDirType(std::string type_);
	std::vector<sf::IntRect>& getRects();
	sf::IntRect getRect(int index_);

	int getNumFrames();
	

};

#endif