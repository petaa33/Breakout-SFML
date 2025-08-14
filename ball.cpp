#pragma once
#include "ball.h"

Ball::Ball(sf::Vector2f startPos) {
	isAlive = true;
	int radius = 24;

	texture = sf::Texture("ball.png");
	sprite = std::make_shared<sf::Sprite>(texture);
	sprite->setOrigin(sf::Vector2f(radius / 2, radius / 2));
	sprite->setPosition(startPos);

	bool isEnabled = true;
	int speed = 25;
	bool hasGravity = true;

	body = std::make_shared<Rigidbody>(isEnabled, speed, hasGravity);
	body->velocity = sf::Vector2f(0, -1);
}

void Ball::bounce() {

}

void Ball::onCollision() {

}

