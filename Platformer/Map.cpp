#include "Map.h"
void Map::drawmap(sf::RenderWindow& window) {
	sf::Sprite tile;
	sf::Texture map;
	map.loadFromFile("jungle.png");
	tile.setTexture(map);
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 25; j++) {
			if (TileMap[i][j] == 'B') {
				tile.setTextureRect(sf::IntRect(0, 0, 16, 16));
			}
			else if (TileMap[i][j] == 'W') {
				tile.setTextureRect(sf::IntRect(16, 0, 16, 16));
			}
			else { continue; }
			tile.setPosition(j * 16, i * 16);
			window.draw(tile);
		}

	}
}