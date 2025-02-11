#include "Physics.h"
#include <algorithm>
#include <functional>

sf::Vector2f Physics::mpos = {0.f,0.f};

void Physics::updateMouse(sf::RenderWindow& wnd)
{
    Physics::mpos = (sf::Vector2f)sf::Mouse::getPosition(wnd);
}

bool Physics::PointVsStat(sf::Vector2f p, StaticObject& o)
{
    float x1, y1, x2, y2, w, h;
    x1 = p.x;
    y1 = p.y;
    x2 = o.getPosition().x;
    y2 = o.getPosition().y;
    w = o.getBBox().w;
    h = o.getBBox().h;

    return (x1 >= x2 && y1 >= y2 && x1 < x2 + w && y1 < y2 + h);
}

bool Physics::RayVsBBox(sf::Vector2f rayOrigin_, sf::Vector2f rayDir_, const BoundingBox b_, sf::Vector2f targetPos_, sf::Vector2f& cp_, sf::Vector2f& cn_, float& ct_)
{
    sf::Vector2f tNear = { (targetPos_.x - rayOrigin_.x) / rayDir_.x, (targetPos_.y - rayOrigin_.y) / rayDir_.y };
    sf::Vector2f tFar = { (targetPos_.x + b_.w - rayOrigin_.x) / rayDir_.x, (targetPos_.y + b_.h - rayOrigin_.y) / rayDir_.y };

    if (tNear.x > tFar.x) { std::swap(tNear.x, tFar.x); }
    if (tNear.y > tFar.y) { std::swap(tNear.y, tFar.y); }

    if (tNear.x > tFar.y || tNear.y > tFar.x) { return false; }

    ct_ = std::max(tNear.x, tNear.y);
    float tHitFar = std::min(tFar.x, tFar.y);


    if (tHitFar < 0) { return false; }

    cp_ = { rayOrigin_.x + ct_ * rayDir_.x, rayOrigin_.y + ct_ * rayDir_.x };

    if (tNear.x > tNear.y)
    {
        if (rayDir_.x < 0)
        {
            cn_ = {1.f,0.f};
        }
        else
        {
            cn_ = { -1.f,0.f };
        }
    }
    else if (tNear.x < tNear.y)
    {
        if (rayDir_.y < 0)
        {
            cn_ = { 0.f,1.f };
        }
        else
        {
            cn_ = { 0.f,-1.f };
        }
    }
    return true;
}

bool Physics::BBoxVsBBox(BoundingBox b1, sf::Vector2f pos1, BoundingBox& b2, sf::Vector2f pos2)
{
    float x1, y1, w1, h1;
    float x2, y2, w2, h2;
    x1 = pos1.x;
    y1 = pos1.y;
    x2 = pos2.x;
    y2 = pos2.y;
    x1 = pos1.x;
    w1 = b1.w;
    w2 = b2.w;
    h1 = b1.h;
    h2 = b2.h;



    return  (x1 < x2 + w2 && y1 < y2 + h2 && x1 >= x2 && y1 >= y2);
}

bool Physics::BBoxVsBBox(float& x_, float& y_, sf::Vector2f size_, BoundingBox& b2_)
{
    return false;
}

bool Physics::DynoVsBBox(DynamicObject& dyno_, BoundingBox& b_, sf::Vector2f& cp_, sf::Vector2f& cn_, sf::Vector2f& ct_, float gameTime_)
{
    return false;
}

