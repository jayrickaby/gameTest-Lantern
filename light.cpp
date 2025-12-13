#include <SFML/Graphics.hpp>
#include "light.h"

LightObject::LightObject(sf::Color givenColour, uint givenSize, int givenSteps):
    colour(givenColour),
    size(givenSize),
    steps(givenSteps),
    lightGradient(createLightGradient()),
    lightTexture(lightGradient),
    lightSprite(lightTexture)
{
    lightSprite.setOrigin({static_cast<float>(size) / 2, static_cast<float>(size) / 2});
    lightSprite.setColor(colour);
};

void LightObject::update(sf::Vector2f givenPosition) {
    lightSprite.setPosition(givenPosition);
}

void LightObject::draw(sf::RenderTexture &cutoutTexture) {
    cutoutTexture.draw(lightSprite);
}


sf::Image LightObject::createLightGradient() {
    sf::Image gradient({size, size}, sf::Color::Black);

    float center = size / 2.f;
    float radius = size / 2.f;

    for (uint8_t y = 0; y < size; y++) {
        for (uint8_t x = 0; x < size; x++) {
            float dx = x - center;
            float dy = y - center;
            float distance = std::sqrt(dx*dx + dy*dy);

            // Calculate brightness based on distance from center
            float brightness = 1.0f - (distance / radius);
            brightness = std::max(0.f, brightness);  // Clamp to 0-1

            // Quantize to steps
            brightness = std::floor(brightness * steps) / steps;

            // Set pixel to grayscale value
            uint8_t gray = static_cast<uint8_t>(brightness * 255);
            gradient.setPixel({x, y}, sf::Color(gray, gray, gray));
        }
    }

    return gradient;
}

void LightObject::setColor(sf::Color newColour) {
    colour = newColour;
    lightSprite.setColor(colour);
}
