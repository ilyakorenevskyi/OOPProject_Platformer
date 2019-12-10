#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include "Hero.h"
#include "Menu.h"
#include "Globals.h"

using namespace sf;
int main()
{
	View view;
	sf::err().rdbuf(NULL);
	sf::RenderWindow window(sf::VideoMode(480,272), "Dangerous Adventure");
	Texture adventurer_t,forest_t,cristal_t,heart_t;
	Sprite background,cristal,heart;
	adventurer_t.loadFromFile("files//adventurer_1.png");
	cristal_t.loadFromFile("files//cristal.png");
	heart_t.loadFromFile("files//heart.png");
	heart.setTexture(heart_t);
	heart.setPosition(50, 5);
	cristal.setTexture(cristal_t);
	cristal.setPosition(15, 5);
	Font ouders;
	ouders.loadFromFile("files//font.ttf");
	AnimationControl hero_anim;
	hero_anim.create("idle", adventurer_t, IntRect(0, 0, 22, 32), 0.003, 4);
	hero_anim.create("walk", adventurer_t, IntRect(0, 32, 20, 30), 0.008, 5);
	hero_anim.create("jump", adventurer_t, IntRect(22, 64, 22, 30), 0.001, 1);
	forest_t.loadFromFile("files//forest_bg.png");
	background.setTexture(forest_t);
	background.setScale(0.5, 0.5);
	background.setPosition(0, 0);
	Hero hero(hero_anim);
	Music main_theme;
	main_theme.openFromFile("files//main_theme.ogg");
	main_theme.play();
	main_theme.setLoop(true);
	Clock clock;
	Font counter_f;
	counter_f.loadFromFile("files//font.ttf");
	std::vector <Map> levels;
	Music coin;
	coin.openFromFile("files//collect.wav");
	Menu main_menu;
	main_menu.setOpen();
	for (int i = 1; i <= 2; i++) {
		levels.push_back(Map("level" + std::to_string(i)));
	}
	sf::Text cristal_count,hp_count;
	cristal_count.setFont(ouders);
	hp_count.setFont(ouders);
	hp_count.setScale(0.3, 0.3);
	hp_count.setCharacterSize(50);
	hp_count.setPosition({ 70 ,3 });
	cristal_count.setScale(0.3, 0.3);
	cristal_count.setCharacterSize(50);
	cristal_count.setPosition({ 35 ,3});
	while (window.isOpen())
	{
		if (!main_menu.isOpen()) {
			hp_count.setString(std::to_string(hero.getHP()));
			cristal_count.setString(std::to_string(hero.getCoins()));
			float t = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			t = t / 1000;
			if (t > 100) t = 20;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape && curr_map > 0) {
						main_menu.setOpen();
					}
				}
				if (event.type == sf::Event::Closed)
					window.close();
				
			}
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				hero.setPressed("A");
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				hero.setPressed("D");
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				if (hero.onGround) {
					hero.setPressed("Space");
				}
			}

			hero.update(t, levels[curr_map -1],coin);
			if (hero.getHP() == 0) {
				levels[curr_map-1].reset();
				hero.reset(levels[curr_map - 1]);
			}
			window.draw(background);
			levels[curr_map - 1].drawmap(window);
			window.draw(cristal);
			window.draw(cristal_count);
			window.draw(heart);
			window.draw(hp_count);
			hero.draw(window);
		}
		else {
			
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window); 
			sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape && curr_map > 0) {
						main_menu.setClosed();
					}

				}
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.key.code == sf::Mouse::Left) {
						main_menu.work(pos, window, hero,levels);
					}
				}
				
			}
			window.clear();
			window.draw(background);
			main_menu.draw(window);
		}
		window.display();
	}

	return 0;
}