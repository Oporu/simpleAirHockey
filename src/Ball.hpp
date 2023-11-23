#ifndef BALL_HPP
#define BALL_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Trail.hpp"
#include "Disc.hpp"
class Ball {
public:
	Ball(float radius=25.0f, sf::Color color=sf::Color::White);
	void render(sf::RenderWindow& window);
	void update(const sf::RenderWindow& window, const Disc& disc);
	sf::Vector2f velocity;
private:
	sf::CircleShape shape;
	std::vector<Trail> trails;
	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& position);
	float getRadius() const;
	float getSpeed() const;
	bool isMoving() const;
	void createTrail(const sf::Vector2f& from, const sf::Vector2f& to);
	bool collision(const Disc& disc);
	static sf::Vector2f getIntersection(sf::Vector2f A1, sf::Vector2f A2, sf::Vector2f B1, sf::Vector2f B2) {
		float m1 = (A2.y - A1.y) / (A2.x - A1.x);
		float c1 = A1.y - m1 * A1.x;
		float m2 = (B2.y - B1.y) / (B2.x - B1.x);
		float c2 = B1.y - m2 * B1.x;

		float x = (c2 - c1) / (m1 - m2);
		float y = m1 * x + c1;

		return {x, y};
	}
};

Ball::Ball(const float radius, const sf::Color color) {
	this->shape.setRadius(radius);
	this->shape.setFillColor(color);
	this->velocity.x = 20.f;
	this->velocity.y = 20.f;
}
void Ball::render(sf::RenderWindow& window) {
	for (const Trail& trail : this->trails)
		trail.render(window);
	this->trails.clear();
	window.draw(this->shape);
}
void Ball::update(const sf::RenderWindow& window, const Disc& disc) {
	const sf::FloatRect box = this->shape.getGlobalBounds();
	const sf::Vector2u windowSize = window.getSize();
	sf::Vector2f position = this->getPosition();
	this->velocity *= 0.985f;

	// if (collision(disc)) {
	// 	std::cout << "collision!\n";
	// 	return;
	// }





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
		} else if (position.y + box.height > windowSize.y) {
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
		} else { // actually hits corner but this is very hard
			this->velocity *= -1.0f;
			remainingMovement = edge - position;
			position = edge;
			std::cout << "you just hit corner!\n";
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
inline float Ball::getRadius() const {
	return this->shape.getRadius();
}
inline float Ball::getSpeed() const {
	return std::sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);
}
inline bool Ball::isMoving() const {
	return this->velocity.x != 0.0f || this->velocity.y != 0.0f;
}
inline void Ball::createTrail(const sf::Vector2f& from, const sf::Vector2f& to) {
	const float radius = this->getRadius();
	this->trails.emplace_back(from, to, this->shape.getFillColor(), sf::Vector2f(radius, radius));
}
inline bool Ball::collision(const Disc &disc) {
	const bool ballIsMoving = this->isMoving();
	const bool discIsMoving = disc.isMoving();
	if (!ballIsMoving && !discIsMoving)
		return false;
	if (ballIsMoving ^ discIsMoving) {
		if (ballIsMoving) {
			sf::Vector2f diff = disc.getPosition() - this->getPosition();
			float diffLength = std::sqrt(diff.x * diff.x + diff.y * diff.y);
			// here
		}
	}

	sf::Vector2f intersection = Ball::getIntersection(this->getPosition(), this->getPosition() + this->velocity, disc.getPosition(), disc.getPosition() + disc.getVelocity());
	if (isnan(intersection.x) || isnan(intersection.y))
		return false;
	if (intersection.x < 0 || intersection.x > 800 || intersection.y < 0 || intersection.y > 600)
		return false;
	
	// std::cout << "intersection: " << intersection.x << ", " << intersection.y << std::endl;
	sf::Vector2f discToIntersection = intersection - disc.getPosition();
	float discSpeed = disc.getSpeed();
	float discToIntersectionLength = std::sqrt(discToIntersection.x * discToIntersection.x + discToIntersection.y * discToIntersection.y);
	float discToIntersectionTime = 0;
	if (discToIntersectionLength != 0 && discSpeed != 0)
		discToIntersectionTime = discToIntersectionLength / discSpeed;
	if (discToIntersectionTime > 1) return false;


	sf::Vector2f ballToIntersection = intersection - this->getPosition();
	float ballSpeed = this->getSpeed();
	float ballToIntersectionLength = std::sqrt(ballToIntersection.x * ballToIntersection.x + ballToIntersection.y * ballToIntersection.y);
	float ballToIntersectionTime = 0;
	if (ballToIntersectionLength != 0 && ballSpeed != 0)
		ballToIntersectionTime = ballToIntersectionLength / ballSpeed;
	if (ballToIntersectionTime > 1) return false;
	// std::cout << "discToIntersectionTime: " << discToIntersectionTime << std::endl;
	// std::cout << "ballToIntersectionTime: " << ballToIntersectionTime << std::endl;
	float avgTime = (discToIntersectionTime + ballToIntersectionTime) / 2.0f;
	std::cout << "avg: " << avgTime << std::endl;
	this->setPosition(this->getPosition() + this->velocity * avgTime);	
	this->velocity *= -1.0f;
	return true;
	// sf::Vector2f normal = intersection - disc.getPosition();
	// normal /= std::sqrt(normal.x * normal.x + normal.y * normal.y);
	// float dot = this->velocity.x * normal.x + this->velocity.y * normal.y;
	// sf::Vector2f reflection = this->velocity - 2.0f * dot * normal;
	// this->velocity = reflection;

}
#endif // !BALL_HPP
