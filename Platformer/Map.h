#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

class Map
{
	sf::Texture map_texture;
	int total_cristals;
	std::string name;
	friend class Hero;
	std::vector<sf::String> TileMap;
public:
	int totalCristals();
	void reset();
	Map(std::string name);
	void drawmap(sf::RenderWindow& window);
};

