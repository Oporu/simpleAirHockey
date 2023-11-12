// #include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Disc.hpp"

int main() {
	sf::RenderWindow window{ { 800u, 600u }, "simpleAirHockey", sf::Style::Close };
	const sf::Color backGroundColor{sf::Color::Black};
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	window.setActive();
	window.clear(backGroundColor);
	window.display();
	Ball ball;
	Disc disc;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Q:
						case sf::Keyboard::Escape:
							window.close();
							break;
						case sf::Keyboard::Up:
						case sf::Keyboard::W:
							ball.velocity.y -= 30.f;
							break;
						case sf::Keyboard::Down:
						case sf::Keyboard::S:
							ball.velocity.y += 30.f;
							break;
						case sf::Keyboard::Left:
						case sf::Keyboard::A:
							ball.velocity.x -= 30.f;
							break;
						case sf::Keyboard::Right:
						case sf::Keyboard::D:
							ball.velocity.x += 30.f;
							break;
						case sf::Keyboard::Space:
							ball.velocity.x *= 2;
							ball.velocity.y *= 2;
							break;
						case sf::Keyboard::Num0:
							ball.velocity.x = 0;
							ball.velocity.y = 0;
							break;
					}
					break;
			}
		}

		ball.update(window);
		disc.update(window);





		window.clear(backGroundColor);
		ball.render(window);
		disc.render(window);
		window.display();
	}
	return 0;
}
