#pragma once
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "Map.h"
extern int curr_map;
class Button {
	bool visible;
	sf::Texture b_texture;
	sf::String name;
	int x, y;
	sf::Sprite b_sprite;
	friend class Menu;
public:
	
	void draw(sf::RenderTarget& window);
	bool isClicked(sf::Vector2f mouse);
	Button(std::string name, int x,int y);
};
class Menu
{
	sf::Font counter_font;
	sf::Text counter_text;
	sf::Texture title_texture;
	sf::Sprite title_sprite;
	bool open;
public:
	std::vector<Button*> buttons;
	
	void setClosed();
	bool isOpen();
	void setOpen();
	void work(sf::Vector2f mouse, sf::RenderWindow& window,Hero&hero, std::vector<Map>& maps);
	void draw(sf::RenderTarget& window);
	Menu();
	~Menu();
};

