#pragma once
#include <SFML/Graphics.hpp>
#include "light.h"
#include "object.h"

class Lantern : public Object{
public:
    // Core Methods
    Lantern(sf::Vector2f givenPosition, float setIgnited);
    void update() override;
    void drawLight(sf::RenderTarget& target);

    // Getters
    bool isIgnited() const {return ignited;}

    // Setter
    void setIgnited();

private:
    // Core Attributes
    bool ignited = false;
    LightObject lightOff;
    LightObject lightOn;

    sf::IntRect offRect;
    sf::IntRect onRect;
};
