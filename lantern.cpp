#include <SFML/Graphics.hpp>
#include "lantern.h"

Lantern::Lantern(sf::Vector2f givenPosition, float setIgnited):
    Object::Object(givenPosition),
    ignited(setIgnited),
    lightOff(sf::Color::White, 24, 4),
    lightOn(sf::Color::Yellow, 65, 8),
    offRect({0,0}, {16,16}),
    onRect({16,0}, {16,16})
{
    if (!texture.loadFromFile("assets/sprites/spritesheet.png")){
        assert("Missing texture for player!\n");
    }

    collisionBox.size = {14.f, 16.f};

    animations.emplace("off", Animation({offRect}, 1.0f));
    animations.emplace("on", Animation({onRect}, 1.0f));
}

void Lantern::update() {
    Object::update();

    sf::Vector2f centre = getCentre();

    if (ignited){
        playAnimation("on");
        lightOn.update(centre);
    }
    else {
        playAnimation("off");
        lightOff.update(centre);
    }
}

void Lantern::drawLight(sf::RenderTarget& target){
    if (ignited){
        lightOn.draw(target);
    }
    else {
        lightOff.draw(target);
    }
}

