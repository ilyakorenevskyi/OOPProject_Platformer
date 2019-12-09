#include "Menu.h"
#include <iostream>
Button::Button(std::string name, int x,int y) {
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
	window.draw(b_sprite);
}
Menu::Menu(){
	title_texture.loadFromFile("files//title.png");
	title_sprite.setTexture (title_texture);
	title_sprite.setScale(0.25, 0.25);
	title_sprite.setPosition((480-title_texture.getSize().x*0.25)/2, 0);
	buttons.push_back(new Button("start", 182,100));
}
void Menu::work(sf::Vector2f mouse) {
	int clicked=-1;
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->isClicked(mouse)) {
			clicked = i;
		}
	}
	switch (clicked) {
	case(0): open = false;
	}
}
void  Menu::draw(sf::RenderTarget& window) {
	window.draw(title_sprite);
	for(auto i:buttons)
		i->draw(window);
}
Menu::~Menu()
{
}
