#include <SFML/Graphics.hpp>
#include <iostream>
#include "Hero.h"
#include "Menu.h"
using namespace sf;
int main()
{
	View view;
	sf::err().rdbuf(NULL);
	sf::RenderWindow window(sf::VideoMode(480,272), "Dangerous Adventure");
	Texture adventurer_t,forest_t,cristal_t;
	Sprite background,cristal;
	adventurer_t.loadFromFile("files//adventurer_1.png");
	cristal_t.loadFromFile("files//cristal.png");
	cristal.setTexture(cristal_t);
	cristal.setPosition(15, 5);
	cristal.setScale(0.9, 0.9);
	Font ouders;
	ouders.loadFromFile("files//font.ttf");
	AnimationControl hero_anim;
	hero_anim.create("idle", adventurer_t, IntRect(0, 0, 22, 32), 0.005, 4);
	hero_anim.create("walk", adventurer_t, IntRect(0, 32, 20, 30), 0.008, 5);
	hero_anim.create("jump", adventurer_t, IntRect(0, 64, 22, 30), 0.005, 3);
	forest_t.loadFromFile("files//forest_bg.png");
	background.setTexture(forest_t);
	background.setScale(0.5, 0.5);
	background.setPosition(0, 0);
	Hero hero(hero_anim);
	Clock clock;
	Font counter_f;
	counter_f.loadFromFile("files//font.ttf");
	std::vector <Map> levels;
	Menu main_menu;
	main_menu.open = true;
	for (int i = 1; i <= 2; i++) {
		levels.push_back(Map("level" + std::to_string(i)));
	}
	int curr_map = 2;
	sf::Text cristal_count;
	cristal_count.setFont(ouders);
	cristal_count.setScale(0.3, 0.3);
	cristal_count.setCharacterSize(50);
	cristal_count.setPosition({ 30 ,3});
	Texture texture;
	Sprite sprite;
	texture.loadFromFile("files//start.png");
	sprite.setTexture(texture);
	sprite.setScale(0.25, 0.25);
	sprite.setPosition(182, 150);
	while (window.isOpen())
	{
		if (!main_menu.open) {
			cristal_count.setString(std::to_string(hero.coins));
			float t = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			t = t / 1000;
			if (t > 100) t = 20;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				hero.setPressed("A");
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				hero.setPressed("D");
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				if (hero.onGround) {
					hero.setPressed("Space");
				}
			}
			hero.update(t, levels[curr_map - 1]);
			window.draw(background);
			levels[curr_map - 1].drawmap(window);
			hero.draw(window);
			window.draw(cristal);
			window.draw(cristal_count);
		}
		else {
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			window.draw(background);
			main_menu.draw(window);
		}
		window.display();
	}

	return 0;
}