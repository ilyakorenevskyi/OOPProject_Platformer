#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
class Map
{
public:
	Map(std::string name);
	sf::String TileMap[17];
	void drawmap(sf::RenderWindow& window);
};

