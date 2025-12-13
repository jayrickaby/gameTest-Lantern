#pragma once
#include <SFML/Graphics.hpp>
#include "object.h"
#include "tilemap.h"

// Copyright (c) 2025 Jay Rickaby

class TileMap;

class Entity : public Object{
public:
    // Core Methods
    Entity(sf::Vector2f givenPosition);
    virtual void update() override;
    virtual void update(float deltaTime, TileMap* map);

protected:
    // Core Attributes
    sf::Vector2f velocity;

    bool onGround;
    int direction;
    float walkSpeed;
    float speed;
    float gravity;

    // Core Methods
    void moveX(float deltaTime, TileMap* map);
    void moveY(float deltaTime, TileMap* map);
    void collideX(sf::FloatRect tileRect, TileType tileType);
    void collideY(sf::FloatRect tileRect, TileType tileType);

    // Methods Hook
    virtual void onCollideX(TileType tileType);
    virtual void onCollideY(TileType tileType);
};
