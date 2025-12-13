#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>


class LightObject{
public:
    LightObject(uint givenSize, int givenSteps);
    void update(sf::Vector2f givenPosition);
    void render(sf::RenderTexture &cutoutTexture);
private:
    float size;

    sf::Image lightGradient;
    sf::Texture lightTexture;
    sf::Sprite lightSprite;

    sf::Image createLightGradient(uint size, int steps);
};
