#pragma once
#include "entity.h"
#include <SFML/Graphics.hpp>

// Copyright (c) 2025 Jay Rickaby

class Player : public Entity{
public:
    // Core Functions
    Player(sf::Vector2f givenPosition);
    void update(float deltaTime, TileMap* map) override;
    void handleInput(float deltaTime);

private:
    // Core Attributes
    float jumpStrength;
    bool canJump;

    // Animation Attributes
    sf::IntRect idleRect;
};
