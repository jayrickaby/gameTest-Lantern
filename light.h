#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>


class LightObject{
public:
    LightObject(sf::Color givenColour, uint givenSize, int givenSteps);
    void update(sf::Vector2f givenPosition);
    void render(sf::RenderTexture &cutoutTexture);

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
