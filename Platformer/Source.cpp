#include <SFML/Graphics.hpp>
#include <iostream>
#include "Hero.h"
using namespace sf;

int main()
{
	Map level1;
	sf::err().rdbuf(NULL);
	sf::RenderWindow window(sf::VideoMode(480,272), "SFML works!");
	int pos = 0;
	Texture adventurer,forest;
	forest.loadFromFile("forest_bg.png");
	Sprite background;
	background.setTexture(forest);
	background.setScale(0.5, 0.5);
	background.setPosition(0, 0);
	float currFrame = 1;
	adventurer.loadFromFile("adventurer_1.png");
	Hero hero(adventurer);
	Clock clock;
	while (window.isOpen())
	{
		float t = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		t = t/1000;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			hero.dx = -0.08;
			
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			hero.dx = 0.08;
		}
		if(Keyboard::isKeyPressed(Keyboard::Space)){
			if (hero.onGround) {
			hero.dy = -0.21;
			hero.onGround = false; }
		}
		hero.update(t,level1);
	
		window.draw(background);
		level1.drawmap(window);
		window.draw(hero.sprite);
		window.display();
	}

	return 0;
}