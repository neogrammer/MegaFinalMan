#ifndef PHYSICS_H__
#define PHYSICS_H__

#include <SFML/System/Vector2.hpp>
#include "../physics/BoundingBox.h"
#include "../objects/DynamicObject.h"
#include "../tilemap/Tilemap.h"
#include <iostream>
#include "../tilemap/Tile.h"
class Physics {
public:
    Physics() = delete; // Prevent instantiation

    // AABB collision check
    static bool checkCollision(const BoundingBox& a, sf::Vector2f posA, const BoundingBox& b, sf::Vector2f posB) {
        return (posA.x < posB.x + b.w && posA.x + a.w > posB.x &&
            posA.y < posB.y + b.h && posA.y + a.h > posB.y);
    }

    // Basic collision resolution - pushes objects out of overlap
    static void resolveCollision(DynamicObject& obj, Tilemap& tilemap) {
        sf::Vector2f objPos = obj.getPosition(); // top-left
        BoundingBox objBox = {
            obj.BBoxWidth(),  // width
            obj.BBoxHeight(),  // height
            0.f,
            0.f
        };

        for (auto& tile : tilemap.getVisibleTiles()) 
        { 
            Tile tmp = *tile;
            tmp.setPosition({ tmp.getPosition().x - obj.BBoxWidth() / 2.f, tmp.getPosition().y - obj.BBoxHeight() / 2.f });
            tmp.setSize({tmp.getSize().x + obj.getBBoxSize().x, tmp.getSize().y + obj.getBBoxSize().y });
            if (checkCollision(objBox, objPos, tmp.getBBox(), tmp.getPosition()))
            {
                // Push out along the smallest penetration axis
                std::cout << "Colliding with ground" << std::endl;

                sf::Vector2f tilePos = tmp.getPosition(); // top-left
                BoundingBox tileBox = tmp.getBBox();      // tile->getBBox().w, tile->getBBox().h

                float overlapX = std::min((objPos.x + objBox.w) - tilePos.x,
                    (tilePos.x + tileBox.w) - objPos.x);
                float overlapY = std::min((objPos.y + objBox.h) - tilePos.y,
                    (tilePos.y + tileBox.h) - objPos.y);

                if (overlapX < overlapY) {
                    // Push out horizontally
                    if (objPos.x < tilePos.x) objPos.x -= overlapX;
                    else objPos.x += overlapX;
                }
                else {
                    std::cout << "Colliding with ground" << std::endl;
                    // Push out vertically
                    if (objPos.y < tilePos.y) objPos.y -= overlapY;
                    else objPos.y += overlapY;
                }
                obj.setPosition(objPos);
            }
        }
    }

    // Apply gravity
    static void applyGravity(DynamicObject& obj, float deltaTime) {
        sf::Vector2f velocity = obj.getVelocity();
        velocity.y += 981.f * deltaTime; // Gravity constant (adjust as needed)
        obj.setVelocity(velocity);
    }

    // General movement with collision
    static void applyMovement(DynamicObject& obj, float deltaTime, Tilemap& tilemap) {
        sf::Vector2f velocity = obj.getVelocity();
        sf::Vector2f newPos = obj.getPosition() + velocity * deltaTime;
        obj.setPosition(newPos);
//        resolveCollision(obj, tilemap);
    }
};

#endif // PHYSICS_H__