#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"

class Hero
{
	public:
	float dx, dy;
	sf::FloatRect rect;
	bool onGround;
	sf::Sprite sprite;
	float currFrame;
	Hero (sf::Texture& texture);
	void update(float t, Map &m);
	void Collision(bool axis, Map &m);
};

