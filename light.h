#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

// Copyright (c) 2025 Jay Rickaby

class LightObject{
public:
    LightObject(sf::Color givenColour, uint givenSize, int givenSteps);
    void update(sf::Vector2f givenPosition);
    void draw(sf::RenderTarget& target);

    // Setters
    void setColor(sf::Color newColour);

private:
    sf::Color colour;
    uint size;
    uint steps;

    sf::Image lightGradient;
    sf::Texture lightTexture;
    sf::Sprite lightSprite;

    sf::Image createLightGradient();
};
