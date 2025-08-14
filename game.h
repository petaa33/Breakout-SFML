#pragma once
#include "paddle.h"
#include "ball.h"

class Game {
private:
	unsigned int windowWidth, windowHeight;
	sf::Clock clock;

	void sytemCollison();
	void systemMovement();
	void systemInput();
	void systemRender();
	void handleDeltaTime();

	std::shared_ptr<Paddle> paddle;
	std::shared_ptr<Ball> ball;
	
public:
	sf::RenderWindow window;
	void run();
	Game();
};