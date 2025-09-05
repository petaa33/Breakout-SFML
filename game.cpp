#include "game.h"
#include "iostream"
#include "score.h"
#include "iostream"

float Game::deltaTime = 0;

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
	handleGamePhase();
	handleDeltaTime();
	systemInput();
	removeOutOfBounds();
	systemModifiers();
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

	if (health.getSprites().size() <= 0) {
		resetGame();
		return;
	}

	if ((ball->shape->getPosition().y + ball->shape->getOrigin().y) >= windowHeight) {
		health.remove();
		ball->shape->setPosition(sf::Vector2f(windowWidth / 2, windowHeight / 2));
	}

	if (entityManager.getBlocks().empty()) {
		entityManager.createBlocks(windowWidth, windowHeight);
	}
}

void Game::handleCollisionBroadPhase() {
	for (auto entity : entityManager.getRigidbodyEntities()) {
		handleCollision(*entity, entityManager.getBlocks());
		handleCollision(*entity, entityManager.getBounds());
		handleCollision(*entity, entityManager.getRigidbodyEntities());
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
		if (entity.name == obj->name) {
			continue;
		}
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

		// This is a special case where previous velocity - [velocity.dot(smallestGap.axis) > 0] can't determine axis from which collision happened since
		// collision can happen between paddle and barrier with paddle having velocity<0,0>
		// because paddle can have modifier which increases it's size and causes collision without actually moving
		if (entity.tag == utils::EntityTag::Paddle && obj->tag == utils::EntityTag::Barrier && velocity == sf::Vector2f(0,0)) {
			smallestGap.axis = static_cast<Paddle&>(entity).normalXTowardPaddle(*obj->shape);
		}

		// If collision between 2 rigidbodies -> move the smaller one
		if (entity.body && obj->body) {
			float entityVolume = entity.shape->getGlobalBounds().size.x * entity.shape->getGlobalBounds().size.y;
			float objVolume = obj->shape->getGlobalBounds().size.x * obj->shape->getGlobalBounds().size.y;

			Entity* smallerEntity = entityVolume < objVolume ? &entity : &*obj;
			smallerEntity->shape->move(smallestGap.overlap * smallestGap.axis);
		} else {
			entity.shape->move(smallestGap.overlap * smallestGap.axis);
		}

		entity.onCollision(smallestGap.axis, *obj);
		obj->onCollision(smallestGap.axis, entity);
	}
}

void Game::resetGame() {
	Score::getInstance().reset();
	health.add(3, windowWidth);
	ball->shape->setPosition(sf::Vector2f(windowWidth / 2, windowHeight / 2));
}

void Game::removeOutOfBounds() {
	for (auto& entity : entityManager.getRigidbodyEntities()) {
		if (entity->shape->getPosition().y + entity->shape->getOrigin().y > windowHeight && entity->tag != utils::EntityTag::Ball) {
			entity->isAlive = false;
		}
	}
}

void Game::systemModifiers() {
	// Only rigidbodies can have modifiers
	for (auto& entity : entityManager.getRigidbodyEntities()) {
		entity->modifiers.erase(std::remove_if(entity->modifiers.begin(), entity->modifiers.end(), 
			[&](std::unique_ptr<Modifier>& modifier) {return !modifier->isActive; }), entity->modifiers.end());

		for (auto& modifier : entity->modifiers) {
			modifier->update();
		}
	}
}