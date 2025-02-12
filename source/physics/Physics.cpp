#include "Physics.h"
#include <algorithm>
#include <functional>

sf::Vector2f Physics::mpos = {0.f,0.f};
std::vector<std::tuple<Tile*, float, sf::Vector2f, sf::Vector2f>> Physics::collisions = {};
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

    std::cout << "tNear.x: " << tNear.x << " | tNear.y: " << tNear.y << std::endl;
    std::cout << "tFar.x: " << tFar.x << " | tFar.y: " << tFar.y << std::endl;
    std::cout << "Raw ct_: " << ct_ << std::endl;



    float tHitFar = std::min(tFar.x, tFar.y);


    if (tHitFar < 0) { return false; }

    cp_ = { rayOrigin_.x + ct_ * rayDir_.x, rayOrigin_.y + ct_ * rayDir_.x };

    sf::Vector2f normalX = { 0.f, 0.f };
    sf::Vector2f normalY = { 0.f, 0.f };



    if (tNear.x > tNear.y)
    {
        if (rayDir_.x < 0)
        {
            normalX = {1.f,0.f};
        }
        else
        {
            normalX = { -1.f,0.f };
        }
    }
    else if (tNear.x < tNear.y)
    {
        if (rayDir_.y < 0)
        {
            normalY = { 0.f,1.f };
        }
        else
        {
            normalY = { 0.f,-1.f };
        }
    }

    cn_ = {normalX.x, normalY.y};


    

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
    sf::Vector2f rayDir_ = { dyno_.getVelocity().x * gameTime_, dyno_.getVelocity().y * gameTime_ };
    if (RayVsBBox({ dyno_.getPosition().x + dyno_.getBBoxSize().x / 2.f, dyno_.getPosition().y + dyno_.getBBoxSize().y / 2.f }, rayDir_, rBox, { expanded_target.x, expanded_target.y }, cp_, cn_, ct_))
    {
        if (cn_.x == 1.f)
        {
            int i = 0;

        }
        std::cout << "Before correction, ct_: " << ct_ << std::endl;
        if (ct_ > 0) {
            float correction = (dyno_.BBoxWidth() / 4) / std::max(std::abs(rayDir_.x), 10.0f);
            if (correction < ct_) {
                ct_ -= correction;
            }
            else {
                ct_ = 0.01f;
            }
        }
        std::cout << "After correction, ct_: " << ct_ << std::endl;

        if (ct_ <= 1.0f)
        {
            return true;
        }
    }

    return false;
}

