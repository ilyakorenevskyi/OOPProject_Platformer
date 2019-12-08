#include "Menu.h"
Button::Button(std::string name, sf::IntRect pos) {
	this->name = name;
	sf::Texture texture;
	this->pos = pos;
	texture.loadFromFile("files/start.png");
	this->sprite.setTexture(texture);
	this->sprite.setScale(0.25, 0.25);
	this->sprite.setPosition(pos.left, pos.top);
}
void Button::draw(sf::RenderTarget& window) {
	sf::Texture texture;
	texture.loadFromFile("files/start.png");
	this->sprite.setTexture(texture);
	this->sprite.setScale(0.25, 0.25);
	window.draw(sprite);
}
Menu::Menu(){
	buttons.push_back(new Button("start", sf::IntRect(182, 50, 0, 0)));
}
void  Menu::draw(sf::RenderTarget& window) {
		buttons[0]->draw(window);
}
Menu::~Menu()
{
}
