#include "game.h"
#include "iostream"

Game::Game() {
	windowWidth = 1280;
	windowHeight = 720;
	window = sf::RenderWindow(sf::VideoMode({ windowWidth, windowHeight }), "Breakout game");

	sf::Vector2f playerStartPos(windowWidth/2, windowHeight - 100);
	sf::Vector2f ballStartPos(windowWidth/2, windowHeight/2);

	paddle = std::make_shared<Paddle>(playerStartPos);
	ball = std::make_shared<Ball>(ballStartPos);

	entityManager.add(paddle);
	entityManager.add(ball);

	clock = sf::Clock();
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
	window.draw(*paddle->shape);
	window.draw(*ball->shape);

	for (auto& block : entityManager.getBlocks()) {
		window.draw(*block->shape);
	}

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
	if (entityManager.getBlocks().empty()) {
		entityManager.createBlocks(windowWidth, windowHeight);
	}
}

void Game::handleCollisionBroadPhase() {
	// Collision between paddle and ball
	if (paddle->shape->getGlobalBounds().findIntersection(ball->shape->getGlobalBounds())) {
		ball->onCollisionPlayer(paddle->shape->getPosition());
	}

	// Collison between rigidbodies and blocks
	for (auto entity : entityManager.getRigidbodyEntities()) {
		handleBounds(*entity);

		for (auto block : entityManager.getBlocks()) {
			auto [gapFoundA, overlapA, axisA] = findGap(*entity->shape, *block->shape);

			if (gapFoundA) {
				continue;
			}

			auto [gapFoundB, overlapB, axisB] = findGap(*block->shape, *entity->shape);

			if (gapFoundB) {
				continue;
			}

			if (overlapA < overlapB) {
				entity->shape->move(overlapA * axisA);
				entity->onCollision(axisA);
			}
			else {
				entity->shape->move(overlapB * axisB);
				entity->onCollision(axisB);
			}
		}
	}
}

std::tuple<bool, float, sf::Vector2f> Game::findGap(const sf::Shape& a, const sf::Shape& b) {
	float smallestOverlap = 1;
	sf::Vector2f axisOfSmallestOverlap;

	sf::Vector2f pointA = a.getPoint(0) - a.getOrigin() + a.getPosition();
	sf::Vector2f pointB = b.getPoint(0) - b.getOrigin() + b.getPosition();

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
			return {true, 0, sf::Vector2f(0,0)};
		}

		if (overlap < smallestOverlap) {
			smallestOverlap = overlap;
			axisOfSmallestOverlap = normal;
		}
	}

	return { false, smallestOverlap, axisOfSmallestOverlap };
}

void Game::handleBounds(Entity& entity) {
	if (entity.shape->getGlobalBounds().size.x / 2 + entity.shape->getPosition().x >= windowWidth) {
		entity.shape->setPosition(sf::Vector2f(windowWidth - entity.shape->getGlobalBounds().size.x / 2, entity.shape->getPosition().y));
		entity.onCollision(sf::Vector2f(-1, 0));
	}

	if (entity.shape->getPosition().x - entity.shape->getGlobalBounds().size.x / 2 <= 0) {
		entity.shape->setPosition(sf::Vector2f(entity.shape->getGlobalBounds().size.x / 2, entity.shape->getPosition().y));
		entity.onCollision(sf::Vector2f(1, 0));
	}
}