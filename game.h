#pragma once
#include "paddle.h"
#include "ball.h"
#include "entityManager.h"
#include "vector"

class Game {
private:
	unsigned int windowWidth, windowHeight;
	sf::Clock clock;
	float deltaTime;

	void sytemCollison();
	void systemMovement();
	void systemInput();
	void systemRender();

	void handleGamePhase();
	void handleDeltaTime();
	void handleCollisionBroadPhase();

	EntityManager entityManager;
	std::shared_ptr<Paddle> paddle;
	std::shared_ptr<Ball> ball;

public:
	sf::RenderWindow window;
	void run();
	Game();
};