#ifndef TILE_H__
#define TILE_H__
#include "../objects/StaticObject.h"
#include "../resources/Cfg.h"
class Tile : public StaticObject
{
	
public:
	friend class Tilemap;
	Tile(Cfg::Textures tex_ = Cfg::Textures::Invariant, sf::Vector2f size_ = {50.f,50.f}, sf::Vector2f pos_ = { 0.f,0.f }, sf::Vector2i texPos_ = {0,0});
	~Tile();

	sf::Vector2i getTexPosition();
};

#endif