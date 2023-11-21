#ifndef DISC_HPP
#define DISC_HPP
#include <SFML/Graphics.hpp>
#include "Trail.hpp"
#include <vector>
#include <memory>
#include <iostream>
class Disc {
	sf::CircleShape shape;
	sf::Vector2f velocity;
	std::vector<Trail> trails;
public:
	Disc(float radius, sf::Color color, const sf::WindowBase& windowBase);
	Disc(const sf::WindowBase& windowBase);
	void update(const sf::WindowBase& windowBase);
	void render(sf::RenderWindow& window);
	const sf::Vector2f& getVelocity() const;
	float getSpeed() const;
	const sf::Vector2f& getPosition() const;
	float getRadius() const;
	bool isMoving() const;
};
Disc::Disc(const float radius, const sf::Color color, const sf::WindowBase& windowBase) {
	this->shape.setRadius(radius);
	this->shape.setFillColor(color);
	const sf::Vector2i& cursorPosition = sf::Mouse::getPosition(windowBase);
	this->shape.setPosition(cursorPosition.x - radius, cursorPosition.y - radius);
}
Disc::Disc(const sf::WindowBase& windowBase) {
	this->shape.setRadius(30.0f);
	this->shape.setFillColor(sf::Color::Green);
	const sf::Vector2i& cursorPosition = sf::Mouse::getPosition(windowBase);
	this->shape.setPosition(cursorPosition.x - 30.0f, cursorPosition.y - 30.0f);
}
void Disc::update(const sf::WindowBase& windowBase) {
	const sf::Vector2f previousPosition = this->shape.getPosition();
	const sf::Vector2i& cursorPosition = sf::Mouse::getPosition(windowBase);
	const float& radius = this->shape.getRadius();
	this->shape.setPosition(cursorPosition.x - radius, cursorPosition.y - radius);
	this->velocity = this->shape.getPosition() - previousPosition;

	const sf::Vector2f& previousCenter = previousPosition + sf::Vector2f(radius, radius);
	const sf::Vector2f& currentCenter = this->shape.getPosition() + sf::Vector2f(radius, radius);
	this->trails.emplace_back(previousCenter, currentCenter, this->shape.getFillColor());
}

void Disc::render(sf::RenderWindow& window) {
	for (const Trail& trail : this->trails)
		trail.render(window);
	window.draw(this->shape);
	this->trails.clear();
}
inline const sf::Vector2f& Disc::getVelocity() const {
	return this->velocity;
}
inline float Disc::getSpeed() const {
	return std::sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);
}
inline const sf::Vector2f& Disc::getPosition() const {
	return this->shape.getPosition();
}
inline float Disc::getRadius() const {
	return this->shape.getRadius();
}
inline bool Disc::isMoving() const {
	return this->velocity.x != 0.0f || this->velocity.y != 0.0f;
}




#endif // !DISC_HPP
