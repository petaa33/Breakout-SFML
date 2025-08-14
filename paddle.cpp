#pragma once
#include "paddle.h"
#include "components.h"

Paddle::Paddle(sf::Vector2f startPos) {
	int width = 128;
	int height = 32;

	texture = sf::Texture("paddle.png");
	sprite = std::make_shared<sf::Sprite>(texture);
	sprite->setOrigin(sf::Vector2f(width / 2, height / 2));
	sprite->setPosition(startPos);

	int speed = 25;
	bool hasGravity = false;

	body = std::make_shared<Rigidbody>(speed, hasGravity);
}

void Paddle::onCollision() {

}

void Paddle::handleInput() {

}

