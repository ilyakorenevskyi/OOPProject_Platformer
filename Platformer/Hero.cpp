#include "Hero.h"

Hero::Hero(AnimationControl &animation) {
	hp = 3;
	coins = 0;
	states = idle;
	pos = sf::FloatRect(56, 44, 20, 30);
	dx = 0, dy = 0;
	this->animation = animation;
}
void Hero::keyCheck() {
	if (pressed_key["D"]) {
		dx = 0.1;
		if (states == idle||dy>=0) {
			states = walk;
			direction = 0;
		}
	}
	if (pressed_key["A"]) {
		dx = -0.1;
		if (states == idle||dy >= 0) {
			states = walk;
			direction = 1;
		}
	}
	if (pressed_key["Space"]) {
		if (states == idle || states == walk ) {
			dy = -0.25;
			onGround = false;
			states = jump;
		}
	}
	if (!(pressed_key["D"] || pressed_key["A"])) {
		dx = 0;
		if (states == walk || dy >= 0) {
			states = idle;
		}
	}
}
void Hero::draw(sf::RenderTarget& window) {
	animation.draw(window, pos.left, pos.top);
}
void Hero::setPressed(std::string key) {
	pressed_key[key] = true;
}
void Hero::update(float t,Map &m,sf::Music &coin) {
	keyCheck();
	if (states == idle) {
		animation.set("idle");
	}
	if (states == walk) {
		animation.set("walk");
	}
	if (states == jump ) {
		animation.set("jump");
	}
	if (dx > 0) direction = 0;
	if (dx < 0) direction = -1;
	animation.reverse(direction);
	pos.left += dx * t;
	Collision(1,m,coin);
	if (!onGround)
		dy += 0.0006 * t;
	pos.top += dy * t;
	onGround = false;
	Collision(0,m,coin);
	animation.tick(t);
	pressed_key["A"] = pressed_key["D"] = pressed_key["Space"] = false;
}
void Hero::Collision(bool axis,Map &m,sf::Music &coin) {
	for (int j = (pos.top) / 16; j < (pos.top + pos.height - 3) / 16 && j < 17; j++) {
		for (int i = (pos.left) / 16; i < (pos.left + pos.width ) / 16 && i < m.TileMap[j].getSize(); i++) {
			if ((m.TileMap[j][i] == 'W' || m.TileMap[j][i] == 'B' || m.TileMap[j][i] == 'I') && axis) //C B он не зайдет на плитку платформы
			{
				if (dx > 0) pos.left = i * 16 - pos.width;
				if (dx < 0) pos.left = i * 16 + 16;
			}
			if (m.TileMap[j][i] == 'D' && axis) {
				m.TileMap[j][i] = ' ';
				coin.stop();
				coin.play();
				coins++;
			}
			if (m.TileMap[j][i] == 'S' && !axis) {
				if(dy>0) pos.left = 33; pos.top = 220;
				if (dy < 0) {
					pos.top = j * 16 + 16;
					dy = 0;
					dx = 0;
					return;
				}
			}
			if (m.TileMap[j][i] == 'B' && !axis) {
				if (dy > 0) {
					pos.top = j * 16 - pos.height + 3;  dy = 0;   onGround = true;
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
