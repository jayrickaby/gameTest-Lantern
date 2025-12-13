#pragma once
#include <SFML/Graphics.hpp>

// Copyright (c) 2025 Jay Rickaby

enum class TileType {
    Air = 0,
    Solid = 1,
};

struct TileRect {
    int startX, startY;
    int endX, endY;
};

class TileMap : public sf::Drawable, public sf::Transformable{
public:
    bool load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    TileType getTileType(int x, int y);
    TileRect getTileRect(const sf::FloatRect& bounds, int tileSize);

    std::unordered_map<int, TileType> tileProperties = {
        {6, TileType::Solid},
        {7, TileType::Solid},
        {8, TileType::Solid},
        {9, TileType::Solid},
        {10, TileType::Solid},
        {11, TileType::Solid},
        {12, TileType::Solid},
        {13, TileType::Solid},
        {14, TileType::Air}
    };

private:
    const int* levelData;
    unsigned int mapWidth;
    unsigned int mapHeight;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Texture tileset;
    sf::VertexArray vertices;
};

