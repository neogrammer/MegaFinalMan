#ifndef TILEMAP_H__
#define TILEMAP_H__
#include "Tileset.h"
#include <memory>
class Tile;
class Tilemap
{
	std::unique_ptr<Tileset> tileset;
	std::vector<std::unique_ptr<Tile> > tiles;
	int pitch;
	
public:
	Tilemap();
	~Tilemap();


	std::vector<Tile*> getVisibleTiles();
	std::vector<Tile*> getTilesInArea(int top_, int left_, int width_, int height_);
	void setTileset(Cfg::Textures tex_, int numTiles_, int pitch_, sf::Vector2f size_);
	void render(sf::RenderWindow& wnd_);
	void setMap(int* tileData, int numTiles_, int pitch_);
	int getPitch();
	int getNumTiles();
	sf::Vector2f getTileSize();
	Cfg::Textures getCurrTexType();
	
};


#endif