#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "player.h"
#include "lantern.h"
#include "light.h"

// Copyright (c) 2025 Jay Rickaby

int main() {
    sf::RenderWindow window(sf::VideoMode({1024,1024}), "Lantern Test");
    sf::View camera(sf::FloatRect({0.f, 0.f}, {128.f,128.f}));

    sf::Clock clock;

    // Create Light Textures
    sf::RenderTexture darknessTexture({128,128});
    sf::RenderTexture glowTexture({128, 128});

    // Create Lights & Lanterns
    LightObject light(sf::Color::White, 63, 8);
    Lantern lantern({112.f, 80.f}, false);

    // Load Map
    TileMap map;
    std::vector<int> levelData{
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        6,  7,  8,  9,  6,  7,  8,  9,  6,  7,  8,  9,  6,  7,  8,  9,
        10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13,
        10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13,
        10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13
    };
    map.load("assets/sprites/spritesheet.png", {8, 8}, levelData.data(), 16, 16);

    // Load Music
    sf::Music musicLayerOne("assets/music/gametest-lantern-layer1.ogg");
    sf::Music musicLayerTwo("assets/music/gametest-lantern-layer2.ogg");

    musicLayerOne.setLooping(true);
    musicLayerTwo.setLooping(true);

    musicLayerOne.play();
    musicLayerTwo.play();

    musicLayerTwo.setVolume(0);

    // Load Player
    Player player({50.f,50.f});

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        float deltaTime = clock.restart().asSeconds();

        // Update functions
        player.update(deltaTime, &map);
        light.update(player.getCentre());
        lantern.update();

        // Ignites the lantern, fades in layer two of music
        if (!lantern.isIgnited()){
            if (player.getCollisionBox().findIntersection(lantern.getCollisionBox())){
                lantern.setIgnited();
            }
        } else {
            if (musicLayerTwo.getVolume() < 100){
                musicLayerTwo.setVolume(musicLayerTwo.getVolume() + 12.5 *deltaTime);
            } else {
                musicLayerTwo.setVolume(100.f);
            }
        }

        // Configure render targets
        window.setView(camera);
        darknessTexture.setView(camera);
        glowTexture.setView(camera);

        // Clear Screen and Textures
        window.clear();
        darknessTexture.clear(sf::Color::Black);
        glowTexture.clear(sf::Color::Transparent);

        // Draw glows and darkness cutouts to respective texture
        lantern.drawLight(darknessTexture);
        light.draw(darknessTexture);
        if (lantern.isIgnited()){
            lantern.drawLight(glowTexture);
        }

        // Finalise and update texture data
        darknessTexture.display();
        glowTexture.display();

        // Construct sprites from source textures
        sf::Sprite darknessSprite(darknessTexture.getTexture());
        sf::Sprite glowSprite(glowTexture.getTexture());

        // Draw to the screen
        // We want the Player to be able to be obscured by darkness if needed.
        window.draw(map);
        window.draw(darknessSprite, sf::BlendMultiply);
        window.draw(glowSprite, sf::BlendAdd);
        lantern.draw(window);
        player.draw(window);

        // Finalise and update the screen!
        window.display();
    }

    return 0;
}
