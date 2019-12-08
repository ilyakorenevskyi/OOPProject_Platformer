#include "Hero.h"

Hero::Hero(sf::Texture& texture) {
	sprite.setTexture(texture);
	pos = sf::FloatRect(56, 44, 20, 30);
	sprite.setScale(0.8, 0.8);
	sprite.setTextureRect(sf::IntRect(0, 0, 22, 32));
	dx = 0, dy = 0;
	currFrame = 1;
}
void Hero::update(float t,Map &m) {
	pos.left += dx * t;
	Collision(1,m);
	if (!onGround) {
		dy += 0.0005 * t;
	}
	pos.top += dy * t;
	onGround = false;
	Collision(0,m);
	currFrame += 0.008 * t;
	if (currFrame >= 6) currFrame = 1;
	if (dx < 0) sprite.setTextureRect(sf::IntRect(20 + 20 * (int)currFrame, 32, -20, 30));
	else if (dx > 0) sprite.setTextureRect(sf::IntRect(20 * (int)currFrame, 32, 20, 30));
	else {
		if (currFrame >= 5) { currFrame = 1; }
		sprite.setTextureRect(sf::IntRect(22 * ((int)currFrame - 1), 0, 22, 32));
	}
	sprite.setPosition(pos.left, pos.top);
	dx = 0;
}
void Hero::Collision(bool axis,Map &m) {
	for (int i = (pos.left) / 16; i < (pos.left + pos.width - 8) / 16; i++) {
		for (int j = (pos.top) / 16; j < (pos.top + pos.height - 10) / 16 && j < 17; j++) {
			if ((m.TileMap[j][i] == 'W' || m.TileMap[j][i] == 'B' || m.TileMap[j][i] == 'I') && axis) //C B он не зайдет на плитку платформы
			{
				if (dx > 0) pos.left = i * 16 - pos.width;
				if (dx < 0) pos.left = i * 16 + 16;
			}
			if (m.TileMap[j][i] == 'B' && !axis) {
				if (dy > 0) {
					pos.top = j * 16 - pos.height + 10;  dy = 0;   onGround = true;
				}
				if (dy < 0) {
					pos.top = j * 16 + 16;
					dy = 0;
					dx = 0;
					return;
				}
			}

			else {
			}

		}
	}
}
