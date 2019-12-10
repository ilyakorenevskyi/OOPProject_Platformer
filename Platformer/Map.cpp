#include "Map.h"
extern float offset_x, offset_y;
Map::Map(std::string name) {
	map_texture.loadFromFile("files//" + name + ".png");
	this->name = name;
	std::ifstream level;
	level.open("maps\\" + name+".txt");
	std::string t;
	while(std::getline(level, t)) {
		TileMap.push_back(t);
	}
	level.close();
	total_cristals = 0;
	for (auto i : TileMap) 
		for (auto j : i) 
			if (j == 'D') total_cristals++;
}
int Map::totalCristals() {
	return total_cristals;
}
void Map::reset(){
	std::ifstream level;
	level.open("maps\\" + name + ".txt");
	std::string t;
	TileMap.clear();
	while (std::getline(level, t)) {
		TileMap.push_back(t);
	}
	level.close();
}
void Map::drawmap(sf::RenderWindow& window) {
	sf::Sprite tile;
	tile.setTexture(map_texture);
	for (int i = 0; i < TileMap.size(); i++) {
		for (int j = 0; j < TileMap[i].getSize(); j++) {
			switch (TileMap[i][j]) {
			case('B'):tile.setTextureRect(sf::IntRect(0, 0, 16, 16)); break;
			case('W'):tile.setTextureRect(sf::IntRect(16, 16, 16, 16)); break;
			case('S'):tile.setTextureRect(sf::IntRect(48, 0, 16, 16)); break;
			case('D'):tile.setTextureRect(sf::IntRect(32, 0, 16, 16)); break;
			case('0'):tile.setTextureRect(sf::IntRect(0, 16, 16, 16)); break;
			case('M'): tile.setTextureRect(sf::IntRect(64, 0, 16, 16)); break;
			case('e'): tile.setTextureRect(sf::IntRect(80, 0, 16, 16)); break;
			case('E'): tile.setTextureRect(sf::IntRect(96, 0, 16, 16)); break;
			default: continue;
			}
			tile.setPosition(j * 16-offset_x, i * 16-offset_y);
			window.draw(tile);
		}

	}
}