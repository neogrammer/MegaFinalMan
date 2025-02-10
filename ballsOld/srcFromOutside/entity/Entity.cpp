#include <entity/Entity.h>
#include <resources/Cfg.h>
#include <iostream>
#include <systems/Physics.h>
#include <algorithm>

Entity::Entity()
{
	pos =v2{0.f,0.f};
	vel = v2{ 0.f,0.f };
	frameInvariant = Frame{};
	frameInvariant.texOffset = { 0.f,0.f };
	frameInvariant.texRect = { {0,0},{50,50} };
	frameInvariant.texture = &Cfg::textures.get((int)Cfg::Textures::Invariant);
	bboxInvariant = BBox{};
	bboxInvariant.sz = v2{ 50.f,50.f };
	hasAnimations = false;
	anims.clear();
	bboxes.clear();
	belowRects.clear();

	belowRects.push_back({ {600.f,300.f}, {50.f,50.f} });
	
}

std::unique_ptr<sf::Sprite> Entity::spr()
{
	std::unique_ptr<sf::Sprite> tmp = std::make_unique<sf::Sprite>();
	if (!hasAnimations || currAnim == "default")
	{
		tmp->setTexture(*frameInvariant.texture);
		tmp->setTextureRect({ {0,0},{50,50} });
		tmp->setPosition({ 0.f,0.f });
	}
	else
	{
		tmp->setTexture(*this->anims[currAnim].frame().texture);
		tmp->setTextureRect(this->anims[currAnim].frame().texRect);
		tmp->setPosition({ pos.x - this->anims[currAnim].frame().texOffset.x , pos.y - this->anims[currAnim].frame().texOffset.y });

	}
	return std::move(tmp);
}

int Entity::getRectsBelow(const Tilemap& tilemap)
{

	auto& tiles = tilemap._tiles;
	belowRects.clear();

	int tileStartX = std::max((int)(pos.x / tiles[0].bbox.sz.x)-1,0);
	
	int tileEndX = std::min((int)((pos.x + size().x) / (int)tiles[0].bbox.sz.x) + 1, tilemap.cols - 1);

	int tileStartY = std::max((int)(pos.y / tiles[0].bbox.sz.x)-1, 0);

	int tileEndY = std::min((int)((pos.y + size().y) / (int)tiles[0].bbox.sz.y) + 1, tilemap.rows - 1);
	//int tileEndX = (int)(pos.x + bboxes[currAnim].at(anims[currAnim].idx]).sz.x) / (int)tiles[0].bbox.sz.x;
	int currTile = 0;
	int currRow = 0;
	int count = 0;
	for (int y = tileStartY; y <= tileEndY; y++)
	{
		for (int x = tileStartX; x <= tileEndX; x++)
		{
			int index = y * tilemap.cols + x;
			if (index > tilemap._tiles.size())
			{
				break;
			}
			if (tiles.at(index).solid == 1)
			{
				count++;
				auto& t = tiles.at(index);
				belowRects.push_back({ v2{t.pos.x,t.pos.y},v2{t.bbox.sz.x,t.bbox.sz.y} });
			}
		}
	}
	return count;
}

void Entity::loadAnimation(std::string name_, sf::Texture& tex_, int numFrames_, std::vector<v2> offsets_, std::vector<v2> bboxes_, v2 frameSize_, v2 startPixel)
{
	if (anims.find(name_) != anims.end())
	{
		std::cout << "Anim already in place" << std::endl;
		return;
	}
	else
	{
		anims.emplace(name_,Animation{});
		anims.at(name_).loadFrames(frameSize_, offsets_, tex_, numFrames_, startPixel);
		bboxes.emplace(name_, std::vector<BBox>{});
		for (int i = 0; i < numFrames_; i++)
		{
			bboxes[name_].emplace_back(bboxes_[i]);
		}
		if (currAnim == "default")
			currAnim = name_;
		hasAnimations = true;

		return;
	}
	return;
}

int Entity::currIdx()
{
	return anims[currAnim].idx;
}

void Entity::update(sf::RenderWindow& wnd_, float dt_, Tilemap& tmap)
{
	if (affectedByGravity)
		vel.y += 777.f * dt_;
	getRectsBelow(tmap);
	bool ticked = false;
	std::vector<std::pair<std::pair<v2, v2>*, float> > z;
	z.clear();
	z.shrink_to_fit();
	for (auto& r : belowRects)
	{
		v2 cp, cn;
		float ct;
		if (Physics::dynamicVrect(pos, bboxes[currAnim].at(currIdx()).sz, vel, r.first, r.second, cp, cn, ct, dt_))
		{
			z.push_back({ &r, ct });
		}
	}
	std::sort(z.begin(), z.end(), [](const auto& a, const auto& b) {
		return a.second < b.second;
		});
	for (auto j : z)
	{

		v2 cp, cn;
		float ct;

		if (Physics::dynamicVrect(pos, bboxes[currAnim].at(currIdx()).sz, vel, j.first->first, j.first->second, cp, cn, ct, dt_))
		{
			auto ab = v2{ std::abs(vel.x), std::abs(vel.y) };
				vel.x += (cn.x * ab.x * (1 - ct));
				vel.y += (cn.y * ab.y * (1 - ct));
		}
	}
	tick(dt_);
}

void Entity::tick(float dt_)
{
	pos += vel * dt_;
}

v2 Entity::size()
{
	return bboxes[currAnim].at(currIdx()).sz;
}

void Entity::render(sf::RenderWindow& wnd_, float dt_)
{
	sf::Sprite playerSpr = sf::Sprite{};
	playerSpr.setTexture(Cfg::textures.get((int)Cfg::Textures::PlayerAtlas));
	playerSpr.setPosition(pos - anims.at(currAnim).frame().texOffset);
	playerSpr.setTextureRect(anims.at(currAnim).rect());
	wnd_.draw(playerSpr);
}

