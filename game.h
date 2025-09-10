#pragma once
#include "paddle.h"
#include "ball.h"
#include "entityManager.h"
#include "health.h"
#include "vector"
#include "audio.h"

struct Gap {
	bool gapFound;
	float overlap;
	sf::Vector2f axis;
};

class Game {
private:
	unsigned int windowWidth, windowHeight;
	sf::Clock clock;

	void sytemCollison();
	void systemMovement();
	void systemInput();
	void systemRender();
	void systemModifiers();

	void handleGamePhase();
	void handleDeltaTime();
	void removeOutOfBounds();

	Gap findGap(const sf::Shape& a, const sf::Shape& b);

	void handleCollisionBroadPhase();
	void handleCollision(Entity& entity, const EntityVecWeak& entities);

	EntityManager entityManager;
	std::shared_ptr<Paddle> paddle;

	Health health;
	void resetGame();

public:
	static float deltaTime;
	sf::RenderWindow window;
	void run();
	Game();
};

