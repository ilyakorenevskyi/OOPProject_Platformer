#include "Map.h"
Map::Map(std::string name) {
	std::ifstream level;
	level.open("maps\\" + name+".txt");
	for (int i = 0; i < 17; i++) {
		std::string t;
		std::getline(level, t);
		TileMap[i] = t;
	}
}
void Map::drawmap(sf::RenderWindow& window) {
	sf::Sprite tile;
	sf::Texture map;
	map.loadFromFile("files//jungle.png");
	tile.setTexture(map);
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < TileMap[i].getSize(); j++) {
			if (TileMap[i][j] == 'B') {
				tile.setTextureRect(sf::IntRect(0, 0, 16, 16));
			}
			else if (TileMap[i][j] == 'W') {
				tile.setTextureRect(sf::IntRect(16, 0, 16, 16));
			}
			else if (TileMap[i][j] == 'S') {
				tile.setTextureRect(sf::IntRect(48, 0, 16, 16));
			}
			else if (TileMap[i][j] == 'D') {
				tile.setTextureRect(sf::IntRect(32, 0, 16, 16));
			}
			else { continue; }
			tile.setPosition(j * 16, i * 16);
			window.draw(tile);
		}

	}
}