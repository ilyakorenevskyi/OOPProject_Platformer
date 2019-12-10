#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
class Map
{

	std::string name;
	friend class Hero;
	std::vector<sf::String> TileMap;
public:
	void reset();
	Map(std::string name);
	void drawmap(sf::RenderWindow& window);
};

