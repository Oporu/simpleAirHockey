#ifndef DISC_HPP
#define DISC_HPP
// #include <iostream>
#include <SFML/Graphics.hpp>
class Disc {
public:
	Disc();
	sf::CircleShape shape{30.f};
	void update(const sf::WindowBase& windowBase);
	void render(sf::RenderWindow& window) const;
};
Disc::Disc() {
	this->shape.setFillColor(sf::Color::Green);
}
void Disc::update(const sf::WindowBase& windowBase) {
	// const sf::Vector2f lastPosition = this->shape.getPosition();
	const sf::Vector2i cursorPosition = sf::Mouse::getPosition(windowBase);
	const float radius = this->shape.getRadius();
	this->shape.setPosition(cursorPosition.x - radius, cursorPosition.y - radius);
	// sf::Vector2f deltaPosition = this->shape.getPosition() - lastPosition;
}

void Disc::render(sf::RenderWindow& window) const {
	return window.draw(this->shape);
}





#endif // !DISC_HPP
