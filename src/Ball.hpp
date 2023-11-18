#ifndef BALL_HPP
#define BALL_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

class Ball {
public:
	Ball(float radius=25.0f, sf::Color color=sf::Color::White);
	void render(sf::RenderWindow& window);
	void update(const sf::RenderWindow& window);
	sf::CircleShape shape;
	sf::Vector2f velocity;
	std::vector<std::shared_ptr<sf::RectangleShape>> trails;
private:
	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& position);
	float getRadius();
	void createTrail(const sf::Vector2f& from, const sf::Vector2f& to);
};

Ball::Ball(const float radius, const sf::Color color) {
	this->shape.setRadius(radius);
	this->shape.setFillColor(color);
	this->velocity.x = 20.f;
	this->velocity.y = 20.f;
}
void Ball::render(sf::RenderWindow& window) {
	// std::cout << this->trails.size() << std::endl;
	for (const std::shared_ptr<sf::RectangleShape>& trail : this->trails)
		window.draw(*trail);
	this->trails.clear();
	window.draw(this->shape);
}
void Ball::update(const sf::RenderWindow& window) {
	const sf::FloatRect box = this->shape.getGlobalBounds();
	const sf::Vector2u windowSize = window.getSize();
	sf::Vector2f position = this->getPosition();
	this->velocity *= 0.985f;

	sf::Vector2f remainingMovement = this->velocity;
	while (remainingMovement.x != 0 || remainingMovement.y != 0) {
		const sf::Vector2f previousPosition = position;
		position += remainingMovement;

		sf::Vector2f edge, pathToEdge;
		if (position.x < 0) {
			edge.x = 0;
			pathToEdge.x = edge.x - previousPosition.x;
		} else if (position.x + box.width > windowSize.x) {
			edge.x = windowSize.x - box.width;
			pathToEdge.x = edge.x - previousPosition.x;
		}
		if (position.y < 0) {
			edge.y = 0;
			pathToEdge.y = edge.y - previousPosition.y;
		}
		else if (position.y + box.height > windowSize.y) {
			edge.y = windowSize.y - box.height;
			pathToEdge.y = edge.y - previousPosition.y;
		}
		sf::Vector2f _1;
		if (remainingMovement.x != 0)
			_1.x = pathToEdge.x / remainingMovement.x;
		if (remainingMovement.y != 0)
			_1.y = pathToEdge.y / remainingMovement.y;

		if (_1.x == 0 && _1.y == 0) {
			remainingMovement.x = 0;
			remainingMovement.y = 0;
		} else if (_1.x > 0 && (_1.x < _1.y || _1.y == 0)) { // hits | first 
			this->velocity.x *= -1;
			remainingMovement.x = edge.x - position.x;
			position.x = edge.x;
			float move_y = remainingMovement.y * _1.x;
			position.y = previousPosition.y + move_y;
			remainingMovement.y -= move_y;
		} else if (_1.y > 0 && (_1.x > _1.y || _1.x == 0)) { // hits - 
			this->velocity.y *= -1;
			remainingMovement.y = edge.y - position.y;
			position.y = edge.y;
			float move_x = remainingMovement.x * _1.y;
			position.x = previousPosition.x + move_x;
			remainingMovement.x -= move_x;
		} else { // corner
			this->velocity *= -1.0f;
			remainingMovement.x = edge.x;
			remainingMovement.y = edge.y;
			position.x = edge.x;
			position.y = edge.y;
		}

		this->createTrail(previousPosition, position);
	}
	this->setPosition(position);
	return;
}
inline sf::Vector2f Ball::getPosition() {
	return this->shape.getPosition();
}
inline void Ball::setPosition(const sf::Vector2f& position) {
	return this->shape.setPosition(position);
}
inline float Ball::getRadius() {
	return this->shape.getRadius();
}
inline void Ball::createTrail(const sf::Vector2f& from, const sf::Vector2f& to) {
	const sf::Vector2f path = to - from;
	const float length = sqrt(path.x * path.x + path.y * path.y);
	const float rotation = (atan2(path.y, path.x) * 180) / M_PI;
	std::shared_ptr<sf::RectangleShape> trail = std::make_shared<sf::RectangleShape>(sf::Vector2f(length,10.0f));
	trail->setOrigin(0, trail->getSize().y/2.0f);
	trail->setPosition(from.x + this->getRadius(), from.y + this->getRadius());
	trail->setRotation(rotation);
	this->trails.push_back(trail);




	// color just for fun
	// trail->setFillColor(sf::Color(rand(),rand(),rand()));
}
#endif // !BALL_HPP
