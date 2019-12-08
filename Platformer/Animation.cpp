#include "Animation.h"

void Animation::tick(float t) {
	if (!playing) return;
	currFrame += speed * t;
	currFrame = (int)currFrame % frame.size();
	if (reverse) sprite.setTextureRect(reverse_frame[currFrame]);
	else frame[currFrame];
}

Animation::Animation(sf::Texture& texture, sf::IntRect pos, float speed, int count){
	this->speed = speed;
	sprite.setTexture(texture);
	currFrame = 0;
	playing = false;
	reverse = false;
	for (int i = 0; i < count; i++) {
		frame.push_back(sf::IntRect(pos.left + i * pos.width, pos.top, pos.width, pos.height));
		reverse_frame.push_back(sf::IntRect(pos.left + (i + 1) * pos.width, pos.top, -pos.width, pos.height));
	}
}
Animation::~Animation()
{
}
void AnimationControl::create(sf::String anim_name, sf::Texture& texture, sf::IntRect pos, float speed, int count) {
	anim[anim_name] = Animation(texture, pos, speed, count);
	currAnim = anim_name;
}
void AnimationControl::draw(sf::RenderTarget& window, int x, int y) {
	anim[currAnim].sprite.setPosition(x, y);
	window.draw(anim[currAnim].sprite);
}
void AnimationControl::set(sf::String curr) {
	currAnim = curr;
};
void AnimationControl::reverse(bool a) { anim[currAnim].reverse = a; };
void AnimationControl::tick(float t) { anim[currAnim].tick(t); };
void AnimationControl::play() { anim[currAnim].playing = 1; };
void AnimationControl::stop() { anim[currAnim].playing = 0; };
