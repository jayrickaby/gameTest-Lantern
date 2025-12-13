#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "player.h"
#include "light.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({1024,1024}), "Lantern Test");
    sf::View camera(sf::FloatRect({0.f, 0.f}, {128.f,128.f}));

    sf::Clock clock;

    // Create Lights
    sf::RenderTexture darknessTexture({128,128});
    LightObject light(sf::Color::Yellow, 63, 8);

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

    musicLayerTwo.setVolume(0.0f);

    // Load Player
    Player player({50.f,50.f});



    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        float deltaTime = clock.restart().asSeconds();

        player.update(deltaTime, &map);
        light.update(player.getCentre());

        darknessTexture.setView(camera);
        darknessTexture.clear(sf::Color::Black);

        light.render(darknessTexture);

        darknessTexture.display();
        window.clear();

        window.setView(camera);
        window.draw(map);

        // Draw the texture
        sf::Sprite darknessSprite(darknessTexture.getTexture());

        window.draw(darknessSprite, sf::BlendAdd);
        window.draw(darknessSprite, sf::BlendMultiply);

        player.render(window);

        window.display();
    }

    return 0;
}
