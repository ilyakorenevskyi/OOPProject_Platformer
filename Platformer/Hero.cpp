#include "Hero.h"
extern float offset_x, offset_y;
Hero::Hero(AnimationControl &animation) {
	hp = 3;
	coins = 0;
	states = idle;
	pos = sf::FloatRect(56, 44, 20, 30);
	dx = 0, dy = 0;
	this->animation = animation;
}
int Hero::getHP() {
	return hp;
}
int Hero::getCoins() {
	return coins;
}
void Hero::reset(Map map) {
	hp = 3;
	coins = 0;
	dx = dy = 0;
	spawn(map);
}
bool Hero::isLevelPassed() {
	return is_passed;
}
void Hero::spawn(Map map) {
	for (int i = 0; i < map.TileMap.size(); i++)
		for (int j = 0; j < map.TileMap[i].getSize(); j++) 
			if (map.TileMap[i][j] == 'H') {
				pos.left = j * 16;
				pos.top = i * 16;
				return;
			}
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
			on_ground = false;
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
	animation.draw(window, pos.left-offset_x, pos.top- offset_y);
}
void Hero::setPressed(std::string key) {
	pressed_key[key] = true;
}
void Hero::update(float t,Map &m) {
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
	Collision(1,m);
	if (!on_ground)
		dy += 0.0006 * t;
	pos.top += dy * t;
	on_ground = false;
	Collision(0,m);
	animation.tick(t);
	pressed_key["A"] = pressed_key["D"] = pressed_key["Space"] = false;
	if (pos.left >= 240)offset_x = pos.left - 480 / 2;
	else offset_x = 0;
	if (pos.top >= 136)offset_y = pos.top - 272 / 2;
	else offset_y = 0;
}
void Hero::Collision(bool axis,Map &m) {
	for (int j = (pos.top) / 16; j < (pos.top + pos.height - 3) / 16 && j < m.TileMap.size(); j++) {
		for (int i = (pos.left) / 16; i < (pos.left + pos.width-3 ) / 16 && i < m.TileMap[j].getSize(); i++) {
			if ((m.TileMap[j][i] == 'W' || m.TileMap[j][i] == 'B' || m.TileMap[j][i] == 'I'||  m.TileMap[j][i] == '0' ) && axis) //C B он не зайдет на плитку платформы
			{
				if (dx > 0) pos.left = i * 16 - pos.width;
				if (dx < 0) pos.left = i * 16 + 16;
			}
			if (m.TileMap[j][i] == 'D' && axis) {
				m.TileMap[j][i] = ' ';
				sound_lib["coin"]->stop();
				sound_lib["coin"]->play();
				coins++;
			}
			if ((m.TileMap[j][i] == 'e'|| m.TileMap[j][i] == 'E') && axis) {
				is_passed = true;
				if (dx > 0) pos.left = i * 16 - pos.width;
				if (dx < 0) pos.left = i * 16 + 16;
			}
			if (m.TileMap[j][i] == 'S' && !axis) {
				if (dy > 0) {
					sound_lib["hurt"]->stop();
					sound_lib["hurt"]->play();
					spawn(m);
					hp--;
				}
				if (dy < 0) {
					pos.top = j * 16 + 16;
					dy = 0;
					dx = 0;
					return;
				}
			}
			if (m.TileMap[j][i] == 'B' && !axis) {
				if (dy > 0) {
					pos.top = j * 16 - pos.height + 3;  dy = 0;   on_ground = true;
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
