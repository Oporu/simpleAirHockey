#ifndef GAME_HPP
#define GAME_HPP

#define USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Disc.hpp"
#include <chrono>
#include <thread>

class Game final {
	sf::RenderWindow window{ { 800u, 600u }, "simpleAirHockey", sf::Style::Close };
	Ball ball;
	Disc disc{ 30.0f, sf::Color::Green, window };
	sf::Clock clock;
	void initializeWindow();
	void handleWindowEvents();
public:
	Game();
	void update();
	void render();
	bool isActive() const;
};

Game::Game() {
	this->initializeWindow();
	clock.restart();
}
void Game::initializeWindow() {
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	window.setActive();
	window.clear();
	window.display();
}
void Game::handleWindowEvents() {
	sf::Event event{};
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
					using sf::Keyboard;
					case Keyboard::Q:
					case Keyboard::Escape:
						window.close();
						break;
					case Keyboard::Up:
					case Keyboard::W:
						ball.velocity.y -= 30.f;
						break;
					case Keyboard::Down:
					case Keyboard::S:
						ball.velocity.y += 30.f;
						break;
					case Keyboard::Left:
					case Keyboard::A:
						ball.velocity.x -= 30.f;
						break;
					case Keyboard::Right:
					case Keyboard::D:
						ball.velocity.x += 30.f;
						break;
					case Keyboard::Space:
						ball.velocity *= 2.f;
						break;
					case Keyboard::Num0:
						ball.velocity.x = 0;
						ball.velocity.y = 0;
						break;
					case Keyboard::Backspace:
						std::this_thread::sleep_for(std::chrono::seconds(1));
						break;
					default:;
				}
				break;
			default:;
		}
	}
}
void Game::update() {
	this->handleWindowEvents();

	const sf::Time elapsed = clock.restart();
	elapsed.asSeconds();
	
	this->ball.update(window, disc);
	this->disc.update(window);
}
void Game::render() {
	this->window.clear();
	this->ball.render(window);
	this->disc.render(window);
	this->window.display();
}
inline bool Game::isActive() const {
	return window.isOpen();
}
#endif