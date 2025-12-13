#include <SFML/Graphics.hpp>
#include "entity.h"
#include "tilemap.h"
#include <iostream>

Entity::Entity(sf::Vector2f givenPosition):
    texture("assets/sprites/missing.png"),
    sprite(texture),
    direction(0),
    walkSpeed(64),
    speed(walkSpeed),
    gravity(450)
{
    // Proper setup
    collisionBox.position = givenPosition;
    collisionBox.size = {14.f, 16.f};
}

void Entity::update(float deltaTime, TileMap* map) {
    // x-axis
    velocity.x = speed*direction;
    moveX(deltaTime, map);
    // y-axis
    velocity.y += gravity * deltaTime;
    moveY(deltaTime, map);

    // update position
    position = collisionBox.position;
    sprite.setPosition(position);
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Entity::moveX(float deltaTime, TileMap* map) {
    collisionBox.position.x += (velocity.x * deltaTime);
    TileRect tiles = map->getTileRect(collisionBox, 8);

    // Check for solid tiles to left or right
    for (int y = tiles.startY; y <= tiles.endY; y++){
        for (int x = tiles.startX; x <= tiles.endX; x++){
            if (map->getTileType(x,y) == TileType::Solid){
                sf::FloatRect tileRect({x*8.f, y*8.f}, {8, 8});

                if (collisionBox.findIntersection(tileRect).has_value()){
                    collideX(tileRect, map->getTileType(x,y));
                }
            }
        }
    }
}

void Entity::moveY(float deltaTime, TileMap* map) {
    collisionBox.position.y += (velocity.y * deltaTime);
    TileRect tiles = map->getTileRect(collisionBox, 8);

    // Always assume player is floating
    onGround = false;

    // Check for solid tiles up or down
    for (int y = tiles.startY; y <= tiles.endY; y++){
        for (int x = tiles.startX; x <= tiles.endX; x++){
            if (map->getTileType(x,y) == TileType::Solid){
                sf::FloatRect tileRect({x*8.f, y*8.f}, {8, 8});

                if (collisionBox.findIntersection(tileRect).has_value()){
                    collideY(tileRect, map->getTileType(x,y));
                }
            }
        }
    }
}

void Entity::collideX(sf::FloatRect tileRect, TileType tileType) {
    sf::FloatRect overlap = *collisionBox.findIntersection(tileRect);

    if (overlap.size.x < overlap.size.y){
        if (velocity.x > 0){
            collisionBox.position.x -= overlap.size.x;
        } else if (velocity.x < 0){
            collisionBox.position.x += overlap.size.x;
        }

        //onCollideX(tileType);
        velocity.x = 0;
    }
}

void Entity::onCollideX(TileType tileType) {
    velocity.x = 0;
}

void Entity::collideY(sf::FloatRect tileRect, TileType tileType) {
    sf::FloatRect overlap = *collisionBox.findIntersection(tileRect);

    if (overlap.size.y < overlap.size.x){
        if (velocity.y > 0){
            collisionBox.position.y -= overlap.size.y;
            onGround = true;
        } else if (velocity.y < 0){
            collisionBox.position.y += overlap.size.y;
        }

        //onCollideY(tileType);
        velocity.y = 0;
    }
}

void Entity::onCollideY(TileType tileType) {
    velocity.y = 0;
}

void Entity::playAnimation(const std::string& name) {
    if (currentAnimation != name){
        currentAnimation = name;
        animations.at(name).reset();
    }
    sprite.setTextureRect(animations.at(currentAnimation).getCurrentFrame());
}


void Entity::playAnimation(const std::string& name, float deltaTime) {
    if (currentAnimation != name){
        currentAnimation = name;
        animations.at(name).reset();
    }
    animations.at(currentAnimation).update(deltaTime);
    sprite.setTextureRect(animations.at(currentAnimation).getCurrentFrame());
}

sf::Vector2f Entity::getCentre() const {
    float originX = position.x + collisionBox.size.x / 2;
    float originY = position.y + collisionBox.size.y / 2;

    return sf::Vector2f{originX, originY};
}


