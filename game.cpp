#include "game.h"
#include "iostream"
#include "score.h"

Game::Game() {
	windowWidth = 1280;
	windowHeight = 800;
	window = sf::RenderWindow(sf::VideoMode({ windowWidth, windowHeight }), "Breakout game");

	sf::Vector2f playerStartPos(windowWidth/2, windowHeight - 100);
	sf::Vector2f ballStartPos(windowWidth/2, windowHeight/2);

	paddle = std::make_shared<Paddle>(playerStartPos);
	ball = std::make_shared<Ball>(ballStartPos);

	entityManager.add(paddle);
	entityManager.add(ball);
	entityManager.createBounds(windowWidth, windowHeight);

	health = Health(windowWidth);
}

void Game::run() {
	handleDeltaTime();
	handleGamePhase();
	systemInput();
	systemMovement();
	sytemCollison();
	systemRender();
	entityManager.update();
}

void Game::systemRender() {
	window.clear(sf::Color::Black);

	for (auto& barrier : entityManager.getBounds()) {
		window.draw(*barrier->shape);
	}

	for (auto& entity : entityManager.getEntities()) {
		window.draw(*entity->shape);
	}

	for (auto& heart : health.getSprites()) {
		window.draw(heart);
	}

	window.draw(Score::getInstance().getText());
	window.display();
}

void Game::sytemCollison() {
	handleCollisionBroadPhase();
}

void Game::systemMovement() {
	for (auto& entity : entityManager.getRigidbodyEntities()) {
		entity->shape->move(entity->body->velocity * entity->body->speed * deltaTime);
	}
}

void Game::systemInput() {
	paddle->handleInput();
}

void Game::handleDeltaTime() {
	deltaTime = clock.restart().asSeconds();
}

void Game::handleGamePhase() {
	if ((ball->shape->getPosition().y + ball->shape->getOrigin().y) >= windowHeight) {
		health.remove();
		ball->shape->setPosition(sf::Vector2f(windowWidth / 2, windowHeight / 2));
	}

	if (entityManager.getBlocks().empty()) {
		entityManager.createBlocks(windowWidth, windowHeight);
	}
}

void Game::handleCollisionBroadPhase() {
	// Collision between paddle and ball
	if (paddle->shape->getGlobalBounds().findIntersection(ball->shape->getGlobalBounds())) {
		ball->onCollisionPlayer(paddle->shape->getPosition());
	}

	// Collison between rigidbodies and static objects
	for (auto entity : entityManager.getRigidbodyEntities()) {
		handleCollision(*entity, entityManager.getBlocks());
		handleCollision(*entity, entityManager.getBounds());
	}
}

Gap Game::findGap(const sf::Shape& a, const sf::Shape& b) {
	float smallestOverlap = 10000000000000;
	sf::Vector2f axisOfSmallestOverlap;

	sf::Vector2f pointA = a.getPoint(0) - a.getOrigin() + a.getPosition();
	sf::Vector2f pointB = b.getPoint(0) - b.getOrigin() + b.getPosition();

	Gap gap;

	for (int i = 0; i < a.getPointCount(); i++) {
		sf::Vector2f point = a.getPoint(i) - a.getOrigin() + a.getPosition();
		sf::Vector2f nextPoint = a.getPoint((i + 1) % a.getPointCount()) - a.getOrigin() + a.getPosition();
		sf::Vector2f normal = (point - nextPoint).perpendicular().normalized();

		float minA = pointA.dot(normal);
		float minB = pointB.dot(normal);
		float maxA = minA;
		float maxB = minB;

		for (int j = 0; j < a.getPointCount(); j++) {
			sf::Vector2f point = a.getPoint(j) - a.getOrigin() + a.getPosition();
			float dot = point.dot(normal);

			if (dot > maxA) {
				maxA = dot;
			}

			if (dot < minA) {
				minA = dot;
			}
		}

		for (int k = 0; k < b.getPointCount(); k++) {
			sf::Vector2f point = b.getPoint(k) - b.getOrigin() + b.getPosition();
			float dot = point.dot(normal);

			if (dot > maxB) {
				maxB = dot;
			}

			if (dot < minB) {
				minB = dot;
			}
		}

		float overlap = std::min(maxA, maxB) - std::max(minA, minB);

		// No collision
		if (overlap <= 0) {
			gap.gapFound = true;
			gap.overlap = 0;
			gap.axis = sf::Vector2f(0, 0);
			return gap;
		}

		if (overlap < smallestOverlap) {
			smallestOverlap = overlap;
			axisOfSmallestOverlap = normal;
		}
	}

	gap.gapFound = false;
	gap.overlap = smallestOverlap;
	gap.axis = axisOfSmallestOverlap;

	return gap;
}

void Game::handleCollision(Entity& entity, const EntityVec& entities) {
	for (auto& obj : entities) {
		Gap gapA = findGap(*entity.shape, *obj->shape);
		if (gapA.gapFound) {
			continue;
		}

		Gap gapB = findGap(*obj->shape, *entity.shape);
		if (gapB.gapFound) {
			continue;
		}

		Gap& smallestGap = gapA.overlap < gapB.overlap ? gapA : gapB;

		auto& velocity = entity.body->velocity;
		if (velocity.dot(smallestGap.axis) > 0) {
			smallestGap.axis = -smallestGap.axis;
		}
		entity.shape->move(smallestGap.overlap * smallestGap.axis);

		entity.onCollision(smallestGap.axis);
		obj->onCollision(smallestGap.axis);
	}
}