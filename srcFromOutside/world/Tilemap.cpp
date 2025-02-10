#include <world/Tilemap.h>
#include <fstream>

Tilemap::Tilemap(v2 size_, int id_)
	: tileset{size_, id_}
	, cols{ 0 }, rows{0}
{
	_tiles.clear();
	_animTiles.clear();
}

bool Tilemap::loadMap(const std::string& filename)
{
	

	std::ifstream iFile;
	iFile.open(filename);
	
	if (iFile.fail() || !iFile.is_open() || !iFile.good())
	{ 
		if (iFile.is_open())
			iFile.close();
		return false;
	}

	iFile >> cols >> rows;

	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			int num;
			iFile >> num;
			v2 pos{ (float)(x * tileset._tiles.at(0).frame.texRect.getSize().x), (float)( y * tileset._tiles.at(0).frame.texRect.getSize().y) };

			_tiles.push_back(tileset._tiles[num]);
			Tile& aTile = _tiles[_tiles.size() - 1];
			aTile.frame = tileset._tiles[num].frame;
			aTile.bbox = tileset._tiles[num].bbox;
			aTile.solid = tileset._tiles[num].solid;
			aTile.frame.texture = tileset._tiles[num].frame.texture;
			aTile.pos = pos;
		}
	}

	// tiles should be good
	// dont use anim tiles yet

	iFile.close();

	return true;
}

void Tilemap::render(sf::RenderWindow& wnd_, float dt_)
{
	int wndColStart = std::max((int)(wnd_.getView().getCenter().x - 800.f) - (int)(tileset._tiles.at(0).frame.texRect.width) / (int)_tiles.at(0).frame.texRect.width, 0);
	int wndRowStart = std::max((int)(wnd_.getView().getCenter().y - 450.f) - (int)(tileset._tiles.at(0).frame.texRect.height) / (int)_tiles.at(0).frame.texRect.height, 0);

	int wndCols = std::min((int)((wnd_.getView().getCenter().x - 800.f) + wnd_.getSize().x)  +  (tileset._tiles.at(0).frame.texRect.width) / (int)_tiles.at(0).frame.texRect.width, cols);
	int wndRows = std::min((int)((wnd_.getView().getCenter().y - 450.f) + wnd_.getSize().y) + (tileset._tiles.at(0).frame.texRect.height) / (int)_tiles.at(0).frame.texRect.height, rows);

	for (int y = wndRowStart; y < wndRows; y++)
	{
		for (int x = wndColStart; x < wndCols; x++)
		{
			wnd_.draw(*_tiles.at(y * cols + x).spr());
		}
	}
}
