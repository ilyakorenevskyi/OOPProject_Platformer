#pragma once
#include <SFML/Graphics.hpp>
class Button {
public:
	sf::String name;
	sf::IntRect pos;
	sf::Sprite sprite;
	void draw(sf::RenderTarget& window);
	void isClicked(int x, int y);
	Button(std::string name, sf::IntRect pos);
};
class Menu
{
public:
	std::vector<Button*> buttons;

	bool open;
	bool isOpen();
	void draw(sf::RenderTarget& window);
	Menu();
	~Menu();
};

