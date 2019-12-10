#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Animation.h"
#include "Map.h"
extern std::map<std::string, sf::Music*> sound_lib;
class Hero
{
	enum { walk, sit, idle, jump } states;
	std::map < std::string, bool> pressed_key;
	AnimationControl animation;
	
	float dx, dy;
	int hp;
	int coins;

public:
	bool direction, is_passed;
	
	sf::FloatRect pos;
	bool on_ground;
	Hero(AnimationControl &anim);
	int getHP();
	int getCoins();
	bool isLevelPassed();
	void reset(Map map);
	void spawn(Map map);
	void setPressed(std::string key);
	void draw(sf::RenderTarget& window);
	void keyCheck();
	void update(float t, Map &m);
	void Collision(bool axis, Map &m);
};

