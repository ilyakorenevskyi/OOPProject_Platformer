#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Animation.h"
#include "Map.h"
class Hero
{
	
	enum { walk, sit, idle, jump } states;
	std::map < std::string, bool> pressed_key;
	AnimationControl animation;
	bool direction;
	float dx, dy;

public:
    int hp;
	int coins;
	sf::FloatRect pos;
	bool onGround;
	Hero(AnimationControl &anim);
	void setPressed(std::string key);
	void draw(sf::RenderTarget& window);
	void keyCheck();
	void update(float t, Map &m, sf::Music& coin);
	void Collision(bool axis, Map &m, sf::Music& coin);
};

