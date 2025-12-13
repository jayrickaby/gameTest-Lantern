#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "animation.h"

class Object{
public:
    Object(sf::Vector2f givenPosition);
    virtual void update ();
    virtual void draw (sf::RenderTarget& target) const;

    // Getters
    sf::Vector2f getCentre() const;
    sf::Vector2f getPosition() const { return position; };

    sf::FloatRect getCollisionBox() const { return collisionBox;}

protected:
    // Core Attributes
    sf::Vector2f position;
    sf::FloatRect collisionBox;
    sf::Texture texture;
    sf::Sprite sprite;

    // Animation Attributes
    std::map<std::string, Animation> animations;
    std::string currentAnimation;

    // Animation Methods
    void playAnimation(const std::string& name);
    void playAnimation(const std::string& name, float deltaTime);
};
