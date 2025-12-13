#include "object.h"

Object::Object(sf::Vector2f givenPosition):
    texture("assets/sprites/missing.png"),
    sprite(texture)
{
    collisionBox.position = givenPosition;
}

void Object::update() {
    position = collisionBox.position;
    sprite.setPosition(position);
}

void Object::draw(sf::RenderTarget& target) const{
    target.draw(sprite);
}

void Object::playAnimation(const std::string& name) {
    if (currentAnimation != name){
        currentAnimation = name;
        animations.at(name).reset();
    }
    sprite.setTextureRect(animations.at(currentAnimation).getCurrentFrame());
}

void Object::playAnimation(const std::string& name, float deltaTime) {
    if (currentAnimation != name){
        currentAnimation = name;
        animations.at(name).reset();
    }
    animations.at(currentAnimation).update(deltaTime);
    sprite.setTextureRect(animations.at(currentAnimation).getCurrentFrame());
}

sf::Vector2f Object::getCentre() const {
    float centreX = position.x + collisionBox.size.x / 2;
    float centreY = position.y + collisionBox.size.y / 2;

    return sf::Vector2f{centreX, centreY};
}


