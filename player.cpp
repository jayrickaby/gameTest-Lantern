#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"

Player::Player(sf::Vector2f givenPosition):
    Entity::Entity(sf::Vector2f(givenPosition)),
    jumpStrength(150.f),
    idleRect({32,0}, {16,16})
{
    if (!texture.loadFromFile("assets/sprites/spritesheet.png")){
        assert("Missing texture for player!\n");
    }

    animations.emplace("idle", Animation({idleRect}, 1.0f));
}

void Player::handleInput(float deltaTime) {
    direction = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) - (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));
    playAnimation("idle");

    if (onGround){
        canJump = true;
    } else {
        canJump = false;
    }

    if (canJump){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
            // Let player jump
            velocity.y = -jumpStrength;
        }
    }

    if (direction != 0){
        // Adjusts direction of sprite to the same direction as movement
        if (currentAnimation == "lookUp"){
            direction = 0;
        }
    }
}

void Player::update(float deltaTime, TileMap* map) {
    speed = walkSpeed;
    handleInput(deltaTime);
    Entity::update(deltaTime, map);
}


