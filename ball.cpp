#pragma once
#include "ball.h"
#include "iostream"

Ball::Ball(sf::Vector2f startPos) {
	isAlive = true;
	int radius = 24;

	texture = sf::Texture("ball.png");
	shape = std::make_shared<sf::CircleShape>(radius, 12);
	shape->setOrigin(sf::Vector2f(radius / 2, radius / 2));
	shape->setPosition(startPos);

	bool isEnabled = true;
	int speed = 100;
	bool hasGravity = true;

	body = std::make_shared<Rigidbody>(isEnabled, speed, hasGravity);
	body->velocity = sf::Vector2f(0, -1);
}

void Ball::bounce() {
}

void Ball::onCollision(sf::Vector2f normal) {
	std::cout << normal.x << " " << normal.y << "\n";
	sf::Vector2f reflected = body->velocity - 2 * (body->velocity.dot(normal)) * normal;
	body->velocity = reflected.normalized();
}

void Ball::onCollisionPlayer(const sf::Vector2f& position) {
	sf::Vector2f dir = shape->getPosition() - position;
	body->velocity = dir.normalized();
}

