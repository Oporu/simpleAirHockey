#ifndef DISC_HPP
#define DISC_HPP
#include <SFML/Graphics.hpp>
class Disc {
public:
	Disc(float radius=30.0f, sf::Color color=sf::Color::Green);
	sf::CircleShape shape;
	void update(const sf::WindowBase& windowBase);
	void render(sf::RenderWindow& window) const;
};
Disc::Disc(const float radius, const sf::Color color) {
	this->shape.setRadius(radius);
	this->shape.setFillColor(color);
}
void Disc::update(const sf::WindowBase& windowBase) {
	const sf::Vector2i& cursorPosition = sf::Mouse::getPosition(windowBase);
	const float& radius = this->shape.getRadius();
	this->shape.setPosition(cursorPosition.x - radius, cursorPosition.y - radius);
}

void Disc::render(sf::RenderWindow& window) const {
	return window.draw(this->shape);
}





#endif // !DISC_HPP
