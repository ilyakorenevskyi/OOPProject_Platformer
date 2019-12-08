#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
class Map
{
	friend class Hero;
	sf::String TileMap[17];
public:
	Map(std::string name);
	void drawmap(sf::RenderWindow& window);
};

