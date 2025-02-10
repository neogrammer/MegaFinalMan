#include "Physics.h"
#include <iostream>
bool Physics::ptVrect(v2 pos, v2 rectPos, v2 rectSize)
{
    return (pos.x < rectPos.x + rectSize.x && pos.x > rectPos.x &&
        pos.y < rectPos.y + rectSize.y && pos.y > rectPos.y);
}

bool Physics::rectVrect(v2 posA, v2 sizeA, v2 posB, v2 sizeB)
{
    return (posA.x < posB.x + sizeB.x && posA.x + sizeA.x > posB.x &&
        posA.y < posB.y + sizeB.y && posA.y + sizeA.y > posB.y);
}




bool Physics::rayVrect(v2 halfsz, v2 ray_origin, v2 ray_dir, v2 targetPos, v2 targetSize, v2& cp, v2& cn, float& t_hit_near, float dt)
{
    v2 t_near = (v2{ (targetPos.x - ray_origin.x) / ray_dir.x,  (targetPos.y - ray_origin.y) / ray_dir.y });
    v2 t_far = (v2{ (targetPos.x + targetSize.x - ray_origin.x) / ray_dir.x ,  (targetPos.y + targetSize.y - ray_origin.y) / ray_dir.y });

    if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
    if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

    if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

   t_hit_near = std::max(t_near.x, t_near.y);
    float t_hit_far = std::min(t_far.x, t_far.y);

    if (t_hit_far < 0) return false;

    cp = v2{ray_origin.x + t_hit_near * ray_dir.x, ray_origin.y + t_hit_near * ray_dir.y };


    if (t_near.x > t_near.y)
    {
        if (ray_dir.x < 0)
        {
            cn = v2{ 1.f,0.f };
        }
        else
        {
            cn = v2{ -1.f,0.f };
        }
    }
    else if (t_near.x < t_near.y)
    { 
        if (ray_dir.y < 0)
        {
            cn = v2{ 0.f,1.f };
        }
        else
        {
            cn = v2{ 0.f,-1.f };
        }
    }

    if (t_hit_near < 1.0f)
        return true;
    else
        return false;
}

bool Physics::dynamicVrect(v2& posA, v2 sizeA, v2& vel, v2 targetPos, v2 targetSize, v2& cp, v2& cn, float& ct, float dt)
{
    if (vel.x == 0 && vel.y == 0)
    {
        return false;
    }

    v2 expandedTargetPos =v2{ targetPos.x - sizeA.x / 2.f, targetPos.y - sizeA.y / 2.f };
    v2 expandedTargetSize = v2{targetSize.x + sizeA.x,targetSize.y + sizeA.y };

    if (rayVrect(v2{ sizeA.x / 2.f , sizeA.y / 2.f }, v2{ posA.x + sizeA.x / 2.f ,posA.y + sizeA.y / 2.f }, v2{ vel.x * dt, vel.y * dt }, expandedTargetPos, expandedTargetSize, cp, cn, ct, dt))
    {
        if (ct < 1.f && ct >= 0.f)
            return true;
    }
    return false;
}
