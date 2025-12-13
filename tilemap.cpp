#include "tilemap.h"
bool TileMap::load(const std::filesystem::path& givenTileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
    levelData = tiles;
    mapWidth = width;
    mapHeight = height;

    // load the tileset texture
    if (!tileset.loadFromFile(givenTileset))
        return false;
    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(width * height * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            const int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            const int tu = tileNumber % (tileset.getSize().x / tileSize.x);
            const int tv = tileNumber / (tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* triangles = &vertices[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // define the 6 matching texture coordinates
            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &tileset;

    // draw the vertex array
    target.draw(vertices, states);
}

TileType TileMap::getTileType(int gridX, int gridY){
    if (gridX < 0 || gridX >= mapWidth || gridY < 0 || gridY >= mapHeight){
        return TileType::Air;
    }
    int tileID = levelData[gridX + gridY * mapWidth];

    return tileProperties.at(tileID);
}

TileRect TileMap::getTileRect(const sf::FloatRect& bounds, int tileSize) {
    TileRect r;

    r.startX = bounds.position.x / tileSize;
    r.endX = (bounds.position.x + bounds.size.x) / tileSize;
    r.startY = bounds.position.y / tileSize;
    r.endY = (bounds.position.y + bounds.size.y) / tileSize;

    return r;
}
