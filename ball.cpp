#pragma once
#include "ball.h"

Ball::Ball(sf::Vector2f startPos) {
	int radius = 24;

	texture = sf::Texture("ball.png");
	sprite = std::make_shared<sf::Sprite>(texture);
	sprite->setOrigin(sf::Vector2f(radius / 2, radius / 2));
	sprite->setPosition(startPos);

	int speed = 25;
	bool hasGravity = true;

	body = std::make_shared<Rigidbody>(speed, hasGravity);
}

void Ball::bounce() {

}

void Ball::onCollision() {

}