bool Physics::DynoVsStatic(DynamicObject& dyno_, StaticObject& s_, sf::Vector2f& cp_, sf::Vector2f& cn_, float& ct_, float gameTime_)
{
    struct rect
    {
        float& x;
        float& y;
        float& w;
        float& h;
        rect(float& x_, float& y_, float& w_, float& h_) : x{ x_ }, y{ y_ }, w{ w_ }, h{ h_ }
        {}
        rect(rect&) = delete;
        rect& operator=(rect&) = delete;
    };

    rect r1{ dyno_.getRigid().getX(), dyno_.getRigid().getY(), dyno_.BBoxWidth(), dyno_.BBoxHeight() };
    rect r2{ s_.posxRef(), s_.posyRef(), s_.getBBox().w, s_.getBBox().h };

    float x1, y1, w1, h1;
    x1 = r1.x;
    y1 = r1.y;
    w1 = dyno_.BBoxWidth();
    h1 = dyno_.BBoxHeight();

    float x2, y2, w2, h2;
    x2 = s_.posxRef();
    y2 = s_.posyRef();
    w2 = s_.getBBox().w;
    h2 = s_.getBBox().h;

    if (dyno_.getVelocity().x == 0 && dyno_.getVelocity().y == 0)
    {
        return false;
    }
    float x, y, w, h;
    x = x2 - dyno_.getBBoxSize().x / 2.f;
    y = y2 - dyno_.getBBoxSize().y / 2.f;
    w = w2 + w1;
    h = h2 + h1;
    rect expanded_target{ x,y,w,h };
    BoundingBox rBox{ w,h,0.f,0.f };
    // 
      // { dyno_.getVelocity().x* gameTime_, dyno_.getVelocity().y }

    if (RayVsBBox({ dyno_.getPosition().x + dyno_.getBBoxSize().x / 2.f, dyno_.getPosition().y + dyno_.getBBoxSize().y / 2.f }, { dyno_.getVelocity().x * gameTime_, dyno_.getVelocity().y * gameTime_ }, rBox, { expanded_target.x, expanded_target.y }, cp_, cn_, ct_))
    {

        //float overlapX = std::min((dyno_.getPosition().x + dyno_.BBoxWidth()) - expanded_target.x,
        //    (expanded_target.x + rBox.w) - dyno_.getPosition().x);
        //float overlapY = std::min((dyno_.getPosition().y + dyno_.BBoxHeight()) - expanded_target.y,
        //    (expanded_target.y + rBox.h) - dyno_.getPosition().y);

        //if (overlapX < overlapY) {
        //    // Push out horizontally
        //    if (dyno_.getPosition().x < expanded_target.x)
        //    {
        //        dyno_.getRigid().getX() -= overlapX;
        //    }
        //    else
        //    {
        //        dyno_.getRigid().getX() += overlapX;
        //    }
        //}
        //else {
        //    std::cout << "Colliding with ground" << std::endl;
        //    // Push out vertically
        //    if (dyno_.getRigid().getY() < expanded_target.y)
        //    {
        //        dyno_.getRigid().getY() -= overlapY;
        //    }
        //    else
        //    {
        //        dyno_.getRigid().getY() += overlapY;
        //    }
        //}

        if (ct_ <= 1.0f)
        {
            return true;
        /*    if (cn_.y == -1.f)
            {
                dyno_.setVelocity({ dyno_.getVelocity().x, 0.f });
                dyno_.setPosition({ x1, y2 - h1 });
            }
            if (cn_.y == 1.f)
            {
                dyno_.setVelocity({ dyno_.getVelocity().x, 0.f });
                dyno_.setPosition({ x1, y2 });
            }
            if (cn_.x == -1.f)
            {
                if (cn_.y == 0.f)
                {
                    dyno_.setVelocity({ 0.f, dyno_.getVelocity().y });
                    dyno_.setPosition({ x2 - w1, y1 });
                }
            }
            if (cn_.x == 1.f)
            {
                if (cn_.y == 0.f)
                {
                    dyno_.setVelocity({ 0.f, dyno_.getVelocity().y });
                    dyno_.setPosition({ x2, y1 });
                }
            }*/
       
        }
    }

    return false;
}

