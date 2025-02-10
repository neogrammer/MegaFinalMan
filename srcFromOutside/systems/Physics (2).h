#ifndef PHYSICS_H__
#define PHYSICS_H__

#include "misc/v2.h"
#include "entity/Entity.h"
#include "world/Tilemap.h"
#include <utility>
class Physics
{
public:
	Physics() = delete;

  	static bool ptVrect(v2 pos, v2 rectPos, v2 rectSize);
	static bool rectVrect(v2 posA, v2 sizeA, v2 posB, v2 sizeB);
	static bool rayVrect(v2 halfsz, v2 ray_origin, v2 ray_dir, v2 targetPos, v2 targetSize, v2& cp, v2& cn, float& ct, float dt);
	static bool dynamicVrect(v2& posA, v2 sizeA, v2& vel, v2 targetPos, v2 targetSize, v2& cp, v2& cn, float& ct, float dt);
};


#endif