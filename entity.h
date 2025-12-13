#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "animation.h"
#include "tilemap.h"

class TileMap;

class Entity{
protected:
    // Core Attributes
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::FloatRect collisionBox;
    sf::Texture texture;
    sf::Sprite sprite;

    bool onGround;
    int direction;
    float walkSpeed;
    float speed;
    float gravity;

    // Animation Attributes
    std::map<std::string, Animation> animations;
    std::string currentAnimation;

    // Core Methods
    void moveX(float deltaTime, TileMap* map);
    void moveY(float deltaTime, TileMap* map);
    void collideX(sf::FloatRect tileRect, TileType tileType);
    void collideY(sf::FloatRect tileRect, TileType tileType);

    // Methods Hook
    virtual void onCollideX(TileType tileType);
    virtual void onCollideY(TileType tileType);

    // Animation Methods
    void playAnimation(const std::string& name);
    void playAnimation(const std::string& name, float deltaTime);

public:
    // Core Methods
    Entity(sf::Vector2f givenPosition);
    //virtual ~Entity();
    virtual void update (float deltaTime, TileMap* map);
    virtual void draw (sf::RenderWindow& window);

    // Getters
    sf::Vector2f getPosition() const { return position; };
    sf::Vector2f getCentre() const;

    // Setters
};
