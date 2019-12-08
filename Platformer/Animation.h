#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
public:
	bool playing,reverse;
	std::vector<sf::IntRect> frame, reverse_frame;
	float currFrame;
	float speed;
	sf::Sprite sprite;
	Animation(sf::Texture& texture, sf::IntRect pos, float speed, int count) {
		this->speed = speed;
		sprite.setTexture(texture);
		currFrame = 0;
		playing = false;
		reverse = false;
	}
	~Animation();
};
class AnimationControl {

};

