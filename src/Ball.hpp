#ifndef BALL_HPP
#define BALL_HPP 
#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <memory>
class Ball {
public:
	Ball();
	void render(sf::RenderWindow& window);
	void update(const sf::RenderWindow& window);
	sf::CircleShape shape{25.f};
	sf::Vector2f velocity{20.f,20.f};
	std::queue<std::shared_ptr<sf::RectangleShape>> trails;
private:
	sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& position);
};

Ball::Ball() {
	this->shape.setFillColor(sf::Color::White);
}
/**
 * @brief yaa
 * @param window 
*/
void Ball::render(sf::RenderWindow& window) {
	std::cout << this->trails.size() << std::endl;
	while (!this->trails.empty()) {
		std::shared_ptr<sf::RectangleShape> trail = this->trails.front();
		window.draw(*trail);
		this->trails.pop();
	}
	window.draw(this->shape);
}
void Ball::update(const sf::RenderWindow& window) {
	const sf::FloatRect box = this->shape.getLocalBounds();
	const sf::Vector2u windowSize = window.getSize();
	sf::Vector2f position = this->getPosition();
	
	this->velocity *= 0.985f;

	sf::Vector2f remainingMovement = this->velocity;
	while (remainingMovement.x != 0 || remainingMovement.y != 0) {
		sf::Vector2f previousPosition = position;
		position += remainingMovement;
		if (position.x < 0) {
			remainingMovement.x = -position.x;
			position.x = 0;
			this->velocity.x *= -1;
		} else if (position.x + box.width > windowSize.x) {
			remainingMovement.x = windowSize.x - box.width - position.x;
			position.x = windowSize.x - box.width;
			this->velocity.x *= -1;
		} else {
			remainingMovement.x = 0;
		}

		if (position.y < 0) {
			remainingMovement.y = -position.y;
			position.y = 0;
			this->velocity.y *= -1;
		} else if (position.y + box.height > windowSize.y) {
			remainingMovement.y = windowSize.y - box.height - position.y;
			position.y = windowSize.y - box.height;
			this->velocity.y *= -1;
		} else {
			remainingMovement.y = 0;
		}
		this->setPosition(position);

		const sf::Vector2f deltaPosition = position - previousPosition;
		const float length = sqrt(deltaPosition.x * deltaPosition.x + deltaPosition.y * deltaPosition.y);
		const float rotation = (atan2(deltaPosition.y, deltaPosition.x) * 180) / M_PI;
		std::shared_ptr<sf::RectangleShape> trail = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape({length,10.0f}));
		trail->setOrigin(0, trail->getSize().y/2);
		trail->setPosition(previousPosition.x + this->shape.getRadius(), previousPosition.y + this->shape.getRadius());
		trail->setRotation(rotation);
		this->trails.push(trail);
	}
	return;
}
inline sf::Vector2f Ball::getPosition() {
	return this->shape.getPosition();
}
inline void Ball::setPosition(const sf::Vector2f& position) {
	return this->shape.setPosition(position);
}
#endif // !BALL_HPP