//void Physics::DynoVsTiles(DynamicObject& dyno_, std::vector<Tile*>& s_, sf::Vector2f& cp_, sf::Vector2f& cn_, float& ct_, float gameTime_, bool& moved_)
//{
//    collisions.clear();
//    
//    moved_ = false;
//    std::vector<std::pair<Tile*, float> > z;
//    for (auto& tile : s_)
//    {
//        sf::Vector2f cp, cn;
//        float ct;
//
//        if (DynoVsStatic(dyno_, *tile, cp, cn, ct, gameTime_))
//        {
//            collisions.emplace_back(std::tuple<Tile*, float, sf::Vector2f, sf::Vector2f>{tile, ct, cp, cn});
//
//            z.push_back(std::pair{ tile, ct});
//        }
//    }
//
//    std::sort(z.begin(), z.end(), [](const std::pair<Tile*,float>& a, const std::pair<Tile*, float>& b) {
//        return a.second < b.second;
//        });
//    std::sort(collisions.begin(), collisions.end(),
//        [](const auto& a, const auto& b) {
//            return std::get<1>(a) < std::get<1>(b); // Sort by contact time
//        });
//
//
//    for (int i = 0; i < collisions.size(); i++)
//    {
//        sf::Vector2f cp, cn;
//        float ct;
//        float widthPad = 20.f;
//        float heightPad = 20.f;
//
//        if (DynoVsStatic(dyno_, *std::get<0>(collisions[i]), cp, cn, ct, gameTime_))
//        {
//
//            sf::Vector2f strongestNormal = { 0.f, 0.f };
//            float minDot = 1.0f; // Start with max possible dot value
//
//            Tile* tilee;
//            sf::Vector2f cpp, cnn;
//            float ctt;
//            for (const auto& [tilee, ctt, cpp, cnn] : collisions)
//            {
//                sf::Vector2f moveDir = dyno_.getVelocity();
//                float dotProduct = std::abs(moveDir.x * cn.x + moveDir.y * cn.y);
//
//                if (dotProduct < minDot) {
//                    minDot = dotProduct;
//                    strongestNormal = cn;
//                }
//            }
//
//            dyno_.setVelocity({
//                 dyno_.getVelocity().x + (strongestNormal.x * (abs(dyno_.getVelocity().x) * (1 - ct_))),
//                 dyno_.getVelocity().y + (strongestNormal.y * (abs(dyno_.getVelocity().y) * (1 - ct_)))
//                });
//
//            dyno_.setPosition({
//                dyno_.getPosition().x + dyno_.getVelocity().x * gameTime_ + 1.f * strongestNormal.x,
//                dyno_.getPosition().y + dyno_.getVelocity().y * gameTime_ + 1.f * strongestNormal.y
//                });
//
//            //float overlapX = std::min((dyno_.getPosition().x + dyno_.BBoxWidth()) - z[i].first->posxRef(),
//            //    (z[i].first->posxRef() + z[i].first->getBBox().w) - dyno_.getPosition().x);
//            //float overlapY = std::min((dyno_.getPosition().y + dyno_.BBoxHeight()) - z[i].first->posyRef(),
//            //    (z[i].first->posyRef() + z[i].first->getBBox().h) - dyno_.getPosition().y);
//
//            //if (overlapX < overlapY) {
//
//            //    // make sure the y overlap is greater than the padding
//            //    if (overlapY > heightPad)
//            //    {
//            //        cn.y = 0.f;
//            //    }
//            //}
//            //else {
//
//            //    // make sure the y overlap is greater than the padding
//            //    if (overlapX > widthPad)
//            //    {
//            //        cn.x = 0.f;
//            //    }
//            //}
//
//            //sf::Vector2f cnVel = dyno_.getVelocity();
//
//
//            //dyno_.setVelocity({ dyno_.getVelocity().x + (cn.x * (abs(dyno_.getVelocity().x) * (1 - ct))),
//            //    dyno_.getVelocity().y + (cn.y * (abs(dyno_.getVelocity().y) * (1 - ct))) });
//            //dyno_.setPosition({ dyno_.getPosition().x + dyno_.getVelocity().x * gameTime_ + 1.f * cn.x, dyno_.getPosition().y + dyno_.getVelocity().y * gameTime_ });
//            //if (((dyno_.getVelocity().x < 0.f) && (cnVel.x > 0.f)) || ((dyno_.getVelocity().x > 0.f) && (cnVel.x < 0.f)))
//            //{
//            //    // bouncing, lets stop that
//            //    dyno_.setVelocity({ 0.f, dyno_.getVelocity().y });
//            //}
//            //if (((dyno_.getVelocity().y < 0.f) && (cnVel.y > 0.f)) || ((dyno_.getVelocity().y > 0.f) && (cnVel.y < 0.f)))
//            //{
//            //    // bouncing, lets stop that
//            //    dyno_.setVelocity({ dyno_.getVelocity().x, 0.f });
//            //}
//            //moved_ = true;
//
//
//         
//        }
//    }
//}

