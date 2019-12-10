#include "Menu.h"
#include <iostream>
Button::Button(std::string name, int x,int y) {
	visible = true;
	this->name = name;
	this->x = x;
	this->y = y;
	b_texture.loadFromFile("files//"+name+".png");
	b_sprite.setTexture(b_texture);
	b_sprite.setScale(0.25, 0.25);
	b_sprite.setPosition(x, y);
}
bool Button::isClicked(sf::Vector2f mouse) {
	if (mouse.x >= x && mouse.x <= x + b_texture.getSize().x*0.25 && mouse.y >= y && mouse.y <= y + b_texture.getSize().y*0.25) {
		return true;
	}
	return false;
}
void Button::draw(sf::RenderTarget& window) {
	if (visible) {
		window.draw(b_sprite);
	}
}
Menu::Menu(){
	title_texture.loadFromFile("files//title.png");
	title_sprite.setTexture (title_texture);
	title_sprite.setScale(0.25, 0.25);
	title_sprite.setPosition((480-title_texture.getSize().x*0.25)/2, 0);
	buttons.push_back(new Button("start", 182,100));
	buttons.push_back(new Button("select_level", 182, 140));
	buttons.push_back(new Button("exit", 182, 180));
	buttons.push_back(new Button("L", 182, 140));
	buttons.push_back(new Button("R", 267, 140));
	buttons.push_back(new Button("Select", 182, 180));
	for (int i = 3; i != buttons.size(); i++) {
		buttons[i]->visible = false;
	}
	counter_font.loadFromFile("files//font.ttf");
	counter_text.setFont(counter_font);
	counter_text.setString(std::to_string(1));
	counter_text.setPosition(235, 140);
	counter_text.setScale(0.5, 0.5);
}
bool Menu::isOpen() {
	return open;
}
void Menu::setOpen() {
	open = true;
}
void Menu::setClosed() {
	open = false;
}
void Menu::work(sf::Vector2f mouse,sf::RenderWindow &window,Hero &hero,std::vector<Map> &maps) {
	int clicked=-1;
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->isClicked(mouse)&&buttons[i]->visible) {
			clicked = i;
		}
	}
	switch (clicked) {
	case(0): {open = false; hero.reset(maps[0]); maps[0].reset(); curr_map = 1; break;  }
	case(1): {
		for (int i = 0; i != 3; i++) {
			buttons[i]->visible = false;
		}
		for (int i = 3; i != buttons.size(); i++) {
			buttons[i]->visible = true;
		}
		break;
	}
	case(2): window.close(); break;
	case(3): {if (curr_map - 1 >= 1)  curr_map--; counter_text.setString(std::to_string(curr_map)); break; }
	case(4): { if (curr_map + 1 <= maps.size()) curr_map++; counter_text.setString(std::to_string(curr_map)); break; }
	case(5): 
		open = false; 
		if (curr_map == 0) curr_map = 1;
		maps[curr_map - 1].reset();
		hero.reset(maps[curr_map-1]);
		for (int i = 0; i != 3; i++) {
			buttons[i]->visible = true;
		}
		for (int i = 3; i != buttons.size(); i++) {
			buttons[i]->visible = false;
		}
		break;

	}
}
void  Menu::draw(sf::RenderTarget& window) {
	window.draw(title_sprite);
	for(auto i:buttons)
		i->draw(window);
	if (buttons[4]->visible) window.draw(counter_text);
}
Menu::~Menu()
{
}
