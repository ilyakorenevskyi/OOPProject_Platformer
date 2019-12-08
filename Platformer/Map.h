#pragma once
#include <SFML/Graphics.hpp>

class Map
{
public:
	sf::String TileMap[17] = {
	"I                      W",
	"I                      W",
	"I                      W",
	"I                      W",
	"I                      W",
	"IBBBB   B  B   B       W",
	"I                  B   W",
	"I                      W",
	"I                B     W",
	"I             B        W",
	"I       BBBB           W",
	"BBBB                   W",
	"I                      W",
	"I                      W",
	"I     BBBBB            W",
	"I                       ",
	"BBBBBBBBBBBBBBBBBBBBBBBW"
	};
	void drawmap(sf::RenderWindow& window);
};

