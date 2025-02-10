#pragma once
#include <misc/BBox.h>
#include <misc/Frame.h>
#include <memory>
#include <unordered_map>
#include <string>
#include <misc/Animation.h>
#include <world/Tilemap.h>
#include <systems/Physics.h>

class Entity
{
public:
	bool affectedByGravity{ true };
	bool hasAnimations{ false };
	std::unordered_map<std::string, Animation> anims{};
	std::unordered_map<std::string, std::vector<BBox>> bboxes{};
	std::string currAnim{ "default" };
	std::vector<std::pair<v2, v2>> belowRects{ {{},{}} };

public:
	Entity();
	v2 size();
	int currIdx();
	~Entity() = default;
	Entity(Entity&&) = default;
	Entity& operator=(Entity&&) = default;
	v2 pos{};
	v2 vel{};
	Frame frameInvariant{ Frame{} };
	BBox bboxInvariant{ BBox{} };

	int getRectsBelow(const Tilemap& tilemap);

	std::unique_ptr<sf::Sprite> spr();
	virtual void update(sf::RenderWindow& wnd_, float dt_, Tilemap& tmap);
	void loadAnimation(std::string name_, sf::Texture& tex_, int numFrames_, std::vector<v2> offsets_, std::vector<v2> bboxes_, v2 frameSize_, v2 startPixel = { 0.f,0.f });
	virtual void render(sf::RenderWindow& wnd_, float dt_);
	void tick(float dt_);
	


};