#ifndef BALL_HPP
#define BALL_HPP 
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

class Ball {
public:
	Ball();
	void render(sf::RenderWindow& window);
	void update(const sf::RenderWindow& window);
	sf::CircleShape shape{25.f};
	sf::Vector2f velocity{20.f,20.f};
	sf::RectangleShape trailShape{{0.f,10.f}};
private:

};

Ball::Ball() {
	this->shape.setFillColor(sf::Color::White);
	this->trailShape.setOrigin(0,this->trailShape.getSize().y/2);
	// this->velocity = sf::Vector2f(20.f,20.f);
}
/**
 * @brief yaa
 * @param window 
*/
void Ball::render(sf::RenderWindow& window) {
	window.draw(this->trailShape);
	window.draw(this->shape);
}
void Ball::update(const sf::RenderWindow& window) {
	sf::Vector2f position = this->shape.getPosition();
	sf::Vector2f previousPosition{position};
	const sf::FloatRect box = this->shape.getLocalBounds();
	
	this->velocity.x *= 0.985f;
	this->velocity.y *= 0.985f;
	position += this->velocity;

	if (position.x < 0) {
		position.x = 0; 
		this->velocity.x *= -1;
	} else if (position.x + box.width > window.getSize().x) {
		position.x = window.getSize().x - box.width;
		this->velocity.x *= -1;
	}
 
	if (position.y < 0) {
		position.y = 0;
		this->velocity.y *= -1;
	} else if (position.y + box.height > window.getSize().y) {
		position.y = window.getSize().y - box.height;
		this->velocity.y *= -1;
	}

	this->shape.setPosition(position);


	// trail
	sf::Vector2f deltaPosition = position - previousPosition;
	float length = sqrt(deltaPosition.x * deltaPosition.x + deltaPosition.y * deltaPosition.y);
	this->trailShape.setSize({length,10.0f});
	// this->trailShape.setSize({100.0f,10.0f});
	this->trailShape.setPosition(previousPosition.x + this->shape.getRadius(), previousPosition.y + this->shape.getRadius());
	float rotation = (atan2(deltaPosition.y, deltaPosition.x) * 180) / M_PI;
	// std::cout << rotation << std::endl;
	this->trailShape.setRotation(rotation);
}
#endif // !BALL_HPP
