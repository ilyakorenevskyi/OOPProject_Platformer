#pragma once
#include <SFML/Graphics.hpp>
class Button {
public:
	sf::Texture b_texture;
	sf::String name;
	int x, y;
	sf::Sprite b_sprite;
	void draw(sf::RenderTarget& window);
	bool isClicked(sf::Vector2f mouse);
	Button(std::string name, int x,int y);
};
class Menu
{
	sf::Texture title_texture;
	sf::Sprite title_sprite;
public:
	std::vector<Button*> buttons;
	bool open;
	bool isOpen();
	void work(sf::Vector2f mouse);
	void draw(sf::RenderTarget& window);
	Menu();
	~Menu();
};

