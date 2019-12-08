#pragma once
#include <SFML/Graphics.hpp>
class Animation;
class AnimationControl {
public:
	sf::String currAnim;
	std::map < sf::String, Animation> anim;
	void create(sf::String anim_name, sf::Texture& texture, sf::IntRect pos, float speed, int count);
	void draw(sf::RenderTarget& window, int x, int y);
	void set(sf::String curr);
	void reverse(bool a);
	void tick(float t);
	void play();
	void stop();
	AnimationControl();

};
class Animation
{

	friend class AnimationControl;
	bool playing,reverse;
	std::vector<sf::IntRect> frame, reverse_frame;
	float currFrame;
	float speed;
	sf::Sprite sprite;
	void tick(float t);
public:
	Animation();
	Animation(sf::Texture& texture, sf::IntRect pos, float speed, int count);
};


