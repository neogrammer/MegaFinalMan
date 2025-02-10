#include "RigidBody.h"
#include "../objects/DynamicObject.h"

RigidBody::RigidBody(DynamicObject* dyno_, sf::Vector2f pos_, sf::Vector2f vel_)
	: owner{dyno_}
	, aabb{}
	, velx{vel_.x}, vely{vel_.y}
{
	posx = pos_.x;
	posy = pos_.y;
	auto& anims = owner->animator.getAnims().getAnims();
	for (auto& animTri : owner->animator.getAnims().getAnims())
	{
		aabb[animTri.first] = std::unordered_map<std::string, std::vector<BoundingBox>>{};
		aabb[animTri.first].clear();
		for (auto& anim : animTri.second)
		{
			anim.second.getDirType();
			aabb[animTri.first] = {};
			aabb[animTri.first].clear();
			aabb.at(animTri.first)[anim.second.getDirType()] = std::vector<BoundingBox>{};
			aabb.at(animTri.first)[anim.second.getDirType()].clear();
			aabb.at(animTri.first)[anim.second.getDirType()].reserve(anim.second.getRects().size());
			for (int i = 0; i < anim.second.getRects().size(); i++)
			{
				aabb.at(animTri.first)[anim.second.getDirType()].push_back(BoundingBox{ (float)anim.second.getRect(i).width, (float)anim.second.getRect(i).height, (float)anim.second.getTexOffset(i).x, (float)anim.second.getTexOffset(i).y });
			}
		}
	}
}

RigidBody::~RigidBody()
{}

BoundingBox RigidBody::getBBox()
{
	auto found = aabb.find(owner->animator.getCurrID());
	if (found != aabb.end())
	{ 
		auto foundd = aabb.at(found->first).find(owner->animator.getCurrDir());
		if (foundd != aabb.at(found->first).end())
		{
			if (owner->animator.getCurrIndex() >= foundd->second.size())
			{
				owner->animator.setCurrIndex(0);
			}

			return aabb.at(found->first).at(foundd->first).at(owner->animator.getCurrIndex());

		}
	}
	return BoundingBox{};
}

float& RigidBody::BBoxWidth(std::string id_, std::string dir_, int index_)
{
	return aabb.at(id_).at(dir_).at(index_).w;
}

float& RigidBody::BBoxHeight(std::string id_, std::string dir_, int index_)
{
	return aabb.at(id_).at(dir_).at(index_).h;
}

float& RigidBody::TexOffX(std::string id_, std::string dir_, int index_)
{
	return aabb.at(id_).at(dir_).at(index_).offx;
}

float& RigidBody::TexOffY(std::string id_, std::string dir_, int index_)
{
	return aabb.at(id_).at(dir_).at(index_).offy;
}


sf::Vector2f RigidBody::getPosition()
{
	return sf::Vector2f{posx,posy};
}

void RigidBody::setPosition(sf::Vector2f pos_)
{
	posx = pos_.x;
	posy = pos_.y;
}

void RigidBody::move(sf::Vector2f dx_, float gameTime_)
{
	posx += dx_.x * gameTime_;
	posy += dx_.y * gameTime_;
}

sf::Vector2f RigidBody::getSize(std::string animName_, std::string dir_, int frameIdx_)
{
	return sf::Vector2f{ aabb[animName_].at(dir_).at(frameIdx_).w,aabb[animName_].at(dir_).at(frameIdx_).h};
}

void RigidBody::setSize(sf::Vector2f size_, std::string animName_, std::string dir_, int frameIdx_)
{
	aabb[animName_].at(dir_).at(frameIdx_).w = size_.x;
	aabb[animName_].at(dir_).at(frameIdx_).h = size_.y;
}

sf::Vector2f RigidBody::getVelocity()
{
	return { velx,vely };
}

void RigidBody::setVelocity(sf::Vector2f vel_)
{
	velx = vel_.x;
	vely = vel_.y;
}

void RigidBody::accelerate(sf::Vector2f acc_, float gameTime_)
{
	velx += acc_.x * gameTime_;
	vely += acc_.y * gameTime_;
}

sf::Vector2f RigidBody::getTexOffset(std::string animName_, std::string dir_, int frameIdx_)
{
	return { aabb[animName_].at(dir_).at(frameIdx_).offx, aabb[animName_].at(dir_).at(frameIdx_).offy };
}

void RigidBody::setTexOffset(sf::Vector2f offset_, std::string animName_, std::string dir_, int frameIdx_)
{
	aabb[animName_].at(dir_).at(frameIdx_).offx = offset_.x;
	aabb[animName_].at(dir_).at(frameIdx_).offy = offset_.y;
}

void RigidBody::setRigidBody()
{

	auto& anims = owner->animator.getAnims().getAnims();
	// load all current tex rects from the animations for each direction each anim set has and load them into parallel map here for aabb collision detection
	for (auto& animTri : owner->animator.getAnims().getAnims())
	{
		aabb[animTri.first] = std::unordered_map<std::string, std::vector<BoundingBox>>{};
		aabb[animTri.first].clear();

		for (auto& anim : animTri.second)
		{
			anim.second.getDirType();
			aabb[animTri.first] = {};
			aabb[animTri.first].clear();
			aabb.at(animTri.first)[anim.second.getDirType()] = std::vector<BoundingBox>{};
			aabb.at(animTri.first)[anim.second.getDirType()].clear();
			aabb.at(animTri.first)[anim.second.getDirType()].reserve(anim.second.getRects().size());
			for (int i = 0; i < anim.second.getRects().size(); i++)
			{
				aabb.at(animTri.first)[anim.second.getDirType()] = std::vector<BoundingBox>{};
				aabb.at(animTri.first)[anim.second.getDirType()].clear();
				aabb.at(animTri.first)[anim.second.getDirType()].reserve(anim.second.getRects().size());
				aabb.at(animTri.first)[anim.second.getDirType()].emplace_back(BoundingBox{ (float)anim.second.getFrame(i).width,(float)anim.second.getFrame(i).height,0.f,0.f });

				//aabb.at(animTri.first)[anim.second.getDirType()].push_back(BoundingBox{ (float)anim.second.getRect(i).width, (float)anim.second.getRect(i).height, (float)anim.second.getTexOffset(i).x, (float)anim.second.getTexOffset(i).y });
			}
		}
	}

}
