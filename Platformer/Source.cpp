#include <SFML/Graphics.hpp>
#include <iostream>
#include "Hero.h"
using namespace sf;

int main()
{
	View view;
	std::vector <Map> levels;
	for (int i = 1; i <= 2; i++) {
		levels.push_back(Map("level"+std::to_string(i)));
	}
	int curr_map = 2;
	Font ouders;
	ouders.loadFromFile("font.ttf");
	sf::err().rdbuf(NULL);
	sf::RenderWindow window(sf::VideoMode(480,272), "Dangerous Adventure");
	AnimationControl hero_anim;
	int pos = 0;
	Texture adventurer,forest,cristal_t;
	Sprite background,cristal;
	adventurer.loadFromFile("adventurer_1.png");
	cristal_t.loadFromFile("cristal.png");
	cristal.setTexture(cristal_t);
	cristal.setPosition(15, 5);
	cristal.setScale(0.9, 0.9);
	hero_anim.create("idle", adventurer, IntRect(0, 0, 22, 32), 0.005, 4);
	hero_anim.create("walk", adventurer, IntRect(0, 32, 20, 30), 0.008, 5);
	hero_anim.create("jump", adventurer, IntRect(0, 64, 22, 30), 0.005, 3);
	forest.loadFromFile("forest_bg.png");
	background.setTexture(forest);
	background.setScale(0.5, 0.5);
	background.setPosition(0, 0);
	Hero hero(hero_anim);
	Clock clock;
	sf::Text cristal_count;
	cristal_count.setFont(ouders);
	cristal_count.setScale(0.3, 0.3);
	cristal_count.setCharacterSize(50);
	cristal_count.setPosition({ 30 ,3});
	while (window.isOpen())
	{
		cristal_count.setString(std::to_string(hero.coins));
		float t = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		t = t/1000;
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
		if(Keyboard::isKeyPressed(Keyboard::Space)){
			if (hero.onGround) {
				hero.setPressed("Space");
			}
		}
		hero.update(t,levels[curr_map-1]);
		window.draw(background);
		levels[curr_map - 1].drawmap(window);
		hero.draw(window);
		window.draw(cristal);
		window.draw(cristal_count);
		window.display();
	}

	return 0;
}