void Physics::DynoVsTiles(DynamicObject& dyno_, std::vector<Tile*>& s_, sf::Vector2f& cp_, sf::Vector2f& cn_, float& ct_, float gameTime_, bool& movedx_, bool& movedy_)
{
    collisions.clear();
    movedy_ = false;
    sf::Vector2f cp{}, cn{};
    float ct{1.f};
    // Collect collision candidates
    for (auto& tile : s_)
    {
        //sf::Vector2f cp, cn;
        //float ct;
        ct = 1.f;
        if (DynoVsStatic(dyno_, *tile, cp, cn, ct, gameTime_))
        {
            std::cout << "YUP" << std::endl;
            collisions.emplace_back(std::tuple<Tile*, float, sf::Vector2f, sf::Vector2f>{tile, ct, cp, cn});
        }
    }

    // Sort collisions by contact time (earlier collisions resolved first)
    std::sort(collisions.begin(), collisions.end(),
        [](const auto& a, const auto& b) {
            return std::get<1>(a) < std::get<1>(b); // Compare by contact time
        });

    // Find the strongest normal
    sf::Vector2f strongestNormal = { 0.f, 0.f };
    float minDot = 1.0f;  // Track the most perpendicular normal
    float bestCt = 1.0f;  // Store the smallest contact time
    Tile* CurrTile{ nullptr };
    
    sf::Vector2f  cpOut{};
    for (auto& [tile, ct, cp, cn] : collisions)
    {
        

        //if (ct < 0 || ct > 1) {
        //    std::cout << "WARNING: Contact time out of range! Clamping ct: " << ct << std::endl;
        //    ct = std::max(0.0f, std::min(ct, 1.0f));  // Clamp to 0-1 range
        //}

        

        

        sf::Vector2f moveDir = dyno_.getVelocity();
        float length = std::sqrt(moveDir.x * moveDir.x + moveDir.y * moveDir.y);
        if (dyno_.getVelocity().x != 0)
        {
            int i = 0;
        }
        if (length > 0.0f) {
            moveDir /= length;  // Normalize the movement direction
        }
        float dotProduct = std::abs(moveDir.x * cn.x + moveDir.y * cn.y);

       // sf::Vector2f moveDir = dyno_.getVelocity();
        //float dotProduct = std::abs(moveDir.x * cn.x + moveDir.y * cn.y);
      

        std::cout << "Collision Normal: " << cn.x << ", " << cn.y << " | Contact Time: " << ct << std::endl;
        std::cout << "MoveDir: " << moveDir.x << ", " << moveDir.y << std::endl;
        std::cout << "Collision Normal: " << cn.x << ", " << cn.y << std::endl;
        std::cout << "Dot Product: " << dotProduct << " | MinDot: " << minDot << std::endl;

        //if (ct < 0) {
        //    std::cout << "WARNING: Player is inside the tile! Adjusting..." << std::endl;
        //    ct = 0;  // Reset to zero to prevent incorrect physics calculations
        //}

       

        if (dotProduct <= minDot)
        {
            minDot = dotProduct;
            strongestNormal = cn;
            bestCt = std::max(0.0f, std::min(ct, 1.0f));  // Clamp between 0 and 1
            cpOut = cp;
            CurrTile = tile;
        }


        //if (cn.y < 0 && cp.y > cpOut.y) { // 🚀 Pick the lowest Y value
        //    cpOut = cp;
        //}

    }

    // Use last known collision normal if no new one is found
   

    std::cout << "Collision Normal recheck: " << cn.x << ", " << cn.y << " | Contact Time: " << ct << std::endl;
    if (strongestNormal == sf::Vector2f{ 0.f, 0.f }) {
        // If no new collision is detected, keep the last valid normal but don't reset position
        strongestNormal = dyno_.getLastCollisionNormal();
    }
    else {
        dyno_.setLastCollisionNormal(strongestNormal);
    }
    // Stop movement along the strongest normal
    sf::Vector2f newVelocity = dyno_.getVelocity();
    if (strongestNormal.y < 0 && CurrTile != nullptr) { // Standing on the ground
        newVelocity.y = 0;

        // 🚀 Fix for teleporting too far up - prevent overshooting!
        float correctedY = CurrTile->getPosition().y - dyno_.BBoxHeight() / 2.f;
        if (dyno_.getPosition().y > correctedY) {
            dyno_.setPosition({ dyno_.getPosition().x, correctedY });
            movedy_ = true;
        }
        else {
            std::cout << "playerY: " << dyno_.getRigid().getY() << ", correctedY: " << correctedY << std::endl;
        }

        /*std::cout << "Corrected Y-Position Target: " << cpOut.y - (dyno_.BBoxHeight()/2.f)-1.f << std::endl;

        dyno_.setPosition({ dyno_.getPosition().x, cpOut.y - (dyno_.BBoxHeight() / 2.f) - 1.f });
        std::cout << "Applying ground collision resolution!" << std::endl;*/
    }
    // 🚀 🚀 🚀 NEW CODE TO FIX WALL CLIMBING 🚀 🚀 🚀
    if (strongestNormal.x != 0) { // Hitting a wall
        std::cout << "Applying wall collision resolution!" << std::endl;
        newVelocity.x = 0;
        movedx_ = true;

        // 🚀 NEW: Fix for getting stuck inside the wall
        float correctedX = (strongestNormal.x > 0) ?
            CurrTile->getPosition().x + CurrTile->getSize().x :
            CurrTile->getPosition().x - dyno_.BBoxWidth() / 2.f;

        if ((strongestNormal.x > 0 && dyno_.getPosition().x < correctedX) ||
            (strongestNormal.x < 0 && dyno_.getPosition().x > correctedX)) {
            dyno_.setPosition({ correctedX, dyno_.getPosition().y });
        }

        // Ensure Y correction doesn’t happen if colliding with a wall
        if (std::abs(strongestNormal.y) < 0.001f) {
            std::cout << "Wall Collision: Stopping X movement without Y correction." << std::endl;
        }
    }

    std::cout << "New Velocity Being Set: " << newVelocity.x << ", " << newVelocity.y << std::endl;
    dyno_.setVelocity(newVelocity);

  
    if (dyno_.getVelocity().y == 0 && strongestNormal.y < 0) {
        float correctedY = CurrTile->getPosition().y - dyno_.BBoxHeight();

        // 🚀 Add a small buffer zone to prevent constant correction
        if (std::abs(dyno_.getPosition().y - correctedY) > 0.05f) {
            std::cout << "Forcing position correction due to stuck collision!" << std::endl;
            dyno_.setPosition({ dyno_.getPosition().x, correctedY - 0.1f });
        }
    }
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
