#include "moveable.h"

void moveable::draw(sf::RenderWindow *window) {
	sf::RectangleShape rect;
	rect.setPosition(Position.x, Position.y);
	rect.setFillColor(sf::Color::Blue);
	rect.setSize(sf::Vector2f(16.0f, 16.0f));
	window->draw(rect);
}