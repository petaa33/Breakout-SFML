#pragma once
#include "paddle.h"
#include "ball.h"
#include "entityManager.h"
#include "health.h"
#include "vector"

struct Gap {
	bool gapFound;
	float overlap;
	sf::Vector2f axis;
};

class Game {
private:
	unsigned int windowWidth, windowHeight;
	sf::Clock clock;
	float deltaTime = 0;

	void sytemCollison();
	void systemMovement();
	void systemInput();
	void systemRender();

	void handleGamePhase();
	void handleDeltaTime();
	
	Gap findGap(const sf::Shape& a, const sf::Shape& b);

	void handleCollisionBroadPhase();
	void handleCollision(Entity& entity, const EntityVec& entities);

	EntityManager entityManager;
	std::shared_ptr<Paddle> paddle;
	std::shared_ptr<Ball> ball;
	Health health;

public:
	sf::RenderWindow window;
	void run();
	Game();
};