void Physics::DynoVsTiles(DynamicObject& dyno_, std::vector<Tile*>& s_, sf::Vector2f& cp_, sf::Vector2f& cn_, float& ct_, float gameTime_, bool& moved_)
{
    moved_ = false;
    std::vector<std::pair<Tile*, float> > z;
    for (auto& tile : s_)
    {
        sf::Vector2f cp, cn;
        float ct;

        if (DynoVsStatic(dyno_, *tile, cp, cn, ct, gameTime_))
        {
            z.push_back(std::pair{ tile, ct});
        }
    }

    std::sort(z.begin(), z.end(), [](const std::pair<Tile*,float>& a, const std::pair<Tile*, float>& b) {
        return a.second < b.second;
        });

    for (int i = 0; i < z.size(); i++)
    {
        sf::Vector2f cp, cn;
        float ct;
        float widthPad = 20.f;
        float heightPad = 20.f;

        if (DynoVsStatic(dyno_, *z[i].first, cp, cn, ct, gameTime_))
        {
            float overlapX = std::min((dyno_.getPosition().x + dyno_.BBoxWidth()) - z[i].first->posxRef(),
                (z[i].first->posxRef() + z[i].first->getBBox().w) - dyno_.getPosition().x);
            float overlapY = std::min((dyno_.getPosition().y + dyno_.BBoxHeight()) - z[i].first->posyRef(),
                (z[i].first->posyRef() + z[i].first->getBBox().h) - dyno_.getPosition().y);

            if (overlapX < overlapY) {

                // make sure the y overlap is greater than the padding
                if (overlapY > heightPad)
                {
                    cn.y = 0.f;
                    //// Push out horizontally
                    //if (dyno_.getPosition().x < z[i].first->posxRef())
                    //{
                    //    dyno_.getRigid().getX() -= overlapX;
                    //}
                    //else
                    //{
                    //    dyno_.getRigid().getX() += overlapX;
                    //}
                }
            }
            else {

                // make sure the y overlap is greater than the padding
                if (overlapX > widthPad)
                {
                    cn.x = 0.f;
                    //std::cout << "Colliding with ground" << std::endl;
                    //// Push out vertically
                    //if (dyno_.getRigid().getY() < z[i].first->posyRef())
                    //{
                    //    dyno_.getRigid().getY() -= overlapY;
                    //}
                    //else
                    //{
                    //    dyno_.getRigid().getY() += overlapY;
                    //}
                }
            }

            sf::Vector2f cnVel = dyno_.getVelocity();


            dyno_.setVelocity({ dyno_.getVelocity().x + (cn.x * (abs(dyno_.getVelocity().x) * (1 - ct))),
                dyno_.getVelocity().y + (cn.y * (abs(dyno_.getVelocity().y) * (1 - ct))) });
            dyno_.setPosition({ dyno_.getPosition().x + dyno_.getVelocity().x * gameTime_ + 1.f * cn.x, dyno_.getPosition().y + dyno_.getVelocity().y * gameTime_ });
            if (((dyno_.getVelocity().x < 0.f) && (cnVel.x > 0.f)) || ((dyno_.getVelocity().x > 0.f) && (cnVel.x < 0.f)))
            {
                // bouncing, lets stop that
                dyno_.setVelocity({ 0.f, dyno_.getVelocity().y });
            }
            if (((dyno_.getVelocity().y < 0.f) && (cnVel.y > 0.f)) || ((dyno_.getVelocity().y > 0.f) && (cnVel.y < 0.f)))
            {
                // bouncing, lets stop that
                dyno_.setVelocity({ dyno_.getVelocity().x, 0.f });
            }
            moved_ = true;
        }
    }
    //if (collided)
    //{
    //    dyno_.setPosition({ dyno_.getPosition().x + dyno_.getVelocity().x, dyno_.getPosition().y });
    //}
}

bool Physics::DynoVsDyno(DynamicObject& dyno_, DynamicObject& dyno2_, sf::Vector2f& cp_, sf::Vector2f& cn_, sf::Vector2f& ct_, float gameTime_)
{
    return false;
}

bool Physics::DynoVsRigid(DynamicObject& dyno_, RigidBody& rb_, sf::Vector2f& cp_, sf::Vector2f& cn_, sf::Vector2f& ct_, float gameTime_)
{
    return false;
}

bool Physics::StatVsStat(StaticObject& stat_, StaticObject& stat2_)
{
    return false;
}

bool Physics::StatVsRigid(StaticObject& stat_, RigidBody& rb_)
{
    return false;
}

bool Physics::StatVsBBox(StaticObject& stat_, BoundingBox& b_)
{
    return false;
}
