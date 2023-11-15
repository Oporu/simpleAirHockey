#ifndef BALL_HPP
#define BALL_HPP 
#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
class Ball {
public:
	Ball();
	void render(sf::RenderWindow& window);
	void update(const sf::RenderWindow& window);
	sf::CircleShape shape{25.f};
	sf::Vector2f velocity{20.f,20.f};
	// sf::RectangleShape trailShape{{0.f,10.f}};
	std::vector<sf::RectangleShape*> trails;
private:
	const sf::Vector2f& getPosition();
	void setPosition(const sf::Vector2f& position);
};

Ball::Ball() {
	this->shape.setFillColor(sf::Color::White);
	// this->trailShape.setOrigin(0, this->trailShape.getSize().y/2);
}
/**
 * @brief yaa
 * @param window 
*/
void Ball::render(sf::RenderWindow& window) {
	for (const sf::RectangleShape* trail : this->trails) {
		window.draw(*trail);
		delete trail;
	}
	this->trails.clear();
	window.draw(this->shape);
}
void Ball::update(const sf::RenderWindow& window) {
	const sf::FloatRect box = this->shape.getLocalBounds();
	const sf::Vector2u windowSize = window.getSize();
	const sf::Vector2f previousPosition = this->getPosition();
	sf::Vector2f position{previousPosition};
	
	this->velocity *= 0.985f;
	position += this->velocity;

	if (position.x < 0) {
		position.x = 0; 
		this->velocity.x *= -1;
	} else if (position.x + box.width > windowSize.x) {
		position.x = windowSize.x - box.width;
		this->velocity.x *= -1;
	}
 
	if (position.y < 0) {
		position.y = 0;
		this->velocity.y *= -1;
	} else if (position.y + box.height > windowSize.y) {
		position.y = windowSize.y - box.height;
		this->velocity.y *= -1;
	}

	this->setPosition(position);


	// trail
	const sf::Vector2f deltaPosition = position - previousPosition;
	const float length = sqrt(deltaPosition.x * deltaPosition.x + deltaPosition.y * deltaPosition.y);
	const float rotation = (atan2(deltaPosition.y, deltaPosition.x) * 180) / M_PI;
	// this->trailShape.setSize({length,10.0f});
	// this->trailShape.setPosition(previousPosition.x + this->shape.getRadius(), previousPosition.y + this->shape.getRadius());
	// this->trailShape.setRotation(rotation);


	sf::RectangleShape* trail = new sf::RectangleShape({length,10.0f});
	trail->setOrigin(0, trail->getSize().y/2);
	trail->setPosition(previousPosition.x + this->shape.getRadius(), previousPosition.y + this->shape.getRadius());
	trail->setRotation(rotation);
	this->trails.push_back(trail);



}
inline const sf::Vector2f& Ball::getPosition() {
	return this->shape.getPosition();
}
inline void Ball::setPosition(const sf::Vector2f& position) {
	return this->shape.setPosition(position);
}
#endif // !BALL_HPP
