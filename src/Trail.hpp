#ifndef TRAIL_HPP
#define TRAIL_HPP
#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>

class Trail {
public:
	Trail(const sf::Vector2f& from, const sf::Vector2f& to, const sf::Color& color=sf::Color::White);
	Trail(const sf::Vector2f& from, const sf::Vector2f& to, const sf::Color& color, const sf::Vector2f& offset);
	void render(sf::RenderWindow& window) const;
private:
	sf::RectangleShape shape;
};
Trail::Trail(const sf::Vector2f& from, const sf::Vector2f& to, const sf::Color& color) {
	const sf::Vector2f delta = to - from;
	const float rotation = std::atan2(delta.y, delta.x) * 180.f / M_PI;
	const float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
	
	this->shape.setPosition(from);
	this->shape.setFillColor(color);
	
	this->shape.setSize({length, 10.f});
	this->shape.setRotation(rotation);
	this->shape.setOrigin(0.f, this->shape.getSize().y / 2.0f);
}
Trail::Trail(const sf::Vector2f& from, const sf::Vector2f& to, const sf::Color& color, const sf::Vector2f& offset) {
	const sf::Vector2f delta = to - from;
	const float rotation = std::atan2(delta.y, delta.x) * 180.f / M_PI;
	const float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
	
	this->shape.setPosition(from + offset);
	this->shape.setFillColor(color);
	
	this->shape.setSize({length, 10.f});
	this->shape.setRotation(rotation);
	this->shape.setOrigin(0.f, this->shape.getSize().y / 2.0f);
}
inline void Trail::render(sf::RenderWindow& window) const {
	window.draw(this->shape);
}
#endif // !TRAIL_HPP